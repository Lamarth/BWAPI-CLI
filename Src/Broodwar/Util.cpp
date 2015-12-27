#include "Util.h"
#include <BWAPI.h>
#include "BWAPI\Player.h"

using namespace System::IO;
using namespace System::Runtime::InteropServices;

extern BWAPI::GameWrapper BWAPI::Broodwar;

namespace BroodWar
{
	double DoubleToDouble(double d)
	{
		return d;
	}

	int IntToInt(int i)
	{
		return i;
	}

    BWAPI::Unitset ToUnitset(IEnumerable<Unit^>^ collection, BWAPI::Unit(*converter)(Unit^))
    {
        BWAPI::Unitset result;
        BWAPI::Unit outelement;
        for each(Unit^ element in collection)
        {
            outelement = (BWAPI::Unit const)(converter(element));
            result.insert(outelement);
        }
        return result;
    }

	void Util::Log(String^ string)
	{
		String^ fileName = Path::Combine(
			Environment::GetFolderPath(Environment::SpecialFolder::Personal),
			"text-from-lib.txt");
		StreamWriter^ file = gcnew StreamWriter(fileName, true);
		file->WriteLine(string);
		file->Close();

		IntPtr ptr = Marshal::StringToHGlobalAnsi(string);
		BWAPI::Broodwar->sendText((char*)ptr.ToPointer());
		Marshal::FreeHGlobal(ptr);
	}

	void Util::LogException(String^ module, Exception^ ex)
	{
		Log(String::Format("Unexpected error occured during {0}: {1}{2}{3}", module, ex->Message, Environment::NewLine, ex->StackTrace));
		while((ex = ex->InnerException) != nullptr)
		{
			Log(String::Format("Internal error is: {0}{1}{2}", ex->Message, Environment::NewLine, ex->StackTrace));
		}
	}

	Api::Player^ Util::ConvertPlayer(void *player)
	{
		return Api::ConvertPlayer(static_cast<BWAPI::Player>(player));
	}

	Api::Unit^ Util::ConvertUnit(void *unit)
	{
        return Api::ConvertUnit(static_cast<BWAPI::Unit>(unit));
	}

	Api::Position^ Util::ConvertPosition(void *position)
	{
        return Api::ConvertPosition(static_cast<BWAPI::Position*>(position));
	}

	void Util::LoadGameInstance(BWAPI::Game* game)
	{
		BWAPI::BroodwarPtr = game;
	}
}
