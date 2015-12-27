#pragma once
#pragma unmanaged

#include <BWAPI/Race.h>

#pragma managed

#include "IIdentifiedObject.h"
#include "Enum\RaceType.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace BroodWar::Api::Enum;

namespace BroodWar
{
	namespace Api
	{
		ref class UnitType;

		public ref class Race : public IIdentifiedObject
		{
		internal:
			BWAPI::Race* instance;
			bool dispose;

			Race(RaceType race);
			Race(BWAPI::Race* race);
			Race(BWAPI::Race race);
			~Race();
			!Race();

		public:
			Race();

			Race(int id);

			virtual property int Id { int get(); }

			/// <summary>
			/// Returns the name of the race. For example Races::Terran.getName() will return a std::string object containing "Terran"
			/// </summary>
			virtual String^ ToString() override;

			property RaceType Type { RaceType get(); }

			bool TypeEquals(RaceType raceType);

			/// <summary>
			/// Returns the worker unit type for the given race. For example Races::Protoss.getWorker() will return a pointer to UnitTypes::Protoss_Probe
			/// </summary>
			property UnitType^ Worker { UnitType^ get(); }

			/// <summary>
			/// Returns the center unit type for the given race. For example Races::Terran.getCenter() will return a pointer to UnitTypes::Terran_Command_Center.
			/// While there are three center types for Zerg (Hatchery, Lair, and Hive), Races::Zerg.getCenter() will only return a pointer to UnitTypes::Zerg_Hatchery,
			/// since it is the unit type needed to make a new center
			/// </summary>
			property UnitType^ Center { UnitType^ get(); }

			/// <summary>
			/// Returns the refinery unit type for the given race. For example: Races::Zerg.getRefinery() will return a pointer to UnitTypes::Zerg_Extractor?
			/// </summary>
			property UnitType^ Refinery { UnitType^ get(); }

			/// <summary>
			/// Returns the transport unit type for the given race. For example: Races::Protoss.getTransport() will return a pointer to UnitTypes::Protoss_Shuttle
			/// </summary>
			property UnitType^ Transport { UnitType^ get(); }

			/// <summary>
			/// Returns the main supply provider unit type for the given race. For example: Races::Terran.getSupplyProvider() will return a pointer to
			/// UnitTypes::Terran_Supply_Depot?
			/// </summary>
			property UnitType^ SupplyProvider { UnitType^ get(); }

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(Race^ other);

			static property List<Race^>^ AllRaces { List<Race^>^ get(); }

			static bool operator == (Race^ first, Race^ second);
			static bool operator != (Race^ first, Race^ second);
		};

		Race^ ConvertRace(BWAPI::Race* race);
		Race^ ConvertRace(BWAPI::Race race);
		BWAPI::Race ConvertRace(Race^ race);
	}
}
