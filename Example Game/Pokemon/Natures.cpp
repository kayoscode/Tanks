#include "Natures.h"

namespace Pkmn {
	const std::map<std::string, eStats, CompareCaseIns> NatureLoader::mStatNameToEnum{
		{ "atk", eStats::Attack },
		{ "spa", eStats::SpecialAttack },
		{ "def", eStats::Defense },
		{ "spd", eStats::SpecialDefense },
		{ "spe", eStats::Speed },
	};

	std::map<std::string, Nature, CompareCaseIns> NatureLoader::LoadNatures(const std::string& fileName) {
		JsonFile file(fileName);
		std::map<std::string, Nature, CompareCaseIns> allNatures;

		JsonObject* natures = file.getHead()->objectValue;

		for (auto nature : natures->getKeys()) {
			JsonObject* natureDetails = nature.second->objectValue;

			std::string natureName = natureDetails->lookupNode("name")->stringValue;

			eStats plusStat, minusStat;
			plusStat = minusStat = eStats::None;

			if (natureDetails->nodeExists("plus")) {
				plusStat = mStatNameToEnum.at(natureDetails->lookupNode("plus")->stringValue);
			}

			if (natureDetails->nodeExists("minus")) {
				minusStat = mStatNameToEnum.at(natureDetails->lookupNode("minus")->stringValue);
			}

			Nature newNature(natureName, plusStat, minusStat);

			allNatures[nature.first] = newNature;
		}

		return allNatures;
	}
}