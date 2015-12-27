#include "Force.h"
#include "Player.h"
#include "..\Util.h"

using namespace BroodWar;

namespace BroodWar
{
	namespace Api
	{
		Force^ ConvertForce(BWAPI::Force force)
		{
			if(force == NULL)
				return nullptr;
			return gcnew Force(force);
		}

		Force::Force(BWAPI::Force force)
		{
			instance = force;
		}

		int Force::Id::get()
		{
			return instance->getID();
		}

		String^ Force::Name::get()
		{
			return gcnew String(instance->getName().c_str());
		}
			
		HashSet<Api::Player^>^ Force::Players::get()
		{
			return ToHashSet<BWAPI::Player, Player^>(instance->getPlayers(), &ConvertPlayer);
		}

		int Force::GetHashCode()
		{
			return instance->getID();
		}

		bool Force::Equals(Object^ o)
		{
			Force^ other = dynamic_cast<Force^>(o);
			return this->Equals(other);
		}

		bool Force::Equals(Api::Force^ other)
		{
			if(ReferenceEquals(nullptr, other))
				return false;
			if(ReferenceEquals(this, other))
				return true;
			return this->instance->getID() == other->instance->getID();
		}

		bool Force::operator == (Api::Force^ first, Api::Force^ second)
		{
			if(ReferenceEquals(first, second))
				return true;
			if(ReferenceEquals(nullptr, first))
				return false;
			return first->Equals(second);
		}

		bool Force::operator != (Api::Force^ first, Api::Force^ second)
		{
			return !(first == second);
		}
	}
}
