#include "UnitType.h"
#include "Race.h"
#include "Weapon.h"
#include "Tech.h"
#include "Upgrade.h"

#include "..\EnumMapping.h"
#include "..\Util.h"

using namespace BroodWar;

namespace BroodWar
{
	namespace Api
	{
		UnitType^ ConvertUnitType(BWAPI::UnitType unitType)
		{
			return gcnew UnitType(unitType);
		}

		BWAPI::UnitType ConvertUnitType(UnitType^ unitType)
		{
			if(unitType == nullptr)
				return BWAPI::UnitType();
			return BWAPI::UnitType(*(unitType->instance));
		}
		
		BWAPI::UnitType ConvertUnitType(Enum::UnitType unitType)
		{
			return EnumMapping::UnitType->Native(unitType);
		}

		UnitType::UnitType(Api::Enum::UnitType type)
		{
			instance = EnumMapping::UnitType->NativePointer(type);
			dispose = true;
		}

		UnitType::UnitType(BWAPI::UnitType* type)
		{
			instance = type;
			dispose = false;
		}

		UnitType::UnitType(BWAPI::UnitType type)
		{
			instance = new BWAPI::UnitType(type);
			dispose = true;
		}

		UnitType::~UnitType()
		{
			if(dispose)
				delete instance;
		}

		UnitType::!UnitType()
		{
			if(dispose)
				delete instance;
		}
		
		UnitType::UnitType()
		{
			instance = new BWAPI::UnitType();
			dispose = true;
		}
		
		UnitType::UnitType(int id)
		{
			instance = new BWAPI::UnitType(id);
			dispose = true;
		}

		int UnitType::Id::get()
		{
			return instance->getID();
		}

		Api::Enum::UnitType UnitType::Type::get()
		{
			return EnumMapping::UnitType->Managed(instance);
		}

		bool UnitType::TypeEquals(Api::Enum::UnitType type)
		{
			return Type == type;
		}

		Api::Race^ UnitType::Race::get()
		{
			return ConvertRace(instance->getRace());
		}

		Tuple<Api::UnitType^, int>^ UnitType::WhatBuilds::get()
		{
			return ToTuple<BWAPI::UnitType, int, Api::UnitType^, int>(instance->whatBuilds(), &ConvertUnitType, &IntToInt);
		}
			
		Dictionary<Api::UnitType^, int>^ UnitType::RequiredUnits::get()
		{
			return ToDictionary<BWAPI::UnitType, int, Api::UnitType^, int>(instance->requiredUnits(), &ConvertUnitType, &IntToInt);
		}
			
		Api::Tech^ UnitType::RequiredTech::get()
		{
			return ConvertTech(instance->requiredTech());
		}
			
		Api::Tech^ UnitType::CloakingTech::get()
		{
			return ConvertTech(instance->cloakingTech());
		}
			
		HashSet<Api::Tech^>^ UnitType::Abilities::get()
		{
			return ToHashSet<BWAPI::TechType, Tech^>(instance->abilities(), &ConvertTech);
		}
			
		HashSet<Api::Upgrade^>^ UnitType::Upgrades::get()
		{
			return ToHashSet<BWAPI::UpgradeType, Upgrade^>(instance->upgrades(), &ConvertUpgrade);
		}
			
		Api::Upgrade^ UnitType::ArmorUpgrade::get()
		{
			return ConvertUpgrade(instance->armorUpgrade());
		}
			
		int UnitType::MaxHitPoints::get()
		{
			return instance->maxHitPoints();
		}
			
		int UnitType::MaxShields::get()
		{
			return instance->maxShields();
		}
			
		int UnitType::MaxEnergy::get()
		{
			return instance->maxEnergy();
		}
			
		int UnitType::Armor::get()
		{
			return instance->armor();
		}
			
		Api::Price^ UnitType::Price::get()
		{
			return gcnew Api::Price(instance->mineralPrice(), instance->gasPrice(), instance->buildTime(), instance->supplyRequired());
		}
			
		int UnitType::ProvidedSupply::get()
		{
			return instance->supplyProvided();
		}
			
		int UnitType::RequiredSpace::get()
		{
			return instance->spaceRequired();
		}
			
		int UnitType::ProvidedSpace::get()
		{
			return instance->spaceProvided();
		}
			
		int UnitType::BuildScore::get()
		{
			return instance->buildScore();
		}
			
		int UnitType::DestroyScore::get()
		{
			return instance->destroyScore();
		}
			
		Api::Enum::UnitSizeType UnitType::Size::get()
		{
			return EnumMapping::UnitSizeType->Managed(instance->size());
		}
			
		int UnitType::TileWidth::get()
		{
			return instance->tileWidth();
		}
			
		int UnitType::TileHeight::get()
		{
			return instance->tileHeight();
		}
			
		int UnitType::DimensionLeft::get()
		{
			return instance->dimensionLeft();
		}
			
		int UnitType::DimensionUp::get()
		{
			return instance->dimensionUp();
		}
			
		int UnitType::DimensionRight::get()
		{
			return instance->dimensionRight();
		}
			
		int UnitType::DimensionDown::get()
		{
			return instance->dimensionDown();
		}
			
		int UnitType::SeekRange::get()
		{
			return instance->seekRange();
		}
			
		int UnitType::SightRange::get()
		{
			return instance->sightRange();
		}
			
		Api::Weapon^ UnitType::GroundWeapon::get()
		{
			return ConvertWeapon(instance->groundWeapon());
		}
			
