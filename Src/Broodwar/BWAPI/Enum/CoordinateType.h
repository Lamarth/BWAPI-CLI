#pragma once

namespace BroodWar
{
	namespace Api
	{
		namespace Enum
		{
			// Conversion:
			// ShapeType managedST = static_cast<ShapeType>(nativeST);
			// and vice versa
			public enum class CoordinateType
			{
				/// <summary>
				/// (0,0) corresponds to the top left corner of the screen
				/// </summary>
				Screen = 1,

				/// <summary>
				/// (0,0) corresponds to the top left corner of the map
				/// </summary>
				Map = 2,

				/// <summary>
				/// (0,0) corresponds to the tip of the mouse
				/// </summary>
				Mouse = 3
			};
		}
	}
}
