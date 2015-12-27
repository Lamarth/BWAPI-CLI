#pragma once
#pragma unmanaged

#include <BWAPI\Player.h>
#include <BWAPI\Playerset.h>
//#pragma make_public(BWAPI::Player)

#pragma managed

#include "Position.h"
#include "Race.h"
#include "Weapon.h"
#include "IIdentifiedObject.h"
#include "Enum\TechType.h"
#include "Enum\UpgradeType.h"
#include "Enum\PlayerType.h"
#include "Enum\UnitType.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace BroodWar
{
	namespace Api
	{
		ref class Unit;
		ref class Force;

		/// <summary>
		/// Each player in a match will have his or her own player instance. There is also a neutral player which owns all the neutral units
		/// </summary>
		public ref class Player sealed : public IIdentifiedObject
		{
		internal:
			BWAPI::Player instance;

			Player(BWAPI::Player player);

		public:
			/// <summary>
			/// Returns a unique ID for the player
			/// </summary>
			virtual property int Id { int get(); }
			
			property Api::Enum::PlayerType Type { Api::Enum::PlayerType get(); }
			
			bool TypeEquals(Api::Enum::PlayerType type);
			
			/// <summary>
			/// Returns the name of the player
			/// </summary>
			property String^ Name { String^ get(); }
			
			/// <summary>
			/// Returns the list of units the player own. Note that units loaded into Terran dropships, Terran bunkers, Terran refineries,
			/// Protoss assimilators, and Zerg extractors are not yet included in the list
			/// </summary>
			property HashSet<Api::Unit^>^ Units { HashSet<Api::Unit^>^ get(); }
			
			/// <summary>
			/// Returns the race of the player
			/// </summary>
			property Api::Race^ Race { Api::Race^ get(); }
			
			/// <summary>
			/// Returns the force the player is on
			/// </summary>
			property Api::Force^ Force { Api::Force^ get(); }
			
			/// <summary>
			/// Returns true if other player is an ally of this player
			/// </summary>
			bool IsAlly(Api::Player^ player);
			
			/// <summary>
			/// Returns true if other player is an enemy of this player
			/// </summary>
			bool IsEnemy(Api::Player^ player);
			
			/// <summary>
			/// Returns true if the player is the neutral player
			/// </summary>
			property bool IsNeutral { bool get(); }
			
			/// <summary>
			/// Returns the starting location of the player. If complete map information is disabled, this function will return TilePositions::Unknown
			/// for enemy players. For the complete set of starting locations for the current map, see Game::getStartLocations
			/// </summary>
			property Api::TilePosition^ StartLocation { Api::TilePosition^ get(); }
			
			/// <summary>
			/// Returns true if the player has achieved victory
			/// </summary>
			property bool IsVictorious { bool get(); }
			
			/// <summary>
			/// Returns true if the player has been defeated
			/// </summary>
			property bool IsDefeated { bool get(); }
			
			/// <summary>
			/// Returns true if the player left the game
			/// </summary>
			property bool LeftGame { bool get(); }
			
			/// <summary>
			/// Returns the amount of minerals the player has
			/// </summary>
			property int Minerals { int get(); }
			
			/// <summary>
			/// Returns the amount of vespene gas the player has
			/// </summary>
			property int Gas { int get(); }
			
			/// <summary>
			/// Returns the cumulative amount of minerals the player has mined up to this point (including the 50 minerals at the start of the game)
			/// </summary>
			property int GatheredMinerals { int get(); }
			
			/// <summary>
			/// Returns the cumulative amount of gas the player has harvested up to this point
			/// </summary>
			property int GatheredGas { int get(); }
			
			/// <summary>
			/// Returns the cumulative amount of minerals the player has spent on repairs up to this point
			/// </summary>
			property int RepairedMinerals { int get(); }
			
			/// <summary>
			/// Returns the cumulative amount of gas the player has spent on repairs up to this point
			/// </summary>
			property int RepairedGas { int get(); }
			
			/// <summary>
			/// Returns the cumulative amount of minerals the player has gained from refunded units up to this point
			/// </summary>
			property int RefundedMinerals { int get(); }
			
			/// <summary>
			/// Returns the cumulative amount of gas the player has gained from refunded units up to this point
			/// </summary>
			property int RefundedGas { int get(); }
			
			/// <summary>
			/// Returns the cumulative amount of minerals the player has spent up to this point (not including repairs)
			/// </summary>
			property int SpentMinerals { int get(); }
			
			/// <summary>
			/// Returns the cumulative amount of gas the player has spent up to this point (not including repairs)
			/// </summary>
			property int SpentGas { int get(); }
			
			/// <summary>
			/// Returns the total amount of supply the player has. If a race is provided, the total supply for the given race will be returned, otherwise the
			/// player's initial race will be used. Supply counts returned by BWAPI are double what you would expect to see from playing the game. This is because
			/// zerglings take up 0.5 in-game supply
			/// </summary>
            property int SupplyTotal { int get(); }
			
			/// <summary>
			/// Returns the total amount of supply the player has. If a race is provided, the total supply for the given race will be returned, otherwise the
			/// player's initial race will be used. Supply counts returned by BWAPI are double what you would expect to see from playing the game. This is because
			/// zerglings take up 0.5 in-game supply
			/// </summary>
			int GetSupplyTotal(Api::Race^ race);
			
			/// <summary>
			/// Returns how much of the supply is actually being used by units. If a race is provided, the used supply for the given race will be returned,
			/// otherwise the player's initial race will be used. Supply counts returned by BWAPI are double what you would expect to see from playing the game.
			/// This is because zerglings take up 0.5 in-game supply
			/// </summary>
            property int SupplyUsed { int get(); }
			
			/// <summary>
			/// Returns how much of the supply is actually being used by units. If a race is provided, the used supply for the given race will be returned,
			/// otherwise the player's initial race will be used. Supply counts returned by BWAPI are double what you would expect to see from playing the game.
			/// This is because zerglings take up 0.5 in-game supply
			/// </summary>
			int GetSupplyUsed(Api::Race^ race);
			
			/// <summary>
			/// Returns the number of all accessible units of the given type
			/// </summary>
			int AllUnitCount(Api::Enum::UnitType unit);
			
			/// <summary>
			/// Returns the number of visible units of the given type
			/// </summary>
			int VisibleUnitCount(Api::Enum::UnitType unit);
			
			/// <summary>
			/// Returns the number of completed units of the given type
			/// </summary>
			int CompletedUnitCount(Api::Enum::UnitType unit);
			
			/// <summary>
			/// Returns the number of incomplete units of the given type
			/// </summary>
			int IncompleteUnitCount(Api::Enum::UnitType unit);
			
			/// <summary>
			/// Returns the number of dead units of the given type
			/// </summary>
			int DeadUnitCount(Api::Enum::UnitType unit);
			
			/// <summary>
			/// Returns the number of killed units of the given type
			/// </summary>
			int KilledUnitCount(Api::Enum::UnitType unit);
			
			/// <summary>
			/// Returns the player's current upgrade level of the given upgrade. To order a unit to upgrade a given upgrade type, see Unit::upgrade
			/// </summary>
			int  GetUpgradeLevel(Api::Enum::UpgradeType upgrade);
			
			/// <summary>
			/// Returns true if the player has finished researching the given tech. To order a unit to research a given tech type, see Unit::research
			/// </summary>
			bool HasResearched(Api::Enum::TechType tech);
			
			/// <summary>
			/// Returns true if the player is researching the given tech. To order a unit to research a given tech type, see Unit::reseach
			/// </summary>
			bool IsResearching(Api::Enum::TechType tech);
			
			/// <summary>
			/// Returns true if the player is upgrading the given upgrade. To order a unit to upgrade a given upgrade type, see Unit::upgrade
			/// </summary>
			bool IsUpgrading(Api::Enum::UpgradeType upgrade);
			
			/// <summary>
			/// Returns the color of the player for drawing
			/// </summary>
			property Drawing::Color Color { Drawing::Color get(); }
			
			/// <summary>
			/// Returns the color of the player for text messages
			/// </summary>
			property int TextColor { int get(); }
			
			/// <summary>
			/// Returns the max energy of the given unit type, taking into account upgrades
			/// </summary>
			int MaxEnergy(Api::Enum::UnitType unit);
			
			/// <summary>
			/// Returns the top speed of the given unit type, includes upgrades
			/// </summary>
			double TopSpeed(Api::Enum::UnitType unit);
			
			/// <summary>
			/// Returns the max range of the given weapon with upgrades
			/// </summary>
			int WeaponMaxRange(Api::Weapon^ weapon);
			
			/// <summary>
			/// Returns the sight range of the given unit type, includes upgrades
			/// </summary>
			int SightRange(Api::Enum::UnitType unit);
			
			/// <summary>
			/// Returns the weapon cooldown of the given unit type, includes upgrades
			/// </summary>
			int WeaponDamageCooldown(Api::Enum::UnitType unit);
			
			/// <summary>
			/// Returns the armor of the given unit type, includes upgrades
			/// </summary>
			int Armor(Api::Enum::UnitType unit);
			
			/// <summary>
			/// Returns the Player's Total Unit Score
			/// </summary>
			property int UnitScore { int get(); }
			
			/// <summary>
			/// Returns the Player's Total Kill Score
			/// </summary>
			property int KillScore { int get(); }
			
			/// <summary>
			/// Returns the Player's Total Buildings Score
			/// </summary>
			property int BuildingScore { int get(); }
			
			/// <summary>
			/// Returns the Player's Total Razings Score
			/// </summary>
			property int RazingScore { int get(); }
			
			/// <summary>
			/// Returns the Player's Custom Score
			/// </summary>
			property int CustomScore { int get(); }
			
			/// <summary>
			/// Returns true if the Player is only observing the game, and not participating
			/// </summary>
			property bool IsObserver { bool get(); }
			
			/// <summary>
			/// Returns the maximum upgrades available specific to the player (Use Map Settings)
			/// </summary>
			int  GetMaxUpgradeLevel(Api::Enum::UpgradeType upgrade);
			
			/// <summary>
			/// Returns true if the research is available for the player to research (Use Map Settings)
			/// </summary>
			bool IsResearchAvailable(Api::Enum::TechType tech);
			
			/// <summary>
			/// Returns true if the unit is available for the player to build (Use Map Settings)
			/// </summary>
			bool IsUnitAvailable(Api::Enum::UnitType unit);

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(Api::Player^ other);

			static bool operator == (Api::Player^ first, Api::Player^ second);
			static bool operator != (Api::Player^ first, Api::Player^ second);
		};

		Player^ ConvertPlayer(BWAPI::Player player);
		BWAPI::Player ConvertPlayer(Player^ player);
	}
}