		int UnitType::MaxGroundHits::get()
		{
			return instance->maxGroundHits();
		}
			
		Api::Weapon^ UnitType::AirWeapon::get()
		{
			return ConvertWeapon(instance->airWeapon());
		}
			
		int UnitType::MaxAirHits::get()
		{
			return instance->maxAirHits();
		}
			
		double UnitType::TopSpeed::get()
		{
			return instance->topSpeed();
		}
			
		int UnitType::Acceleration::get()
		{
			return instance->acceleration();
		}
			
		int UnitType::HaltDistance::get()
		{
			return instance->haltDistance();
		}
			
		int UnitType::TurnRadius::get()
		{
			return instance->turnRadius();
		}
			
		bool UnitType::CanProduce::get()
		{
			return instance->canProduce();
		}
			
		bool UnitType::CanAttack::get()
		{
			return instance->canAttack();
		}
			
		bool UnitType::CanMove::get()
		{
			return instance->canMove();
		}
			
		bool UnitType::IsFlyer::get()
		{
			return instance->isFlyer();
		}
			
		bool UnitType::RegeneratesHp::get()
		{
			return instance->regeneratesHP();
		}
			
		bool UnitType::IsSpellcaster::get()
		{
			return instance->isSpellcaster();
		}
			
		bool UnitType::HasPermanentCloak::get()
		{
			return instance->hasPermanentCloak();
		}
			
		bool UnitType::IsInvincible::get()
		{
			return instance->isInvincible();
		}
			
		bool UnitType::IsOrganic::get()
		{
			return instance->isOrganic();
		}
			
		bool UnitType::IsMechanical::get()
		{
			return instance->isMechanical();
		}
			
		bool UnitType::IsRobotic::get()
		{
			return instance->isRobotic();
		}
			
		bool UnitType::IsDetector::get()
		{
			return instance->isDetector();
		}
			
		bool UnitType::IsResourceContainer::get()
		{
			return instance->isResourceContainer();
		}
			
		bool UnitType::IsResourceDepot::get()
		{
			return instance->isResourceDepot();
		}
			
		bool UnitType::IsRefinery::get()
		{
			return instance->isRefinery();
		}
			
		bool UnitType::IsWorker::get()
		{
			return instance->isWorker();
		}
			
		bool UnitType::RequiresPsi::get()
		{
			return instance->requiresPsi();
		}
			
		bool UnitType::RequiresCreep::get()
		{
			return instance->requiresCreep();
		}
			
		bool UnitType::IsTwoUnitsInOneEgg::get()
		{
			return instance->isTwoUnitsInOneEgg();
		}
			
		bool UnitType::IsBurrowable::get()
		{
			return instance->isBurrowable();
		}
			
		bool UnitType::IsCloakable::get()
		{
			return instance->isCloakable();
		}
			
		bool UnitType::IsBuilding::get()
		{
			return instance->isBuilding();
		}
			
		bool UnitType::IsAddon::get()
		{
			return instance->isAddon();
		}
			
		bool UnitType::IsFlyingBuilding::get()
		{
			return instance->isFlyingBuilding();
		}
			
		bool UnitType::IsNeutral::get()
		{
			return instance->isNeutral();
		}
			
		bool UnitType::IsHero::get()
		{
			return instance->isHero();
		}
			
		bool UnitType::IsPowerup::get()
		{
			return instance->isPowerup();
		}
			
		bool UnitType::IsBeacon::get()
		{
			return instance->isBeacon();
		}
			
		bool UnitType::IsFlagBeacon::get()
		{
			return instance->isFlagBeacon();
		}
			
		bool UnitType::IsSpecialBuilding::get()
		{
			return instance->isSpecialBuilding();
		}
			
		bool UnitType::IsSpell::get()
		{
			return instance->isSpell();
		}
			
		bool UnitType::ProducesLarva::get()
		{
			return instance->producesLarva();
		}

		bool UnitType::IsMineralField::get()
		{
			return instance->isMineralField();
		}

		bool UnitType::CanBuildAddon::get()
		{
			return instance->canBuildAddon();
		}

		int UnitType::GetHashCode()
		{
			return instance->getID();
		}

		bool UnitType::Equals(Object^ o)
		{
			UnitType^ other = dynamic_cast<UnitType^>(o);
			return this->Equals(other);
		}

		bool UnitType::Equals(UnitType^ other)
		{
			if(ReferenceEquals(nullptr, other))
				return false;
			if(ReferenceEquals(this, other))
				return true;
			return this->instance->getID() == other->instance->getID();
		}

		List<UnitType^>^ UnitType::AllUnitTypes::get()
		{
			return ToList<BWAPI::UnitType, UnitType^>(BWAPI::UnitTypes::allUnitTypes(), &ConvertUnitType);
		}

		List<UnitType^>^ UnitType::AllMacroTypes::get()
		{
			return ToList<BWAPI::UnitType, UnitType^>(BWAPI::UnitTypes::allMacroTypes(), &ConvertUnitType);
		}

		bool UnitType::operator == (UnitType^ first, UnitType^ second)
		{
			if(ReferenceEquals(first, second))
				return true;
			if(ReferenceEquals(nullptr, first))
				return false;
			return first->Equals(second);
		}

		bool UnitType::operator != (UnitType^ first, UnitType^ second)
		{
			return !(first == second);
		}
	}
}
