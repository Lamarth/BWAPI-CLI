#include "Event.h"
#include "Position.h"
#include "Player.h"
#include "Unit.h"

using namespace System::Runtime::InteropServices;

namespace BroodWar
{
	namespace Api
	{
		Event^ ConvertEvent(BWAPI::Event ev)
		{
			return gcnew Event(ev);
		}

		Event::Event(BWAPI::Event* ev)
		{
			instance = ev;
			dispose = false;
		}

		Event::Event(BWAPI::Event ev)
		{
			instance = new BWAPI::Event(ev);
			dispose = true;
		}

		Event::~Event()
		{
			if(dispose)
				delete instance;
		}

		Event::!Event()
		{
			if(dispose)
				delete instance;
		}
		
		Event::Event()
		{
			instance = new BWAPI::Event();
			dispose = true;
		}

		Event::Event(Event^ copy)
		{
			instance = new BWAPI::Event(*(copy->instance));
			dispose = true;
		}

		EventType Event::Type::get()
		{
			return static_cast<EventType>(instance->getType());
		}

		void Event::Type::set(EventType eventType)
		{
			instance->setType(static_cast<BWAPI::EventType::Enum>(eventType));
		}
			
		Api::Position^ Event::Position::get()
		{
			return ConvertPosition(instance->getPosition());
		}

		void Event::Position::set(Api::Position^ value)
		{
			instance->setPosition(ConvertPosition(value));
		}
			
		String^ Event::Text::get()
		{
			return gcnew String(instance->getText().c_str());
		}

		void Event::Text::set(String^ value)
		{
			IntPtr str = Marshal::StringToHGlobalAnsi(value);
			instance->setText((const char*)str.ToPointer());
			Marshal::FreeHGlobal(str);
		}
			
		Api::Unit^ Event::Unit::get()
		{
			return ConvertUnit(instance->getUnit());
		}

		void Event::Unit::set(Api::Unit^ value)
		{
			instance->setUnit(ConvertUnit(value));
		}
			
		Api::Player^ Event::Player::get()
		{
			return ConvertPlayer(instance->getPlayer());
		}

		void Event::Player::set(Api::Player^ value)
		{
			instance->setPlayer(ConvertPlayer(value));
		}
			
		bool Event::IsWinner::get()
		{
			return instance->isWinner();
		}

		void Event::IsWinner::set(bool value)
		{
			instance->setWinner(value);
		}

		Event^ Event::MatchStart()
		{
			return ConvertEvent(BWAPI::Event::MatchStart());
		}
		
		Event^ Event::MatchEnd(bool isWinner)
		{
			return ConvertEvent(BWAPI::Event::MatchEnd(isWinner));
		}
		
		Event^ Event::MatchFrame()
		{
			return ConvertEvent(BWAPI::Event::MatchFrame());
		}
		
		Event^ Event::MenuFrame()
		{
			return ConvertEvent(BWAPI::Event::MenuFrame());
		}
		
		Event^ Event::SendText(String^ text)
		{
			IntPtr str = Marshal::StringToHGlobalAnsi(text);
			Event^ rez = gcnew Api::Event(BWAPI::Event::SendText((const char*)str.ToPointer()));
			Marshal::FreeHGlobal(str);
			return rez;
		}
		
		Event^ Event::ReceiveText(Api::Player^ player, String^ text)
		{
			IntPtr str = Marshal::StringToHGlobalAnsi(text);
			Event^ rez = ConvertEvent(BWAPI::Event::ReceiveText(ConvertPlayer(player), (const char*)str.ToPointer()));
			Marshal::FreeHGlobal(str);
			return rez;
		}
		
		Event^ Event::PlayerLeft(Api::Player^ player)
		{
			return ConvertEvent(BWAPI::Event::PlayerLeft(ConvertPlayer(player)));
		}
		
		Event^ Event::NukeDetect(Api::Position^ target)
		{
			return ConvertEvent(BWAPI::Event::NukeDetect(ConvertPosition(target)));
		}
		
		Event^ Event::UnitDiscover(Api::Unit^ unit)
		{
			return ConvertEvent(BWAPI::Event::UnitDiscover(ConvertUnit(unit)));
		}
		
		Event^ Event::UnitEvade(Api::Unit^ unit)
		{
			return ConvertEvent(BWAPI::Event::UnitEvade(ConvertUnit(unit)));
		}
		
		Event^ Event::UnitShow(Api::Unit^ unit)
		{
			return ConvertEvent(BWAPI::Event::UnitShow(ConvertUnit(unit)));
		}
		
		Event^ Event::UnitHide(Api::Unit^ unit)
		{
			return ConvertEvent(BWAPI::Event::UnitHide(ConvertUnit(unit)));
		}
		
		Event^ Event::UnitCreate(Api::Unit^ unit)
		{
			return ConvertEvent(BWAPI::Event::UnitCreate(ConvertUnit(unit)));
		}
		
		Event^ Event::UnitDestroy(Api::Unit^ unit)
		{
			return ConvertEvent(BWAPI::Event::UnitDestroy(ConvertUnit(unit)));
		}
		
		Event^ Event::UnitMorph(Api::Unit^ unit)
		{
			return ConvertEvent(BWAPI::Event::UnitMorph(ConvertUnit(unit)));
		}
		
		Event^ Event::UnitRenegade(Api::Unit^ unit)
		{
			return ConvertEvent(BWAPI::Event::UnitRenegade(ConvertUnit(unit)));
		}
		
		Event^ Event::SaveGame(String^ gameName)
		{
			IntPtr str = Marshal::StringToHGlobalAnsi(gameName);
			Event^ rez = ConvertEvent(BWAPI::Event::SaveGame((const char*)str.ToPointer()));
			Marshal::FreeHGlobal(str);
			return rez;
		}
		
		Event^ Event::UnitComplete(Api::Unit^ unit)
		{
			return ConvertEvent(BWAPI::Event::UnitComplete(ConvertUnit(unit)));
		}

		bool Event::operator == (Api::Event^ first, Api::Event^ second)
		{
			return *(first->instance) == *(second->instance);
		}

		bool Event::operator != (Api::Event^ first, Api::Event^ second)
		{
			return !(*(first->instance) == *(second->instance));
		}
	}
}