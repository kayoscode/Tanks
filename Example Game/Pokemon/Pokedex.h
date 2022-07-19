#pragma once
#include "Serializers/JSON Serializer/JsonFile.h"
#include "defs.h"
#include "Evos.h"

#include <string>

#include <map>

namespace Pkmn {
	class PokemonData {
	public:
		PokemonData() 
			:BaseStats(),
			DexNum(0),
			FemaleRatio(0),
			MaleRatio(0),
			Height(0),
			Weight(0),
			EvoType(nullptr),
			Name()
		{
		}

		PokemonData(const PokemonData& other)
			:DexNum(other.DexNum),
			BaseStats(),
			MaleRatio(other.MaleRatio),
			FemaleRatio(other.FemaleRatio),
			GenderLess(other.GenderLess),
			MaleOnly(other.MaleOnly),
			FemaleOnly(other.FemaleOnly),
			BaseSpecies(other.BaseSpecies),
			Types(other.Types),
			Evos(other.Evos),
			Prevo(other.Prevo),
			EvoType(nullptr),
			EvoCondition(other.EvoCondition),
			Abilities(other.Abilities),
			HiddenAbility(other.HiddenAbility),
			EggGroups(other.EggGroups),
			RequiredItems(other.RequiredItems),
			OtherForms(other.OtherForms),
			ChangesFrom(other.ChangesFrom),
			Color(other.Color),
			Height(other.Height),
			Weight(other.Weight),
			Name(other.Name),
			LevelUpMoveset(other.LevelUpMoveset),
			TMMoveset(other.TMMoveset),
			EggMoves(other.EggMoves)
		{
			// Copy stats, clone evo type.
			for (int i = 0; i < eStats::None; i++) {
				BaseStats[i] = other.BaseStats[i];
			}

			if (other.EvoType) {
				EvoType = other.EvoType->Clone();
			}
			else {
				EvoType = nullptr;
			}
		}

		PokemonData& operator=(const PokemonData& other) {
			// Copy stats, clone evo type.
			for (int i = 0; i < eStats::None; i++) {
				BaseStats[i] = other.BaseStats[i];
			}

			if (other.EvoType) {
				EvoType = other.EvoType->Clone();
			}
			else {
				EvoType = nullptr;
			}

			DexNum = other.DexNum;
			MaleRatio = other.MaleRatio;
			FemaleRatio = other.FemaleRatio;
			GenderLess = other.GenderLess;
			MaleOnly = other.MaleOnly;
			FemaleOnly = other.FemaleOnly;
			BaseSpecies = other.BaseSpecies;
			Types = other.Types;
			Evos = other.Evos;
			Prevo = other.Prevo;
			EvoCondition = other.EvoCondition;
			Abilities = other.Abilities;
			HiddenAbility = other.HiddenAbility;
			EggGroups = other.EggGroups;
			RequiredItems = other.RequiredItems;
			OtherForms = other.OtherForms;
			ChangesFrom = other.ChangesFrom;
			Color = other.Color;
			Height = other.Height;
			Weight = other.Weight;
			Name = other.Name;

			LevelUpMoveset = other.LevelUpMoveset;
			TMMoveset = other.TMMoveset;
			EggMoves = other.EggMoves;

			return *this;
		}

		~PokemonData()
		{
			delete EvoType;
		}

		/// <summary>
		/// Data pertaining to movesets.
		/// </summary>
		std::map<int, std::vector<std::string>> LevelUpMoveset;
		std::vector<std::string> TMMoveset;
		std::vector<std::string> EggMoves;

		/// <summary>
		/// Provides an integer for each base stat.
		/// </summary>
		int DexNum;
		int BaseStats[eStats::None];

		// 50:50 if genderRatio is not provided.
		double MaleRatio;
		double FemaleRatio;
		bool GenderLess = false;
		bool MaleOnly = false;
		bool FemaleOnly = false;

		// Unused for a while (for now).
		std::string BaseSpecies;

		std::vector<std::string> Types;

		std::vector<std::string> Evos;
		std::string Prevo;

		// The type of evolution which the pkmn employs.
		EvoTypeBase* EvoType;

		// Condition example: at night.
		std::string EvoCondition;

		std::vector<std::string> Abilities;
		std::string HiddenAbility;

		std::vector<std::string> EggGroups;

		// Required item example: Abomanoite
		// Taken from the property <requiredItem: string> : <requiredItems: [strArray]>
		// Changes the pokemon form
		std::vector<std::string> RequiredItems;
		// The list of other potential forms for the mon.
		std::vector<std::string> OtherForms;
		// Indicates the base form
		std::string ChangesFrom;

		std::string Color;
		std::string Name;

		double Height;
		double Weight;
	};

	/// <summary>
	/// From a json file, loads the entire pokedex into memory.
	/// </summary>
	class PokedexLoader {
	public:
		static std::map<std::string, PokemonData, CompareCaseIns> LoadPokedex(const std::string& fileName);
	};
}
