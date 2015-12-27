#pragma once
#pragma unmanaged

#include <BWAPI\Unit.h>
#include <BWAPI\Unitset.h>
//#pragma make_public(BWAPI::Unit)

#pragma managed

#include "Enum\OrderType.h"
#include "Tech.h"
#include "Upgrade.h"
#include "UnitType.h"
#include "Position.h"
#include "Region.h"
#include "UnitCommand.h"
#include "IIdentifiedObject.h"

using namespace System;
using namespace System::Collections::Generic;

namespace BroodWar
{
	namespace Api
	{
		ref class Player;

		/// <summary>
		/// The Unit class is used to get information about individual units as well as issue orders to units. Each unit in the game has a unique Unit object,
		/// and Unit objects are not deleted until the end of the match (so you don't need to worry about unit pointers becoming invalid).
		/// 
		/// Every Unit in the game is either accessible or inaccessible. To determine if an AI can access a particular unit, BWAPI checks to see if
		/// Flag::CompleteMapInformation? is enabled. So there are two cases to consider - either the flag is enabled, or it is disabled:
		/// 
		/// If Flag::CompleteMapInformation? is disabled, then a unit is accessible if and only if it is visible. Note also that some properties of visible enemy
		/// units will not be made available to the AI (such as the contents of visible enemy dropships). If a unit is not visible, Unit::exists will return false,
		/// regardless of whether or not the unit exists. This is because absolutely no state information on invisible enemy units is made available to the AI.
		/// To determine if an enemy unit has been destroyed, the AI must watch for AIModule::onUnitDestroy messages from BWAPI, which is only called for visible
		/// units which get destroyed.
		/// 
		/// If Flag::CompleteMapInformation? is enabled, then all units that exist in the game are accessible, and Unit::exists is accurate for all units. Similarly
		/// AIModule::onUnitDestroy messages are generated for all units that get destroyed, not just visible ones.
		/// 
		/// If a Unit is not accessible, in general the only the getInitial__ functions will be available to the AI. However for units that were owned by the player,
		/// getPlayer and getType will continue to work for units that have been destroyed.
		/// </summary>
		public ref class Unit sealed : public IIdentifiedObject
		{
		internal:
			BWAPI::Unit instance;

			Unit(BWAPI::Unit unit);

		public:
			/// <summary>
			/// Returns a unique ID for this unit. It simply casts the unit's address as an integer, since each unit has a unique address
			/// </summary>
			virtual property int Id { int get(); }

			/// <summary>
			/// Returns the unit ID that is used in a replay (*.rep) file's action recordings
			/// </summary>
			property int ReplayId { int get(); }

			/// <summary>
			/// Returns a pointer to the player that owns this unit
			/// </summary>
			property Api::Player^ Player { Api::Player^ get(); }

			/// <summary>
			/// Returns the current type of the unit
			/// </summary>
			property Api::UnitType^ UnitType { Api::UnitType^ get(); }

			/// <summary>
			/// Returns the position of the unit on the map
			/// </summary>
			property Api::Position^ Position { Api::Position^ get(); }

			/// <summary>
			/// Returns the build tile position of the unit on the map. Useful if the unit is a building. The tile position is of the top left corner of the building
			/// </summary>
			property Api::TilePosition^ TilePosition { Api::TilePosition^ get(); }

			/// <summary>
			/// Returns the direction the unit is facing, measured in radians. An angle of 0 means the unit is facing east
			/// </summary>
			property double Angle { double get(); }

			/// <summary>
			/// Returns the x component of the unit's velocity, measured in pixels per frame
			/// </summary>
			property double VelocityX { double get(); }

			/// <summary>
			/// Returns the y component of the unit's velocity, measured in pixels per frame
			/// </summary>
			property double VelocityY { double get(); }

			/// <summary>
			/// Returns the region that this unit is currently in
			/// </summary>
			property Api::Region^ Region { Api::Region^ get(); }

			/// <summary>
			/// Returns the X coordinate of the left side of the unit
			/// </summary>
			property int Left { int get(); }

			/// <summary>
			/// Returns the Y coordinate of the top side of the unit
			/// </summary>
			property int Top { int get(); }

			/// <summary>
			/// Returns the X coordinate of the right side of the unit
			/// </summary>
			property int Right { int get(); }

			/// <summary>
			/// Returns the Y coordinate of the bottom side of the unit
			/// </summary>
			property int Bottom { int get(); }

			/// <summary>
			/// Returns the unit's current amount of hit points
			/// </summary>
			property int HitPoints { int get(); }

			/// <summary>
			/// Returns the unit's current amount of shields
			/// </summary>
			property int Shields { int get(); }

			/// <summary>
			/// Returns the unit's current amount of energy
			/// </summary>
			property int Energy { int get(); }

			/// <summary>
			/// Returns the unit's current amount of containing resources. Useful for determining how much minerals are left in a mineral patch,
			/// or how much gas is left in a geyser (can also be called on a refinery/assimilator/extractor)
			/// </summary>
			property int Resources { int get(); }

			/// <summary>
			/// Retrieves the group ID of a resource. Can be used to identify which resources belong to an expansion
			/// </summary>
			property int ResourceGroup { int get(); }

			/// <summary>
			/// Returns the edge-to-edge distance between the current unit and the target unit
			/// </summary>
			int Distance(Api::Unit^ target);

			/// <summary>
			/// Returns the distance from the edge of the current unit to the target position
			/// </summary>
			int Distance(Api::Position^ target);

			/// <summary>
			/// Returns true if the unit is able to move to the target unit
			/// </summary>
			bool HasPath(Api::Unit^ target);

			/// <summary>
			/// Returns true if the unit is able to move to the target position
			/// </summary>
			bool HasPath(Api::Position^ target);

			/// <summary>
			/// Returns the frame of the last successful command. Frame is comparable to Game::getFrameCount()
			/// </summary>
			property int LastCommandFrame { int get(); }

			/// <summary>
			/// Returns the last successful command
			/// </summary>
			property Api::UnitCommand^ LastCommand { Api::UnitCommand^ get(); }

			/// <summary>
			/// Returns the player that last attacked this unit
			/// </summary>
			property Api::Player^ LastAttackingPlayer { Api::Player^ get(); }

			/// <summary>
			/// Returns the initial type of the unit or Unknown if it wasn't a neutral unit at the beginning of the game
			/// </summary>
			property Api::UnitType^ InitialType { Api::UnitType^ get(); }

			/// <summary>
			/// Returns the initial position of the unit on the map, or Positions::Unknown if the unit wasn't a neutral unit at the beginning of the game
			/// </summary>
			property Api::Position^ InitialPosition { Api::Position^ get(); }

			/// <summary>
			/// Returns the initial build tile position of the unit on the map, or TilePositions::Unknown if the unit wasn't a neutral unit at the
			/// beginning of the game. The tile position is of the top left corner of the building
			/// </summary>
			property Api::TilePosition^ InitialTilePosition { Api::TilePosition^ get(); }

			/// <summary>
			/// Returns the unit's initial amount of hit points, or 0 if it wasn't a neutral unit at the beginning of the game
			/// </summary>
			property int InitialHitPoints { int get(); }

			/// <summary>
			/// Returns the unit's initial amount of containing resources, or 0 if the unit wasn't a neutral unit at the beginning of the game
			/// </summary>
			property int InitialResources { int get(); }

			/// <summary>
			/// Returns the unit's current kill count
			/// </summary>
			property int KillCount { int get(); }

			/// <summary>
			/// Returns the unit's acid spore count
			/// </summary>
			property int AcidSporeCount { int get(); }

			/// <summary>
			/// Returns the number of interceptors the Protoss Carrier has
			/// </summary>
			property int InterceptorCount { int get(); }

			/// <summary>
			/// Returns the number of scarabs in the Protoss Reaver
			/// </summary>
			property int ScarabCount { int get(); }

			/// <summary>
			/// Returns the number of spider mines in the Terran Vulture
			/// </summary>
			property int SpiderMineCount { int get(); }

			/// <summary>
			/// Returns unit's ground weapon cooldown. It is 0 if the unit is ready to attack
			/// </summary>
			property int GroundWeaponCooldown { int get(); }

			/// <summary>
			/// Returns unit's air weapon cooldown. It is 0 if the unit is ready to attack
			/// </summary>
			property int AirWeaponCooldown { int get(); }

			/// <summary>
			/// Returns unit's ground weapon cooldown. It is 0 if the unit is ready cast a spell
			/// </summary>
			property int SpellCooldown { int get(); }

			/// <summary>
			/// Returns the remaining hit points of the defense matrix. Initially a defense Matrix has 250 points see Unit::getDefenseMatrixTimer, Unit::isDefenseMatrixed
			/// </summary>
			property int DefenseMatrixPoints { int get(); }

			/// <summary>
			/// Returns the time until the defense matrix wears off. 0 -> No defense Matrix present
			/// </summary>
			property int DefenseMatrixTimer { int get(); }

			/// <summary>
			/// Returns the time until the ensnare effect wears off. 0 -> No ensnare effect present
			/// </summary>
			property int EnsnareTimer { int get(); }

			/// <summary>
			/// Returns the time until the radiation wears off. 0 -> No radiation present
			/// </summary>
			property int IrradiateTimer { int get(); }

			/// <summary>
			/// Returns the time until the lockdown wears off. 0 -> No lockdown present
			/// </summary>
			property int LockdownTimer { int get(); }

			/// <summary>
			/// Returns the time until the maelstrom wears off. 0 -> No maelstrom present
			/// </summary>
			property int MaelstromTimer { int get(); }

			property int OrderTimer { int get(); }

			/// <summary>
			/// Returns the time until the plague wears off. 0 -> No plague present
			/// </summary>
			property int PlagueTimer { int get(); }

			/// <summary>
			/// Returns the amount of time until the unit is removed, or 0 if the unit does not have a remove timer. Used to determine how much
			/// time remains before hallucinated units, dark swarm, etc have until they are removed
			/// </summary>
			property int RemoveTimer { int get(); }

			/// <summary>
			/// Returns the time until the stasis field wears off. 0 -> No stasis field present
			/// </summary>
			property int StasisTimer { int get(); }

			/// <summary>
			/// Returns the time until the stimpack wears off. 0 -> No stimpack boost present
			/// </summary>
			property int StimTimer { int get(); }

			/// <summary>
			/// Returns the building type a worker is about to construct. If the unit is a morphing Zerg unit or an incomplete building,
			/// this returns the UnitType the unit is about to become upon completion
			/// </summary>
			property Api::UnitType^ BuildType { Api::UnitType^ get(); }

			/// <summary>
			/// Returns the list of units queued up to be trained. \see Unit::train, Unit::cancelTrain, Unit::isTraining
			/// </summary>
			property List<Api::UnitType^>^ TrainingQueue { List<Api::UnitType^>^ get(); }

			/// <summary>
			/// Returns the tech that the unit is currently researching. If the unit is not researching anything, TechTypes::None is returned.
			/// \see Unit::research, Unit::cancelResearch, Unit::isResearching, Unit::getRemainingResearchTime
			/// </summary>
			property Api::Tech^ Tech { Api::Tech^ get(); }

			/// <summary>
			/// Returns the upgrade that the unit is currently upgrading. If the unit is not upgrading anything, UpgradeTypes::None is returned.
			/// \see Unit::upgrade, Unit::cancelUpgrade, Unit::isUpgrading, Unit::getRemainingUpgradeTime
			/// </summary>
			property Api::Upgrade^ Upgrade { Api::Upgrade^ get(); }

			/// <summary>
			/// Returns the remaining build time of a unit/building that is being constructed
			/// </summary>
			property int RemainingBuildTime { int get(); }

			/// <summary>
			/// Returns the remaining time of the unit that is currently being trained. If the unit is a Hatchery, Lair, or Hive, this returns the amount
			/// of time until the next larva spawns, or 0 if the unit already has 3 larva
			/// </summary>
			property int RemainingTrainTime { int get(); }

			/// <summary>
			/// Returns the amount of time until the unit is done researching its current tech. If the unit is not researching anything, 0 is returned.
			/// \see Unit::research, Unit::cancelResearch, Unit::isResearching, Unit::getTech
			/// </summary>
			property int RemainingResearchTime { int get(); }

			/// <summary>
			/// Returns the amount of time until the unit is done upgrading its current upgrade. If the unit is not upgrading anything, 0 is returned.
			/// \see Unit::upgrade, Unit::cancelUpgrade, Unit::isUpgrading, Unit::getUpgrade
			/// </summary>
			property int RemainingUpgradeTime { int get(); }

			/// <summary>
			/// If the unit is an SCV that is constructing a building, this will return the building it is constructing. If the unit is a Terran
			/// building that is being constructed, this will return the SCV that is constructing it
			/// </summary>
			property Api::Unit^ BuildUnit { Api::Unit^ get(); }

			/// <summary>
			/// Generally returns the appropriate target unit after issuing an order that accepts a target unit (i.e. attack, repair, gather, follow, etc.).
			/// To check for a target that has been acquired automatically (without issuing an order) see getOrderTarget
			/// </summary>
			property Api::Unit^ Target { Api::Unit^ get(); }

			/// <summary>
			/// Returns the target position the unit is moving to (provided a valid path to the target position exists)
			/// </summary>
			property Api::Position^ TargetPosition { Api::Position^ get(); }

			property Api::Enum::OrderType Order { Api::Enum::OrderType get(); }

			property Api::Enum::OrderType SecondaryOrder { Api::Enum::OrderType get(); }

			/// <summary>
			/// This is usually set when the low level unit AI acquires a new target automatically. For example if an enemy probe comes in range of your marine,
			/// the marine will start attacking it, and getOrderTarget will be set in this case, but not getTarget
			/// </summary>
			property Api::Unit^ OrderTarget { Api::Unit^ get(); }

			/// <summary>
			/// Returns the target position for the units order. For example for the move order getTargetPosition returns the end of the units path but this returns
			/// the location the unit is trying to move to. 
			/// </summary>
			property Api::Position^ OrderTargetPosition { Api::Position^ get(); }

			/// <summary>
			/// Returns the position the building is rallied to. If the building does not produce units, Positions::None is returned.
			/// \see Unit::setRallyPoint, Unit::getRallyUnit
			/// </summary>
			property Api::Position^ RallyPosition { Api::Position^ get(); }

			/// <summary>
			/// Returns the unit the building is rallied to. If the building is not rallied to any unit, NULL is returned.
			/// \see Unit::setRallyPoint, Unit::getRallyPosition
			/// </summary>
			property Api::Unit^ RallyUnit { Api::Unit^ get(); }

			/// <summary>
			/// Returns the add-on of this unit, or NULL if the unit doesn't have an add-on
			/// </summary>
			property Api::Unit^ Addon { Api::Unit^ get(); }

			/// <summary>
			/// Returns the corresponding connected nydus canal of this unit, or NULL if the unit does not have a connected nydus canal
			/// </summary>
			property Api::Unit^ NydusExit { Api::Unit^ get(); }

			/// <summary>
			/// Returns the power up the unit is holding, or NULL if the unit is not holding a power up
			/// </summary>
			property Api::Unit^ PowerUp { Api::Unit^ get(); }

			/// <summary>
			/// Returns the dropship, shuttle, overlord, or bunker that is this unit is loaded in to
			/// </summary>
			property Api::Unit^ Transport { Api::Unit^ get(); }

			/// <summary>
			/// Returns a list of the units loaded into a Terran Bunker, Terran Dropship, Protoss Shuttle, or Zerg Overlord
			/// </summary>
			property HashSet<Api::Unit^>^ LoadedUnits { HashSet<Api::Unit^>^ get(); }

			/// <summary>
			/// For Protoss Interceptors, this returns the Carrier unit this Interceptor is controlled by. For all other unit types this function returns NULL
			/// </summary>
			property Api::Unit^ Carrier { Api::Unit^ get(); }

			/// <summary>
			/// Returns the set of interceptors controlled by this unit. If the unit has no interceptors, or is not a Carrier, this function returns an empty set
			/// </summary>
			property HashSet<Api::Unit^>^ Interceptors { HashSet<Api::Unit^>^ get(); }

			/// <summary>
			/// For Zerg Larva, this returns the Hatchery, Lair, or Hive unit this Larva was spawned from. For all other unit types this function returns NULL
			/// </summary>
			property Api::Unit^ Hatchery { Api::Unit^ get(); }

			/// <summary>
			/// Returns the set of larva spawned by this unit. If the unit has no larva, or is not a Hatchery, Lair, or Hive, this function returns an empty set.
			/// Equivalent to clicking "Select Larva" from the Starcraft GUI
			/// </summary>
			property HashSet<Api::Unit^>^ Larva { HashSet<Api::Unit^>^ get(); }

			/// <summary>
			/// Returns the set of units within the given radius of this unit
			/// </summary>
			HashSet<Api::Unit^>^ UnitsInRadius(int radius);

			/// <summary>
			/// Returns the set of units within weapon range of this unit
			/// </summary>
			HashSet<Api::Unit^>^ UnitsInWeaponRange(Api::Weapon^ weapon);

			/// <summary>
			/// Returns the unit's custom client info. The client is responsible for deallocation.
			/// Sets the unit's custom client info. The client is responsible for deallocation.
			/// </summary>
			property IntPtr ClientInfo { IntPtr get(); void set(IntPtr value); }

			/// <summary>
			/// 3 cases to consider:
			/// - If exists() returns true, the unit exists.
			/// - If exists() returns false and the unit is owned by self(), then the unit does not exist.
			/// - If exists() returns false and the unit is not owned by self(), then the unit may or may not exist.
			/// 
			/// \see Unit::isVisible.
			/// </summary>
			property bool Exists { bool get(); }

			/// <summary>
			/// Returns true if the Nuclear Missile Silo has a nuke
			/// </summary>
			property bool HasNuke { bool get(); }

			/// <summary>
			/// Returns true if the unit is currently accelerating
			/// </summary>
			property bool IsAccelerating { bool get(); }

			property bool IsAttacking { bool get(); }

			property bool IsAttackFrame { bool get(); }

			/// <summary>
			/// Returns true if the unit is being constructed. Always true for incomplete Protoss and Zerg buildings, and true for incomplete Terran
			/// buildings that have an SCV constructing them. If the SCV halts construction, isBeingConstructed will return false.
			/// \see Unit::build, Unit::cancelConstruction, Unit::haltConstruction, Unit::isConstructing
			/// </summary>
			property bool IsBeingConstructed { bool get(); }

			/// <summary>
			/// Returns true if the unit is a mineral patch or refinery that is being gathered
			/// </summary>
			property bool IsBeingGathered { bool get(); }

			/// <summary>
			/// Returns true if the unit is currently being healed by a Terran Medic, or repaired by a Terran SCV
			/// </summary>
			property bool IsBeingHealed { bool get(); }

			/// <summary>
			/// Returns true if the unit is currently blind from a Medic's Optical Flare
			/// </summary>
			property bool IsBlind { bool get(); }

			/// <summary>
			/// Returns true if the unit is currently braking/slowing down
			/// </summary>
			property bool IsBraking { bool get(); }

			/// <summary>
			/// Returns true if the unit is a Zerg unit that is current burrowed.
			/// \see Unit::burrow, Unit::unburrow
			/// </summary>
			property bool IsBurrowed { bool get(); }

			/// <summary>
			/// Returns true if the unit is a worker that is carrying gas.
			/// \see Unit::returnCargo, Unit::isGatheringGas
			/// </summary>
			property bool IsCarryingGas { bool get(); }

			/// <summary>
			/// Returns true if the unit is a worker that is carrying minerals.
			/// \see Unit::returnCargo, Unit::isGatheringMinerals
			/// </summary>
			property bool IsCarryingMinerals { bool get(); }

			/// <summary>
			/// Returns true if the unit is cloaked.
			/// \see Unit::cloak, Unit::decloak
			/// </summary>
			property bool IsCloaked { bool get(); }

			/// <summary>
			/// Returns true if the unit has been completed
			/// </summary>
			property bool IsCompleted { bool get(); }

			/// <summary>
			/// Returns true when a unit has been issued an order to build a structure and is moving to the build location. Also returns true for Terran
			/// SCVs while they construct a building.
			/// \see Unit::build, Unit::cancelConstruction, Unit::haltConstruction, Unit::isBeingConstructed
			/// </summary>
			property bool IsConstructing { bool get(); }

			/// <summary>
			/// Returns true if the unit has a defense matrix from a Terran Science Vessel
			/// </summary>
			property bool IsDefenseMatrixed { bool get(); }

			/// <summary>
			/// Returns true if the unit is detected
			/// </summary>
			property bool IsDetected { bool get(); }

			/// <summary>
			/// Returns true if the unit has been ensnared by a Zerg Queen
			/// </summary>
			property bool IsEnsnared { bool get(); }

			/// <summary>
			/// Returns true if the unit is following another unit.
			/// \see Unit::follow, Unit::getTarget
			/// </summary>
			property bool IsFollowing { bool get(); }

			/// <summary>
			/// Returns true if the unit is in one of the four states for gathering gas (MoveToGas, WaitForGas, HarvestGas, ReturnGas).
			/// \see Unit::isCarryingGas
			/// </summary>
			property bool IsGatheringGas { bool get(); }

			/// <summary>
			/// Returns true if the unit is in one of the four states for gathering minerals (MoveToMinerals, WaitForMinerals, MiningMinerals, ReturnMinerals).
			/// \see Unit::isCarryingMinerals
			/// </summary>
			property bool IsGatheringMinerals { bool get(); }

			/// <summary>
			/// Returns true for hallucinated units, false for normal units. Returns true for hallucinated enemy units only if Complete Map Information is enabled.
			/// \see Unit::getRemoveTimer
			/// </summary>
			property bool IsHallucination { bool get(); }

			/// <summary>
			/// Returns true if the unit is holding position
			/// \see Unit::holdPosition
			/// </summary>
			property bool IsHoldingPosition { bool get(); }

			/// <summary>
			/// Returns true if the unit is not doing anything.
			/// \see Unit::stop
			/// </summary>
			property bool IsIdle { bool get(); }

			/// <summary>
			/// Returns true if the unit can be interrupted
			/// </summary>
			property bool IsInterruptible { bool get(); }

			/// <summary>
			/// Returns true if the unit is invincible
			/// </summary>
			property bool IsInvincible { bool get(); }

			/// <summary>
			/// Returns true if the unit can attack a specified target from its current position
			/// </summary>
			bool IsInWeaponRange(Api::Unit^ target);

			/// <summary>
			/// Returns true if the unit is being irradiated by a Terran Science Vessel.
			/// \see Unit::getIrradiateTimer
			/// </summary>
			property bool IsIrradiated { bool get(); }

			/// <summary>
			/// Returns true if the unit is a Terran building that is currently lifted off the ground.
			/// \see Unit::lift,Unit::land
			/// </summary>
			property bool IsLifted { bool get(); }

			/// <summary>
			/// Return true if the unit is loaded into a Terran Bunker, Terran Dropship, Protoss Shuttle, or Zerg Overlord.
			/// \see Unit::load, Unit::unload, Unit::unloadAll
			/// </summary>
			property bool IsLoaded { bool get(); }

			/// <summary>
			/// Returns true if the unit is locked down by a Terran Ghost.
			/// \see Unit::getLockdownTimer
			/// </summary>
			property bool IsLockedDown { bool get(); }

			/// <summary>
			/// Returns true if the unit is being maelstrommed.
			/// \see Unit::getMaelstromTimer
			/// </summary>
			property bool IsMaelstrommed { bool get(); }

			/// <summary>
			/// Returns true if the unit is a zerg unit that is morphing.
			/// \see Unit::morph, Unit::cancelMorph, Unit::getBuildType, Unit::getRemainingBuildTime
			/// </summary>
			property bool IsMorphing { bool get(); }

			/// <summary>
			/// Returns true if the unit is moving.
			/// \see Unit::attack, Unit::stop
			/// </summary>
			property bool IsMoving { bool get(); }

			/// <summary>
			/// Returns true if the unit has been parasited by some other player
			/// </summary>
			property bool IsParasited { bool get(); }

			/// <summary>
			/// Returns true if the unit is patrolling between two positions.
			/// \see Unit::patrol
			/// </summary>
			property bool IsPatrolling { bool get(); }

			/// <summary>
			/// Returns true if the unit has been plagued by a Zerg Defiler.
			/// \see Unit::getPlagueTimer
			/// </summary>
			property bool IsPlagued { bool get(); }

			/// <summary>
			/// Returns true if the unit is a Terran SCV that is repairing or moving to repair another unit
			/// </summary>
			property bool IsRepairing { bool get(); }

			/// <summary>
			/// Returns true if the unit is a building that is researching tech. See TechTypes for the complete list of available techs in Broodwar.
			/// \see Unit::research, Unit::cancelResearch, Unit::getTech, Unit::getRemainingResearchTime
			/// </summary>
			property bool IsResearching { bool get(); }

			/// <summary>
			/// Returns true if the unit has been selected by the user via the starcraft GUI. Only available if you enable Flag::UserInput during AIModule::onStart.
			/// \see Game::getSelectedUnits
			/// </summary>
			property bool IsSelected { bool get(); }

			/// <summary>
			/// Returns true if the unit is a Terran Siege Tank that is currently in Siege mode.
			/// \see Unit::siege, Unit::unsiege
			/// </summary>
			property bool IsSieged { bool get(); }

			/// <summary>
			/// Returns true if the unit is starting to attack.
			/// \see Unit::attackUnit, Unit::getGroundWeaponCooldown, Unit::getAirWeaponCooldown
			/// </summary>
			property bool IsStartingAttack { bool get(); }

			/// <summary>
			/// Returns true if the unit has been stasised by a Protoss Arbiter.
			/// \see Unit::getStasisTimer
			/// </summary>
			property bool IsStasised { bool get(); }

			/// <summary>
			/// Returns true if the unit is currently stimmed.
			/// \see Unit::getStimTimer
			/// </summary>
			property bool IsStimmed { bool get(); }

			/// <summary>
			/// Returns true if the unit is being pushed off of another unit
			/// </summary>
			property bool IsStuck { bool get(); }

			/// <summary>
			/// Returns true if the unit is training units (i.e. a Barracks training Marines).
			/// \see Unit::train, Unit::getTrainingQueue, Unit::cancelTrain, Unit::getRemainingTrainTime
			/// </summary>
			property bool IsTraining { bool get(); }

			/// <summary>
			/// Returns true if the unit was recently attacked
			/// </summary>
			property bool IsUnderAttack { bool get(); }

			/// <summary>
			/// Returns true if the unit is under a Dark Swarm
			/// </summary>
			property bool IsUnderDarkSwarm { bool get(); }

			/// <summary>
			/// Returns true if the unit is under a Disruption Web
			/// </summary>
			property bool IsUnderDisruptionWeb { bool get(); }

			/// <summary>
			/// Returns true if the unit is under a Protoss Psionic Storm
			/// </summary>
			property bool IsUnderStorm { bool get(); }

			/// <summary>
			/// Returns true if the unit is a Protoss building that is unpowered because no pylons are in range
			/// </summary>
			property bool IsPowered { bool get(); }

			/// <summary>
			/// Returns true if the unit is a building that is upgrading. See UpgradeTypes for the complete list of available upgrades in Broodwar.
			/// \see Unit::upgrade, Unit::cancelUpgrade, Unit::getUpgrade, Unit::getRemainingUpgradeTime
			/// </summary>
			property bool IsUpgrading { bool get(); }

			/// <summary>
			/// Returns true if the unit is visible. If the CompleteMapInformation?  cheat flag is enabled, existing units hidden by the fog of war will be
			/// accessible, but isVisible will still return false.
			/// \see Unit::exists
			/// </summary>
			bool IsVisible();

			/// <summary>
			/// Returns true if the unit is visible. If the CompleteMapInformation?  cheat flag is enabled, existing units hidden by the fog of war will be
			/// accessible, but isVisible will still return false.
			/// \see Unit::exists
			/// </summary>
			bool IsVisible(Api::Player^ player);

			/// <summary>
			/// Returns true if the unit is able to execute the given command, or false if there is an error
			/// </summary>
			bool CanIssueCommand(Api::UnitCommand^ command);

			/// <summary>
			/// Issues the give unit command, or returns false if there is an error
			/// </summary>
			bool IssueCommand(Api::UnitCommand^ command);

			/// <summary>
			/// Orders the unit to attack move to the specified location
			/// </summary>
			bool Attack(Api::Position^ target, bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to attack the specified unit
			/// </summary>
			bool Attack(Api::Unit^ target, bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to build the given unit type at the given position. Note that if the player does not have enough resources when the unit attempts
			/// to place the building down, the order will fail. The tile position specifies where the top left corner of the building will be placed
			/// </summary>
            bool Build(Api::Enum::UnitType type, Api::TilePosition^ target);

			/// <summary>
			/// Orders the unit to build the given addon. The unit must be a Terran building that can have an addon and the specified unit type must be an addon unit type
			/// </summary>
			bool BuildAddon(Api::UnitType^ type);

			/// <summary>
			/// Orders this unit to add the specified unit type to the training queue. Note that the player must have sufficient resources to train. If you wish to make
			/// units from a hatchery, use getLarva to get the larva associated with the hatchery and then call morph on the larva you want to morph. This command can also
			/// be used to make interceptors and scarabs
			/// </summary>
			bool Train(Api::Enum::UnitType type);

			/// <summary>
			/// Orders the unit to morph into the specified unit type. Returns false if given a wrong type.
			/// \see Unit::cancelMorph, Unit::isMorphing
			/// </summary>
			bool Morph(Api::Enum::UnitType type);

			/// <summary>
			/// Orders the unit to research the given tech type.
			/// \see Unit::cancelResearch, Unit::Unit#isResearching, Unit::getRemainingResearchTime, Unit::getTech
			/// </summary>
			bool Research(Api::Tech^ tech);

			/// <summary>
			/// Orders the unit to upgrade the given upgrade type.
			/// \see Unit::cancelUpgrade, Unit::Unit#isUpgrading, Unit::getRemainingUpgradeTime, Unit::getUpgrade
			/// </summary>
			bool PerformUpgrade(Api::Upgrade^ upgrade);

			/// <summary>
			/// Orders the unit to set its rally position to the specified position.
			/// \see Unit::getRallyPosition, Unit::getRallyUnit
			/// </summary>
			bool SetRallyPoint(Api::Position^ target);

			/// <summary>
			/// Orders the unit to set its rally unit to the specified unit.
			/// \see Unit::setRallyPosition, Unit::getRallyPosition, Unit::getRallyUnit
			/// </summary>
			bool SetRallyPoint(Api::Unit^ target);

			/// <summary>
			/// Orders the unit to move from its current position to the specified position.
			/// \see Unit::isMoving. 
			/// </summary>
			bool Move(Api::Position^ target, bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to patrol between its current position and the specified position.
			/// \see Unit::isPatrolling. 
			/// </summary>
			bool Patrol(Api::Position^ target, bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to hold its position
			/// </summary>
			bool HoldPosition(bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to stop
			/// </summary>
			bool Stop(bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to follow the specified unit.
			/// \see Unit::isFollowing
			/// </summary>
			bool Follow(Api::Unit^ target, bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to gather the specified unit (must be mineral or refinery type).
			/// \see Unit::isGatheringGas, Unit::isGatheringMinerals
			/// </summary>
			bool Gather(Api::Unit^ target, bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to return its cargo to a nearby resource depot such as a Command Center. Only workers that are carrying minerals or gas
			/// can be ordered to return cargo.
			/// \see Unit::isCarryingGas, Unit::isCarryingMinerals
			/// </summary>
			bool ReturnCargo(bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to repair the specified unit. Only Terran SCVs can be ordered to repair, and the target must be a mechanical Terran unit or building.
			/// \see Unit::isRepairing
			/// </summary>
			bool Repair(Api::Unit^ target, bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to burrow. Either the unit must be a Zerg Lurker, or the unit must be a Zerg ground unit and burrow tech must be researched.
			/// \see: Unit::unburrow, Unit::isBurrowed
			/// </summary>
			bool Burrow();

			/// <summary>
			/// Orders the burrowed unit to unburrow.
			/// \see: Unit::burrow, Unit::isBurrowed.
			/// </summary>
			bool Unburrow();

			/// <summary>
			/// Orders the unit to cloak.
			/// \see: Unit::decloak, Unit::isCloaked
			/// </summary>
			bool Cloak();

			/// <summary>
			/// Orders the unit to decloak.
			/// \see: Unit::cloak, Unit::isCloaked
			/// </summary>
			bool Decloak();

			/// <summary>
			/// Orders the unit to siege. Note: unit must be a Terran siege tank.
			/// \see Unit::unsiege, Unit::isSieged
			/// </summary>
			bool Siege();

			/// <summary>
			/// Orders the unit to unsiege. Note: unit must be a Terran siege tank.
			/// \see: Unit::unsiege, Unit::isSieged
			/// </summary>
			bool Unsiege();

			/// <summary>
			/// Orders the unit to lift. Note: unit must be a Terran building that can be lifted.
			/// \see Unit::land, Unit::isLifted. 
			/// </summary>
			bool Lift();

			/// <summary>
			/// Orders the unit to land. Note: unit must be a Terran building that is currently lifted.
			/// \see Unit::lift, Unit::isLifted
			/// </summary>
			bool Land(Api::TilePosition^ target);

			/// <summary>
			/// Orders the unit to load the target unit.
			/// \see Unit::unload, Unit::unloadAll, Unit::getLoadedUnits, Unit:isLoaded
			/// </summary>
			bool Load(Api::Unit^ target, bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to unload the target unit.
			/// \see Unit::load, Unit::unloadAll, Unit::getLoadedUnits, Unit:isLoaded
			/// </summary>
			bool Unload(Api::Unit^ target);

			/// <summary>
			/// Orders the unit to unload all loaded units at the unit's current position.
			/// \see Unit::load, Unit::unload, Unit::unloadAll, Unit::getLoadedUnits, Unit:isLoaded
			/// </summary>
			bool UnloadAll(bool shiftQueueCommand);

			/// <summary>
			/// Orders the unit to unload all loaded units at the specified location. Unit should be a Terran Dropship, Protoss Shuttle, or Zerg Overlord. If the
			/// unit is a Terran Bunker, the units will be unloaded right outside the bunker, like in the first version of unloadAll.
			/// \see Unit::load, Unit::unload, Unit::unloadAll, Unit::getLoadedUnits, Unit:isLoaded
			/// </summary>
			bool UnloadAll(Api::Position^ target, bool shiftQueueCommand);

			/// <summary>
			/// Works like the right click in the GUI
			/// </summary>
			bool RightClick(Api::Position^ target, bool shiftQueueCommand);

			/// <summary>
			/// Works like the right click in the GUI. Right click on a mineral patch to order a worker to mine, right click on an enemy to attack it
			/// </summary>
			bool RightClick(Api::Unit^ target, bool shiftQueueCommand);

			/// <summary>
			/// Orders the SCV to stop constructing the building, and the building is left in a partially complete state until it is canceled, destroyed, or completed.
			/// \see Unit::isConstructing
			/// </summary>
			bool HaltConstruction();

			/// <summary>
			/// Orders the building to stop being constructed.
			/// \see Unit::beingConstructed
			/// </summary>
			bool CancelConstruction();

			/// <summary>
			/// Orders the unit to stop making the addon
			/// </summary>
			bool CancelAddon();

			/// <summary>
			/// Orders the unit to remove the specified unit from its training queue.
			/// \see Unit::train, Unit::cancelTrain, Unit::isTraining, Unit::getTrainingQueue
			/// </summary>
			bool CancelTrain(int slot);

			/// <summary>
			/// Orders the unit to stop morphing.
			/// \see Unit::morph, Unit::isMorphing
			/// </summary>
			bool CancelMorph();

			/// <summary>
			/// Orders the unit to cancel a research in progress.
			/// \see Unit::research, Unit::isResearching, Unit::getTech
			/// </summary>
			bool CancelResearch();

			/// <summary>
			/// Orders the unit to cancel an upgrade in progress.
			/// \see Unit::upgrade, Unit::isUpgrading, Unit::getUpgrade
			/// </summary>
			bool CancelUpgrade();

			/// <summary>
			/// Orders the unit to use a tech not requiring a target (ie Stim Pack). Returns true if it is a valid tech
			/// </summary>
			bool UseTech(Api::Tech^ tech);

			/// <summary>
			/// Orders the unit to use a tech requiring a position target (ie Dark Swarm). Returns true if it is a valid tech
			/// </summary>
			bool UseTech(Api::Tech^ tech, Api::Position^ target);

			/// <summary>
			/// Orders the unit to use a tech requiring a unit target (ie Irradiate). Returns true if it is a valid tech
			/// </summary>
			bool UseTech(Api::Tech^ tech, Api::Unit^ target);

			/// <summary>
			/// Moves a Flag Beacon to the target location
			/// </summary>
			bool PlaceCop(Api::TilePosition^ target);

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(Unit^ other);

			static bool operator == (Unit^ first, Unit^ second);
			static bool operator != (Unit^ first, Unit^ second);
		};

		Api::Unit^ ConvertUnit(BWAPI::Unit unit);
		BWAPI::Unit ConvertUnit(Api::Unit^ unit);
	}
}