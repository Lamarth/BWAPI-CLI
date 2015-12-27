#include "Weapon.h"
#include "Tech.h"
#include "UnitType.h"
#include "Upgrade.h"

#include "..\EnumMapping.h"

namespace BroodWar
{
	namespace Api
	{
		BWAPI::WeaponType ConvertWeapon(Weapon^ weapon)
		{
			if(weapon == nullptr)
				return BWAPI::WeaponType();
			return *(weapon->instance);
		}

		Weapon^ ConvertWeapon(BWAPI::WeaponType weapon)
		{
			return gcnew Weapon(weapon);
		}

		Weapon::Weapon(Api::Enum::WeaponType type)
		{
			instance = EnumMapping::WeaponType->NativePointer(type);
			dispose = true;
		}

		Weapon::Weapon(BWAPI::WeaponType *type)
		{
			instance = type;
			dispose = false;
		}

		Weapon::Weapon(BWAPI::WeaponType type)
		{
			instance = new BWAPI::WeaponType(type);
			dispose = true;
		}

		Weapon::~Weapon()
		{
			if(dispose)
				delete instance;
		}

		Weapon::!Weapon()
		{
			if(dispose)
				delete instance;
		}

		Weapon::Weapon()
		{
			instance = new BWAPI::WeaponType();
			dispose = true;
		}
		
		Weapon::Weapon(int id)
		{
			instance = new BWAPI::WeaponType(id);
			dispose = true;
		}

		int Weapon::Id::get()
		{
			return instance->getID();
		}

		Api::Enum::WeaponType Weapon::Type::get()
		{
			return EnumMapping::WeaponType->Managed(instance);
		}

		bool Weapon::TypeEquals(Api::Enum::WeaponType weaponType)
		{
			return Type == weaponType;
		}

		Api::Tech^ Weapon::Tech::get()
		{
			return ConvertTech(instance->getTech());
		}

		Api::UnitType^ Weapon::WhatUses::get()
		{
			return ConvertUnitType(instance->whatUses());
		}

		int Weapon::DamageAmount::get()
		{
			return instance->damageAmount();
		}

		int Weapon::DamageBonus::get()
		{
			return instance->damageBonus();
		}

		int Weapon::DamageCooldown::get()
		{
			return instance->damageCooldown();
		}

		int Weapon::DamageFactor::get()
		{
			return instance->damageFactor();
		}

		Api::Upgrade^ Weapon::Upgrade::get()
		{
			return ConvertUpgrade(instance->upgradeType());
		}

		Api::Enum::DamageType Weapon::DamageType::get()
		{
			return EnumMapping::DamageType->Managed(instance->damageType());
		}

		Api::Enum::ExplosionType Weapon::ExplosionType::get()
		{
			return EnumMapping::ExplosionType->Managed(instance->explosionType());
		}

		int Weapon::MinRange::get()
		{
			return instance->minRange();
		}

		int Weapon::MaxRange::get()
		{
			return instance->maxRange();
		}

		int Weapon::InnerSplashRadius::get()
		{
			return instance->innerSplashRadius();
		}

		int Weapon::MedianSplashRadius::get()
		{
			return instance->medianSplashRadius();
		}

		int Weapon::OuterSplashRadius::get()
		{
			return instance->outerSplashRadius();
		}

		Api::Enum::Targets Weapon::Targets::get()
		{
			Api::Enum::Targets rez = Api::Enum::Targets::None;
			if(instance->targetsAir())
				rez = rez | Api::Enum::Targets::Air;
			if(instance->targetsGround())
				rez = rez | Api::Enum::Targets::Ground;
			if(instance->targetsMechanical())
				rez = rez | Api::Enum::Targets::Mechanical;
			if(instance->targetsOrganic())
				rez = rez | Api::Enum::Targets::Organic;
			if(instance->targetsNonBuilding())
				rez = rez | Api::Enum::Targets::NonBuilding;
			if(instance->targetsNonRobotic())
				rez = rez | Api::Enum::Targets::NonRobotic;
			if(instance->targetsTerrain())
				rez = rez | Api::Enum::Targets::Terrain;
			if(instance->targetsOrgOrMech())
				rez = rez | Api::Enum::Targets::OrgOrMech;
			if(instance->targetsOwn())
				rez = rez | Api::Enum::Targets::Own;
			return rez;
		}

		int Weapon::GetHashCode()
		{
			return instance->getID();
		}

		bool Weapon::Equals(Object^ o)
		{
			Weapon^ other = dynamic_cast<Weapon^>(o);
			return this->Equals(other);
		}

		bool Weapon::Equals(Weapon^ other)
		{
			if(ReferenceEquals(nullptr, other))
				return false;
			if(ReferenceEquals(this, other))
				return true;
			return this->instance->getID() == other->instance->getID();
		}

		List<Weapon^>^ Weapon::AllWeapons::get()
		{
			return ToList<BWAPI::WeaponType, Weapon^>(BWAPI::WeaponTypes::allWeaponTypes(), &ConvertWeapon);
		}

		List<Weapon^>^ Weapon::NormalWeapons::get()
		{
			return ToList<BWAPI::WeaponType, Weapon^>(BWAPI::WeaponTypes::normalWeaponTypes(), &ConvertWeapon);
		}

		List<Weapon^>^ Weapon::SpecialWeapons::get()
		{
			return ToList<BWAPI::WeaponType, Weapon^>(BWAPI::WeaponTypes::specialWeaponTypes(), &ConvertWeapon);
		}

		bool Weapon::operator == (Weapon^ first, Weapon^ second)
		{
			if(ReferenceEquals(first, second))
				return true;
			if(ReferenceEquals(nullptr, first))
				return false;
			return first->Equals(second);
		}

		bool Weapon::operator != (Weapon^ first, Weapon^ second)
		{
			return !(first == second);
		}
	}
}
