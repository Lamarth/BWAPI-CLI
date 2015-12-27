#pragma unmanaged

#include <BWAPI.h>

#pragma managed

#include "AIManaged.h"

using namespace System;
using namespace System::Configuration;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;

namespace BroodWar
{
	namespace Loader
	{
		static AIManaged::AIManaged()
		{
			try
			{
				String^ currentLocation = Assembly::GetExecutingAssembly()->Location;
				String^ configFile = String::Format("{0}.config", currentLocation);
				ExeConfigurationFileMap^ fileMap = gcnew ExeConfigurationFileMap();
				fileMap->ExeConfigFilename = configFile;
				System::Configuration::Configuration^ config = ConfigurationManager::OpenMappedExeConfiguration(fileMap, ConfigurationUserLevel::None);

				String^ path = config->AppSettings->Settings["Path"]->Value;
				String^ assemblyName = config->AppSettings->Settings["Assembly"]->Value;
				String^ type = config->AppSettings->Settings["Module"]->Value;

				if(!Path::IsPathRooted(path))
				{
					path = Path::Combine(Path::GetDirectoryName(currentLocation), path);
				}

				Assembly^ assembly = Assembly::LoadFrom(Path::Combine(path, assemblyName));
				if(assembly == nullptr)
				{
					Util::Log(String::Format("Could not load assembly {0} from path {1}", assemblyName, path));
					return;
				}
				Type^ module = assembly->GetType(type);
				if(module == nullptr)
				{
					Util::Log(String::Format("Could not load type {0}", type));
					return;
				}
				ConstructorInfo^ constructor = module->GetConstructor(gcnew array<Type^> { });
				if(constructor == nullptr)
				{
					Util::Log(String::Format("Could not find constructor for type {0}", type));
					return;
				}
				aiBase = dynamic_cast<AiBase^>(constructor->Invoke(gcnew array<Object^> { }));
				if(aiBase == nullptr)
				{
					Util::Log(String::Format("Could not create instance of type {0}", type));
					return;
				}

				Util::Log("Startup successful");
			}
			catch(Exception^ ex)
			{
				Util::LogException("initialization", ex);
			}
		}

		void AIManaged::Start()
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnStart();
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnStart", ex);
			}
		}
		
		void AIManaged::End(bool isWinner)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnEnd(isWinner);
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnEnd", ex);
			}
		}
		
		void AIManaged::Frame()
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnFrame();
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnFrame", ex);
			}
		}
		
		void AIManaged::SendText(System::String^ text)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnSendText(text);
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnSendText", ex);
			}
		}
		
		void AIManaged::ReceiveText(BWAPI::Player player, System::String^ text)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnReceiveText(Util::ConvertPlayer(player), text);
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnReceiveText", ex);
			}
		}
		
		void AIManaged::PlayerLeft(BWAPI::Player player)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnPlayerLeft(Util::ConvertPlayer(player));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnPlayerLeft", ex);
			}
		}
		
		void AIManaged::NukeDetect(BWAPI::Position target)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnNukeDetect(Util::ConvertPosition(&target));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnNukeDetect", ex);
			}
		}
		
		void AIManaged::UnitDiscover(BWAPI::Unit unit)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnUnitDiscover(Util::ConvertUnit(unit));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnUnitDiscover", ex);
			}
		}
		
		void AIManaged::UnitEvade(BWAPI::Unit unit)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnUnitEvade(Util::ConvertUnit(unit));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnUnitEvade", ex);
			}
		}
		
		void AIManaged::UnitShow(BWAPI::Unit unit)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnUnitShow(Util::ConvertUnit(unit));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnUnitShow", ex);
			}
		}
		
		void AIManaged::UnitHide(BWAPI::Unit unit)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnUnitHide(Util::ConvertUnit(unit));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnUnitHide", ex);
			}
		}
		
		void AIManaged::UnitCreate(BWAPI::Unit unit)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnUnitCreate(Util::ConvertUnit(unit));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnUnitCreate", ex);
			}
		}
		
		void AIManaged::UnitDestroy(BWAPI::Unit unit)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnUnitDestroy(Util::ConvertUnit(unit));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnUnitDestroy", ex);
			}
		}
		
		void AIManaged::UnitMorph(BWAPI::Unit unit)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnUnitMorph(Util::ConvertUnit(unit));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnUnitMorph", ex);
			}
		}
		
		void AIManaged::UnitRenegade(BWAPI::Unit unit)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnUnitRenegade(Util::ConvertUnit(unit));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnUnitRenegade", ex);
			}
		}
		
		void AIManaged::SaveGame(System::String^ gameName)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnSaveGame(gameName);
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnSaveGame", ex);
			}
		}
		
		void AIManaged::UnitComplete(BWAPI::Unit unit)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnUnitComplete(Util::ConvertUnit(unit));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnUnitComplete", ex);
			}
		}

		void AIManaged::PlayerDropped(BWAPI::Player player)
		{
			try
			{
				if(aiBase != nullptr)
					aiBase->OnPlayerDropped(Util::ConvertPlayer(player));
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnPlayerDropped", ex);
			}
		}
	}
}
