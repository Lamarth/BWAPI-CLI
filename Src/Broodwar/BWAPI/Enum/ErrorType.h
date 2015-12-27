#pragma once

namespace BroodWar
{
	namespace Api
	{
		namespace Enum
		{
			/// <summary>
			/// Functions in BWAPI may set an error code. To retrieve the error code, call Game::getLastError
			/// </summary>
			public enum class ErrorType
			{
				/// <summary>
				/// Returned if you try to order a unit or get information from a unit that no longer exists
				/// </summary>
				UnitDoesNotExist,

				/// <summary>
				/// Returned if you try to retrieve information about a unit that is not currently visible or is dead
				/// </summary>
				UnitNotVisible,

				/// <summary>
				/// Returned when attempting to order a unit that BWAPI does not own (i.e. can't order enemy army to go away)
				/// </summary>
				UnitNotOwned,

				/// <summary>
				/// Returned when trying to order a unit to do something when it is performing another order or is in a
				/// state which prevents it from performing the desired order. For example, ordering a Terran Engineering
				/// Bay to upgrade something while it is already upgrading something else will return this error.
				/// Similarly, trying to train units from a factory that is lifted will return this error
				/// </summary>
				UnitBusy,

				/// <summary>
				/// Returned if you do something weird like try to build a Pylon with an SCV, or train Vultures in a Barracks, or order a Hydralisk to lay a spider mine
				/// </summary>
				IncompatibleUnitType,

				/// <summary>
				/// Returned when trying to use a tech type with the wrong Unit::useTech method
				/// </summary>
				IncompatibleTechType,

				/// <summary>
				/// Returned if you to do something like try to cancel an upgrade when the unit isn't upgrading
				/// </summary>
				IncompatibleState,

				/// <summary>
				/// Returned if you try to research something that is already researched
				/// </summary>
				AlreadyResearched,

				/// <summary>
				/// Returned if you try to upgrade something that is already fully upgraded
				/// </summary>
				FullyUpgraded,

				/// <summary>
				/// Returned if you try to research something that is already being researched
				/// </summary>
				CurrentlyResearching,

				/// <summary>
				/// Returned if you try to upgrade something that is already being upgraded
				/// </summary>
				CurrentlyUpgrading,

				/// <summary>
				/// Returned if you try to train or build something without enough minerals
				/// </summary>
				InsufficientMinerals,

				/// <summary>
				/// Returned if you try to train or build something without enough vespene gas
				/// </summary>
				InsufficientGas,

				/// <summary>
				/// Returned if you try to train something without enough supply
				/// </summary>
				InsufficientSupply,	

				/// <summary>
				/// Returned if you to do something like try to order a Defiler to cast a Dark Swarm without enough energy
				/// </summary>
				InsufficientEnergy,

				/// <summary>
				/// Returned if you do something like try to train Medics when you don't have an Academy, or try to lay Spider Mines before
				/// spider mines have been researched
				/// </summary>
				InsufficientTech,

				/// <summary>
				/// Returned if you do something like try to lay Spider Mines when your Vulture is out of Spider Mines. Same thing with Reavers and Scarabs
				/// </summary>
				InsufficientAmmo,

				/// <summary>
				/// Returned if you try to train more Interceptors than the Carrier can hold, try to train more Scarabs than a Reaver can hold,
				/// or try to load more units into a transport than there is space
				/// </summary>
				InsufficientSpace,

				/// <summary>
				/// Returned if you try to build a barracks at TilePositions::None or something similar
				/// </summary>
				InvalidTilePosition,

				/// <summary>
				/// Returned if you try to construct a building on an unbuildable location
				/// </summary>
				UnbuildableLocation,

				/// <summary>
				/// Returned if you try to construct a building where the worker cannot reach based on static map data
				/// </summary>
				UnreachableLocation,

				/// <summary>
				/// Returned if you order an immovable unit, like a Protoss Photon Cannon, to attack a unit that is out of range
				/// </summary>
				OutOfRange,

				/// <summary>
				/// Returned if you do something like order a Vulture to attack a flying unit
				/// </summary>
				UnableToHit,

				/// <summary>
				/// Returned if you try to get information that is not allowed with the given flag settings. For example, trying to read
				/// the enemy's resource counts while the CompleteMapInformation?  flag is not enabled will return this error. Similarly,
				/// trying to read the coordinates of the screen or mouse while the UserInput flag is not enabled will also return this error
				/// </summary>
				AccessDenied,

				/// <summary>
				/// Used when a file can't be found
				/// </summary>
				FileNotFound,

				/// <summary>
				/// Used for bad parameters, like passing NULL or an empty string
				/// </summary>
				InvalidParameter,

				/// <summary>
				/// Used when no error has been encountered
				/// </summary>
				None,

				/// <summary>
				/// Used when the error code is not recognized or can not be determined
				/// </summary>
				Unknown,
			};
		}
	}
}
