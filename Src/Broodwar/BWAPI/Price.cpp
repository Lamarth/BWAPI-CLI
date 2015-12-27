#include "Price.h"

namespace BroodWar
{
	namespace Api
	{
		Price::Price(int minerals, int gas, int timeFrames, int supply)
		{
			_minerals = minerals;
			_gas = gas;
			_timeFrames = timeFrames;
			_supply = supply;
		}
			
		int Price::Minerals::get()
		{
			return _minerals;
		}

		int Price::Gas::get()
		{
			return _gas;
		}
			
		int Price::TimeFrames::get()
		{
			return _timeFrames;
		}

		int Price::Supply::get()
		{
			return _supply;
		}
	}
}
