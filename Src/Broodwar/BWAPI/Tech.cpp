#include "Tech.h"
#include "Race.h"
#include "Weapon.h"
#include "UnitType.h"

#include "..\EnumMapping.h"
#include "..\Util.h"

using namespace System::Collections::Generic;
using namespace BroodWar;

namespace BroodWar
{
	namespace Api
	{
		Tech^ ConvertTech(BWAPI::TechType tech)
		{
			return gcnew Tech(tech);
		}

		BWAPI::TechType ConvertTech(Tech^ tech)
		{
			if(tech == nullptr)
				return BWAPI::TechType();
			return BWAPI::TechType(*(tech->instance));
		}

		BWAPI::TechType ConvertTech(TechType tech)
		{
			return EnumMapping::TechType->Native(tech);
		}

		Tech::Tech(Api::Enum::TechType type)
		{
			instance = EnumMapping::TechType->NativePointer(type);
			dispose = true;
		}

		Tech::Tech(BWAPI::TechType *type)
		{
			instance = type;
			dispose = false;
		}

		Tech::Tech(BWAPI::TechType type)
		{
			instance = new BWAPI::TechType(type);
			dispose = true;
		}

		Tech::~Tech()
		{
			if(dispose)
				delete instance;
		}

		Tech::!Tech()
		{
			if(dispose)
				delete instance;
		}

		Tech::Tech()
		{
			instance = new BWAPI::TechType();
			dispose = true;
		}
		
		Tech::Tech(int id)
		{
			instance = new BWAPI::TechType(id);
			dispose = true;
		}

		int Tech::Id::get()
		{
			return instance->getID();
		}

		Api::Enum::TechType Tech::Type::get()
		{
			return EnumMapping::TechType->Managed(instance);
		}

		bool Tech::TypeEquals(Api::Enum::TechType techType)
		{
			return Type == techType;
		}

		Api::Race^ Tech::Race::get()
		{
			return ConvertRace(instance->getRace());
		}

		int Tech::MineralPrice::get()
		{
			return instance->mineralPrice();
		}

		int Tech::GasPrice::get()
		{
			return instance->gasPrice();
		}

		int Tech::ResearchTime::get()
		{
			return instance->researchTime();
		}

		int Tech::EnergyCost::get()
		{
			return instance->energyCost();
		}

		Api::UnitType^ Tech::WhatResearches::get()
		{
			return ConvertUnitType(instance->whatResearches());
		}

		Api::Weapon^ Tech::Weapon::get()
		{
			return ConvertWeapon(instance->getWeapon());
		}

		bool Tech::TargetsUnit::get()
		{
			return instance->targetsUnit();
		}

		bool Tech::TargetsPosition::get()
		{
			return instance->targetsPosition();
		}

		HashSet<Api::UnitType^>^ Tech::WhatUses::get()
		{
			return ToHashSet<BWAPI::UnitType, UnitType^>(instance->whatUses(), &ConvertUnitType);
		}

		Api::Enum::OrderType Tech::Order::get()
		{
			return EnumMapping::OrderType->Managed(instance->getOrder());
		}

		int Tech::GetHashCode()
		{
			return instance->getID();
		}

		bool Tech::Equals(Object^ o)
		{
			Tech^ other = dynamic_cast<Tech^>(o);
			return this->Equals(other);
		}

		bool Tech::Equals(Tech^ other)
		{
			if(ReferenceEquals(nullptr, other))
				return false;
			if(ReferenceEquals(this, other))
				return true;
			return this->instance->getID() == other->instance->getID();
		}

		List<Tech^>^ Tech::AllTechs::get()
		{
			return ToList<BWAPI::TechType, Tech^>(BWAPI::TechTypes::allTechTypes(), &ConvertTech);
		}

		bool Tech::operator == (Tech^ first, Tech^ second)
		{
			if(ReferenceEquals(first, second))
				return true;
			if(ReferenceEquals(nullptr, first))
				return false;
			return first->Equals(second);
		}

		bool Tech::operator != (Tech^ first, Tech^ second)
		{
			return !(first == second);
		}
	}
}
