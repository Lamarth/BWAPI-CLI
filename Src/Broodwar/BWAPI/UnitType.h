#pragma once

#include <BWAPI/UnitType.h>

#pragma managed

#include "Race.h"
#include "Price.h"
#include "IIdentifiedObject.h"
#include "Enum\UnitType.h"
#include "Enum\UnitSizeType.h"

using namespace System;
using namespace System::Collections::Generic;

namespace BroodWar
{
	namespace Api
	{
		ref class Tech;
		ref class Upgrade;
		ref class Weapon;

		/// <summary>
		/// The UnitType class is used to get information about a particular type of unit, such as the build time of a Lurker,
		/// or the mineral price of an Ultralisk. TODO Add the unittype table from the wiki
		/// </summary>
		public ref class UnitType sealed : public IIdentifiedObject
		{
		internal:
			BWAPI::UnitType* instance;
			bool dispose;

			UnitType(Api::Enum::UnitType type);
			UnitType(BWAPI::UnitType* type);
			UnitType(BWAPI::UnitType type);
			~UnitType();
			!UnitType();
			
		public:
			UnitType();

			UnitType(int id);

			virtual property int Id { int get(); }

			property Api::Enum::UnitType Type { Api::Enum::UnitType get(); }
			
			bool TypeEquals(Api::Enum::UnitType type);
			
			/// <summary>
			/// Returns the race that the unit belongs to. For example UnitTypes::Terran_SCV.getRace() will return Races::Terran
			/// </summary>
			property Api::Race^ Race { Api::Race^ get(); }
			
			/// <summary>
			/// Returns what builds this unit type. The second number will usually be 1 unless the unit type is Protoss_Archon or Protoss_Dark_Archon.
			/// Units that cannot be created, such as critters and mineral fields, will return a pair where the unit type is UnitTypes::None, and the
			/// second component is 0.
			/// 
			/// Example: UnitTypes::Terran_Marine.whatBuilds() will return an std::pair, where the first component is UnitTypes::Terran_Barracks
			/// </summary>
			property Tuple<Api::UnitType^, int>^ WhatBuilds { Tuple<Api::UnitType^, int>^ get(); }
			
			/// <summary>
			/// Returns the units the player is required to have before it can train or build the given unit type.
			/// 
			/// Example: UnitTypes::Terran_Battlecruiser.requiredUnits() will return a dictionary of three keys:
			/// UnitTypes::Terran_Starport, UnitTypes::Terran_Control_Tower, and UnitTypes::Terran_Physics_Lab
			/// </summary>
			property Dictionary<Api::UnitType^, int>^ RequiredUnits { Dictionary<Api::UnitType^, int>^ get(); }
			
			/// <summary>
			/// Included in the API for completeness, since the only units that actually needs tech to be trained are the Zerg_Lurker and Zerg_Lurker_Egg.
			/// The tech type needed is TechTypes::Lurker_Aspect
			/// </summary>
			property Api::Tech^ RequiredTech { Api::Tech^ get(); }
			
			/// <summary>
			/// Returns the tech used to cloak the unit, or TechTypes::None if the unit cannot cloak or is permanently cloaked
			/// </summary>
			property Api::Tech^ CloakingTech { Api::Tech^ get(); }
			
			/// <summary>
			/// Returns the set of tech types this unit can use, provided the tech types have been researched and the unit has enough energy
			/// </summary>
			property HashSet<Api::Tech^>^ Abilities { HashSet<Api::Tech^>^ get(); }
			
			/// <summary>
			/// Returns the set of upgrade types that can affect this unit
			/// </summary>
			property HashSet<Api::Upgrade^>^ Upgrades { HashSet<Api::Upgrade^>^ get(); }
			
			/// <summary>
			/// Returns the upgrade that increase's the unit's armor, or UpgradeTypes::None if no upgrade increase's this unit's armor.
			/// For example UnitTypes::Terran_Marine.armorUpgrade() will return a pointer to UpgradeTypes::Terran_Infantry_Armor
			/// </summary>
			property Api::Upgrade^ ArmorUpgrade { Api::Upgrade^ get(); }
			
			/// <summary>
			/// Returns the maximum amount of hit points the unit type can have
			/// </summary>
			property int MaxHitPoints { int get(); }
			
			/// <summary>
			/// Returns the maximum amount of shields the unit type can have
			/// </summary>
			property int MaxShields { int get(); }
			
			/// <summary>
			/// Returns the maximum amount of energy the unit type can have
			/// </summary>
			property int MaxEnergy { int get(); }
			
			/// <summary>
			/// Returns the amount of armor the non-upgraded unit type has
			/// </summary>
			property int Armor { int get(); }
			
			/// <summary>
			/// Unit price
			/// </summary>
			property Api::Price^ Price { Api::Price^ get(); }
			
			/// <summary>
			/// Returns the amount of supply produced by this unit (i.e. for a Protoss_Pylon). Supply counts returned by BWAPI are double what
			/// you would expect to see from playing the game. This is because zerglings take up 0.5 in-game supply
			/// </summary>
			property int ProvidedSupply { int get(); }
			
			/// <summary>
			/// Returns the amount of space this unit type takes up inside a bunker or transport unit
			/// </summary>
			property int RequiredSpace { int get(); }
			
			/// <summary>
			/// Returns the amount of space this unit type provides
			/// </summary>
			property int ProvidedSpace { int get(); }
			
			/// <summary>
			/// Returns the score which is used to determine the total scores in the after-game stats screen
			/// </summary>
			property int BuildScore { int get(); }
			
			/// <summary>
			/// Returns the score which is used to determine the total scores in the after-game stats screen
			/// </summary>
			property int DestroyScore { int get(); }
			
			/// <summary>
			/// Returns the size of the unit - either Small, Medium, Large, or Independent
			/// </summary>
			property Api::Enum::UnitSizeType Size { Api::Enum::UnitSizeType get(); }
			
			/// <summary>
			/// Returns the tile width of the unit. Useful for determining the size of buildings. For example UnitTypes::Terran_Supply_Depot.tileWidth() will return 3
			/// </summary>
			property int TileWidth { int get(); }
			
			/// <summary>
			/// Returns the tile height of the unit. Useful for determining the size of buildings. For example UnitTypes::Terran_Supply_Depot.tileHeight() will return 2
			/// </summary>
			property int TileHeight { int get(); }
			
			/// <summary>
			/// Distance from the center of the unit to the left edge of the unit, measured in pixels
			/// </summary>
			property int DimensionLeft { int get(); }
			
			/// <summary>
			/// Distance from the center of the unit to the top edge of the unit, measured in pixels
			/// </summary>
			property int DimensionUp { int get(); }
			
			/// <summary>
			/// Distance from the center of the unit to the right edge of the unit, measured in pixels
			/// </summary>
			property int DimensionRight { int get(); }
			
			/// <summary>
			/// Distance from the center of the unit to the bottom edge of the unit, measured in pixels
			/// </summary>
			property int DimensionDown { int get(); }
			
			/// <summary>
			/// Returns the range at which the unit will start targeting enemy units, measured in pixels
			/// </summary>
			property int SeekRange { int get(); }
			
			/// <summary>
			/// Returns how far the un-upgraded unit type can see into the fog of war, measured in pixels
			/// </summary>
			property int SightRange { int get(); }
			
			/// <summary>
			/// Returns the unit's ground weapon
			/// </summary>
			property Api::Weapon^ GroundWeapon { Api::Weapon^ get(); }
			
			property int MaxGroundHits { int get(); }
			
			/// <summary>
			/// Returns the unit's air weapon
			/// </summary>
			property Api::Weapon^ AirWeapon { Api::Weapon^ get(); }
			
			property int MaxAirHits { int get(); }
			
			/// <summary>
			/// Returns the unit's non-upgraded top speed in pixels per frame. For Terran buildings that can lift off and the Zerg Infested
			/// Command Center, this returns how fast the building moves when it is lifted
			/// </summary>
			property double TopSpeed { double get(); }
			
			/// <summary>
			/// Returns how fast the unit can accelerate to its top speed. What units this quantity is measured in is currently unknown
			/// </summary>
			property int Acceleration { int get(); }
			
			/// <summary>
			/// Related to how fast the unit can halt. What units this quantity is measured in is currently unknown
			/// </summary>
			property int HaltDistance { int get(); }
			
			/// <summary>
			/// Related to how fast the unit can turn. What units this quantity is measured in is currently unknown
			/// </summary>
			property int TurnRadius { int get(); }
			
			/// <summary>
			/// Returns true if the unit can train other units. For example, UnitTypes::Terran_Barracks.canProduce() will return true,
			/// while UnitTypes::Terran_Marine?.canProduce() will return false. This is also true for two non-building units: Protoss Carrier
			/// (can produce interceptors) and Protoss Reaver (can produce scarabs)
			/// </summary>
			property bool CanProduce { bool get(); }
			
			/// <summary>
			/// Returns true if the unit can attack (either ground or air). Returns false for units that can only inflict damage via special abilities (such as Protoss High Templar)
			/// </summary>
			property bool CanAttack { bool get(); }
			
			/// <summary>
			/// Returns true if the unit can move. Note that buildings will return false, even Terran buildings which can move once lifted
			/// </summary>
			property bool CanMove { bool get(); }
			
			/// <summary>
			/// Returns true for flying/air units
			/// </summary>
			property bool IsFlyer { bool get(); }
			
			/// <summary>
			/// Returns true for units that regenerate health (i.e. zerg units)
			/// </summary>
			property bool RegeneratesHp { bool get(); }
			
			/// <summary>
			/// Returns true if the unit type is capable of casting spells / using technology
			/// </summary>
			property bool IsSpellcaster { bool get(); }
			
			/// <summary>
			/// Returns true for the two units that are permanently cloaked - Protoss Observer and Protoss Dark Templar
			/// </summary>
			property bool HasPermanentCloak { bool get(); }
			
			/// <summary>
			/// Returns true for units that cannot be destroyed (i.e. Terran Nuclear Missile, Mineral Field, Vespene Geyser, etc)
			/// </summary>
			property bool IsInvincible { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is organic, such as a Terran Marine
			/// </summary>
			property bool IsOrganic { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is mechanical such as a Terran Vulture
			/// </summary>
			property bool IsMechanical { bool get(); }
			
			/// <summary>
			/// Returns true for the four robotic Protoss units - Probe, Shuttle, Reaver, and Observer
			/// </summary>
			property bool IsRobotic { bool get(); }
			
			/// <summary>
			/// Returns true for the seven units that can detect cloaked units - Terran Science Vessel, Spell Scanner Sweep, Zerg Overlord,
			/// Protoss Observer, Terran Missile Turret, Zerg Spore Colony, and Protoss Photon Cannon
			/// </summary>
			property bool IsDetector { bool get(); }
			
			/// <summary>
			/// Returns true for the five units that hold resources - Mineral Field, Vespene Geyser, Terran Refinery, Zerg Extractor, and Protoss Assimilator
			/// </summary>
			property bool IsResourceContainer { bool get(); }
			
			/// <summary>
			/// Returns true for the five units that can accept resources - Terran Command Center, Protoss Nexus, Zerg Hatchery, Zerg Lair, and Zerg Hive
			/// </summary>
			property bool IsResourceDepot { bool get(); }
			
			/// <summary>
			/// Returns true for Terran Refinery, Zerg Extractor, and Protoss Assimilator
			/// </summary>
			property bool IsRefinery { bool get(); }
			
			/// <summary>
			/// Returns true for Protoss Probe, Terran SCV, and Zerg Drone
			/// </summary>
			property bool IsWorker { bool get(); }
			
			/// <summary>
			/// Returns true for buildings that must be near a pylon to be constructed
			/// </summary>
			property bool RequiresPsi { bool get(); }
			
			/// <summary>
			/// Returns true for buildings that can only be built on zerg creep
			/// </summary>
			property bool RequiresCreep { bool get(); }
			
			/// <summary>
			/// Returns true for Zergling and Scourge
			/// </summary>
			property bool IsTwoUnitsInOneEgg { bool get(); }
			
			/// <summary>
			/// Returns true for Zerg Lurker and units that can burrow when burrow tech is researched
			/// </summary>
			property bool IsBurrowable { bool get(); }
			
			/// <summary>
			/// Returns true for units that can be cloaked - Terran Ghost and Terran Wraith. Does not include units which have permanent
			/// cloak (Protoss Observer and Protoss Dark Templar)
			/// </summary>
			property bool IsCloakable { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is a building (also true for mineral field and vespene geyser)
			/// </summary>
			property bool IsBuilding { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is an add-on, such as a Terran Comsat Station
			/// </summary>
			property bool IsAddon { bool get(); }
			
			/// <summary>
			/// Returns true for Terran buildings that can lift off (i.e. Barracks)
			/// </summary>
			property bool IsFlyingBuilding { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is neutral, such as a critter or mineral field
			/// </summary>
			property bool IsNeutral { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is a Hero unit
			/// </summary>
			property bool IsHero { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is a Powerup unit
			/// </summary>
			property bool IsPowerup { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is a regular Beacon
			/// </summary>
			property bool IsBeacon { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is a flag Beacon
			/// </summary>
			property bool IsFlagBeacon { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is a special building
			/// </summary>
			property bool IsSpecialBuilding { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is a spell unit
			/// </summary>
			property bool IsSpell { bool get(); }
			
			/// <summary>
			/// Returns true if the unit produces larva
			/// </summary>
			property bool ProducesLarva { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is one of the three mineral field types
			/// </summary>
			property bool IsMineralField { bool get(); }
			
			/// <summary>
			/// Returns true if the unit is capable of constructing an addon. This consists of Command Center, Factory, Starport, and Science Facility
			/// </summary>
			property bool CanBuildAddon { bool get(); }

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(UnitType^ other);

			static property List<UnitType^>^ AllUnitTypes { List<UnitType^>^ get(); }
			static property List<UnitType^>^ AllMacroTypes { List<UnitType^>^ get(); }

			static bool operator == (UnitType^ first, UnitType^ second);
			static bool operator != (UnitType^ first, UnitType^ second);
		};

		UnitType^ ConvertUnitType(BWAPI::UnitType unitType);
		BWAPI::UnitType ConvertUnitType(UnitType^ unitType);
		BWAPI::UnitType ConvertUnitType(Enum::UnitType unitType);
	}
}
