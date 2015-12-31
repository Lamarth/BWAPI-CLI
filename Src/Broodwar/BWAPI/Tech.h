#pragma once
#pragma unmanaged

#include <BWAPI\UnitType.h>
#include <BWAPI\WeaponType.h>
#include <BWAPI\TechType.h>

#pragma managed

#include "Race.h"
#include "Price.h"
#include "IIdentifiedObject.h"
#include "Enum\OrderType.h"
#include "Enum\TechType.h"

using namespace System::Collections::Generic;

namespace BroodWar
{
	namespace Api
	{
		ref class UnitType;
		ref class Weapon;

		public ref class Tech sealed
		{
		internal:
			BWAPI::TechType* instance;
			bool dispose;

			Tech(Api::Enum::TechType type);
			Tech(BWAPI::TechType *type);
			Tech(BWAPI::TechType type);
			~Tech();
			!Tech();

		public:
			Tech();
			Tech(int id);

			virtual property int Id { int get(); }

			property Api::Enum::TechType Type { Api::Enum::TechType get(); }

			bool TypeEquals(Api::Enum::TechType techType);

			/// <summary>
			/// Returns the race that uses the TechType. For example, TechTypes::Scanner_Sweep?.getRace() will return Races::Terran
			/// </summary>
			property Api::Race^ Race { Api::Race^ get(); }

            /// <summary>
            /// Tech price
            /// </summary>
            property Api::Price^ Price { Api::Price^ get(); }

			/// <summary>
			/// Returns the amount of energy used each time this tech type is used
			/// </summary>
			property int EnergyCost { int get(); }
			
			/// <summary>
			/// Returns the type of unit that researches this tech type. If this tech type is available for free (does not need to be researched),
			/// then this method will return UnitTypes::None
			/// </summary>
			property Api::UnitType^ WhatResearches { Api::UnitType^ get(); }
			
			/// <summary>
			/// Returns the corresponding weapon for this tech type, or TechTypes::None if no corresponding weapon exists. For example, TechTypes::Dark_Swarm.getWeapon()
			/// will return a pointer to WeaponTypes::Dark_Swarm
			/// </summary>
			property Api::Weapon^ Weapon { Api::Weapon^ get(); }
			
			/// <summary>
			/// Returns true if this tech type must be used on another unit (i.e. Irradiate)
			/// </summary>
			property bool TargetsUnit { bool get(); }
			
			/// <summary>
			/// Returns true if this tech type must be specified a position (i.e. Dark Swarm)
			/// </summary>
			property bool TargetsPosition { bool get(); }
			
			/// <summary>
			/// Returns the set of units that can use this tech type. Usually this will just be a set of one unit type, however in some cases, such as
			/// TechTypes::Burrowing, several unit types will be returned
			/// </summary>
			property HashSet<Api::UnitType^>^ WhatUses { HashSet<Api::UnitType^>^ get(); }
			
			/// <summary>
			/// Returns the order used to execute this tech type as an action
			/// </summary>
			property Api::Enum::OrderType Order { Api::Enum::OrderType get(); }

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(Tech^ other);

			static property List<Tech^>^ AllTechs { List<Tech^>^ get(); }

			static bool operator == (Tech^ first, Tech^ second);
			static bool operator != (Tech^ first, Tech^ second);
		};

		Tech^ ConvertTech(BWAPI::TechType tech);
		BWAPI::TechType ConvertTech(Tech^ tech);
		BWAPI::TechType ConvertTech(TechType tech);
	}
}
