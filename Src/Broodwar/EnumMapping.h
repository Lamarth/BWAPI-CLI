#pragma once
#pragma unmanaged

#include <BWAPI\BulletType.h>
#include <BWAPI\Color.h>
#include <BWAPI\DamageType.h>
#include <BWAPI\Error.h>
#include <BWAPI\ExplosionType.h>
#include <BWAPI\GameType.h>
#include <BWAPI\Order.h>
#include <BWAPI\PlayerType.h>
#include <BWAPI\Race.h>
#include <BWAPI\TechType.h>
#include <BWAPI\UnitCommandType.h>
#include <BWAPI\UnitSizeType.h>
#include <BWAPI\UnitType.h>
#include <BWAPI\UpgradeType.h>
#include <BWAPI\WeaponType.h>

#pragma managed

#include "EnumClassMap.h"

#include "BWAPI\Enum\BulletType.h"
#include "BWAPI\Enum\DamageType.h"
#include "BWAPI\Enum\ErrorType.h"
#include "BWAPI\Enum\ExplosionType.h"
#include "BWAPI\Enum\GameType.h"
#include "BWAPI\Enum\OrderType.h"
#include "BWAPI\Enum\PlayerType.h"
#include "BWAPI\Enum\RaceType.h"
#include "BWAPI\Enum\TechType.h"
#include "BWAPI\Enum\TournamentAction.h"
#include "BWAPI\Enum\UnitCommandType.h"
#include "BWAPI\Enum\UnitSizeType.h"
#include "BWAPI\Enum\UnitType.h"
#include "BWAPI\Enum\UpgradeType.h"
#include "BWAPI\Enum\WeaponType.h"

using namespace BroodWar;

namespace BroodWar
{
	private ref class EnumMapping abstract sealed
	{
	public:
		static EnumClassMap<BWAPI::UnitCommandType, Api::Enum::UnitCommandType>^ UnitCommandType;
		static EnumClassMap<BWAPI::DamageType,      Api::Enum::DamageType>^ DamageType;
		static EnumClassMap<BWAPI::BulletType,      Api::Enum::BulletType>^ BulletType;
		static EnumClassMap<BWAPI::ExplosionType,   Api::Enum::ExplosionType>^ ExplosionType;
		static EnumClassMap<BWAPI::GameType,        Api::Enum::GameType>^ GameType;
		static EnumClassMap<BWAPI::PlayerType,      Api::Enum::PlayerType>^ PlayerType;
		static EnumClassMap<BWAPI::UnitSizeType,    Api::Enum::UnitSizeType>^ UnitSizeType;
		static EnumClassMap<BWAPI::Order,           Api::Enum::OrderType>^ OrderType;
		static EnumClassMap<BWAPI::Error,           Api::Enum::ErrorType>^ ErrorType;
		static EnumClassMap<BWAPI::Race,            Api::Enum::RaceType>^ RaceType;
		static EnumClassMap<BWAPI::UnitType,        Api::Enum::UnitType>^ UnitType;
		static EnumClassMap<BWAPI::TechType,        Api::Enum::TechType>^ TechType;
		static EnumClassMap<BWAPI::UpgradeType,     Api::Enum::UpgradeType>^ UpgradeType;
		static EnumClassMap<BWAPI::WeaponType,      Api::Enum::WeaponType>^ WeaponType;
				
		static EnumMapping();

		static System::Drawing::Color ToNativeColor(BWAPI::Color color);

		static System::Drawing::Color ToNativeColor(BWAPI::Color *color);

		static BWAPI::Color* ToBwColorPointer(System::Drawing::Color^ color);

		static BWAPI::Color ToBwColor(System::Drawing::Color^ color);
	};
}