#include "BaseMove.h"
#include "Logger/StaticLogger.h"

namespace Pkmn {
	std::map<std::string, eMoveCategory> StringToCategory{
		{ "Status", eMoveCategory::Status },
		{ "Physical", eMoveCategory::Physical },
		{ "Special", eMoveCategory::Special },
	};

	std::map<std::string, eMoveTarget> StringToTarget{
		{ "all", eMoveTarget::All },
		{ "allAdjacent", eMoveTarget::AllAdjacent },
		{ "allAdjacentFoes", eMoveTarget::AllAdjacentFoes },
		{ "any", eMoveTarget::Any },
		{ "normal", eMoveTarget::Normal },
		{ "self", eMoveTarget::Self },
		{ "randomNormal", eMoveTarget::RandomNormal },
		{ "scripted", eMoveTarget::Scripted },
		{ "adjacentAlly", eMoveTarget::AdjacentAlly },
		{ "adjacentAllyOrSelf", eMoveTarget::AdjacentAllyOrSelf },
		{ "allies", eMoveTarget::Allies },
		{ "allySide", eMoveTarget::AllySide },
		{ "adjacentFoe", eMoveTarget::AdjacentFoe },
		{ "allyTeam", eMoveTarget::AllyTeam },
		{ "foeSide", eMoveTarget::FoeSide },
	};

	std::map<std::string, eMoveFlags> StringToFlag{
		{ "contact", eMoveFlags::Contact },
		{ "protect", eMoveFlags::Protect },
		{ "mirror", eMoveFlags::Mirror },
		{ "heal", eMoveFlags::Heal },
		{ "snatch", eMoveFlags::Snatch },
		{ "reflectable", eMoveFlags::Reflectable },
		{ "allyanim", eMoveFlags::AllyAnim },
		{ "bite", eMoveFlags::Bite },
		{ "punch", eMoveFlags::Punch },
		{ "nonsky", eMoveFlags::NonSky },
		{ "bypasssub", eMoveFlags::ByPassSub },
		{ "gravity", eMoveFlags::Gravity },
		{ "distance", eMoveFlags::Distance },
		{ "recharge", eMoveFlags::Recharge },
		{ "charge", eMoveFlags::Charge },
		{ "bullet", eMoveFlags::Bullet },
		{ "sound", eMoveFlags::Sound },
		{ "powder", eMoveFlags::Powder },
		{ "defrost", eMoveFlags::Defrost },
		{ "dance", eMoveFlags::Dance },
		{ "pulse", eMoveFlags::Pulse },
	};

	std::map<std::string, std::shared_ptr<MoveBase>> 
		MoveLoader::LoadMoves(const std::string& fileName) 
	{
		std::map<std::string, std::shared_ptr<MoveBase>> moves;
		JsonFile file(fileName);

		JsonObject* moveObject = file.getHead()->objectValue;

		for (auto move : moveObject->getKeys()) {
			std::shared_ptr<MoveBase> moveData =
				MoveFactory::CreateMoveData(move);

			moves[move.first] = moveData;
		}

		// TODO: this is still not working properly. Each move needs to have multiple
		// primary statuses. One for each possible type (only if it includes it in the structure).
		auto v = moves["swagger"];
		v = moves["bonerush"];
		v = moves["bounce"];
		return moves;
	}

	std::shared_ptr<MoveBase> MoveFactory::CreateMoveData(std::pair<const std::string, 
		JsonValue*>& data) 
	{
		// Handle all special moves.
		if (data.first == "dragondarts") {
			return std::make_shared<SmartTargetMove>(data.second->objectValue);
		}

		return std::make_shared<MoveBase>(data.second->objectValue);
	}

