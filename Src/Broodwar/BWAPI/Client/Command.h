#pragma once
#pragma unmanaged

#include <BWAPI\Client\Command.h>

#pragma managed

#include "CommandType.h"

namespace BroodWar
{
	namespace Api
	{
		namespace Client
		{
			public ref class Command sealed
			{
			internal:
				BWAPIC::Command* instance;

				Command(BWAPIC::Command command);
				~Command();
				!Command();
			public:
				Command();
				Command(CommandType type, int value1, int value2);
				property CommandType Type
				{
					CommandType get();
					void set(CommandType value);
				}
				property int Value1
				{
					int get();
					void set(int value);
				}
				property int Value2
				{
					int get();
					void set(int value);
				}
			};
		}
	}
}
