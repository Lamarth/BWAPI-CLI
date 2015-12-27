#pragma once

namespace BroodWar
{
	namespace Api
	{
		namespace Enum
		{
			[System::Flags]
			public enum class Targets
			{
				None = 0x0,
				Air = 0x1,
				Ground = 0x2,
				Mechanical = 0x4,
				Organic = 0x8,
				NonBuilding = 0x10,
				NonRobotic = 0x20,
				Terrain = 0x40,
				OrgOrMech = 0x80,
				Own = 0x100
			};
		}
	}
}
