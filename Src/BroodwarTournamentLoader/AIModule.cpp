#pragma unmanaged

#include <BWAPI.h>

#pragma managed

#include "AIManaged.h"
#include "AIModule.h"

using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace BroodWar::Loader;

Assembly^ ResolveAssembly(Object ^sender, ResolveEventArgs ^e);

void Preload()
{
	AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(&ResolveAssembly);
}

void LoadGameInstance(BWAPI::Game* game)
{
	BroodWar::Util::LoadGameInstance(game);
}

void AIModule::onStart()
{
	AIManaged::Start();
}

void AIModule::onEnd(bool isWinner)
{
	AIManaged::End(isWinner);
}

void AIModule::onFrame()
{
	AIManaged::Frame();
}

void AIModule::onSendText(std::string text)
{
	AIManaged::SendText(gcnew System::String(text.c_str()));
}

void AIModule::onReceiveText(BWAPI::Player player, std::string text)
{
	AIManaged::ReceiveText(player, gcnew System::String(text.c_str()));
}

void AIModule::onPlayerLeft(BWAPI::Player player)
{
	AIManaged::PlayerLeft(player);
}

void AIModule::onNukeDetect(BWAPI::Position target)
{
	AIManaged::NukeDetect(target);
}

void AIModule::onUnitDiscover(BWAPI::Unit unit)
{
	AIManaged::UnitDiscover(unit);
}

void AIModule::onUnitEvade(BWAPI::Unit unit)
{
	AIManaged::UnitEvade(unit);
}

void AIModule::onUnitShow(BWAPI::Unit unit)
{
	AIManaged::UnitShow(unit);
}

void AIModule::onUnitHide(BWAPI::Unit unit)
{
	AIManaged::UnitHide(unit);
}

void AIModule::onUnitCreate(BWAPI::Unit unit)
{
	AIManaged::UnitCreate(unit);
}

void AIModule::onUnitDestroy(BWAPI::Unit unit)
{
	AIManaged::UnitDestroy(unit);
}

void AIModule::onUnitMorph(BWAPI::Unit unit)
{
	AIManaged::UnitMorph(unit);
}

void AIModule::onUnitRenegade(BWAPI::Unit unit)
{
	AIManaged::UnitRenegade(unit);
}

void AIModule::onSaveGame(std::string gameName)
{
	AIManaged::SaveGame(gcnew System::String(gameName.c_str()));
}

void AIModule::onUnitComplete(BWAPI::Unit unit)
{
	AIManaged::UnitComplete(unit);
}

void AIModule::onPlayerDropped(BWAPI::Player player)
{
	AIManaged::PlayerDropped(player);
}

Assembly^ ResolveAssembly(Object ^sender, ResolveEventArgs ^e)
{
	String^ folder = Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location);
	AssemblyName^ assemblyName = gcnew AssemblyName(e->Name);
	for each (String^ extension in gcnew array<String^> { ".dll", ".exe" })
	{
		String^ fileName = Path::Combine(folder, assemblyName->Name + extension);
		try
		{
			return Assembly::LoadFile(fileName);
		}
		catch (...)
		{
		}
	}
	return nullptr;
}
