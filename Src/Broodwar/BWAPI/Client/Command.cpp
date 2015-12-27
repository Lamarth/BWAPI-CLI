#include "Command.h"

namespace BroodWar
{
	namespace Api
	{
		namespace Client
		{
			Command::Command(BWAPIC::Command command)
			{
				instance = new BWAPIC::Command(command);
			}

			Command::~Command()
			{
				delete instance;
			}

			Command::!Command()
			{
				delete instance;
			}
			
			Command::Command()
			{
				instance = new BWAPIC::Command();
			}

			Command::Command(CommandType type, int value1, int value2)
			{
				instance = new BWAPIC::Command(static_cast<BWAPIC::CommandType::Enum>(type), value1, value2);
			}

			CommandType Command::Type::get()
			{
				return static_cast<CommandType>(instance->type);
			}

			void Command::Type::set(CommandType type)
			{
				instance->type = static_cast<BWAPIC::CommandType::Enum>(type);
			}

			int Command::Value1::get()
			{
				return instance->value1;
			}

			void Command::Value1::set(int value)
			{
				instance->value1 = value;
			}

			int Command::Value2::get()
			{
				return instance->value2;
			}

			void Command::Value2::set(int value)
			{
				instance->value2 = value;
			}
		}
	}
}
