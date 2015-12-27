#pragma once
#pragma unmanaged

#include <BWAPI\Force.h>
#include <BWAPI\Forceset.h>

#pragma managed

#include "IIdentifiedObject.h"

using namespace System;
using namespace System::Collections::Generic;

namespace BroodWar
{
	namespace Api
	{
		ref class Player;

		public ref class Force sealed : public IIdentifiedObject
		{
		private:
			BWAPI::Force instance;

		internal:
			Force(BWAPI::Force force);

		public:
			virtual property int Id { int get(); }
			property String^ Name { String^ get(); }
			property HashSet<Player^>^ Players { HashSet<Player^>^ get(); }

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(Api::Force^ other);

			static bool operator == (Api::Force^ first, Api::Force^ second);
			static bool operator != (Api::Force^ first, Api::Force^ second);
		};

		Force^ ConvertForce(BWAPI::Force force);
	}
}
