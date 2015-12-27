#include "Upgrade.h"
#include "UnitType.h"
#include "Race.h"

#include "..\EnumMapping.h"
#include "..\Util.h"

using namespace BroodWar;

namespace BroodWar
{
	namespace Api
	{
		Upgrade^ ConvertUpgrade(BWAPI::UpgradeType upgrade)
		{
			return gcnew Upgrade(upgrade);
		}

		BWAPI::UpgradeType ConvertUpgrade(Upgrade^ upgrade)
		{
			if(upgrade == nullptr)
				return BWAPI::UpgradeType();
			return BWAPI::UpgradeType(*(upgrade->instance));
		}
		
		BWAPI::UpgradeType ConvertUpgrade(Enum::UpgradeType upgrade)
		{
			return EnumMapping::UpgradeType->Native(upgrade);
		}

		Upgrade::Upgrade(Api::Enum::UpgradeType type)
		{
			instance = EnumMapping::UpgradeType->NativePointer(type);
			dispose = true;
		}

		Upgrade::Upgrade(BWAPI::UpgradeType* type)
		{
			instance = type;
			dispose = false;
		}
			
		Upgrade::Upgrade(BWAPI::UpgradeType type)
		{
			instance = new BWAPI::UpgradeType(type);
			dispose = true;
		}
			
		Upgrade::~Upgrade()
		{
			if(dispose)
				delete instance;
		}
			
		Upgrade::!Upgrade()
		{
			if(dispose)
				delete instance;
		}
		
		Upgrade::Upgrade()
		{
			instance = new BWAPI::UpgradeType();
			dispose = true;
		}
		
		Upgrade::Upgrade(int id)
		{
			instance = new BWAPI::UpgradeType(id);
			dispose = true;
		}

		int Upgrade::Id::get()
		{
			return instance->getID();
		}

		Api::Enum::UpgradeType Upgrade::Type::get()
		{
			return EnumMapping::UpgradeType->Managed(instance);
		}
			
		bool Upgrade::TypeEquals(Api::Enum::UpgradeType type)
		{
			return Type == type;
		}
			
		Api::Race^ Upgrade::Race::get()
		{
			return ConvertRace(instance->getRace());
		}
			
		int Upgrade::MineralPrice(int level)
		{
			return instance->mineralPrice(level);
		}
			
		int Upgrade::MineralPriceFactor::get()
		{
			return instance->mineralPriceFactor();
		}
			
		int Upgrade::GasPrice(int level)
		{
			return instance->gasPrice(level);
		}
			
		int Upgrade::GasPriceFactor::get()
		{
			return instance->gasPriceFactor();
		}
			
		int Upgrade::UpgradeTime(int level)
		{
			return instance->upgradeTime(level);
		}
			
		int Upgrade::UpgradeTimeFactor::get()
		{
			return instance->upgradeTimeFactor();
		}
			
		int Upgrade::MaxRepeats::get()
		{
			return instance->maxRepeats();
		}
			
		Api::UnitType^ Upgrade::WhatUpgrades::get()
		{
			return ConvertUnitType(instance->whatUpgrades());
		}
			
		Api::UnitType^ Upgrade::WhatsRequired(int level)
		{
			return ConvertUnitType(instance->whatsRequired(level));
		}
			
		HashSet<Api::UnitType^>^ Upgrade::WhatUses::get()
		{
			return ToHashSet<BWAPI::UnitType, Api::UnitType^>(instance->whatUses(), &ConvertUnitType);
		}

		int Upgrade::GetHashCode()
		{
			return instance->getID();
		}

		bool Upgrade::Equals(Object^ o)
		{
			Upgrade^ other = dynamic_cast<Upgrade^>(o);
			return this->Equals(other);
		}

		bool Upgrade::Equals(Upgrade^ other)
		{
			if(ReferenceEquals(nullptr, other))
				return false;
			if(ReferenceEquals(this, other))
				return true;
			return this->instance->getID() == other->instance->getID();
		}

		List<Upgrade^>^ Upgrade::AllUpgrades::get()
		{
			return ToList<BWAPI::UpgradeType, Upgrade^>(BWAPI::UpgradeTypes::allUpgradeTypes(), &ConvertUpgrade);
		}

		bool Upgrade::operator == (Upgrade^ first, Upgrade^ second)
		{
			if(ReferenceEquals(first, second))
				return true;
			if(ReferenceEquals(nullptr, first))
				return false;
			return first->Equals(second);
		}

		bool Upgrade::operator != (Upgrade^ first, Upgrade^ second)
		{
			return !(first == second);
		}
	}
}
