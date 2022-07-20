#include "BaseMove.h"
#include "Logger/StaticLogger.h"

namespace Pkmn {
	std::map<std::string, eMoveCategory> StringToCategory{
		{ "Status", eMoveCategory::Status },
		{ "Physical", eMoveCategory::Physical },
		{ "Special", eMoveCategory::Status },
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
				MoveFactory::CreateMoveData(move.second->objectValue);

			moves[move.first] = moveData;
		}

		return moves;
	}

	std::shared_ptr<MoveBase> MoveFactory::CreateMoveData(JsonObject* data) {
		return std::make_shared<MoveBase>(data);
	}

	MoveBase::MoveBase(JsonObject* moveData) 
	{
		mMoveNumber = moveData->lookupNode("num")->numberValue;
		mName = moveData->lookupNode("name")->stringValue;
		mPP = moveData->lookupNode("pp")->numberValue;
		mPriority = moveData->lookupNode("priority")->numberValue;
		mBasePower = moveData->lookupNode("basePower")->numberValue;

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

		// Load primary and secondary effects.
	}
}