namespace BroodwarFSharp

open Position

type Gm = BroodWar.Api.Game
type Ut = BroodWar.Api.Unit

[<Sealed>]
type Unit(ut:Ut) =
    // Cache the position of the unit - it may be used extensively
    let mutable _Frame = Gm.FrameCount
    let mutable _Position = Position.apiToPixel ut.Position
    let mutable _LastKnownFrame = _Frame
    let mutable _LastKnownPosition = _Position
    let mutable _LastKnownUnitType = ut.UnitType
    let mutable _LastKnownPlayer = ut.Player
    let renewUnit () =
        if _Frame <> Gm.FrameCount then
            _Frame <- Gm.FrameCount
            _Position <- Position.apiToPixel ut.Position
            if _Position <> Position.unknownPixel then
                _LastKnownFrame <- _Frame
                _LastKnownPosition <- _Position
                _LastKnownUnitType <- ut.UnitType
                _LastKnownPlayer <- ut.Player
        
    static let unitTable = new System.Collections.Generic.Dictionary<int, Unit>()
    static member NewGame() = unitTable.Clear()

    /// <summary>
    /// Wraps a unit object
    /// </summary>
    static member convert (ut:Ut) =
        match unitTable.TryGetValue ut.Id with
        | true, unit when unit.Id = ut.Id -> unit
        | _ ->
            let unit = new Unit(ut)
            unitTable.[ut.Id] <- unit
            unit
    static member tryConvert (ut:Ut) =
        if ut = null then None
        else Some (Unit.convert ut)
    static member seenUnits = unitTable.Values |> Array.ofSeq

    static member notifyUnitDestroyed (ut:Ut) = unitTable.Remove ut.Id |> ignore

    static member (|~|) (unit1:Unit, unit2:Unit) = unit1.Position |~| unit2.Position

    member private unit.Unit = ut

    /// <summary>
    /// Returns a unique ID for this unit. It simply casts the unit's address in Broodwar as an integer, since each unit has a unique address
    /// </summary>
    member unit.Id = ut.Id

    /// <summary>
    /// Returns the unit ID that is used in a replay (*.rep) file's action recordings
    /// </summary>
    member unit.ReplayId = ut.ReplayId

    /// <summary>
    /// Returns the player that owns this unit
    /// </summary>
    member unit.Player = ut.Player

    /// <summary>
    /// Returns the current type of the unit
    /// </summary>
    member unit.UnitType = ut.UnitType

    /// <summary>
    /// Returns the position of the unit on the map
    /// </summary>
    member unit.Position =
        renewUnit ()
        _Position

    /// <summary>
    /// Returns the last known position of the unit on the map, if any
    /// </summary>
    member unit.LastKnownPosition =
        renewUnit ()
        _LastKnownPosition

    /// <summary>
    /// Returns the last known frame for a unit
    /// </summary>
    member unit.LastKnownFrame =
        renewUnit ()
        _LastKnownFrame

    /// <summary>
    /// Returns the last known type for a unit
    /// </summary>
    member unit.LastKnownUnitType =
        renewUnit ()
        _LastKnownUnitType

    /// <summary>
    /// Returns the last known player for a unit
    /// </summary>
    member unit.LastKnownPlayer =
        renewUnit ()
        _LastKnownPlayer

    /// <summary>
    /// Returns the build tile position of the unit on the map. Useful if the unit is a building. The tile position is of the top left corner of the building
    /// </summary>
    member unit.TilePosition = Position.apiToTile ut.TilePosition

    /// <summary>
    /// Returns the direction the unit is facing, measured in radians. An angle of 0 means the unit is facing east
    /// </summary>
    member unit.Angle = ut.Angle

    /// <summary>
    /// Returns the x component of the unit's velocity, measured in pixels per frame
    /// </summary>
    member unit.VelocityX = ut.VelocityX * 1.<pixel/frame>

    /// <summary>
    /// Returns the y component of the unit's velocity, measured in pixels per frame
    /// </summary>
    member unit.VelocityY = ut.VelocityY * 1.<pixel/frame>

