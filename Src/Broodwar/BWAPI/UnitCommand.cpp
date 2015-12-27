#include "UnitCommand.h"
#include "Unit.h"

#include "..\EnumMapping.h"

namespace BroodWar
{
	namespace Api
	{
		UnitCommand^ ConvertUnitCommand(BWAPI::UnitCommand command)
		{
			return gcnew UnitCommand(command);
		}

		BWAPI::UnitCommand ConvertUnitCommand(UnitCommand^ command)
		{
			if(command == nullptr)
				return BWAPI::UnitCommand();
			return BWAPI::UnitCommand(*(command->instance));
		}

		UnitCommand::UnitCommand(BWAPI::UnitCommand* command)
		{
			instance = command;
			dispose = false;
		}

		UnitCommand::UnitCommand(BWAPI::UnitCommand command)
		{
			instance = new BWAPI::UnitCommand(command);
			dispose = true;
		}

		UnitCommand::UnitCommand()
		{
			instance = new BWAPI::UnitCommand();
			dispose = true;
		}
		
		UnitCommand::UnitCommand(Api::Unit^ unit, Api::Enum::UnitCommandType type, Api::Unit^ target, int x, int y, int extra)
		{
			instance = new BWAPI::UnitCommand(unit->instance, EnumMapping::UnitCommandType->Native(type), target->instance, x, y, extra);
			dispose = true;
		}

		UnitCommand::~UnitCommand()
		{
			if(dispose)
				delete instance;
		}

		UnitCommand::!UnitCommand()
		{
			if(dispose)
				delete instance;
		}

		Api::Enum::UnitCommandType UnitCommand::Type::get()
		{
			return EnumMapping::UnitCommandType->Managed(instance->type);
		}
		
		bool UnitCommand::TypeEquals(Api::Enum::UnitCommandType type)
		{
			return Type == type;
		}
		
		Api::Unit^ UnitCommand::Unit::get()
		{
			return gcnew Api::Unit(instance->getUnit());
		}
		
		Api::Unit^ UnitCommand::Target::get()
		{
			return gcnew Api::Unit(instance->getTarget());
		}
		
		Api::Position^ UnitCommand::TargetPosition::get()
		{
			return gcnew Api::Position(instance->getTargetPosition());
		}
		
		Api::TilePosition^ UnitCommand::TargetTilePosition::get()
		{
			return gcnew Api::TilePosition(instance->getTargetTilePosition());
		}
		
		Api::UnitType^ UnitCommand::UnitType::get()
		{
			return gcnew Api::UnitType(instance->getUnitType());
		}
		
		Api::Tech^ UnitCommand::Tech::get()
		{
			return gcnew Api::Tech(instance->getTechType());
		}
		
		Api::Upgrade^ UnitCommand::Upgrade::get()
		{
			return gcnew Api::Upgrade(instance->getUpgradeType());
		}
		
		int UnitCommand::Slot::get()
		{
			return instance->getSlot();
		}
		
		bool UnitCommand::IsQueued::get()
		{
			return instance->isQueued();
		}

		UnitCommand^ UnitCommand::Attack(Api::Unit^ unit, Api::Position^ target, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::attack(unit->instance, *(target->instance), shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::Attack(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::attack(unit->instance, target->instance, shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::Build(Api::Unit^ unit, Api::TilePosition^ target, Api::UnitType^ type)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::build(unit->instance, *(target->instance), *(type->instance)));
		}
		
		UnitCommand^ UnitCommand::BuildAddon(Api::Unit^ unit, Api::UnitType^ type)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::buildAddon(unit->instance, *(type->instance)));
		}
		
