#pragma once

#pragma unmanaged

#include <set>
#include <vector>
#include <list>
#include <map>
#include <utility>

#pragma managed

#include "BWAPI\Unit.h"
#include "BWAPI\Game.h"

using namespace std;
using namespace System;
using namespace System::Collections::Generic;
using namespace BroodWar;
using namespace BroodWar::Api;

namespace BroodWar
{
	template <typename TIn1, typename TIn2, typename TOut1, typename TOut2>
	Tuple<TOut1, TOut2>^ ToTuple(pair<TIn1, TIn2> p, TOut1 (*converter1)(TIn1), TOut2 (*converter2)(TIn2))
	{
		return gcnew Tuple<TOut1, TOut2>(converter1(p.first), converter2(p.second));
	}
	
	//template <typename TIn, typename TOut>
	//HashSet<TOut>^ ToHashSet(unordered_set<TIn> collection, TOut (*converter)(TIn))
	//{
	//	HashSet<TOut>^ result = gcnew HashSet<TOut>();
	//	set<TIn>::iterator it;
	//	for(it = collection.begin(); it != collection.end(); it++)
	//		result->Add(converter(*it));
	//	return result;
	//}

    template <typename TIn, typename TOut>
    HashSet<TOut>^ ToHashSet(unordered_set<TIn, hash<void*>> collection, TOut(*converter)(TIn))
    {
        HashSet<TOut>^ result = gcnew HashSet<TOut>();
        unordered_set<TIn, hash<void*>>::iterator it;
        for (it = collection.begin(); it != collection.end(); it++)
            result->Add(converter(*it));
        return result;
    }

    //template <typename TIn, typename TOut>
    //HashSet<TOut>^ ToHashSet(unordered_set<TIn, hash<int>> collection, TOut(*converter)(TIn))
    //{
    //    HashSet<TOut>^ result = gcnew HashSet<TOut>();
    //    set<TIn, hash<int>>::iterator it;
    //    for (it = collection.begin(); it != collection.end(); it++)
    //        result->Add(converter(*it));
    //    return result;
    //}

    template <typename TIn, typename TOut>
    HashSet<TOut>^ ToHashSet(const BWAPI::SetContainer<TIn> collection, TOut(*converter)(TIn))
    {
        HashSet<TOut>^ result = gcnew HashSet<TOut>();
        BWAPI::SetContainer<TIn>::iterator it;
        for (it = collection.begin(); it != collection.end(); it++)
            result->Add(converter(*it));
        return result;
    }

	template <typename TIn, typename TOut>
	List<TOut>^ ToList(vector<TIn> collection, TOut (*converter)(TIn))
	{
		List<TOut>^ rez = gcnew List<TOut>(collection.size());
		vector<TIn>::iterator it;
		for(it = collection.begin(); it != collection.end(); it++)
			rez->Add(converter(*it));
		return rez;
	}

    template <typename TIn, typename TOut>
    List<TOut>^ ToList(list<TIn> collection, TOut(*converter)(TIn))
    {
        List<TOut>^ rez = gcnew List<TOut>(collection.size());
        list<TIn>::iterator it;
        for (it = collection.begin(); it != collection.end(); it++)
            rez->Add(converter(*it));
        return rez;
    }

	template <typename TIn, typename TOut>
	List<TOut>^ ToList(deque<TIn> collection, TOut (*converter)(TIn))
	{
		List<TOut>^ rez = gcnew List<TOut>(collection.size());
		deque<TIn>::iterator it;
		for(it = collection.begin(); it != collection.end(); it++)
			rez->Add(converter(*it));
		return rez;
	}

	template <typename TIn, typename TOut>
	List<TOut>^ ToList(BWAPI::SetContainer<TIn> collection, TOut (*converter)(TIn))
	{
		List<TOut>^ rez = gcnew List<TOut>(collection.size());
		BWAPI::SetContainer<TIn>::iterator it;
		for(it = collection.begin(); it != collection.end(); it++)
			rez->Add(converter(*it));
		return rez;
	}

	template <typename TIn1, typename TIn2, typename TOut1, typename TOut2>
	Dictionary<TOut1, TOut2>^ ToDictionary(map<TIn1, TIn2> m, TOut1 (*converter1)(TIn1), TOut2 (*converter2)(TIn2))
	{
		std::map<TIn1, TIn2>::iterator it;
		Dictionary<TOut1, TOut2>^ rez = gcnew Dictionary<TOut1, TOut2>(m.size());
		for(it = m.begin(); it != m.end(); it++)
			rez->Add(converter1(it->first), converter2(it->second));
		return rez;
	}

    BWAPI::Unitset ToUnitset(IEnumerable<Unit^>^ collection, BWAPI::Unit(*converter)(Unit^));

    //template <typename TIn, typename TOut>
	//set<TOut> ToSet(IEnumerable<TIn>^ collection, TOut (*converter)(TIn))
	//{
	//	set<TOut> result;
	//	TOut outelement;
	//	for each(TIn element in collection)
	//	{
	//		outelement = (TOut const)(converter(element));
	//		result.insert(outelement);
	//	}
	//	return result;
	//}

	template <typename TIn, typename TOut>
	vector<TOut> ToVector(ICollection<TIn>^ collection, TOut (*converter)(TIn))
	{
		vector<TOut> result;
		result.reserve(collection->Count);
		TOut outelement;
		for each(TIn element in collection)
		{
			outelement = (TOut const)(converter(element));
			result.insert(outelement);
		}
		return result;
	}

	double DoubleToDouble(double d);

	int IntToInt(int i);

	public ref class Util abstract sealed
	{
	public:
		static void Log(String^ string);

		static void LogException(String^ module, Exception^ ex);

        // Can't export because of templates breaking the #pragma make_public(BWAPI::Player/Position/Unit)
        //static Api::Player^ ConvertPlayer(BWAPI::Player player);
        static Api::Player^ ConvertPlayer(void *player);

        //static Api::Unit^ ConvertUnit(BWAPI::Unit unit);
        static Api::Unit^ ConvertUnit(void *unit);

        //static Api::Position^ ConvertPosition(BWAPI::Position *position);
        static Api::Position^ ConvertPosition(void *position);

		static void LoadGameInstance(BWAPI::Game* game);
	};
}
