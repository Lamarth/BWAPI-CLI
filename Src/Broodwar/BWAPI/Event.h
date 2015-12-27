#pragma once
#pragma unmanaged

#include <BWAPI\Event.h>

#pragma managed

#include "Enum\EventType.h"
#include "Player.h"
#include "Unit.h"
#include "Position.h"

using namespace System;

namespace BroodWar
{
	namespace Api
	{
		public ref class Event sealed
		{
		internal:
			BWAPI::Event* instance;
			bool dispose;

			Event(BWAPI::Event* ev);
			Event(BWAPI::Event ev);
			~Event();
			!Event();

		public:
			Event();
			Event(Event^ copy);

			property EventType Type
			{
				EventType get();
				void set(EventType value);
			}
			property Api::Position^ Position
			{
				Api::Position^ get();
				void set(Api::Position^ value);
			}
			property String^ Text
			{
				String^ get();
				void set(String^ value);
			}
			property Api::Unit^ Unit
			{
				Api::Unit^ get();
				void set(Api::Unit^ value);
			}
			property Api::Player^ Player
			{
				Api::Player^ get();
				void set(Api::Player^ value);
			}
			property bool IsWinner
			{
				bool get();
				void set(bool value);
			}

			static Event^ MatchStart();
			static Event^ MatchEnd(bool isWinner);
			static Event^ MatchFrame();
			static Event^ MenuFrame();
			static Event^ SendText(String^ text);
			static Event^ ReceiveText(Api::Player^ player, String^ text);
			static Event^ PlayerLeft(Api::Player^ player);
			static Event^ NukeDetect(Api::Position^ target);
			static Event^ UnitDiscover(Api::Unit^ unit);
			static Event^ UnitEvade(Api::Unit^ unit);
			static Event^ UnitShow(Api::Unit^ unit);
			static Event^ UnitHide(Api::Unit^ unit);
			static Event^ UnitCreate(Api::Unit^ unit);
			static Event^ UnitDestroy(Api::Unit^ unit);
			static Event^ UnitMorph(Api::Unit^ unit);
			static Event^ UnitRenegade(Api::Unit^ unit);
			static Event^ SaveGame(String^ gameName);
			static Event^ UnitComplete(Api::Unit^ unit);

			static bool operator == (Api::Event^ first, Api::Event^ second);
			static bool operator != (Api::Event^ first, Api::Event^ second);
		};

		Event^ ConvertEvent(BWAPI::Event ev);
	}
}