		UnitCommand^ UnitCommand::Train(Api::Unit^ unit, Api::UnitType^ type)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::train(unit->instance, *(type->instance)));
		}
		
		UnitCommand^ UnitCommand::Morph(Api::Unit^ unit, Api::UnitType^ type)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::morph(unit->instance, *(type->instance)));
		}
		
		UnitCommand^ UnitCommand::Research(Api::Unit^ unit, Api::Tech^ tech)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::research(unit->instance, *(tech->instance)));
		}
		
		UnitCommand^ UnitCommand::PerformUpgrade(Api::Unit^ unit, Api::Upgrade^ upgrade)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::upgrade(unit->instance, *(upgrade->instance)));
		}
		
		UnitCommand^ UnitCommand::SetRallyPoint(Api::Unit^ unit, Api::Position^ target)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::setRallyPoint(unit->instance, *(target->instance)));
		}
		
		UnitCommand^ UnitCommand::SetRallyPoint(Api::Unit^ unit, Api::Unit^ target)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::setRallyPoint(unit->instance, target->instance));
		}
		
		UnitCommand^ UnitCommand::Move(Api::Unit^ unit, Api::Position^ target, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::move(unit->instance, *(target->instance), shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::Patrol(Api::Unit^ unit, Api::Position^ target, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::patrol(unit->instance, *(target->instance), shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::HoldPosition(Api::Unit^ unit, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::holdPosition(unit->instance, shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::Stop(Api::Unit^ unit, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::stop(unit->instance, shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::Follow(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::follow(unit->instance, target->instance, shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::Gather(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::gather(unit->instance, target->instance, shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::ReturnCargo(Api::Unit^ unit, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::returnCargo(unit->instance, shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::Repair(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::repair(unit->instance, target->instance, shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::Burrow(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::burrow(unit->instance));
		}
		
		UnitCommand^ UnitCommand::Unburrow(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::unburrow(unit->instance));
		}
		
		UnitCommand^ UnitCommand::Cloak(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::cloak(unit->instance));
		}
		
		UnitCommand^ UnitCommand::Decloak(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::decloak(unit->instance));
		}
		
		UnitCommand^ UnitCommand::Siege(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::siege(unit->instance));
		}
		
		UnitCommand^ UnitCommand::Unsiege(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::unsiege(unit->instance));
		}
		
		UnitCommand^ UnitCommand::Lift(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::lift(unit->instance));
		}
		
		UnitCommand^ UnitCommand::Land(Api::Unit^ unit, Api::TilePosition^ target)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::land(unit->instance, *(target->instance)));
		}
		
		UnitCommand^ UnitCommand::Load(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand )
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::load(unit->instance, target->instance, shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::Unload(Api::Unit^ unit, Api::Unit^ target)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::unload(unit->instance, target->instance));
		}
		
		UnitCommand^ UnitCommand::UnloadAll(Api::Unit^ unit, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::unloadAll(unit->instance, shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::UnloadAll(Api::Unit^ unit, Api::Position^ target, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::unloadAll(unit->instance, *(target->instance), shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::RightClick(Api::Unit^ unit, Api::Position^ target, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::rightClick(unit->instance, *(target->instance), shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::RightClick(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::rightClick(unit->instance, target->instance, shiftQueueCommand));
		}
		
		UnitCommand^ UnitCommand::HaltConstruction(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::haltConstruction(unit->instance));
		}
		
		UnitCommand^ UnitCommand::CancelConstruction(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::cancelConstruction(unit->instance));
		}
		
		UnitCommand^ UnitCommand::CancelAddon(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::cancelAddon(unit->instance));
		}
		
		UnitCommand^ UnitCommand::CancelTrain(Api::Unit^ unit, int slot)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::cancelTrain(unit->instance, slot));
		}
		
		UnitCommand^ UnitCommand::CancelMorph(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::cancelMorph(unit->instance));
		}
		
		UnitCommand^ UnitCommand::CancelResearch(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::cancelResearch(unit->instance));
		}
		
		UnitCommand^ UnitCommand::CancelUpgrade(Api::Unit^ unit)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::cancelUpgrade(unit->instance));
		}
		
		UnitCommand^ UnitCommand::UseTech(Api::Unit^ unit, Api::Tech^ tech)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::useTech(unit->instance, *(tech->instance)));
		}
		
		UnitCommand^ UnitCommand::UseTech(Api::Unit^ unit, Api::Tech^ tech, Api::Position^ target)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::useTech(unit->instance, *(tech->instance), *(target->instance)));
		}
		
		UnitCommand^ UnitCommand::UseTech(Api::Unit^ unit, Api::Tech^ tech, Api::Unit^ target)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::useTech(unit->instance, *(tech->instance), target->instance));
		}
		
		UnitCommand^ UnitCommand::PlaceCop(Api::Unit^ unit, Api::TilePosition^ target)
		{
			return gcnew Api::UnitCommand(BWAPI::UnitCommand::placeCOP(unit->instance, *(target->instance)));
		}

		int UnitCommand::GetHashCode()
		{
			int result = Unit == nullptr ? 0 : Unit->GetHashCode();
			result = (result * 397) ^ (Target == nullptr ? 0 : Target->GetHashCode());
			result = (result * 397) ^ Type.GetHashCode();
			result = (result * 397) ^ instance->x;
			result = (result * 397) ^ instance->y;
			result = (result * 397) ^ instance->extra;
			return result;
		}

		bool UnitCommand::Equals(Object^ o)
		{
			UnitCommand^ other = dynamic_cast<UnitCommand^>(o);
			return this->Equals(other);
		}

		bool UnitCommand::Equals(UnitCommand^ other)
		{
			if(ReferenceEquals(nullptr, other))
				return false;
			if(ReferenceEquals(this, other))
				return true;
			return this->GetHashCode() == other->GetHashCode();
		}

		bool UnitCommand::operator == (UnitCommand^ first, UnitCommand^ second)
		{
			return *(first->instance) == *(second->instance);
		}

		bool UnitCommand::operator != (UnitCommand^ first, UnitCommand^ second)
		{
			return *(first->instance) != *(second->instance);
		}
	}
}
