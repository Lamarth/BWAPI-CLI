#include "Unit.h"
#include "Player.h"
#include "UnitType.h"
#include "Position.h"
#include "TilePosition.h"
#include "Region.h"
#include "Tech.h"
#include "Upgrade.h"
#include "Weapon.h"

#include "..\EnumMapping.h"
#include "..\Util.h"

using namespace BroodWar;

namespace BroodWar
{
	namespace Api
	{
		Api::Unit^ ConvertUnit(BWAPI::Unit unit)
		{
			if(unit == nullptr)
				return nullptr;
			return gcnew Api::Unit(unit);
		}

		BWAPI::Unit ConvertUnit(Api::Unit^ unit)
		{
			if(unit == nullptr)
				return nullptr;
			return unit->instance;
		}

		Unit::Unit(BWAPI::Unit unit)
		{
			instance = unit;
		}

		int Unit::Id::get()
		{
			return instance->getID();
		}

		int Unit::ReplayId::get()
		{
			return instance->getReplayID();
		}

		Api::Player^ Unit::Player::get()
		{
			return ConvertPlayer(instance->getPlayer());
		}

		Api::UnitType^ Unit::UnitType::get()
		{
			return ConvertUnitType(instance->getType());
		}

		Api::Position^ Unit::Position::get()
		{
			return ConvertPosition(instance->getPosition());
		}

		Api::TilePosition^ Unit::TilePosition::get()
		{
			return ConvertTilePosition(instance->getTilePosition());
		}

		double Unit::Angle::get()
		{
			return instance->getAngle();
		}

		double Unit::VelocityX::get()
		{
			return instance->getVelocityX();
		}

		double Unit::VelocityY::get()
		{
			return instance->getVelocityY();
		}

		Api::Region^ Unit::Region::get()
		{
			return ConvertRegion(instance->getRegion());
		}

		int Unit::Left::get()
		{
			return instance->getLeft();
		}

		int Unit::Top::get()
		{
			return instance->getTop();
		}

		int Unit::Right::get()
		{
			return instance->getRight();
		}

		int Unit::Bottom::get()
		{
			return instance->getBottom();
		}

		int Unit::HitPoints::get()
		{
			return instance->getHitPoints();
		}

		int Unit::Shields::get()
		{
			return instance->getShields();
		}

		int Unit::Energy::get()
		{
			return instance->getEnergy();
		}

		int Unit::Resources::get()
		{
			return instance->getResources();
		}

		int Unit::ResourceGroup::get()
		{
			return instance->getResourceGroup();
		}

		int Unit::Distance(Api::Unit^ target)
		{
			return instance->getDistance(ConvertUnit(target));
		}

		int Unit::Distance(Api::Position^ target)
		{
			return instance->getDistance(ConvertPosition(target));
		}

		bool Unit::HasPath(Api::Unit^ target)
		{
			return instance->hasPath(ConvertUnit(target));
		}

		bool Unit::HasPath(Api::Position^ target)
		{
			return instance->hasPath(ConvertPosition(target));
		}

		int Unit::LastCommandFrame::get()
		{
			return instance->getLastCommandFrame();
		}

		Api::UnitCommand^ Unit::LastCommand::get()
		{
			return ConvertUnitCommand(instance->getLastCommand());
		}

		Api::Player^ Unit::LastAttackingPlayer::get()
		{
			return ConvertPlayer(instance->getLastAttackingPlayer());
		}

		Api::UnitType^ Unit::InitialType::get()
		{
			return ConvertUnitType(instance->getInitialType());
		}

		Api::Position^ Unit::InitialPosition::get()
		{
			return ConvertPosition(instance->getInitialPosition());
		}

		Api::TilePosition^ Unit::InitialTilePosition::get()
		{
			return ConvertTilePosition(instance->getInitialTilePosition());
		}

		int Unit::InitialHitPoints::get()
		{
			return instance->getInitialHitPoints();
		}

		int Unit::InitialResources::get()
		{
			return instance->getInitialResources();
		}

		int Unit::KillCount::get()
		{
			return instance->getKillCount();
		}

		int Unit::AcidSporeCount::get()
		{
			return instance->getAcidSporeCount();
		}

		int Unit::InterceptorCount::get()
		{
			return instance->getInterceptorCount();
		}

		int Unit::ScarabCount::get()
		{
			return instance->getScarabCount();
		}

