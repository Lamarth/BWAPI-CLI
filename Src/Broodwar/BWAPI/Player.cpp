#include "Player.h"
#include "Race.h"
#include "Force.h"
#include "Weapon.h"
#include "TilePosition.h"
#include "Unit.h"

#include "..\EnumMapping.h"
#include "..\Util.h"

using namespace BroodWar;

namespace BroodWar
{
	namespace Api
	{
		Player^ ConvertPlayer(BWAPI::Player player)
		{
			if(player == NULL)
				return nullptr;
			return gcnew Player(player);
		}

		BWAPI::Player ConvertPlayer(Player^ player)
		{
			if(player == nullptr)
				return NULL;
			return player->instance;
		}

		Player::Player(BWAPI::Player player)
		{
			instance = player;
		}
			
		Api::Enum::PlayerType Player::Type::get()
		{
			return EnumMapping::PlayerType->Managed(instance->getType());
		}

		bool Player::TypeEquals(Api::Enum::PlayerType type)
		{
			return Type == type;
		}

		int Player::Id::get()
		{
			return instance->getID();
		}

		String^ Player::Name::get()
		{
			return gcnew String(instance->getName().c_str());
		}

		HashSet<Api::Unit^>^ Player::Units::get()
		{
			return ToHashSet<BWAPI::Unit, Unit^>(instance->getUnits(), &ConvertUnit);
		}

		Api::Race^ Player::Race::get()
		{
			return ConvertRace(instance->getRace());
		}

		Api::Force^ Player::Force::get()
		{
			return ConvertForce(instance->getForce());
		}

		bool Player::IsAlly(Api::Player^ player)
		{
			return instance->isAlly(ConvertPlayer(player));
		}

		bool Player::IsEnemy(Api::Player^ player)
		{
			return instance->isEnemy(ConvertPlayer(player));
		}

		bool Player::IsNeutral::get()
		{
			return instance->isNeutral();
		}

		Api::TilePosition^ Player::StartLocation::get()
		{
			return ConvertTilePosition(instance->getStartLocation());
		}

		bool Player::IsVictorious::get()
		{
			return instance->isVictorious();
		}

		bool Player::IsDefeated::get()
		{
			return instance->isDefeated();
		}

		bool Player::LeftGame::get()
		{
			return instance->leftGame();
		}

		int Player::Minerals::get()
		{
			return instance->minerals();
		}

		int Player::Gas::get()
		{
			return instance->gas();
		}

		int Player::GatheredMinerals::get()
		{
			return instance->gatheredMinerals();
		}

		int Player::GatheredGas::get()
		{
			return instance->gatheredGas();
		}

		int Player::RepairedMinerals::get()
		{
			return instance->repairedMinerals();
		}

		int Player::RepairedGas::get()
		{
			return instance->repairedGas();
		}

		int Player::RefundedMinerals::get()
		{
			return instance->refundedMinerals();
		}

		int Player::RefundedGas::get()
		{
			return instance->refundedGas();
		}

		int Player::SpentMinerals::get()
		{
			return instance->spentMinerals();
		}

		int Player::SpentGas::get()
		{
			return instance->spentGas();
		}

        int Player::SupplyTotal::get()
		{
			return instance->supplyTotal();
		}

		int Player::GetSupplyTotal(Api::Race^ race)
		{
			return instance->supplyTotal(ConvertRace(race));
		}

		int Player::SupplyUsed::get()
		{
			return instance->supplyUsed();
		}

		int Player::GetSupplyUsed(Api::Race^ race)
		{
			return instance->supplyUsed(ConvertRace(race));
		}

		int Player::AllUnitCount(Api::Enum::UnitType unit)
		{
			return instance->allUnitCount(EnumMapping::UnitType->Native(unit));
		}

		int Player::VisibleUnitCount(Api::Enum::UnitType unit)
		{
			return instance->visibleUnitCount(EnumMapping::UnitType->Native(unit));
		}

		int Player::CompletedUnitCount(Api::Enum::UnitType unit)
		{
			return instance->completedUnitCount(EnumMapping::UnitType->Native(unit));
		}

