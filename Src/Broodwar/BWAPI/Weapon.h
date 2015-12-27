#pragma once
#pragma unmanaged

#include <BWAPI\UnitType.h>
#include <BWAPI\WeaponType.h>

#pragma managed

#include "IIdentifiedObject.h"
#include "Enum\WeaponType.h"
#include "Enum\DamageType.h"
#include "Enum\ExplosionType.h"
#include "Enum\Targets.h"

using namespace System::Collections::Generic;

namespace BroodWar
{
	namespace Api
	{
		ref class UnitType;
		ref class Tech;
		ref class Upgrade;
		ref class DamageType;
		ref class ExplosionType;

		public ref class Weapon : public IIdentifiedObject
		{
		internal:
			BWAPI::WeaponType* instance;
			bool dispose;

			Weapon(Api::Enum::WeaponType type);
			Weapon(BWAPI::WeaponType *type);
			Weapon(BWAPI::WeaponType type);
			~Weapon();
			!Weapon();

		public:
			Weapon();
			Weapon(int id);

			virtual property int Id { int get(); }

			property Api::Enum::WeaponType Type { Api::Enum::WeaponType get(); }
			
			bool TypeEquals(Api::Enum::WeaponType weaponType);
			
			/// <summary>
			/// Returns the tech type that must be researched before this weapon can be used, or TechTypes::None if no tech type is required
			/// </summary>
			property Api::Tech^ Tech { Api::Tech^ get(); }
			
			/// <summary>
			/// Returns the unit that can use this weapon
			/// </summary>
			property Api::UnitType^ WhatUses { Api::UnitType^ get(); }
			
			/// <summary>
			/// Returns the amount of damage that this weapon deals per attack
			/// </summary>
			property int DamageAmount { int get(); }
			
			property int DamageBonus { int get(); }
			
			/// <summary>
			/// Returns the amount of cooldown time between attacks
			/// </summary>
			property int DamageCooldown { int get(); }
			
			/// <summary>
			/// Returns the amount that the damage increases per upgrade. see WeaponType::upgradeType
			/// </summary>
			property int DamageFactor { int get(); }
			
			/// <summary>
			/// Returns the upgrade type that can be upgraded to increase the attack damage
			/// </summary>
			property Api::Upgrade^ Upgrade { Api::Upgrade^ get(); }
			
			/// <summary>
			/// Returns the type of damage that this weapon uses (i.e. concussive, normal, explosive, etc)
			/// </summary>
			property Api::Enum::DamageType DamageType { Api::Enum::DamageType get(); }
			
			/// <summary>
			/// Returns the type of explosion that this weapon uses
			/// </summary>
			property Api::Enum::ExplosionType ExplosionType { Api::Enum::ExplosionType get(); }
			
			/// <summary>
			/// Returns the minimum attack range of the weapon, measured in pixels, 0 for most things except WeaponTypes::Arclite_Shock_Cannon
			/// (the weapon of the Terran Siege Tank in Siege Mode)
			/// </summary>
			property int MinRange { int get(); }
			
			/// <summary>
			/// Returns the maximum attack range of the weapon, measured in pixels
			/// </summary>
			property int MaxRange { int get(); }
			
			/// <summary>
			/// Inner radius used in splash damage calculations
			/// </summary>
			property int InnerSplashRadius { int get(); }
			
			/// <summary>
			/// Median radius used in splash damage calculations
			/// </summary>
			property int MedianSplashRadius { int get(); }
			
			/// <summary>
			/// Outer radius used in splash damage calculations
			/// </summary>
			property int OuterSplashRadius { int get(); }
			
			/// <summary>
			/// Returns what units can attack this weapon
			/// </summary>
			property Api::Enum::Targets Targets { Api::Enum::Targets get(); }

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(Weapon^ other);

			/// <summary>
			/// Returns the set of all the Weapons
			/// </summary>
			static property List<Weapon^>^ AllWeapons { List<Weapon^>^ get(); }

			/// <summary>
			/// Returns the set of all normal weapons
			/// </summary>
			static property List<Weapon^>^ NormalWeapons { List<Weapon^>^ get(); }

			/// <summary>
			/// Returns the set of all special weapons
			/// </summary>
			static property List<Weapon^>^ SpecialWeapons { List<Weapon^>^ get(); }

			static bool operator == (Weapon^ first, Weapon^ second);
			static bool operator != (Weapon^ first, Weapon^ second);
		};

		BWAPI::WeaponType ConvertWeapon(Weapon^ weapon);
		Weapon^ ConvertWeapon(BWAPI::WeaponType weapon);
	}
}
