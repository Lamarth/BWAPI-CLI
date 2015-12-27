#include "Bullet.h"
#include "Player.h"
#include "Position.h"
#include "Unit.h"

#include "..\EnumMapping.h"

namespace BroodWar
{
	namespace Api
	{
		Bullet^ ConvertBullet(BWAPI::Bullet bullet)
		{
			if(bullet == NULL)
				return nullptr;
			return gcnew Bullet(bullet);
		}

		Bullet::Bullet(BWAPI::Bullet type)
		{
			instance = type;
		}

		Api::Enum::BulletType Bullet::Type::get()
		{
			return EnumMapping::BulletType->Managed(instance->getType());
		}

		int Bullet::Id::get()
		{
			return instance->getID();
		}
			
		bool Bullet::TypeEquals(Api::Enum::BulletType type)
		{
			return Type == type;
		}
			
		Player^ Bullet::Player::get()
		{
			return ConvertPlayer(instance->getPlayer());
		}
			
		Unit^ Bullet::Source::get()
		{
			return ConvertUnit(instance->getSource());
		}
			
		Position^ Bullet::Position::get()
		{
			return ConvertPosition(instance->getPosition());
		}
			
		double Bullet::Angle::get()
		{
			return instance->getAngle();
		}
			
		double Bullet::VelocityX::get()
		{
			return instance->getVelocityX();
		}
			
		double Bullet::VelocityY::get()
		{
			return instance->getVelocityY();
		}
			
		Unit^ Bullet::Target::get()
		{
			return ConvertUnit(instance->getTarget());
		}
			
		Position^ Bullet::TargetPosition::get()
		{
			return ConvertPosition(instance->getTargetPosition());
		}
			
		int Bullet::RemoveTimer::get()
		{
			return instance->getRemoveTimer();
		}
			
		bool Bullet::Exists::get()
		{
			return instance->exists();
		}
			
		bool Bullet::IsVisible()
		{
			return instance->isVisible();
		}
			
		bool Bullet::IsVisible(Api::Player^ player)
		{
			return instance->isVisible(ConvertPlayer(player));
		}

		int Bullet::GetHashCode()
		{
			return instance->getID();
		}

		bool Bullet::Equals(Object^ o)
		{
			Bullet^ other = dynamic_cast<Bullet^>(o);
			return this->Equals(other);
		}

		bool Bullet::Equals(Bullet^ other)
		{
			if(ReferenceEquals(nullptr, other))
				return false;
			if(ReferenceEquals(this, other))
				return true;
			return this->instance->getID() == other->instance->getID();
		}

		bool Bullet::operator == (Bullet^ first, Bullet^ second)
		{
			if(ReferenceEquals(first, second))
				return true;
			if(ReferenceEquals(nullptr, first))
				return false;
			return first->Equals(second);
		}

		bool Bullet::operator != (Bullet^ first, Bullet^ second)
		{
			return !(first == second);
		}
	}
}
