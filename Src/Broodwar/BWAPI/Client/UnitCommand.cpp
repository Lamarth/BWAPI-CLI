#include "UnitCommand.h"

using namespace BroodWar::Api;

namespace BroodWar
{
	namespace Api
	{
		namespace Client
		{
			UnitCommand::UnitCommand(BWAPIC::UnitCommand command)
			{
				instance = new BWAPIC::UnitCommand(command);
			}

			UnitCommand::~UnitCommand()
			{
				delete instance;
			}

			UnitCommand::!UnitCommand()
			{
				delete instance;
			}

			UnitCommand::UnitCommand()
			{
				instance = new BWAPIC::UnitCommand();
			}

			UnitCommandType UnitCommand::CommandType::get()
			{
				return EnumMapping::UnitCommandType->Managed(instance->type);
			}

			void UnitCommand::CommandType::set(UnitCommandType type)
			{
				instance->type = EnumMapping::UnitCommandType->Native(type);
			}

			int UnitCommand::UnitIndex::get()
			{
				return instance->unitIndex;
			}

			void UnitCommand::UnitIndex::set(int value)
			{
				instance->unitIndex = value;
			}

			int UnitCommand::TargetIndex::get()
			{
				return instance->targetIndex;
			}

			void UnitCommand::TargetIndex::set(int value)
			{
				instance->targetIndex = value;
			}

			int UnitCommand::X::get()
			{
				return instance->x;
			}

			void UnitCommand::X::set(int value)
			{
				instance->x = value;
			}

			int UnitCommand::Y::get()
			{
				return instance->y;
			}

			void UnitCommand::Y::set(int value)
			{
				instance->y = value;
			}

			int UnitCommand::Extra::get()
			{
				return instance->extra;
			}

			void UnitCommand::Extra::set(int value)
			{
				instance->extra = value;
			}
		}
	}
}