		int Player::IncompleteUnitCount(Api::Enum::UnitType unit)
		{
			return instance->incompleteUnitCount(EnumMapping::UnitType->Native(unit));
		}

		int Player::DeadUnitCount(Api::Enum::UnitType unit)
		{
			return instance->deadUnitCount(EnumMapping::UnitType->Native(unit));
		}

		int Player::KilledUnitCount(Api::Enum::UnitType unit)
		{
			return instance->killedUnitCount(EnumMapping::UnitType->Native(unit));
		}

		int Player::GetUpgradeLevel(Api::Enum::UpgradeType upgrade)
		{
			return instance->getUpgradeLevel(EnumMapping::UpgradeType->Native(upgrade));
		}

		bool Player::HasResearched(Api::Enum::TechType tech)
		{
			return instance->hasResearched(EnumMapping::TechType->Native(tech));
		}

		bool Player::IsResearching(Api::Enum::TechType tech)
		{
			return instance->isResearching(EnumMapping::TechType->Native(tech));
		}

		bool Player::IsUpgrading(Api::Enum::UpgradeType upgrade)
		{
			return instance->isUpgrading(EnumMapping::UpgradeType->Native(upgrade));
		}

		Color Player::Color::get()
		{
			return EnumMapping::ToNativeColor(instance->getColor());
		}

		int Player::TextColor::get()
		{
			return instance->getTextColor();
		}

		int Player::MaxEnergy(Api::Enum::UnitType unit)
		{
			return instance->maxEnergy(EnumMapping::UnitType->Native(unit));
		}

		double Player::TopSpeed(Api::Enum::UnitType unit)
		{
			return instance->topSpeed(EnumMapping::UnitType->Native(unit));
		}

		int Player::WeaponMaxRange(Api::Weapon^ weapon)
		{
			return instance->weaponMaxRange(ConvertWeapon(weapon));
		}

		int Player::SightRange(Api::Enum::UnitType unit)
		{
			return instance->sightRange(EnumMapping::UnitType->Native(unit));
		}

		int Player::WeaponDamageCooldown(Api::Enum::UnitType unit)
		{
			return instance->weaponDamageCooldown(EnumMapping::UnitType->Native(unit));
		}

		int Player::Armor(Api::Enum::UnitType unit)
		{
			return instance->armor(EnumMapping::UnitType->Native(unit));
		}

		int Player::UnitScore::get()
		{
			return instance->getUnitScore();
		}

		int Player::KillScore::get()
		{
			return instance->getKillScore();
		}

		int Player::BuildingScore::get()
		{
			return instance->getBuildingScore();
		}

		int Player::RazingScore::get()
		{
			return instance->getRazingScore();
		}

		int Player::CustomScore::get()
		{
			return instance->getCustomScore();
		}

		bool Player::IsObserver::get()
		{
			return instance->isObserver();
		}

		int Player::GetMaxUpgradeLevel(Api::Enum::UpgradeType upgrade)
		{
			return instance->getMaxUpgradeLevel(EnumMapping::UpgradeType->Native(upgrade));
		}

		bool Player::IsResearchAvailable(Api::Enum::TechType tech)
		{
			return instance->isResearchAvailable(EnumMapping::TechType->Native(tech));
		}

		bool Player::IsUnitAvailable(Api::Enum::UnitType unit)
		{
			return instance->isUnitAvailable(EnumMapping::UnitType->Native(unit));
		}

		int Player::GetHashCode()
		{
			return instance->getID();
		}

		bool Player::Equals(Object^ o)
		{
			Api::Player^ other = dynamic_cast<Api::Player^>(o);
			return this->Equals(other);
		}

		bool Player::Equals(Api::Player^ other)
		{
			if(ReferenceEquals(nullptr, other))
				return false;
			if(ReferenceEquals(this, other))
				return true;
			return this->instance->getID() == other->instance->getID();
		}

		bool Player::operator == (Api::Player^ first, Api::Player^ second)
		{
			if(ReferenceEquals(first, second))
				return true;
			if(ReferenceEquals(nullptr, first))
				return false;
			return first->Equals(second);
		}

		bool Player::operator != (Api::Player^ first, Api::Player^ second)
		{
			return !(first == second);
		}
	}
}
