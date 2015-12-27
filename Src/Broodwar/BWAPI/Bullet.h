#pragma once
#pragma unmanaged

#include <BWAPI/Bullet.h>

#pragma managed

#include "Enum\BulletType.h"
#include "Position.h"
#include "IIdentifiedObject.h"

using namespace System;
using namespace BroodWar;
using namespace BroodWar::Api;
using namespace BroodWar::Api::Enum;

namespace BroodWar
{
	namespace Api
	{
		ref class Player;
		ref class Unit;

		public ref class Bullet sealed : public IIdentifiedObject
		{
		internal:
			BWAPI::Bullet instance;
				
			Bullet(BWAPI::Bullet type);

		public:
			virtual property int Id { int get(); }

			property BulletType Type { BulletType get(); }
			bool TypeEquals(BulletType type);
			property Api::Player^ Player { Api::Player^ get(); }
			property Unit^ Source { Unit^ get(); }
			property Api::Position^ Position { Api::Position^ get(); }
			property double Angle { double get(); }
			property double VelocityX { double get(); }
			property double VelocityY { double get(); }
			property Unit^ Target { Unit^ get(); }
			property Api::Position^ TargetPosition { Api::Position^ get(); }
			property int RemoveTimer { int get(); }
			property bool Exists { bool get(); }
			bool IsVisible();
			bool IsVisible(Api::Player^ player);

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(Bullet^ other);

			static bool operator == (Bullet^ first, Bullet^ second);
			static bool operator != (Bullet^ first, Bullet^ second);
		};

		Bullet^ ConvertBullet(BWAPI::Bullet bullet);
	}
}
