#pragma once
#pragma unmanaged

#include <BWAPI\Client\UnitCommand.h>

#pragma managed

#include "..\..\EnumMapping.h"

using namespace BroodWar::Api::Enum;

namespace BroodWar
{
	namespace Api
	{
		namespace Client
		{
			public ref class UnitCommand sealed
			{
			internal:
				BWAPIC::UnitCommand* instance;

				UnitCommand(BWAPIC::UnitCommand command);
				~UnitCommand();
				!UnitCommand();
			public:
				UnitCommand();
				property UnitCommandType CommandType
				{
					UnitCommandType get();
					void set(UnitCommandType value);
				}
				property int UnitIndex
				{
					int get();
					void set(int value);
				}
				property int TargetIndex
				{
					int get();
					void set(int value);
				}
				property int X
				{
					int get();
					void set(int value);
				}
				property int Y
				{
					int get();
					void set(int value);
				}
				property int Extra
				{
					int get();
					void set(int value);
				}
			};
		}
	}
}
