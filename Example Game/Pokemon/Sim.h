#pragma once
#include "Types.h"
#include "Natures.h"
#include "Pokedex.h"
#include "BaseMove.h"

#include <time.h>
#include <map>
#include <random>

constexpr int CritOdds = 16;

namespace Pkmn {
	class BattleSimBase {
	public:
		BattleSimBase() {
			std::random_device dev;
			mRNG = std::mt19937(dev());
			mCritDistribution = std::uniform_int_distribution<std::mt19937::result_type>(1, CritOdds);

			LoadResources();
		}

		virtual ~BattleSimBase() {

		}

	protected:
		/// <summary>
		/// Loads json files for pokemon, types, and natures.
		/// </summary>
		void LoadResources() {
			mTypes = TypeLoader::LoadTypes("./res/data/TypeChart.json");
			mNatures = NatureLoader::LoadNatures("./res/data/Natures.json");
			mPokemonData = PokedexLoader::LoadPokedex("./res/data/Pokedex.json");
			mMoveData = MoveLoader::LoadMoves("./res/data/Moves.json");
		}

		/// <summary>
		/// Sets up the simulator with a set seed.
		/// </summary>
		inline void SeedSimulator(int seed) {
			mRNG.seed(seed);
		}

		/// <summary>
		/// Generates a random number within the set distribution.
		/// </summary>
		/// <returns></returns>
		inline int GenRandom() {
			return mCritDistribution(mRNG);
		}

		/// <summary>
		/// Deterines whether the move is a critical hit or not.
		/// </summary>
		/// <returns></returns>
		inline bool IsCrit() {
			return mCritDistribution(mRNG) == 1;
		}

	private:
		std::mt19937 mRNG;
		std::uniform_int_distribution<std::mt19937::result_type> mCritDistribution;
		std::map<std::string, Type, CompareCaseIns> mTypes;
		std::map<std::string, Nature, CompareCaseIns> mNatures;
		std::map<std::string, PokemonData, CompareCaseIns> mPokemonData;
		std::map<std::string, std::shared_ptr<MoveBase>> mMoveData;
	};

	class BattleSimSingleBattle : public BattleSimBase {

	};
}