	void MoveBase::LoadBaseData(JsonObject* moveData) {
		mMoveNumber = moveData->lookupNode("num")->numberValue;
		mName = moveData->lookupNode("name")->stringValue;
		mPP = moveData->lookupNode("pp")->numberValue;
		mPriority = moveData->lookupNode("priority")->numberValue;
		mBasePower = moveData->lookupNode("basePower")->numberValue;
		mType = moveData->lookupNode("type")->stringValue;

		// Load move category.
		std::string moveCategory = moveData->lookupNode("category")->stringValue;
		if (StringToCategory.find(moveCategory) != StringToCategory.end()) {
			mCategory = StringToCategory[moveCategory];
		}
		else {
			StaticLogger::instance.warning("Invalid category detected: {s} in move {s}",
				moveCategory.c_str(), mName.c_str());
		}

		// Load move target.
		std::string moveTarget = moveData->lookupNode("target")->stringValue;
		if (StringToTarget.find(moveTarget) != StringToTarget.end()) {
			mTarget = StringToTarget[moveTarget];
		}
		else {
			StaticLogger::instance.warning("Invalid target detected: {s} in move {s}",
				moveTarget.c_str(), mName.c_str());
		}

		// Load move accuracy.
		JsonValue* accuracy = moveData->lookupNode("accuracy");
		if (accuracy->type == JsonValueType::Boolean) {
			mBypassAccuracyCheck = true;
			mAccuracy = 100;
		}
		else {
			mAccuracy = accuracy->numberValue;
		}

		// Load flags.
		JsonObject* flags = moveData->lookupNode("flags")->objectValue;

		for (auto flag : flags->getKeys()) {
			if (StringToFlag.find(flag.first) != StringToFlag.end()) {
				mFlags |= StringToFlag[flag.first];
			}
			else {
				StaticLogger::instance.warning("Invalid flag detected: {s} on move {s}",
					flag.first.c_str(), mName.c_str());
			}
		}

		// Load in optional generic move data.
		if (moveData->nodeExists("drain")) {
			JsonArray* drainData = moveData->lookupNode("drain")->arrayValue;
			mDrainFactor = (double)drainData->get(0)->numberValue / 
				drainData->get(1)->numberValue;
		}

		if (moveData->nodeExists("heal")) {
			JsonArray* healData = moveData->lookupNode("heal")->arrayValue;
			mHealingFactor = (double)healData->get(0)->numberValue / 
				healData->get(1)->numberValue;
		}

		if (moveData->nodeExists("struggleRecoil")) {
			mRecoilFactor = .5;
		}
		else if (moveData->nodeExists("recoil")) {
			JsonArray* recoilData = moveData->lookupNode("recoil")->arrayValue;
			mRecoilFactor = (double)recoilData->get(0)->numberValue / 
				recoilData->get(1)->numberValue;
		}

		// Load multihit data.
		if (moveData->nodeExists("multihit")) {
			JsonValue* multihit = moveData->lookupNode("multihit");

			if (multihit->type == JsonValueType::Array) {
				mMinHits = multihit->arrayValue->get(0)->numberValue;
				mMaxHits = multihit->arrayValue->get(1)->numberValue;
			}
			else {
				mMinHits = multihit->numberValue;
				mMaxHits = mMinHits;
			}
		}

		if (moveData->nodeExists("ignoreImmunity")) {
			if (moveData->lookupNode("ignoreImmunity")->type ==
				JsonValueType::Boolean) 
			{
				mIgnoreImmunity = moveData->lookupNode("ignoreImmunity")->booleanValue;
			}
		}

		if (moveData->nodeExists("willCrit")) {
			mWillCrit = true;
		}
	}

	void MoveBase::LoadEffectData(JsonObject* effectData) {
		// Load primary effects.
		mPrimaryEffect = MoveEffectFactory::LoadMoveEffect(effectData);

		// Load secondary effects.
		if (effectData->nodeExists("secondary")) {
			if (!effectData->lookupNode("secondary")->isNull) {
				mSecondaryEffects.push_back(MoveEffectFactory::LoadMoveEffect(
						effectData->lookupNode("secondary")->objectValue));
			}
		}
		else if (effectData->nodeExists("secondaries")) {
			JsonArray* secondaryEffects = effectData->lookupNode("secondaries")->arrayValue;

			for (int i = 0; i < secondaryEffects->size(); i++) {
				mSecondaryEffects.push_back(MoveEffectFactory::
					LoadMoveEffect(secondaryEffects->get(i)->objectValue));
			}
		}
	}

	std::shared_ptr<MoveEffectBase> MoveEffectFactory::
		LoadMoveEffect(JsonObject* effectRoot) 
	{
		int chance = 100;
		if (effectRoot->nodeExists("chance")) {
			chance = effectRoot->lookupNode("chance")->numberValue;
		}

		bool targetSelf = false;
		if (effectRoot->nodeExists("self")) {
			targetSelf = true;
			effectRoot = effectRoot->lookupNode("self")->objectValue;
		}

		// Figure out what type of effect we are dealing with, and add it.
		if (effectRoot->nodeExists("status")) {
			std::string status = effectRoot->lookupNode("status")->stringValue;
			return std::make_shared<StatusMoveEffect>(targetSelf, chance, status);
		}
		else if (effectRoot->nodeExists("boosts")) {
			JsonObject* boostObject = effectRoot->lookupNode("boosts")->objectValue;

			int atkBoost, spaBoost, defBoost, spdBoost, speBoost;
			atkBoost = spaBoost = defBoost = spdBoost = speBoost = 0;

			if (boostObject->nodeExists("atk")) {
				atkBoost = boostObject->lookupNode("atk")->numberValue;
			}

			if (boostObject->nodeExists("spa")) {
				spaBoost = boostObject->lookupNode("spa")->numberValue;
			}

			if (boostObject->nodeExists("def")) {
				defBoost = boostObject->lookupNode("def")->numberValue;
			}

			if (boostObject->nodeExists("spd")) {
				spdBoost = boostObject->lookupNode("spd")->numberValue;
			}

			if (boostObject->nodeExists("spe")) {
				speBoost = boostObject->lookupNode("spe")->numberValue;
			}

			return std::make_shared<BoostMoveEffect>(targetSelf, chance,
				atkBoost, spaBoost, defBoost, spdBoost, speBoost);
		}
		else if (effectRoot->nodeExists("volatileStatus")) {
			std::string status = effectRoot->lookupNode("volatileStatus")->stringValue;
			return std::make_shared<VolatileStatusEffect>(targetSelf, chance, status);
		}
		else if (effectRoot->nodeExists("sideCondition")) {
			std::string sideCondition = effectRoot->lookupNode("sideCondition")->stringValue;
			return std::make_shared<SideConditionEffect>(targetSelf, chance, sideCondition);
		}

		// Otherwise, we don't have an architectype for this effect.
		return nullptr;
	}
}