		int Unit::SpiderMineCount::get()
		{
			return instance->getSpiderMineCount();
		}

		int Unit::GroundWeaponCooldown::get()
		{
			return instance->getGroundWeaponCooldown();
		}

		int Unit::AirWeaponCooldown::get()
		{
			return instance->getAirWeaponCooldown();
		}

		int Unit::SpellCooldown::get()
		{
			return instance->getSpellCooldown();
		}

		int Unit::DefenseMatrixPoints::get()
		{
			return instance->getDefenseMatrixPoints();
		}

		int Unit::DefenseMatrixTimer::get()
		{
			return instance->getDefenseMatrixTimer();
		}

		int Unit::EnsnareTimer::get()
		{
			return instance->getEnsnareTimer();
		}

		int Unit::IrradiateTimer::get()
		{
			return instance->getIrradiateTimer();
		}

		int Unit::LockdownTimer::get()
		{
			return instance->getLockdownTimer();
		}

		int Unit::MaelstromTimer::get()
		{
			return instance->getMaelstromTimer();
		}

		int Unit::OrderTimer::get()
		{
			return instance->getOrderTimer();
		}

		int Unit::PlagueTimer::get()
		{
			return instance->getPlagueTimer();
		}

		int Unit::RemoveTimer::get()
		{
			return instance->getRemoveTimer();
		}

		int Unit::StasisTimer::get()
		{
			return instance->getStasisTimer();
		}

		int Unit::StimTimer::get()
		{
			return instance->getStimTimer();
		}

		Api::UnitType^ Unit::BuildType::get()
		{
			return ConvertUnitType(instance->getBuildType());
		}

		List<Api::UnitType^>^ Unit::TrainingQueue::get()
		{
			return ToList<BWAPI::UnitType, Api::UnitType^>(instance->getTrainingQueue(), &ConvertUnitType);
		}

		Api::Tech^ Unit::Tech::get()
		{
			return ConvertTech(instance->getTech());
		}

		Api::Upgrade^ Unit::Upgrade::get()
		{
			return ConvertUpgrade(instance->getUpgrade());
		}

		int Unit::RemainingBuildTime::get()
		{
			return instance->getRemainingBuildTime();
		}

		int Unit::RemainingTrainTime::get()
		{
			return instance->getRemainingTrainTime();
		}

		int Unit::RemainingResearchTime::get()
		{
			return instance->getRemainingResearchTime();
		}

		int Unit::RemainingUpgradeTime::get()
		{
			return instance->getRemainingUpgradeTime();
		}

		Api::Unit^ Unit::BuildUnit::get()
		{
			return ConvertUnit(instance->getBuildUnit());
		}

		Api::Unit^ Unit::Target::get()
		{
			return ConvertUnit(instance->getTarget());
		}

		Api::Position^ Unit::TargetPosition::get()
		{
			return ConvertPosition(instance->getTargetPosition());
		}

		Api::Enum::OrderType Unit::Order::get()
		{
			return EnumMapping::OrderType->Managed(instance->getOrder());
		}

		Api::Enum::OrderType Unit::SecondaryOrder::get()
		{
			return EnumMapping::OrderType->Managed(instance->getSecondaryOrder());
		}

		Api::Unit^ Unit::OrderTarget::get()
		{
			return ConvertUnit(instance->getOrderTarget());
		}

		Api::Position^ Unit::OrderTargetPosition::get()
		{
			return ConvertPosition(instance->getOrderTargetPosition());
		}

		Api::Position^ Unit::RallyPosition::get()
		{
			return ConvertPosition(instance->getRallyPosition());
		}

		Api::Unit^ Unit::RallyUnit::get()
		{
			return ConvertUnit(instance->getRallyUnit());
		}

		Api::Unit^ Unit::Addon::get()
		{
			return ConvertUnit(instance->getAddon());
		}

		Api::Unit^ Unit::NydusExit::get()
		{
			return ConvertUnit(instance->getNydusExit());
		}

		Api::Unit^ Unit::PowerUp::get()
		{
			return ConvertUnit(instance->getPowerUp());
		}

		Api::Unit^ Unit::Transport::get()
		{
			return ConvertUnit(instance->getTransport());
		}

		HashSet<Api::Unit^>^ Unit::LoadedUnits::get()
		{
			return ToHashSet<BWAPI::Unit, Unit^>(instance->getLoadedUnits(), &ConvertUnit);
		}

