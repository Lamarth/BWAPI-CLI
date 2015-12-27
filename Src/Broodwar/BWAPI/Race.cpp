#include "Race.h"
#include "UnitType.h"

#include "..\EnumMapping.h"
#include "..\Util.h"

namespace BroodWar
{
	namespace Api
	{
		Race^ ConvertRace(BWAPI::Race* race)
		{
			if(race == NULL)
				return nullptr;
			return gcnew Race(race);
		}

		Race^ ConvertRace(BWAPI::Race race)
		{
			return gcnew Race(race);
		}

		BWAPI::Race ConvertRace(Race^ race)
		{
			if(race == nullptr)
				return BWAPI::Race();
			return BWAPI::Race(*(race->instance));
		}

		Race::Race(Api::Enum::RaceType race)
		{
			instance = EnumMapping::RaceType->NativePointer(race);
			dispose = true;
		}

		Race::Race(BWAPI::Race* race)
		{
			instance = race;
			dispose = false;
		}

		Race::Race(BWAPI::Race race)
		{
			instance = new BWAPI::Race(race);
			dispose = true;
		}

		Race::~Race()
		{
			if(dispose)
				delete instance;
		}

		Race::!Race()
		{
			if(dispose)
				delete instance;
		}

		Race::Race()
		{
			instance = new BWAPI::Race();
			dispose = true;
		}

		Race::Race(int id)	
		{
			instance = new BWAPI::Race(id);
			dispose = true;
		}

		int Race::Id::get()
		{
			return instance->getID();
		}

		System::String^ Race::ToString()
		{
			return gcnew System::String(instance->c_str());
		}

		Api::Enum::RaceType Race::Type::get()
		{
			return EnumMapping::RaceType->Managed(instance);
		}

		bool Race::TypeEquals(Api::Enum::RaceType raceType)
		{
			return Type == raceType;
		}

		Api::UnitType^ Race::Worker::get()
		{
			return ConvertUnitType(instance->getWorker());
		}

		Api::UnitType^ Race::Center::get()
		{
			return ConvertUnitType(instance->getCenter());
		}

		Api::UnitType^ Race::Refinery::get()
		{
			return ConvertUnitType(instance->getRefinery());
		}

		Api::UnitType^ Race::Transport::get()
		{
			return ConvertUnitType(instance->getTransport());
		}

		Api::UnitType^ Race::SupplyProvider::get()
		{
			return ConvertUnitType(instance->getSupplyProvider());
		}

		int Race::GetHashCode()
		{
			return instance->getID();
		}

		bool Race::Equals(Object^ o)
		{
			Api::Race^ other = dynamic_cast<Api::Race^>(o);
			return this->Equals(other);
		}

		bool Race::Equals(Race^ other)
		{
			if(ReferenceEquals(nullptr, other))
				return false;
			if(ReferenceEquals(this, other))
				return true;
			return this->instance->getID() == other->instance->getID();
		}

		List<Race^>^ Race::AllRaces::get()
		{
			return ToList<BWAPI::Race, Race^>(BWAPI::Races::allRaces(), &ConvertRace);
		}

		bool Race::operator == (Race^ first, Race^ second)
		{
			if(ReferenceEquals(first, second))
				return true;
			if(ReferenceEquals(nullptr, first))
				return false;
			return first->Equals(second);
		}

		bool Race::operator != (Race^ first, Race^ second)
		{
			return !(first == second);
		}
	}
}
