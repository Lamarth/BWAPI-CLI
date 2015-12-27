#pragma once

namespace BroodWar
{
	namespace Api
	{
		namespace Enum
		{
			//direct mapping
			public enum class Latency
			{
				SinglePlayer = 2,
				LanLow = 5,
				LanMedium = 7,
				LanHigh = 9,
				BattlenetLow = 14,
				BattlenetMedium = 19,
				BattlenetHigh = 24
			};
		}
	}
}