		Api::Unit^ Unit::Carrier::get()
		{
			return ConvertUnit(instance->getCarrier());
		}

		HashSet<Api::Unit^>^ Unit::Interceptors::get()
		{
			return ToHashSet<BWAPI::Unit, Unit^>(instance->getInterceptors(), &ConvertUnit);
		}

		Api::Unit^ Unit::Hatchery::get()
		{
			return ConvertUnit(instance->getHatchery());
		}

		HashSet<Api::Unit^>^ Unit::Larva::get()
		{
			return ToHashSet<BWAPI::Unit, Unit^>(instance->getLarva(), &ConvertUnit);
		}

		HashSet<Api::Unit^>^ Unit::UnitsInRadius(int radius)
		{
			return ToHashSet<BWAPI::Unit, Unit^>(instance->getUnitsInRadius(radius), &ConvertUnit);
		}

		HashSet<Api::Unit^>^ Unit::UnitsInWeaponRange(Api::Weapon^ weapon)
		{
			return ToHashSet<BWAPI::Unit, Unit^>(instance->getUnitsInWeaponRange(*(weapon->instance)), &ConvertUnit);
		}

		IntPtr Unit::ClientInfo::get()
		{
			return IntPtr(instance->getClientInfo());
		}

		void Unit::ClientInfo::set(IntPtr value)
		{
			instance->setClientInfo(value.ToPointer());
		}

		bool Unit::Exists::get()
		{
			return instance->exists();
		}

		bool Unit::HasNuke::get()
		{
			return instance->hasNuke();
		}

		bool Unit::IsAccelerating::get()
		{
			return instance->isAccelerating();
		}

		bool Unit::IsAttacking::get()
		{
			return instance->isAttacking();
		}

		bool Unit::IsAttackFrame::get()
		{
			return instance->isAttackFrame();
		}

		bool Unit::IsBeingConstructed::get()
		{
			return instance->isBeingConstructed();
		}

		bool Unit::IsBeingGathered::get()
		{
			return instance->isBeingGathered();
		}

		bool Unit::IsBeingHealed::get()
		{
			return instance->isBeingHealed();
		}

		bool Unit::IsBlind::get()
		{
			return instance->isBlind();
		}

		bool Unit::IsBraking::get()
		{
			return instance->isBraking();
		}

		bool Unit::IsBurrowed::get()
		{
			return instance->isBurrowed();
		}

		bool Unit::IsCarryingGas::get()
		{
			return instance->isCarryingGas();
		}

		bool Unit::IsCarryingMinerals::get()
		{
			return instance->isCarryingMinerals();
		}

		bool Unit::IsCloaked::get()
		{
			return instance->isCloaked();
		}

		bool Unit::IsCompleted::get()
		{
			return instance->isCompleted();
		}

		bool Unit::IsConstructing::get()
		{
			return instance->isConstructing();
		}

		bool Unit::IsDefenseMatrixed::get()
		{
			return instance->isDefenseMatrixed();
		}

		bool Unit::IsDetected::get()
		{
			return instance->isDetected();
		}

		bool Unit::IsEnsnared::get()
		{
			return instance->isEnsnared();
		}

		bool Unit::IsFollowing::get()
		{
			return instance->isFollowing();
		}

		bool Unit::IsGatheringGas::get()
		{
			return instance->isGatheringGas();
		}

		bool Unit::IsGatheringMinerals::get()
		{
			return instance->isGatheringMinerals();
		}

		bool Unit::IsHallucination::get()
		{
			return instance->isHallucination();
		}

		bool Unit::IsHoldingPosition::get()
		{
			return instance->isHoldingPosition();
		}

		bool Unit::IsIdle::get()
		{
			return instance->isIdle();
		}

		bool Unit::IsInterruptible::get()
		{
			return instance->isInterruptible();
		}

		bool Unit::IsInvincible::get()
		{
			return instance->isInvincible();
		}

		bool Unit::IsInWeaponRange(Api::Unit^ target)
		{
			return instance->isInWeaponRange(ConvertUnit(target));
		}

		bool Unit::IsIrradiated::get()
		{
			return instance->isIrradiated();
		}

		bool Unit::IsLifted::get()
		{
			return instance->isLifted();
		}

		bool Unit::IsLoaded::get()
		{
			return instance->isLoaded();
		}

		bool Unit::IsLockedDown::get()
		{
			return instance->isLockedDown();
		}

