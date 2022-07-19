#pragma once
#include "defs.h"
#include "Serializers/JSON Serializer/JsonFile.h"

#include <string>
#include <map>

namespace Pkmn {
	/// <summary>
	/// Class holding information about a pokemon's nature.
	/// </summary>
	class Nature {
	public:
		Nature(const std::string& natureName, 
			eStats plusStat,
			eStats minusStat)
			:mNatureName(natureName),
			mPlusStat(plusStat),
			mMinusStat(minusStat)
		{
		}

		Nature(const Nature& nature)
			:mNatureName(nature.mNatureName),
			mPlusStat(nature.mPlusStat),
			mMinusStat(nature.mMinusStat)
		{
		}

		Nature() 
			:mNatureName(),
			mPlusStat(eStats::None),
			mMinusStat(eStats::None)
		{
		}

		Nature& operator=(const Nature& other) {
			this->mNatureName = other.mNatureName;
			this->mPlusStat = other.mPlusStat;
			this->mMinusStat = other.mMinusStat;

			return *this;
		}

		~Nature() {

		}

		eStats GetPlusStat() const {
			return mPlusStat;
		}

		eStats GetMinusStat() const {
			return mMinusStat;
		}

		std::string GetNatureName() const {
			return mNatureName;
		}

	private:
		eStats mPlusStat;
		eStats mMinusStat;
		std::string mNatureName;
	};

	/// <summary>
	/// Loads all natures and details about them from a file.
	/// </summary>
	class NatureLoader {
	public:
		static std::map<std::string, Nature, CompareCaseIns> LoadNatures(const std::string& fileName);

	private:
		static const std::map<std::string, eStats, CompareCaseIns> mStatNameToEnum;
	};
};
