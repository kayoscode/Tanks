#pragma once

#include "Serializers/JSON Serializer/JsonFile.h"
#include "defs.h"

#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

constexpr double DamageTakenToMultiplier(int damageTaken) {
	switch (damageTaken) {
	case 0: 
		return 1;
	case 1: 
		return 2;
	case 2: 
		return .5;
	case 3: 
		return 0;
	}

	std::cout << "Invalid dmg modifier\n";
	return -1;
}

namespace Pkmn 
{
	/// <summary>
	/// Stores information about a type.
	/// </summary>
	class Type {
	public:
		/// <summary>
		/// Standard constructor
		/// </summary>
		/// <param name="name"></param>
		/// <param name="damageMatchups"></param>
		Type(const std::string& name,
			const std::map<std::string, double, CompareCaseIns>& damageTakenMatchups)
			: TypeName(name),
			mDamageTakenMatchups(damageTakenMatchups)
		{
		}

		Type(const Type& type)
			:TypeName(type.TypeName),
			mDamageTakenMatchups(mDamageTakenMatchups)
		{
		}

		Type() 
			:TypeName(""),
			mDamageTakenMatchups()
		{
		}

		Type& operator=(const Type& other) {
			this->TypeName = other.TypeName;
			this->mDamageTakenMatchups = other.mDamageTakenMatchups;

			return *this;
		}

		std::string GetTypeName() const {
			return TypeName;
		}

		/// <summary>
		/// Returns the total damage multiplier of the type.
		/// </summary>
		/// <param name="attackingType"></param>
		/// <returns></returns>
		double GetDamageTaken(const Type& attackingType) const {
			return mDamageTakenMatchups.at(attackingType.GetTypeName());
		}

		/// <summary>
		/// Special attributes are things such as abilities which activate based
		/// on the specific type. For example, ghost types can always escape battle.
		/// Also includes the status ailments which cannot affect the type. EX: 
		/// fire cannot be burned.
		/// </summary>
		/// <param name="attributeName"></param>
		/// <returns></returns>
		bool AffectedByAilment(const std::string& statusName) const {
			if (mDamageTakenMatchups.find(statusName) != mDamageTakenMatchups.end()) {
				return mDamageTakenMatchups.at(statusName) == 0.0;
			}

			return true;
		}

		~Type() {

		}

	private:
		std::string TypeName;
		std::map<std::string, double, CompareCaseIns> mDamageTakenMatchups;
	};

	/// <summary>
	/// Loads a dictionary of each type as well as their type matchups
	/// from the given file.
	/// </summary>
	class TypeLoader {
	public:
		/// <summary>
		/// Loads the type matchups.
		/// </summary>
		/// <param name="typeMatchupFile"></param>
		/// <returns></returns>
		static std::map<std::string, Type, CompareCaseIns> LoadTypes(const std::string& typeMatchupFile) {
			std::map<std::string, Type, CompareCaseIns> types;

			JsonFile file(typeMatchupFile);
			JsonObject* allTypes = file.getHead()->objectValue->
				lookupNode("Typechart")->objectValue;

			// Load each type.
			for (auto type : allTypes->getKeys()) {
				JsonObject* typeInfo = type.second->objectValue->
					lookupNode("damageTaken")->objectValue;

				std::map<std::string, double, CompareCaseIns> damageTaken;

				for (auto matchup : typeInfo->getKeys()) {
					int effectiveness = (int)matchup.second->numberValue;
					double multiplier = DamageTakenToMultiplier(effectiveness);

					damageTaken[matchup.first] = multiplier;
				}

				Type newType(type.first, damageTaken);
				types[type.first] = newType;
			}

			return types;
		}
	};

}