		bool Unit::IsMaelstrommed::get()
		{
			return instance->isMaelstrommed();
		}

		bool Unit::IsMorphing::get()
		{
			return instance->isMorphing();
		}

		bool Unit::IsMoving::get()
		{
			return instance->isMoving();
		}

		bool Unit::IsParasited::get()
		{
			return instance->isParasited();
		}

		bool Unit::IsPatrolling::get()
		{
			return instance->isPatrolling();
		}

		bool Unit::IsPlagued::get()
		{
			return instance->isPlagued();
		}

		bool Unit::IsRepairing::get()
		{
			return instance->isRepairing();
		}

		bool Unit::IsResearching::get()
		{
			return instance->isResearching();
		}

		bool Unit::IsSelected::get()
		{
			return instance->isSelected();
		}

		bool Unit::IsSieged::get()
		{
			return instance->isSieged();
		}

		bool Unit::IsStartingAttack::get()
		{
			return instance->isStartingAttack();
		}

		bool Unit::IsStasised::get()
		{
			return instance->isStasised();
		}

		bool Unit::IsStimmed::get()
		{
			return instance->isStimmed();
		}

		bool Unit::IsStuck::get()
		{
			return instance->isStuck();
		}

		bool Unit::IsTraining::get()
		{
			return instance->isTraining();
		}

		bool Unit::IsUnderAttack::get()
		{
			return instance->isUnderAttack();
		}

		bool Unit::IsUnderDarkSwarm::get()
		{
			return instance->isUnderDarkSwarm();
		}

		bool Unit::IsUnderDisruptionWeb::get()
		{
			return instance->isUnderDisruptionWeb();
		}

		bool Unit::IsUnderStorm::get()
		{
			return instance->isUnderStorm();
		}

		bool Unit::IsPowered::get()
		{
			return instance->isPowered();
		}

		bool Unit::IsUpgrading::get()
		{
			return instance->isUpgrading();
		}

		bool Unit::IsVisible()
		{
			return instance->isVisible();
		}

		bool Unit::IsVisible(Api::Player^ player)
		{
			return instance->isVisible(ConvertPlayer(player));
		}

		bool Unit::CanIssueCommand(Api::UnitCommand^ command)
		{
			return instance->canIssueCommand(ConvertUnitCommand(command));
		}

		bool Unit::IssueCommand(Api::UnitCommand^ command)
		{
			return instance->issueCommand(ConvertUnitCommand(command));
		}

		bool Unit::Attack(Api::Position^ target, bool shiftQueueCommand)
		{
			return instance->attack(ConvertPosition(target), shiftQueueCommand);
		}

		bool Unit::Attack(Api::Unit^ target, bool shiftQueueCommand)
		{
			return instance->attack(ConvertUnit(target), shiftQueueCommand);
		}

        bool Unit::Build(Api::Enum::UnitType type, Api::TilePosition^ target)
		{
            return instance->build(EnumMapping::UnitType->Native(type), ConvertTilePosition(target));
		}

		bool Unit::BuildAddon(Api::UnitType^ type)
		{
			return instance->buildAddon(ConvertUnitType(type));
		}

		bool Unit::Train(Api::Enum::UnitType type)
		{
			return instance->train(EnumMapping::UnitType->Native(type));
		}

		bool Unit::Morph(Api::Enum::UnitType type)
		{
			return instance->morph(EnumMapping::UnitType->Native(type));
		}

		bool Unit::Research(Api::Tech^ tech)
		{
			return instance->research(ConvertTech(tech));
		}

		bool Unit::PerformUpgrade(Api::Upgrade^ upgrade)
		{
			return instance->upgrade(ConvertUpgrade(upgrade));
		}

		bool Unit::SetRallyPoint(Api::Position^ target)
		{
			return instance->setRallyPoint(ConvertPosition(target));
		}

		bool Unit::SetRallyPoint(Api::Unit^ target)
		{
			return instance->setRallyPoint(ConvertUnit(target));
		}

		bool Unit::Move(Api::Position^ target, bool shiftQueueCommand)
		{
			return instance->move(ConvertPosition(target), shiftQueueCommand);
		}

		bool Unit::Patrol(Api::Position^ target, bool shiftQueueCommand)
		{
			return instance->patrol(ConvertPosition(target), shiftQueueCommand);
		}

		bool Unit::HoldPosition(bool shiftQueueCommand)
		{
			return instance->holdPosition(shiftQueueCommand);
		}

