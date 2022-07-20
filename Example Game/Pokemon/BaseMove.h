#pragma once

#include "Serializers/JSON Serializer/JsonFile.h"
#include "defs.h"

#include <string>
#include <map>
#include <vector>

namespace Pkmn {
	enum eMoveCategory {
		Physical,
		Special,
		Status
	};

	enum eMoveTarget {
		// Can target an adjacent mon.
		RandomNormal,
		Normal,
		Scripted,
		// Targets an adjacent mon which is on your team.
		AdjacentAlly,
		AdjacentAllyOrSelf,
		// All allies.
		Allies,
		AllySide,
		AllyTeam,
		// Only the user.
		Self,
		// All adjacent mons including allies.
		AllAdjacent,
		AdjacentFoe,
		// All adjacent enemies.
		AllAdjacentFoes,
		FoeSide,
		// Anything but yourself.
		Any,
		// Targets the battlefield.
		All
	};

	enum eMoveFlags {
		// Attacker physically contacts the target.
		Contact = 1,
		// The move IS affected by protect.
		Protect = Contact * 2,
		// The move IS affected by mirrormove.
		Mirror = Protect * 2,
		// The move heals the user.
		Heal = Mirror * 2,
		// The move can be stolen with snatch.
		Snatch = Heal * 2,
		// Move does not affect mons with the bulletproof abiltiy.
		Bullet = Snatch * 2,
		// Affected by magic coat (move) and magic bounce (ability)
		Reflectable = Bullet * 2,
		// Going to assume this shit does nothing. I have no idea.
		AllyAnim = Reflectable * 2,
		// Bypass target pokemon substitute.
		ByPassSub = AllyAnim * 2,
		// Is a biting move.
		Bite = ByPassSub * 2,
		// Is a punching move.
		Punch = Bite * 2,
		// No clue.
		NonSky = Punch * 2,
		// The move cannot be used under the effect of gravity.
		Gravity = NonSky * 2,
		// Can hit non adjacent mons in triple battles (probably no need to worry about this).
		Distance = Gravity * 2,
		// Causes the user to take a turn to recharge after using.
		Recharge = Distance * 2,
		// The move takes effect after the second turn and can avoid the delay using power herb.
		Charge = Recharge * 2,
		// The move makes sound.
		Sound = Charge * 2,
		// The move is a powder move.
		Powder = Sound * 2,
		// The move will always defrost target.
		Defrost = Powder * 2,
		// The move is a dancing move.
		Dance = Defrost * 2,
		// The move is a pulse move.
		Pulse = Dance * 2,
	};

	/// <summary>
	/// Temporary class to setup move interface.
	/// </summary>
	class Mon {

	};

	/// <summary>
	/// Handles possible effects of moves.
	/// Handles secondary effects of moves such as boosts and status.
	/// Handles the target as well.
	/// </summary>
	class MoveEffect {
	public:
		MoveEffect() {

		}

		virtual ~MoveEffect() {

		}

		void Effect(Mon& target, const Mon& source, int rng) {
			if (rng <= mChance) {
				OnHit(target, source);
			}
		}

		virtual void OnHit(Mon& target, const Mon& source) = 0;

	protected:
		// Can be either Self or Normal. Normal means it affects the target 
		// Of the move, and Self means it affects the user.
		eMoveTarget mTarget = eMoveTarget::Normal;
		int mChance = 0;
	};

	class BoostMoveEffect : public MoveEffect {
	public:
		void OnHit(Mon& target, const Mon& source) {
			// foreach boost effect, apply the modifier.
		}
	protected:
		signed char mBoostEffects[eStats::None] = { 0 };
	};

	class StatusMoveEffect : public MoveEffect {
	public:
		void OnHit(Mon& target, const Mon& source) {
			// target.trySetStatus(status, source);
		}
	private:
		// For now, let's just store a string because I don't have an enumeration setup for status yet.
		std::string status;
	};

	/// <summary>
	/// Abstract class to store information about moves.
	/// </summary>
	class MoveBase {
	public:
		MoveBase(JsonObject* moveData);

		~MoveBase() {
		}

		MoveBase(const MoveBase& other) 
		{
		}

		MoveBase& operator=(const MoveBase& other) {
		}

		virtual bool OnTry(const Mon& source) {
			return false;
		}

		virtual void OnHit(Mon& target, const Mon& source) {

		}

	protected:
		int mMoveNumber = 0;

		eMoveCategory mCategory = eMoveCategory::Status;
		eMoveTarget mTarget = eMoveTarget::Normal;

		bool mBypassAccuracyCheck = false;
		char mAccuracy = 0;
		std::string mName;
		std::string mType;
		int mPP = 0;
		char mPriority = 0;
		int mFlags = 0;
		int mCritRatio = 0;
		int mBasePower = 0;

		// Option values which should still be handled generically.
		double mDrainFactor = 0;
		double mHealingFactor = 0;
		double mRecoilFactor = 0;
		int mMinHits = 1;
		int mMaxHits = 1;

		std::shared_ptr<MoveEffect> mPrimaryEffect;
		std::vector<std::shared_ptr<MoveEffect>> mSecondaryEffects;

	private:
	};

	class MoveLoader {
	public:
		static std::map<std::string, std::shared_ptr<MoveBase>>
			LoadMoves(const std::string& fileName);
	};

	class MoveFactory {
	public:
		static std::shared_ptr<MoveBase> CreateMoveData(JsonObject* move);
	};
}