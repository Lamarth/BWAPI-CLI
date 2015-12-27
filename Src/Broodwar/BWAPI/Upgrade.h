#pragma once
#pragma unmanaged

#include <BWAPI\UpgradeType.h>

#pragma managed

#include "Race.h"
#include "IIdentifiedObject.h"
#include "Enum\UpgradeType.h"

using namespace System::Collections::Generic;

namespace BroodWar
{
	namespace Api
	{
		public ref class Upgrade : public IIdentifiedObject
		{
		internal:
			BWAPI::UpgradeType* instance;
			bool dispose;

			Upgrade(Api::Enum::UpgradeType type);
			Upgrade(BWAPI::UpgradeType* type);
			Upgrade(BWAPI::UpgradeType type);
			~Upgrade();
			!Upgrade();

		public:
			Upgrade();
			Upgrade(int id);

			virtual property int Id { int get(); }

			property UpgradeType Type { UpgradeType get(); }
			
			bool TypeEquals(UpgradeType type);
			
			/// <summary>
			/// Returns the race the upgrade is for. For example, UpgradeTypes::Terran_Infantry_Armor.getRace() will return Races::Terran
			/// </summary>
			property Api::Race^ Race { Api::Race^ get(); }
			
			/// <summary>
			/// Returns the mineral price for the first upgrade
			/// </summary>
			int MineralPrice(int level);
			
			/// <summary>
			/// Returns the amount that the mineral price increases for each additional upgrade
			/// </summary>
			property int MineralPriceFactor { int get(); }
			
			/// <summary>
			/// Returns the vespene gas price for the first upgrade
			/// </summary>
			int GasPrice(int level);
			
			/// <summary>
			/// Returns the amount that the vespene gas price increases for each additional upgrade
			/// </summary>
			property int GasPriceFactor { int get(); }
			
			/// <summary>
			/// Returns the number of frames needed to research the first upgrade
			/// </summary>
			int UpgradeTime(int level);
			
			/// <summary>
			/// Returns the number of frames that the upgrade time increases for each additional upgrade
			/// </summary>
			property int UpgradeTimeFactor { int get(); }
			
			/// <summary>
			/// Returns the maximum number of times the upgrade can be researched
			/// </summary>
			property int MaxRepeats { int get(); }
			
			/// <summary>
			/// Returns the type of unit that researches the upgrade
			/// </summary>
			property Api::UnitType^ WhatUpgrades { Api::UnitType^ get(); }
			
			/// <summary>
			/// Returns the type of unit that is additionally required for the upgrade
			/// </summary>
			Api::UnitType^ WhatsRequired(int level);
			
			/// <summary>
			/// Returns the set of units that are affected by this upgrade
			/// </summary>
			property HashSet<Api::UnitType^>^ WhatUses { HashSet<Api::UnitType^>^ get(); }

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(Upgrade^ other);

			static property List<Upgrade^>^ AllUpgrades { List<Upgrade^>^ get(); }

			static bool operator == (Upgrade^ first, Upgrade^ second);
			static bool operator != (Upgrade^ first, Upgrade^ second);
		};

		Upgrade^ ConvertUpgrade(BWAPI::UpgradeType upgrade);
		BWAPI::UpgradeType ConvertUpgrade(Upgrade^ upgrade);
		BWAPI::UpgradeType ConvertUpgrade(Enum::UpgradeType upgrade);
	}
}