		bool Unit::Stop(bool shiftQueueCommand)
		{
			return instance->stop(shiftQueueCommand);
		}

		bool Unit::Follow(Api::Unit^ target, bool shiftQueueCommand)
		{
			return instance->follow(ConvertUnit(target), shiftQueueCommand);
		}

		bool Unit::Gather(Api::Unit^ target, bool shiftQueueCommand)
		{
			return instance->gather(ConvertUnit(target), shiftQueueCommand);
		}

		bool Unit::ReturnCargo(bool shiftQueueCommand)
		{
			return instance->returnCargo(shiftQueueCommand);
		}

		bool Unit::Repair(Api::Unit^ target, bool shiftQueueCommand)
		{
			return instance->repair(ConvertUnit(target));
		}

		bool Unit::Burrow()
		{
			return instance->burrow();
		}

		bool Unit::Unburrow()
		{
			return instance->unburrow();
		}

		bool Unit::Cloak()
		{
			return instance->cloak();
		}

		bool Unit::Decloak()
		{
			return instance->decloak();
		}

		bool Unit::Siege()
		{
			return instance->siege();
		}

		bool Unit::Unsiege()
		{
			return instance->unsiege();
		}

		bool Unit::Lift()
		{
			return instance->lift();
		}

		bool Unit::Land(Api::TilePosition^ target)
		{
			return instance->land(ConvertTilePosition(target));
		}

		bool Unit::Load(Api::Unit^ target, bool shiftQueueCommand)
		{
			return instance->load(ConvertUnit(target));
		}

		bool Unit::Unload(Api::Unit^ target)
		{
			return instance->unload(ConvertUnit(target));
		}

		bool Unit::UnloadAll(bool shiftQueueCommand)
		{
			return instance->unloadAll(shiftQueueCommand);
		}

		bool Unit::UnloadAll(Api::Position^ target, bool shiftQueueCommand)
		{
			return instance->unloadAll(ConvertPosition(target), shiftQueueCommand);
		}

		bool Unit::RightClick(Api::Position^ target, bool shiftQueueCommand)
		{
			return instance->rightClick(ConvertPosition(target), shiftQueueCommand);
		}

		bool Unit::RightClick(Api::Unit^ target, bool shiftQueueCommand)
		{
			return instance->rightClick(ConvertUnit(target));
		}

		bool Unit::HaltConstruction()
		{
			return instance->haltConstruction();
		}

		bool Unit::CancelConstruction()
		{
			return instance->cancelConstruction();
		}

		bool Unit::CancelAddon()
		{
			return instance->cancelAddon();
		}

		bool Unit::CancelTrain(int slot)
		{
			return instance->cancelTrain(slot);
		}

		bool Unit::CancelMorph()
		{
			return instance->cancelMorph();
		}

		bool Unit::CancelResearch()
		{
			return instance->cancelResearch();
		}

		bool Unit::CancelUpgrade()
		{
			return instance->cancelUpgrade();
		}

		bool Unit::UseTech(Api::Tech^ tech)
		{
			return instance->useTech(ConvertTech(tech));
		}

		bool Unit::UseTech(Api::Tech^ tech, Api::Position^ target)
		{
			return instance->useTech(ConvertTech(tech), ConvertPosition(target));
		}

		bool Unit::UseTech(Api::Tech^ tech, Api::Unit^ target)
		{
			return instance->useTech(ConvertTech(tech), ConvertUnit(target));
		}

		bool Unit::PlaceCop(Api::TilePosition^ target)
		{
			return instance->placeCOP(ConvertTilePosition(target));
		}

		int Unit::GetHashCode()
		{
			return instance->getID();
		}

		bool Unit::Equals(Object^ o)
		{
			Unit^ other = dynamic_cast<Unit^>(o);
			return this->Equals(other);
		}

		bool Unit::Equals(Unit^ other)
		{
			if(ReferenceEquals(nullptr, other))
				return false;
			if(ReferenceEquals(this, other))
				return true;
			return this->instance->getID() == other->instance->getID();
		}

		bool Unit::operator == (Unit^ first, Unit^ second)
		{
			if(ReferenceEquals(first, second))
				return true;
			if(ReferenceEquals(nullptr, first))
				return false;
			return first->Equals(second);
		}

		bool Unit::operator != (Unit^ first, Unit^ second)
		{
			return !(first == second);
		}
	}
}