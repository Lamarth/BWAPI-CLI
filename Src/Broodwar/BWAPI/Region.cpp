#include "Region.h"
#include "..\Util.h"

using namespace BroodWar;

namespace BroodWar
{
	namespace Api
	{
		Region^ ConvertRegion(BWAPI::Region region)
		{
			if(region == NULL)
				return nullptr;
			return gcnew Region(region);
		}

		Region::Region(BWAPI::Region region)
		{
			instance = region;
		}
			
		int Region::Id::get()
		{
			return instance->getID();
		}

		int Region::RegionGroupId::get()
		{
			return instance->getRegionGroupID();
		}

		Position^ Region::Center::get()
		{
			return ConvertPosition(instance->getCenter());
		}

		bool Region::IsHigherGround::get()
		{
			return instance->isHigherGround();
		}

		int Region::DefensePriority::get()
		{
			return instance->getDefensePriority();
		}

		bool Region::IsAccessible::get()
		{
			return instance->isAccessible();
		}

		HashSet<Region^>^ Region::Neighbours::get()
		{
			return ToHashSet<BWAPI::Region, Region^>(instance->getNeighbors(), &ConvertRegion);
		}

		Rectangle Region::Bounds::get()
		{
			return System::Drawing::Rectangle(
				instance->getBoundsLeft(),
				instance->getBoundsTop(),
				instance->getBoundsRight() - instance->getBoundsLeft(),
				instance->getBoundsBottom() - instance->getBoundsTop());
		}

		Region^ Region::ClosestAccessibleRegion::get()
		{
			return ConvertRegion(instance->getClosestAccessibleRegion());
		}

		Region^ Region::ClosestInaccessibleRegion::get()
		{
			return ConvertRegion(instance->getClosestInaccessibleRegion());
		}

		int Region::DistanceTo(Region^ region)
		{
			return instance->getDistance(region->instance);
		}

		int Region::GetHashCode()
		{
			return instance->getID();
		}

		bool Region::Equals(Object^ o)
		{
			Region^ other = dynamic_cast<Region^>(o);
			return this->Equals(other);
		}

		bool Region::Equals(Region^ other)
		{
			if(ReferenceEquals(nullptr, other))
				return false;
			if(ReferenceEquals(this, other))
				return true;
			return this->instance->getID() == other->instance->getID();
		}

		bool Region::operator == (Region^ first, Region^ second)
		{
			if(ReferenceEquals(first, second))
				return true;
			if(ReferenceEquals(nullptr, first))
				return false;
			return first->Equals(second);
		}

		bool Region::operator != (Region^ first, Region^ second)
		{
			return !(first == second);
		}
	}
}
