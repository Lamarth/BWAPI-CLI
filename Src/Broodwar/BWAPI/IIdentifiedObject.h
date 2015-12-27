#pragma once

#pragma managed

namespace BroodWar
{
	namespace Api
	{
		public interface class IIdentifiedObject
		{
			property int Id { int get(); }
		};
	}
}
