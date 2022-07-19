#include "Pokedex.h"
#include "Logger/StaticLogger.h"

constexpr int Generation = 8;

namespace Pkmn {
	static void LoadTypes(JsonObject* pkmnJson, PokemonData& data) {
		JsonArray* types = pkmnJson->lookupNode("types")->arrayValue;

		for (int i = 0; i < types->size(); i++) {
			data.Types.push_back(types->get(i)->stringValue);
		}
	}

	static void LoadGenderData(JsonObject* pkmnJson, PokemonData& data) {
		if (pkmnJson->nodeExists("genderRatio")) {
			JsonObject* genderRatioData = pkmnJson->lookupNode("genderRatio")->objectValue;

			data.MaleRatio = genderRatioData->lookupNode("M")->floatValue;
			data.FemaleRatio = genderRatioData->lookupNode("F")->floatValue;
		}
		else {
			data.MaleRatio = .5;
			data.FemaleRatio = .5;
		}

		if (pkmnJson->nodeExists("gender")) {
			std::string gender = pkmnJson->lookupNode("gender")->stringValue;

			if (gender == "N") {
				data.GenderLess = true;
			}
			else if (gender == "M") {
				data.MaleOnly = true;
			}
			else if (gender == "F") {
				data.FemaleOnly = true;
			}
		}
	}

	static void LoadBaseStats(JsonObject* pkmnJson, PokemonData& data) {
		JsonObject* baseStats = pkmnJson->lookupNode("baseStats")->objectValue;

		data.BaseStats[(int)eStats::HP] = baseStats->lookupNode("hp")->numberValue;
		data.BaseStats[(int)eStats::Attack] = baseStats->lookupNode("atk")->numberValue;
		data.BaseStats[(int)eStats::Defense] = baseStats->lookupNode("def")->numberValue;
		data.BaseStats[(int)eStats::SpecialAttack] = baseStats->lookupNode("spa")->numberValue;
		data.BaseStats[(int)eStats::SpecialDefense] = baseStats->lookupNode("spd")->numberValue;
		data.BaseStats[(int)eStats::Speed] = baseStats->lookupNode("spe")->numberValue;

		data.Height = pkmnJson->lookupNode("heightm")->floatValue;
		data.Weight = pkmnJson->lookupNode("weightkg")->floatValue;
		data.Color = pkmnJson->lookupNode("color")->stringValue;
	}

	static void LoadEggGroups(JsonObject* pkmnJson, PokemonData& data) {
		JsonArray* eggGroups = pkmnJson->lookupNode("eggGroups")->arrayValue;

		for (int i = 0; i < eggGroups->size(); i++) {
			data.EggGroups.push_back(eggGroups->get(i)->stringValue);
		}
	}

	static void LoadAbilities(JsonObject* pkmnJson, PokemonData& data) {
		JsonObject* abilities = pkmnJson->lookupNode("abilities")->objectValue;

		for (auto ability : abilities->getKeys()) {
			if (ability.first != "H") {
				data.Abilities.push_back(ability.second->stringValue);
			}
		}

		// Add the hidden ability if it exists.
		if (abilities->nodeExists("H")) {
			data.HiddenAbility = abilities->lookupNode("H")->stringValue;
		}
	}

	static void LoadForms(JsonObject* pkmnJson, PokemonData& data) {
		if (pkmnJson->nodeExists("baseSpecies")) {
			data.BaseSpecies = pkmnJson->lookupNode("baseSpecies")->stringValue;
		}

		if (pkmnJson->nodeExists("otherFormes")) {
			JsonArray* otherForms = pkmnJson->lookupNode("otherFormes")->arrayValue;

			for (int i = 0; i < otherForms->size(); i++) {
				data.OtherForms.push_back(otherForms->get(i)->stringValue);
			}
		}

		if (pkmnJson->nodeExists("changesFrom")) {
			data.ChangesFrom = pkmnJson->lookupNode("changesFrom")->stringValue;
		}

		if (pkmnJson->nodeExists("requiredItem")) {
			data.RequiredItems.push_back(pkmnJson->lookupNode("requiredItem")->stringValue);
		}
		else if (pkmnJson->nodeExists("requiredItems")) {
			JsonArray* requiredItems = pkmnJson->lookupNode("requiredItems")->arrayValue;

			for (int i = 0; i < requiredItems->size(); i++) {
				data.RequiredItems.push_back(requiredItems->get(i)->stringValue);
			}
		}
	}

