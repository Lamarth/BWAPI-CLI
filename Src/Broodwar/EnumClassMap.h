#pragma once

#pragma unmanaged

#include <set>

#pragma managed

#include "Util.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace BroodWar
{
	template <typename TNative, typename TManaged>
	private ref class EnumClassMap
	{
	private:
		Dictionary<int, TManaged>^ dictionaryForward;
		Dictionary<TManaged, int>^ dictionaryBackward;

	internal:
		EnumClassMap(int size)
		{
			dictionaryForward = gcnew Dictionary<int, TManaged>(size);
			dictionaryBackward = gcnew Dictionary<TManaged, int>(size);
		}

		void Add(const TNative* native, TManaged managed)
		{
			dictionaryForward->Add(native->getID(), managed);
			dictionaryBackward->Add(managed, native->getID());
		}

		TManaged Managed(TNative native)
		{
			return dictionaryForward[native.getID()];
		}

		TManaged Managed(const TNative* native)
		{
			return dictionaryForward[native->getID()];
		}

		TNative Native(TManaged managed)
		{
			return TNative(dictionaryBackward[managed]);
		}

		TNative* NativePointer(TManaged managed)
		{
			return new TNative(dictionaryBackward[managed]);
		}
	};
}
