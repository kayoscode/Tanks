#pragma once
#include <string>
#include <iostream>

#include "Serializers/JSON Serializer/JsonFile.h"
#include "Logger/StaticLogger.h"

namespace Pkmn {
	class EvoTypeBase {
	public:
		EvoTypeBase() {

		}

		EvoTypeBase(const EvoTypeBase& other) {

		}

		~EvoTypeBase() {

		}

		virtual EvoTypeBase* Clone() {
			return new EvoTypeBase(*this);
		}

		// virtual bool MeetsCondition(const Pokemon& mon);
	protected:
	private:
	};

	/// <summary>
	/// Handles level up evolutions.
	/// </summary>
	class EvoTypeLevelUp : public EvoTypeBase {
	public:
		EvoTypeLevelUp(int evoLevel) : mLevel(evoLevel) {

		}

		EvoTypeLevelUp(const EvoTypeLevelUp& other) 
			:mLevel(other.mLevel)
		{
		}

		virtual ~EvoTypeLevelUp() {

		}

		static std::string GetConditionProperty() {
			return "evoLevel";
		}

		virtual EvoTypeLevelUp* Clone() {
			return new EvoTypeLevelUp(*this);
		}

	private:
		int mLevel;
	};

	/// <summary>
	/// Handles level ups with use-items.
	/// </summary>
	class EvoTypeUseItem : public EvoTypeBase {
	public: 
		EvoTypeUseItem(const std::string& item)
			:mUseItem(item)
		{
		}

		EvoTypeUseItem(const EvoTypeUseItem& other)
			: mUseItem(other.mUseItem)
		{
		}

		virtual ~EvoTypeUseItem() {

		}

		virtual EvoTypeUseItem* Clone() {
			return new EvoTypeUseItem(*this);
		}

		static std::string GetConditionProperty() {
			return "evoItem";
		}

	private:
		std::string mUseItem;
	};

	/// <summary>
	/// Handles evolutions that trigger when leveling up with a specific move.
	/// </summary>
	class EvoTypeLevelMove : public EvoTypeBase {
	public:
		EvoTypeLevelMove(const std::string& levelUpMove)
			:mLevelMove(levelUpMove) 
		{
		}

		EvoTypeLevelMove(const EvoTypeLevelMove& other)
			:mLevelMove(other.mLevelMove)
		{
		}

		virtual EvoTypeLevelMove* Clone() {
			return new EvoTypeLevelMove(*this);
		}

		virtual ~EvoTypeLevelMove() {

		}

		static std::string GetConditionProperty() {
			return "evoMove";
		}

	private:
		std::string mLevelMove;
	};

	/// <summary>
	/// Handles evolutions that trigger when leveling up holding a specific item.
	/// </summary>
	class EvoTypeLevelHold : public EvoTypeBase {
	public:
		EvoTypeLevelHold(const std::string& item)
			:mLevelItem(item) 
		{
		}

		EvoTypeLevelHold(const EvoTypeLevelHold& other)
			:mLevelItem(other.mLevelItem)
		{
		}

		virtual EvoTypeLevelHold* Clone() {
			return new EvoTypeLevelHold(*this);
		}

		virtual ~EvoTypeLevelHold() {

		}

		static std::string GetConditionProperty() {
			return "evoItem";
		}

	private:
		std::string mLevelItem;
	};

	/// <summary>
	/// Triggers evolution if friendship is above a certain point.
	/// </summary>
	class EvoTypeLevelFriendship : public EvoTypeBase {
	public:
		EvoTypeLevelFriendship()
		{
		}

		EvoTypeLevelFriendship(const EvoTypeLevelFriendship& other)
		{
		}

		virtual EvoTypeLevelFriendship* Clone() {
			return new EvoTypeLevelFriendship(*this);
		}

		virtual ~EvoTypeLevelFriendship() {

		}
	private:
	};

	/// <summary>
	/// Generates an evo type from a json object.
	/// </summary>
	class EvoTypeFactory {
	public:
		static EvoTypeBase* LoadEvoType(JsonObject* pokemonNode) {
			// Handle level up evo condition.
			if (pokemonNode->nodeExists(EvoTypeLevelUp::GetConditionProperty())) {
				int evoLevel = pokemonNode->lookupNode(EvoTypeLevelUp::GetConditionProperty())->numberValue;
				return new EvoTypeLevelUp(evoLevel);
			}

			if (pokemonNode->nodeExists("evoType")) {
				std::string evoType = pokemonNode->lookupNode("evoType")->stringValue;

				if (evoType == "other") {
					// Have to be handled on a case-by-case basis.
				}
				else if (evoType == "levelExtra") {
					// Have to be handled on a case-by-case basis.
				}
				else if (evoType == "trade") {
					// Should be converted into a different type of evo.
				}
				else if (evoType == "useItem") {
					if (pokemonNode->nodeExists(EvoTypeUseItem::GetConditionProperty())) {
						std::string evoItem = pokemonNode->
							lookupNode(EvoTypeUseItem::GetConditionProperty())->stringValue;

						return new EvoTypeUseItem(evoItem);
					}
					// Otherwise, we have a problem.
					StaticLogger::instance.warning("Use item unspecified");
				}
				else if (evoType == "levelHold") {
					if (pokemonNode->nodeExists(EvoTypeLevelHold::GetConditionProperty())) {
						std::string evoItem = pokemonNode->
							lookupNode(EvoTypeLevelHold::GetConditionProperty())->stringValue;

						return new EvoTypeLevelHold(evoItem);
					}
					// Otherwise, we have a problem.
					StaticLogger::instance.warning("Use item unspecified");
				}
				else if (evoType == "levelMove") {
					if (pokemonNode->nodeExists(EvoTypeLevelMove::GetConditionProperty())) {
						std::string levelMove = pokemonNode->
							lookupNode(EvoTypeLevelMove::GetConditionProperty())->stringValue;

						return new EvoTypeLevelMove(levelMove);
					}
				}
				else if (evoType == "levelFriendship") {
					return new EvoTypeLevelFriendship();
				}
				else {
					// We have a different type of levelType which I didn't see.
					std::cout << "Unhandled level type: " << evoType << "\n";
					StaticLogger::instance.warning("Unhandled level type: {s}", evoType.c_str());
				}
			}

			return nullptr;
		}
	};

}