	static void LoadEvos(JsonObject* pkmnJson, PokemonData& data) {
		// Load the pre evolution.
		if (pkmnJson->nodeExists("prevo")) {
			data.Prevo = pkmnJson->lookupNode("prevo")->stringValue;
		}

		// Load all possible future evolutions.
		if (pkmnJson->nodeExists("evos")) {
			JsonArray* evos = pkmnJson->lookupNode("evos")->arrayValue;

			for (int i = 0; i < evos->size(); i++) {
				data.Evos.push_back(evos->get(i)->stringValue);
			}
		}

		if (pkmnJson->nodeExists("evoCondition")) {
			data.EvoCondition = pkmnJson->lookupNode("evoCondition")->stringValue;
		}

		// Load the evolution type.
		data.EvoType = EvoTypeFactory::LoadEvoType(pkmnJson);
	}

	static void LoadLearnsets(JsonObject* learnsets, PokemonData& data) {
		for (auto moves : learnsets->getKeys()) {
			JsonArray* moveInfo = moves.second->arrayValue;

			for (int i = 0; i < moveInfo->size(); i++) {
				// Parse the move string into to correct data array.
				std::string move = moveInfo->get(i)->stringValue;

				// Load the first number from the string.
				size_t parseIndex = 0;
				int generation = std::stoi(move, &parseIndex, 10);

				if (generation == Generation && parseIndex < move.size()) {
					char moveType = move[parseIndex];

					switch (moveType) {
					case 'V':
						//Virtual console meaning it must be transferred from another game and is therefore not applicable.
					case 'T':
						// Tutor moves also don't have an impact on this game since I make my own move tutors.
					case 'S':
						// S means event move. For our purposes, event moves do not matter either.
						break;
					case 'M':
						// TM or HM move.
						data.TMMoveset.push_back(moves.first);
						break;
					case 'E':
						// Egg move.
						data.EggMoves.push_back(moves.first);
						break;
					case 'L':
						// Level up move.
						{
							parseIndex++;
							int level = std::stoi(move.substr(parseIndex), &parseIndex, 10);
							data.LevelUpMoveset[level].push_back(moves.first);
						}
						break;
					default: 
						StaticLogger::instance.warning("Undefined move type: {s}: '{c}' {s}",
							data.Name.c_str(), moveType, moves.first.c_str());
						break;
					}
				}
			}
		}
	}

	std::map<std::string, PokemonData, CompareCaseIns> PokedexLoader::
		LoadPokedex(const std::string& fileName) 
	{
		std::map<std::string, PokemonData, CompareCaseIns> pokedex;
		JsonFile file(fileName);

		JsonObject* pokemon = file.getHead()->objectValue->lookupNode("Pkmn")->objectValue;
		JsonObject* movesets = file.getHead()->objectValue->lookupNode("Learnsets")->objectValue;

		for (auto pkmn : pokemon->getKeys()) {
			PokemonData pkmnData;
			JsonObject* pkmnJson = pkmn.second->objectValue;

			pkmnData.DexNum = pkmnJson->lookupNode("num")->numberValue;
			pkmnData.Name = pkmnJson->lookupNode("name")->stringValue;

			LoadTypes(pkmnJson, pkmnData);
			LoadGenderData(pkmnJson, pkmnData);
			LoadBaseStats(pkmnJson, pkmnData);
			LoadEggGroups(pkmnJson, pkmnData);
			LoadAbilities(pkmnJson, pkmnData);
			LoadForms(pkmnJson, pkmnData);
			LoadEvos(pkmnJson, pkmnData);
			
			// Load the learnsets if available.
			if (movesets->nodeExists(pkmn.first)) {
				JsonObject* learnsetData = movesets->
					lookupNode(pkmn.first)->objectValue;

				if (learnsetData->nodeExists("learnset")) {
					LoadLearnsets(learnsetData->lookupNode("learnset")->objectValue, pkmnData);
				}
			}

			pokedex[pkmn.first] = pkmnData;
		}

		return pokedex;
	}
}