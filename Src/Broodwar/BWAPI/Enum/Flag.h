#pragma once

namespace BroodWar
{
	namespace Api
	{
		namespace Enum
		{
			//direct mapping
			public enum class Flag
			{
				/// <summary>
				/// Enable to get information about all units on the map, not just the visible units
				/// </summary>
				CompleteMapInformation = 0,

				/// <summary>
				/// Enable to get information from the user (what units are selected, chat messages the user enters, etc)
				/// </summary>
				UserInput = 1,

				Max
			};
		}
	}
}