//    /// <summary>
//    /// Returns the region that this unit is currently in
//    /// </summary>
//    member unit.Region = ut.Region

    /// <summary>
    /// Returns the X coordinate of the left side of the unit
    /// </summary>
    member unit.Left = ut.Left * 1<pixel>

    /// <summary>
    /// Returns the Y coordinate of the top side of the unit
    /// </summary>
    member unit.Top = ut.Top * 1<pixel>

    /// <summary>
    /// Returns the X coordinate of the right side of the unit
    /// </summary>
    member unit.Right = ut.Right * 1<pixel>

    /// <summary>
    /// Returns the Y coordinate of the bottom side of the unit
    /// </summary>
    member unit.Bottom = ut.Bottom * 1<pixel>

    /// <summary>
    /// Returns the position of the top left and the bottom right corner of the unit
    /// </summary>
    member unit.Rectangle = Pos (ut.Left * 1<pixel>, ut.Top * 1<pixel>), Pos (ut.Right * 1<pixel>, ut.Bottom * 1<pixel>)

    /// <summary>
    /// Returns the unit's current amount of hit points
    /// </summary>
    member unit.HitPoints = ut.HitPoints

    /// <summary>
    /// Returns the unit's current amount of shields
    /// </summary>
    member unit.Shields = ut.Shields

    /// <summary>
    /// Returns the unit's current amount of energy
    /// </summary>
    member unit.Energy = ut.Energy

    /// <summary>
    /// Returns the unit's current amount of containing resources. Useful for determining how much minerals are left in a mineral patch,
    /// or how much gas is left in a geyser (can also be called on a refinery/assimilator/extractor)
    /// </summary>
    member unit.Resources = ut.Resources

    /// <summary>
    /// Retrieves the group ID of a resource. Can be used to identify which resources belong to an expansion
    /// </summary>
    member unit.ResourceGroup = ut.ResourceGroup

    /// <summary>
    /// Returns the frame of the last successful command. Frame is comparable to Game::getFrameCount()
    /// </summary>
    member unit.LastCommandFrame = ut.LastCommandFrame

    /// <summary>
    /// Returns the last successful command
    /// </summary>
    member unit.LastCommand = ut.LastCommand

    /// <summary>
    /// Returns the player that last attacked this unit
    /// </summary>
    member unit.LastAttackingPlayer = ut.LastAttackingPlayer

    /// <summary>
    /// Returns the initial type of the unit or Unknown if it wasn't a neutral unit at the beginning of the game
    /// </summary>
    member unit.InitialType = ut.InitialType

    /// <summary>
    /// Returns the initial position of the unit on the map, or Positions::Unknown if the unit wasn't a neutral unit at the beginning of the game
    /// </summary>
    member unit.InitialPosition = Position.apiToPixel ut.InitialPosition

    /// <summary>
    /// Returns the initial build tile position of the unit on the map, or TilePositions::Unknown if the unit wasn't a neutral unit at the
    /// beginning of the game. The tile position is of the top left corner of the building
    /// </summary>
    member unit.InitialTilePosition = Position.apiToTile ut.InitialTilePosition

    /// <summary>
    /// Returns the unit's initial amount of hit points, or 0 if it wasn't a neutral unit at the beginning of the game
    /// </summary>
    member unit.InitialHitPoints = ut.InitialHitPoints

    /// <summary>
    /// Returns the unit's initial amount of containing resources, or 0 if the unit wasn't a neutral unit at the beginning of the game
    /// </summary>
    member unit.InitialResources = ut.InitialResources

    /// <summary>
    /// Returns the unit's current kill count
    /// </summary>
    member unit.KillCount = ut.KillCount

    /// <summary>
    /// Returns the unit's acid spore count
    /// </summary>
    member unit.AcidSporeCount = ut.AcidSporeCount

    /// <summary>
    /// Returns the number of interceptors the Protoss Carrier has
    /// </summary>
    member unit.InterceptorCount = ut.InterceptorCount

    /// <summary>
    /// Returns the number of scarabs in the Protoss Reaver
    /// </summary>
    member unit.ScarabCount = ut.ScarabCount

    /// <summary>
    /// Returns the number of spider mines in the Terran Vulture
    /// </summary>
    member unit.SpiderMineCount = ut.SpiderMineCount

    /// <summary>
    /// Returns unit's ground weapon cooldown. It is 0 if the unit is ready to attack
    /// </summary>
    member unit.GroundWeaponCooldown = ut.GroundWeaponCooldown

    /// <summary>
    /// Returns unit's air weapon cooldown. It is 0 if the unit is ready to attack
    /// </summary>
    member unit.AirWeaponCooldown = ut.AirWeaponCooldown

    /// <summary>
    /// Returns unit's ground weapon cooldown. It is 0 if the unit is ready cast a spell
    /// </summary>
    member unit.SpellCooldown = ut.SpellCooldown

    /// <summary>
    /// Returns the remaining hit points of the defense matrix. Initially a defense Matrix has 250 points see Unit::getDefenseMatrixTimer, Unit::isDefenseMatrixed
    /// </summary>
    member unit.DefenseMatrixPoints = ut.DefenseMatrixPoints

    /// <summary>
    /// Returns the time until the defense matrix wears off. 0 -> No defense Matrix present
    /// </summary>
    member unit.DefenseMatrixTimer = ut.DefenseMatrixTimer

    /// <summary>
    /// Returns the time until the ensnare effect wears off. 0 -> No ensnare effect present
    /// </summary>
    member unit.EnsnareTimer = ut.EnsnareTimer

    /// <summary>
    /// Returns the time until the radiation wears off. 0 -> No radiation present
    /// </summary>
    member unit.IrradiateTimer = ut.IrradiateTimer

    /// <summary>
    /// Returns the time until the lockdown wears off. 0 -> No lockdown present
    /// </summary>
    member unit.LockdownTimer = ut.LockdownTimer

    /// <summary>
    /// Returns the time until the maelstrom wears off. 0 -> No maelstrom present
    /// </summary>
    member unit.MaelstromTimer = ut.MaelstromTimer

    /// <summary>
    /// Returns the value of an internal timer specific to the primary order.
    /// </summary>
    member unit.OrderTimer = ut.OrderTimer

    /// <summary>
    /// Returns the time until the plague wears off. 0 -> No plague present
    /// </summary>
    member unit.PlagueTimer = ut.PlagueTimer

    /// <summary>
    /// Returns the amount of time until the unit is removed, or 0 if the unit does not have a remove timer. Used to determine how much
    /// time remains before hallucinated units, dark swarm, etc have until they are removed
    /// </summary>
    member unit.RemoveTimer = ut.RemoveTimer

    /// <summary>
    /// Returns the time until the stasis field wears off. 0 -> No stasis field present
    /// </summary>
    member unit.StasisTimer = ut.StasisTimer

    /// <summary>
    /// Returns the time until the stimpack wears off. 0 -> No stimpack boost present
    /// </summary>
    member unit.StimTimer = ut.StimTimer

    /// <summary>
    /// Returns the building type a worker is about to construct. If the unit is a morphing Zerg unit or an incomplete building,
    /// this returns the UnitType the unit is about to become upon completion
    /// </summary>
    member unit.BuildType = ut.BuildType

    /// <summary>
    /// Returns the list of units queued up to be trained. \see Unit::train, Unit::cancelTrain, Unit::isTraining
    /// </summary>
    member unit.TrainingQueue = ut.TrainingQueue

    /// <summary>
    /// Returns the tech that the unit is currently researching. If the unit is not researching anything, TechTypes::None is returned.
    /// \see Unit::research, Unit::cancelResearch, Unit::isResearching, Unit::getRemainingResearchTime
    /// </summary>
    member unit.Tech = ut.Tech

    /// <summary>
    /// Returns the upgrade that the unit is currently upgrading. If the unit is not upgrading anything, UpgradeTypes::None is returned.
    /// \see Unit::upgrade, Unit::cancelUpgrade, Unit::isUpgrading, Unit::getRemainingUpgradeTime
    /// </summary>
    member unit.Upgrade = ut.Upgrade

    /// <summary>
    /// Returns the remaining build time of a unit/building that is being constructed
    /// </summary>
    member unit.RemainingBuildTime = ut.RemainingBuildTime

    /// <summary>
    /// Returns the remaining time of the unit that is currently being trained. If the unit is a Hatchery, Lair, or Hive, this returns the amount
    /// of time until the next larva spawns, or 0 if the unit already has 3 larva
    /// </summary>
    member unit.RemainingTrainTime = ut.RemainingTrainTime

    /// <summary>
    /// Returns the amount of time until the unit is done researching its current tech. If the unit is not researching anything, 0 is returned.
    /// \see Unit::research, Unit::cancelResearch, Unit::isResearching, Unit::getTech
    /// </summary>
    member unit.RemainingResearchTime = ut.RemainingResearchTime

    /// <summary>
    /// Returns the amount of time until the unit is done upgrading its current upgrade. If the unit is not upgrading anything, 0 is returned.
    /// \see Unit::upgrade, Unit::cancelUpgrade, Unit::isUpgrading, Unit::getUpgrade
    /// </summary>
    member unit.RemainingUpgradeTime = ut.RemainingUpgradeTime

    /// <summary>
    /// If the unit is an SCV that is constructing a building, this will return the building it is constructing. If the unit is a Terran
    /// building that is being constructed, this will return the SCV that is constructing it
    /// </summary>
    member unit.BuildUnit = Unit.tryConvert ut.BuildUnit

    /// <summary>
    /// Generally returns the appropriate target unit after issuing an order that accepts a target unit (i.e. attack, repair, gather, follow, etc.).
    /// To check for a target that has been acquired automatically (without issuing an order) see getOrderTarget
    /// </summary>
    member unit.Target = Unit.tryConvert ut.Target

    /// <summary>
    /// Returns the target position the unit is moving to (provided a valid path to the target position exists)
    /// </summary>
    member unit.TargetPosition = Position.apiToPixel ut.TargetPosition

    /// <summary>
    /// Retrieves the primary Order that the unit is assigned. Primary orders are distinct actions such as Orders::AttackUnit and Orders::PlayerGuard.
    /// </summary>
    member unit.Order = ut.Order

    /// <summary>
    /// Retrieves the secondary Order that the unit is assigned. Secondary
    /// orders are run in the background as a sub-order. An example would be Orders::TrainFighter,
    /// because a @Carrier can move and train fighters at the same time.
    /// </summary>
    member unit.SecondaryOrder = ut.SecondaryOrder

    /// <summary>
    /// This is usually set when the low level unit AI acquires a new target automatically. For example if an enemy probe comes in range of your marine,
    /// the marine will start attacking it, and getOrderTarget will be set in this case, but not getTarget
    /// </summary>
    member unit.OrderTarget = Unit.tryConvert ut.OrderTarget

    /// <summary>
    /// Returns the target position for the units order. For example for the move order getTargetPosition returns the end of the units path but this returns
    /// the location the unit is trying to move to. 
    /// </summary>
    member unit.OrderTargetPosition = Position.apiToPixel ut.OrderTargetPosition

    /// <summary>
    /// Returns the position the building is rallied to. If the building does not produce units, Positions::None is returned.
    /// \see Unit::setRallyPoint, Unit::getRallyUnit
    /// </summary>
    member unit.RallyPosition = Position.apiToPixel ut.RallyPosition

    /// <summary>
    /// Returns the unit the building is rallied to. If the building is not rallied to any unit, None is returned.
    /// \see Unit::setRallyPoint, Unit::getRallyPosition
    /// </summary>
    member unit.RallyUnit = Unit.tryConvert ut.RallyUnit

    /// <summary>
    /// Returns the add-on of this unit, or None if the unit doesn't have an add-on
    /// </summary>
    member unit.Addon = Unit.tryConvert ut.Addon

    /// <summary>
    /// Returns the corresponding connected nydus canal of this unit, or None if the unit does not have a connected nydus canal
    /// </summary>
    member unit.NydusExit = Unit.tryConvert ut.NydusExit

    /// <summary>
    /// Returns the power up the unit is holding, or None if the unit is not holding a power up
    /// </summary>
    member unit.PowerUp = Unit.tryConvert ut.PowerUp

    /// <summary>
    /// Returns the dropship, shuttle, overlord, or bunker that is this unit is loaded in to
    /// </summary>
    member unit.Transport = Unit.tryConvert ut.Transport

    /// <summary>
    /// Returns a list of the units loaded into a Terran Bunker, Terran Dropship, Protoss Shuttle, or Zerg Overlord
    /// </summary>
    member unit.LoadedUnits = Seq.map Unit.convert ut.LoadedUnits |> Array.ofSeq

    /// <summary>
    /// For Protoss Interceptors, this returns the Carrier unit this Interceptor is controlled by. For all other unit types this function returns None
    /// </summary>
    member unit.Carrier = Unit.tryConvert ut.Carrier

    /// <summary>
    /// Returns the set of interceptors controlled by this unit. If the unit has no interceptors, or is not a Carrier, this function returns an empty set
    /// </summary>
    member unit.Interceptors = Seq.map Unit.convert ut.Interceptors |> Array.ofSeq

    /// <summary>
    /// For Zerg Larva, this returns the Hatchery, Lair, or Hive unit this Larva was spawned from. For all other unit types this function returns None
    /// </summary>
    member unit.Hatchery = Unit.tryConvert ut.Hatchery

    /// <summary>
    /// Returns the set of larva spawned by this unit. If the unit has no larva, or is not a Hatchery, Lair, or Hive, this function returns an empty set.
    /// Equivalent to clicking "Select Larva" from the Starcraft GUI
    /// </summary>
    member unit.Larva = Seq.map Unit.convert ut.Larva |> Array.ofSeq

    /// <summary>
    /// Returns the set of units within the given radius of this unit
    /// </summary>
    member unit.isUnitInRadius radius = ((|~~|) unit.Rectangle) >> ((>=) radius)

    /// <summary>
    /// 3 cases to consider:
    /// - If exists() returns true, the unit exists.
    /// - If exists() returns false and the unit is owned by self(), then the unit does not exist.
    /// - If exists() returns false and the unit is not owned by self(), then the unit may or may not exist.
    /// 
    /// \see Unit::isVisible.
    /// </summary>
    member unit.Exists = ut.Exists

    /// <summary>
    /// Returns true if the Nuclear Missile Silo has a nuke
    /// </summary>
    member unit.HasNuke = ut.HasNuke

    /// <summary>
    /// Returns true if the unit is currently accelerating
    /// </summary>
    member unit.IsAccelerating = ut.IsAccelerating

    /// <summary>
    /// Returns true if the unit is currently attacking something
    /// </summary>
    member unit.IsAttacking = ut.IsAttacking

    /// <summary>
    /// Returns true if the unit is currently displaying the attack animation - could possibly be interrupted
    /// </summary>
    member unit.IsAttackFrame = ut.IsAttackFrame

    /// <summary>
    /// Returns true if the unit is being constructed. Always true for incomplete Protoss and Zerg buildings, and true for incomplete Terran
    /// buildings that have an SCV constructing them. If the SCV halts construction, isBeingConstructed will return false.
    /// \see Unit::build, Unit::cancelConstruction, Unit::haltConstruction, Unit::isConstructing
    /// </summary>
    member unit.IsBeingConstructed = ut.IsBeingConstructed

    /// <summary>
    /// Returns true if the unit is a mineral patch or refinery that is being gathered
    /// </summary>
    member unit.IsBeingGathered = ut.IsBeingGathered

    /// <summary>
    /// Returns true if the unit is currently being healed by a Terran Medic, or repaired by a Terran SCV
    /// </summary>
    member unit.IsBeingHealed = ut.IsBeingHealed

    /// <summary>
    /// Returns true if the unit is currently blind from a Medic's Optical Flare
    /// </summary>
    member unit.IsBlind = ut.IsBlind

    /// <summary>
    /// Returns true if the unit is currently braking/slowing down
    /// </summary>
    member unit.IsBraking = ut.IsBraking

    /// <summary>
    /// Returns true if the unit is a Zerg unit that is current burrowed.
    /// \see Unit::burrow, Unit::unburrow
    /// </summary>
    member unit.IsBurrowed = ut.IsBurrowed

    /// <summary>
    /// Returns true if the unit is a worker that is carrying gas.
    /// \see Unit::returnCargo, Unit::isGatheringGas
    /// </summary>
    member unit.IsCarryingGas = ut.IsCarryingGas

    /// <summary>
    /// Returns true if the unit is a worker that is carrying minerals.
    /// \see Unit::returnCargo, Unit::isGatheringMinerals
    /// </summary>
    member unit.IsCarryingMinerals = ut.IsCarryingMinerals

    /// <summary>
    /// Returns true if the unit is cloaked.
    /// \see Unit::cloak, Unit::decloak
    /// </summary>
    member unit.IsCloaked = ut.IsCloaked

    /// <summary>
    /// Returns true if the unit has been completed
    /// </summary>
    member unit.IsCompleted = ut.IsCompleted

    /// <summary>
    /// Returns true when a unit has been issued an order to build a structure and is moving to the build location. Also returns true for Terran
    /// SCVs while they construct a building.
    /// \see Unit::build, Unit::cancelConstruction, Unit::haltConstruction, Unit::isBeingConstructed
    /// </summary>
    member unit.IsConstructing = ut.IsConstructing

    /// <summary>
    /// Returns true if the unit has a defense matrix from a Terran Science Vessel
    /// </summary>
    member unit.IsDefenseMatrixed = ut.IsDefenseMatrixed

    /// <summary>
    /// Returns true if the unit is detected
    /// </summary>
    member unit.IsDetected = ut.IsDetected

    /// <summary>
    /// Returns true if the unit has been ensnared by a Zerg Queen
    /// </summary>
    member unit.IsEnsnared = ut.IsEnsnared

    /// <summary>
    /// Returns true if the unit is following another unit.
    /// \see Unit::follow, Unit::getTarget
    /// </summary>
    member unit.IsFollowing = ut.IsFollowing

    /// <summary>
    /// Returns true if the unit is in one of the four states for gathering gas (MoveToGas, WaitForGas, HarvestGas, ReturnGas).
    /// \see Unit::isCarryingGas
    /// </summary>
    member unit.IsGatheringGas = ut.IsGatheringGas

    /// <summary>
    /// Returns true if the unit is in one of the four states for gathering minerals (MoveToMinerals, WaitForMinerals, MiningMinerals, ReturnMinerals).
    /// \see Unit::isCarryingMinerals
    /// </summary>
    member unit.IsGatheringMinerals = ut.IsGatheringMinerals

    /// <summary>
    /// Returns true for hallucinated units, false for normal units. Returns true for hallucinated enemy units only if Complete Map Information is enabled.
    /// \see Unit::getRemoveTimer
    /// </summary>
    member unit.IsHallucination = ut.IsHallucination

    /// <summary>
    /// Returns true if the unit is holding position
    /// \see Unit::holdPosition
    /// </summary>
    member unit.IsHoldingPosition = ut.IsHoldingPosition

    /// <summary>
    /// Returns true if the unit is not doing anything.
    /// \see Unit::stop
    /// </summary>
    member unit.IsIdle = ut.IsIdle

    /// <summary>
    /// Returns true if the unit can be interrupted
    /// </summary>
    member unit.IsInterruptible = ut.IsInterruptible

    /// <summary>
    /// Returns true if the unit is invincible
    /// </summary>
    member unit.IsInvincible = ut.IsInvincible

    /// <summary>
    /// Returns true if the unit can attack a specified target from its current position
    /// </summary>
    member unit.IsInWeaponRange(target) = ut.IsInWeaponRange(target)

    /// <summary>
    /// Returns true if the unit is being irradiated by a Terran Science Vessel.
    /// \see Unit::getIrradiateTimer
    /// </summary>
    member unit.IsIrradiated = ut.IsIrradiated

    /// <summary>
    /// Returns true if the unit is a Terran building that is currently lifted off the ground.
    /// \see Unit::lift,Unit::land
    /// </summary>
    member unit.IsLifted = ut.IsLifted

    /// <summary>
    /// Return true if the unit is loaded into a Terran Bunker, Terran Dropship, Protoss Shuttle, or Zerg Overlord.
    /// \see Unit::load, Unit::unload, Unit::unloadAll
    /// </summary>
    member unit.IsLoaded = ut.IsLoaded

    /// <summary>
    /// Returns true if the unit is locked down by a Terran Ghost.
    /// \see Unit::getLockdownTimer
    /// </summary>
    member unit.IsLockedDown = ut.IsLockedDown

    /// <summary>
    /// Returns true if the unit is being maelstrommed.
    /// \see Unit::getMaelstromTimer
    /// </summary>
    member unit.IsMaelstrommed = ut.IsMaelstrommed

    /// <summary>
    /// Returns true if the unit is a zerg unit that is morphing.
    /// \see Unit::morph, Unit::cancelMorph, Unit::getBuildType, Unit::getRemainingBuildTime
    /// </summary>
    member unit.IsMorphing = ut.IsMorphing

    /// <summary>
    /// Returns true if the unit is moving.
    /// \see Unit::attack, Unit::stop
    /// </summary>
    member unit.IsMoving = ut.IsMoving

    /// <summary>
    /// Returns true if the unit has been parasited by some other player
    /// </summary>
    member unit.IsParasited = ut.IsParasited

    /// <summary>
    /// Returns true if the unit is patrolling between two positions.
    /// \see Unit::patrol
    /// </summary>
    member unit.IsPatrolling = ut.IsPatrolling

    /// <summary>
    /// Returns true if the unit has been plagued by a Zerg Defiler.
    /// \see Unit::getPlagueTimer
    /// </summary>
    member unit.IsPlagued = ut.IsPlagued

    /// <summary>
    /// Returns true if the unit is a Terran SCV that is repairing or moving to repair another unit
    /// </summary>
    member unit.IsRepairing = ut.IsRepairing

    /// <summary>
    /// Returns true if the unit is a building that is researching tech. See TechTypes for the complete list of available techs in Broodwar.
    /// \see Unit::research, Unit::cancelResearch, Unit::getTech, Unit::getRemainingResearchTime
    /// </summary>
    member unit.IsResearching = ut.IsResearching

    /// <summary>
    /// Returns true if the unit has been selected by the user via the starcraft GUI. Only available if you enable Flag::UserInput during AIModule::onStart.
    /// \see Game::getSelectedUnits
    /// </summary>
    member unit.IsSelected = ut.IsSelected

    /// <summary>
    /// Returns true if the unit is a Terran Siege Tank that is currently in Siege mode.
    /// \see Unit::siege, Unit::unsiege
    /// </summary>
    member unit.IsSieged = ut.IsSieged

    /// <summary>
    /// Returns true if the unit is starting to attack.
    /// \see Unit::attackUnit, Unit::getGroundWeaponCooldown, Unit::getAirWeaponCooldown
    /// </summary>
    member unit.IsStartingAttack = ut.IsStartingAttack

    /// <summary>
    /// Returns true if the unit has been stasised by a Protoss Arbiter.
    /// \see Unit::getStasisTimer
    /// </summary>
    member unit.IsStasised = ut.IsStasised

    /// <summary>
    /// Returns true if the unit is currently stimmed.
    /// \see Unit::getStimTimer
    /// </summary>
    member unit.IsStimmed = ut.IsStimmed

    /// <summary>
    /// Returns true if the unit is being pushed off of another unit
    /// </summary>
    member unit.IsStuck = ut.IsStuck

    /// <summary>
    /// Returns true if the unit is training units (i.e. a Barracks training Marines).
    /// \see Unit::train, Unit::getTrainingQueue, Unit::cancelTrain, Unit::getRemainingTrainTime
    /// </summary>
    member unit.IsTraining = ut.IsTraining

    /// <summary>
    /// Returns true if the unit was recently attacked
    /// </summary>
    member unit.IsUnderAttack = ut.IsUnderAttack

    /// <summary>
    /// Returns true if the unit is under a Dark Swarm
    /// </summary>
    member unit.IsUnderDarkSwarm = ut.IsUnderDarkSwarm

    /// <summary>
    /// Returns true if the unit is under a Disruption Web
    /// </summary>
    member unit.IsUnderDisruptionWeb = ut.IsUnderDisruptionWeb

    /// <summary>
    /// Returns true if the unit is under a Protoss Psionic Storm
    /// </summary>
    member unit.IsUnderStorm = ut.IsUnderStorm

    /// <summary>
    /// Returns true if the unit is a Protoss building that is unpowered because no pylons are in range
    /// </summary>
    member unit.IsPowered = ut.IsPowered

    /// <summary>
    /// Returns true if the unit is a building that is upgrading. See UpgradeTypes for the complete list of available upgrades in Broodwar.
    /// \see Unit::upgrade, Unit::cancelUpgrade, Unit::getUpgrade, Unit::getRemainingUpgradeTime
    /// </summary>
    member unit.IsUpgrading = ut.IsUpgrading

    /// <summary>
    /// Returns true if the unit is visible. If the CompleteMapInformation?  cheat flag is enabled, existing units hidden by the fog of war will be
    /// accessible, but isVisible will still return false.
    /// \see Unit::exists
    /// </summary>
    member unit.IsVisible() = ut.IsVisible()

    /// <summary>
    /// Returns true if the unit is visible to the specified player. If the CompleteMapInformation?  cheat flag is enabled, existing units hidden by the fog of war will be
    /// accessible, but isVisible will still return false.
    /// \see Unit::exists
    /// </summary>
    member unit.IsVisible(player) = ut.IsVisible(player)

    /// <summary>
    /// Returns true if the unit is able to execute the given command, or false if there is an error
    /// </summary>
    member unit.CanIssueCommand(command) = ut.CanIssueCommand(command)

    /// <summary>
    /// Issues the give unit command, or returns false if there is an error
    /// </summary>
    member unit.IssueCommand(command) = ut.IssueCommand(command)

    /// <summary>
    /// Orders the unit to attack move to the specified location
    /// </summary>
    member unit.Attack(target, shiftQueueCommand) = ut.Attack(Position.pixelToApi target, shiftQueueCommand)

    /// <summary>
    /// Orders the unit to attack the specified unit
    /// </summary>
    member unit.Attack(target:Unit, shiftQueueCommand) = ut.Attack(target.Unit, shiftQueueCommand)

    /// <summary>
    /// Orders the unit to build the given unit type at the given position. Note that if the player does not have enough resources when the unit attempts
    /// to place the building down, the order will fail. The tile position specifies where the top left corner of the building will be placed
    /// </summary>
    member unit.Build(unitType, target) = ut.Build(unitType, Position.tileToApi target)

    /// <summary>
    /// Orders the unit to build the given addon. The unit must be a Terran building that can have an addon and the specified unit type must be an addon unit type
    /// </summary>
    member unit.BuildAddon(unitType) = ut.BuildAddon(unitType)

    /// <summary>
    /// Orders this unit to add the specified unit type to the training queue. Note that the player must have sufficient resources to train. If you wish to make
    /// units from a hatchery, use Larva to get the larva associated with the hatchery and then call morph on the larva you want to morph. This command can also
    /// be used to make interceptors and scarabs
    /// </summary>
    member unit.Train(unitType) = ut.Train(unitType)

    /// <summary>
    /// Orders the unit to morph into the specified unit type. Returns false if given a wrong type.
    /// \see Unit::cancelMorph, Unit::isMorphing
    /// </summary>
    member unit.Morph(unitType) = ut.Morph(unitType)

    /// <summary>
    /// Orders the unit to research the given tech type.
    /// \see Unit::cancelResearch, Unit::Unit#isResearching, Unit::getRemainingResearchTime, Unit::getTech
    /// </summary>
    member unit.Research(tech) = ut.Research(tech)

    /// <summary>
    /// Orders the unit to upgrade the given upgrade type.
    /// \see Unit::cancelUpgrade, Unit::Unit#isUpgrading, Unit::getRemainingUpgradeTime, Unit::getUpgrade
    /// </summary>
    member unit.PerformUpgrade(upgrade) = ut.PerformUpgrade(upgrade)

    /// <summary>
    /// Orders the unit to set its rally position to the specified position.
    /// \see Unit::getRallyPosition, Unit::getRallyUnit
    /// </summary>
    member unit.SetRallyPoint(target) = ut.SetRallyPoint(Position.pixelToApi target)

    /// <summary>
    /// Orders the unit to set its rally unit to the specified unit.
    /// \see Unit::setRallyPosition, Unit::getRallyPosition, Unit::getRallyUnit
    /// </summary>
    member unit.SetRallyPoint(target:Unit) = ut.SetRallyPoint(target.Unit)

    /// <summary>
    /// Orders the unit to move from its current position to the specified position.
    /// \see Unit::isMoving. 
    /// </summary>
    member unit.Move(target, shiftQueueCommand) = ut.Move(Position.pixelToApi target, shiftQueueCommand)

    /// <summary>
    /// Orders the unit to patrol between its current position and the specified position.
    /// \see Unit::isPatrolling. 
    /// </summary>
    member unit.Patrol(target, shiftQueueCommand) = ut.Patrol(Position.pixelToApi target, shiftQueueCommand)

    /// <summary>
    /// Orders the unit to hold its position
    /// </summary>
    member unit.HoldPosition(shiftQueueCommand) = ut.HoldPosition(shiftQueueCommand)

    /// <summary>
    /// Orders the unit to stop
    /// </summary>
    member unit.Stop(shiftQueueCommand) = ut.Stop(shiftQueueCommand)

    /// <summary>
    /// Orders the unit to follow the specified unit.
    /// \see Unit::isFollowing
    /// </summary>
    member unit.Follow(target:Unit, shiftQueueCommand) = ut.Follow(target.Unit, shiftQueueCommand)

    /// <summary>
    /// Orders the unit to gather the specified unit (must be mineral or refinery type).
    /// \see Unit::isGatheringGas, Unit::isGatheringMinerals
    /// </summary>
    member unit.Gather(target:Unit, shiftQueueCommand) = ut.Gather(target.Unit, shiftQueueCommand)

    /// <summary>
    /// Orders the unit to return its cargo to a nearby resource depot such as a Command Center. Only workers that are carrying minerals or gas
    /// can be ordered to return cargo.
    /// \see Unit::isCarryingGas, Unit::isCarryingMinerals
    /// </summary>
    member unit.ReturnCargo(shiftQueueCommand) = ut.ReturnCargo(shiftQueueCommand)

    /// <summary>
    /// Orders the unit to repair the specified unit. Only Terran SCVs can be ordered to repair, and the target must be a mechanical Terran unit or building.
    /// \see Unit::isRepairing
    /// </summary>
    member unit.Repair(target:Unit, shiftQueueCommand) = ut.Repair(target.Unit, shiftQueueCommand)

    /// <summary>
    /// Orders the unit to burrow. Either the unit must be a Zerg Lurker, or the unit must be a Zerg ground unit and burrow tech must be researched.
    /// \see: Unit::unburrow, Unit::isBurrowed
    /// </summary>
    member unit.Burrow() = ut.Burrow()

    /// <summary>
    /// Orders the burrowed unit to unburrow.
    /// \see: Unit::burrow, Unit::isBurrowed.
    /// </summary>
    member unit.Unburrow() = ut.Unburrow()

    /// <summary>
    /// Orders the unit to cloak.
    /// \see: Unit::decloak, Unit::isCloaked
    /// </summary>
    member unit.Cloak() = ut.Cloak()

    /// <summary>
    /// Orders the unit to decloak.
    /// \see: Unit::cloak, Unit::isCloaked
    /// </summary>
    member unit.Decloak() = ut.Decloak()

    /// <summary>
    /// Orders the unit to siege. Note: unit must be a Terran siege tank.
    /// \see Unit::unsiege, Unit::isSieged
    /// </summary>
    member unit.Siege() = ut.Siege()

    /// <summary>
    /// Orders the unit to unsiege. Note: unit must be a Terran siege tank.
    /// \see: Unit::unsiege, Unit::isSieged
    /// </summary>
    member unit.Unsiege() = ut.Unsiege()

    /// <summary>
    /// Orders the unit to lift. Note: unit must be a Terran building that can be lifted.
    /// \see Unit::land, Unit::isLifted. 
    /// </summary>
    member unit.Lift() = ut.Lift()

    /// <summary>
    /// Orders the unit to land. Note: unit must be a Terran building that is currently lifted.
    /// \see Unit::lift, Unit::isLifted
    /// </summary>
    member unit.Land(target) = ut.Land(Position.tileToApi target)

    /// <summary>
    /// Orders the unit to load the target unit.
    /// \see Unit::unload, Unit::unloadAll, Unit::getLoadedUnits, Unit:isLoaded
    /// </summary>
    member unit.Load(target:Unit, shiftQueueCommand) = ut.Load(target.Unit, shiftQueueCommand)

    /// <summary>
    /// Orders the unit to unload the target unit.
    /// \see Unit::load, Unit::unloadAll, Unit::getLoadedUnits, Unit:isLoaded
    /// </summary>
    member unit.Unload(target:Unit) = ut.Unload(target.Unit)

    /// <summary>
    /// Orders the unit to unload all loaded units at the unit's current position.
    /// \see Unit::load, Unit::unload, Unit::unloadAll, Unit::getLoadedUnits, Unit:isLoaded
    /// </summary>
    member unit.UnloadAll(shiftQueueCommand) = ut.UnloadAll(shiftQueueCommand)

    /// <summary>
    /// Orders the unit to unload all loaded units at the specified location. Unit should be a Terran Dropship, Protoss Shuttle, or Zerg Overlord. If the
    /// unit is a Terran Bunker, the units will be unloaded right outside the bunker, like in the first version of unloadAll.
    /// \see Unit::load, Unit::unload, Unit::unloadAll, Unit::getLoadedUnits, Unit:isLoaded
    /// </summary>
    member unit.UnloadAll(target, shiftQueueCommand) = ut.UnloadAll(Position.pixelToApi target, shiftQueueCommand)

    /// <summary>
    /// Works like the right click in the GUI
    /// </summary>
    member unit.RightClick(target, shiftQueueCommand) = ut.RightClick(Position.pixelToApi target, shiftQueueCommand)

    /// <summary>
    /// Works like the right click in the GUI. Right click on a mineral patch to order a worker to mine, right click on an enemy to attack it
    /// </summary>
    member unit.RightClick(target:Unit, shiftQueueCommand) = ut.RightClick(target.Unit, shiftQueueCommand)

    /// <summary>
    /// Orders the SCV to stop constructing the building, and the building is left in a partially complete state until it is canceled, destroyed, or completed.
    /// \see Unit::isConstructing
    /// </summary>
    member unit.HaltConstruction() = ut.HaltConstruction()

    /// <summary>
    /// Orders the building to stop being constructed.
    /// \see Unit::beingConstructed
    /// </summary>
    member unit.CancelConstruction() = ut.CancelConstruction()

    /// <summary>
    /// Orders the unit to stop making the addon
    /// </summary>
    member unit.CancelAddon() = ut.CancelAddon()

    /// <summary>
    /// Orders the unit to remove the specified unit from its training queue.
    /// \see Unit::train, Unit::cancelTrain, Unit::isTraining, Unit::getTrainingQueue
    /// </summary>
    member unit.CancelTrain(slot) = ut.CancelTrain(slot)

    /// <summary>
    /// Orders the unit to stop morphing.
    /// \see Unit::morph, Unit::isMorphing
    /// </summary>
    member unit.CancelMorph() = ut.CancelMorph()

    /// <summary>
    /// Orders the unit to cancel a research in progress.
    /// \see Unit::research, Unit::isResearching, Unit::getTech
    /// </summary>
    member unit.CancelResearch() = ut.CancelResearch()

    /// <summary>
    /// Orders the unit to cancel an upgrade in progress.
    /// \see Unit::upgrade, Unit::isUpgrading, Unit::getUpgrade
    /// </summary>
    member unit.CancelUpgrade() = ut.CancelUpgrade()

    /// <summary>
    /// Orders the unit to use a tech not requiring a target (ie Stim Pack). Returns true if it is a valid tech
    /// </summary>
    member unit.UseTech(tech) = ut.UseTech(tech)

    /// <summary>
    /// Orders the unit to use a tech requiring a position target (ie Dark Swarm). Returns true if it is a valid tech
    /// </summary>
    member unit.UseTech(tech, pos) = ut.UseTech(tech, Position.pixelToApi pos)

    /// <summary>
    /// Orders the unit to use a tech requiring a unit target (ie Irradiate). Returns true if it is a valid tech
    /// </summary>
    member unit.UseTech(tech, target:Unit) = ut.UseTech(tech, target.Unit)

    /// <summary>
    /// Moves a Flag Beacon to the target location
    /// </summary>
    member unit.PlaceCop(target) = ut.PlaceCop(Position.tileToApi target)

    /// <summary>
    /// Returns the position of the unit on the map
    /// </summary>
    static member inline position (unit:Unit) = unit.Position
    /// <summary>
    /// Returns the build tile position of the unit on the map. Useful if the unit is a building. The tile position is of the top left corner of the building
    /// </summary>
    static member inline tilePosition (unit:Unit) = unit.TilePosition

    /// <summary>
    /// Returns the edge-to-edge distance between the current unit and the target unit
    /// </summary>
    static member Distance(first:Unit, second:Unit) = first.Rectangle |~~| second.Rectangle

    /// <summary>
    /// Returns the distance from the edge of the current unit to the target position
    /// </summary>
    static member Distance(unit:Unit, target) = unit.Rectangle |~~| (target, target)

    /// <summary>
    /// Returns true if the unit is able to move to the target unit
    /// </summary>
    static member HasPath(unit:Unit, target:Unit) = unit.Unit.HasPath target.Unit

    /// <summary>
    /// Returns true if the unit is able to move to the target position
    /// </summary>
    static member HasPath(unit:Unit, target) = Position.pixelToApi target |> unit.Unit.HasPath
