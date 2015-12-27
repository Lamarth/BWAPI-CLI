#pragma once

namespace BroodWar
{
	namespace Api
	{
		public ref class Price sealed
		{
		private:
			int _minerals, _gas, _timeFrames, _supply;
		public:
			Price(int minerals, int gas, int timeFrames, int supply);
			
			property int Minerals { int get(); }

			property int Gas { int get(); }

			property int TimeFrames { int get(); }

			property int Supply { int get(); }
		};
	}
}
