#pragma unmanaged

#include <BWAPI.h>

#pragma managed

#include "TournamentManaged.h"

using namespace System;
using namespace System::Configuration;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;
using namespace BroodWar::Api::Enum;

namespace BroodWar
{
	namespace Loader
	{
		static TournamentManaged::TournamentManaged()
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
				String^ type = config->AppSettings->Settings["Tournament"]->Value;

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
				tournamentBase = dynamic_cast<TournamentBase^>(constructor->Invoke(gcnew array<Object^> { }));
				if(tournamentBase == nullptr)
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

		bool TournamentManaged::Action(int action, void* parameter)
		{
			try
			{
				if(tournamentBase != nullptr)
					return tournamentBase->OnAction(static_cast<TournamentAction>(action), IntPtr(parameter));
				return true;
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnAction", ex);
                return false;
			}
		}
		
		void TournamentManaged::FirstAdvertisement()
		{
			try
			{
				if(tournamentBase != nullptr)
					tournamentBase->OnFirstAdvertisement();
			}
			catch(Exception^ ex)
			{
				Util::LogException("OnFirstAdvertisement", ex);
			}
		}
	}
}
