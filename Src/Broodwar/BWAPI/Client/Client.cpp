#pragma warning(push)
#pragma warning(disable:4005)
#include "Client.h"
#include "..\Game.h"
#pragma warning(pop)

extern BWAPI::Client BWAPI::BWAPIClient;

namespace BroodWar
{
	namespace Api
	{
		namespace Client
		{
			bool Client::IsConnected::get()
			{
				return BWAPI::BWAPIClient.isConnected();
			}

			bool Client::Connect()
			{
				bool result = BWAPI::BWAPIClient.connect();
				if(result)
					Api::Game::Rebind();
				return result;
			}

			void Client::Disconnect()
			{
				BWAPI::BWAPIClient.disconnect();
			}
			
			void Client::Update()
			{
				BWAPI::BWAPIClient.update();
			}
			
			//GameData^ Client::Data::get()
			//{
			//	#pragma warning Implement
			//	throw gcnew System::NotImplementedException();
			//}

			//void Client::Data::set(GameData^ value)
			//{
			//	#pragma warning Implement
			//	throw gcnew System::NotImplementedException();
			//}
		}
	}
}
