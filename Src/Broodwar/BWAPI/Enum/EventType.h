#pragma once

namespace BroodWar
{
	namespace Api
	{
		namespace Enum
		{
			//direct mapping
			public enum class EventType
			{
				MatchStart,
				MatchEnd,
				MatchFrame,
				MenuFrame,
				SendText,
				ReceiveText,
				PlayerLeft,
				NukeDetect,
				UnitDiscover,
				UnitEvade,
				UnitShow,
				UnitHide,
				UnitCreate,
				UnitDestroy,
				UnitMorph,
				UnitRenegade,
				SaveGame,
				UnitComplete,
				//TriggerAction,
				PlayerDropped,
				None
			};
		}
	}
}
