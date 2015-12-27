#pragma once
#pragma unmanaged

#include <BWAPI\Region.h>
#include <BWAPI\Regionset.h>

#pragma managed

#include "IIdentifiedObject.h"
#include "Position.h"

using namespace System::Collections::Generic;
using namespace System::Drawing;

namespace BroodWar
{
	namespace Api
	{
		public ref class Region sealed : public IIdentifiedObject
		{
		internal:
			BWAPI::Region instance;

			Region(BWAPI::Region region);

		public:
			virtual property int Id { int get(); }
			property int RegionGroupId { int get(); }
			property Position^ Center { Position^ get(); }
			property bool IsHigherGround { bool get(); }
			property int DefensePriority { int get(); }
			property bool IsAccessible { bool get(); }
			property HashSet<Region^>^ Neighbours { HashSet<Region^>^ get(); }
			property System::Drawing::Rectangle Bounds { System::Drawing::Rectangle get(); }
			property Region^ ClosestAccessibleRegion { Region^ get(); }
			property Region^ ClosestInaccessibleRegion { Region^ get(); }
			int DistanceTo(Region^ region);

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(Region^ other);

			static bool operator == (Region^ first, Region^ second);
			static bool operator != (Region^ first, Region^ second);
		};

		Region^ ConvertRegion(BWAPI::Region region);
	}
}
