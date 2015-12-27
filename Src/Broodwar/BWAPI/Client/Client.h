#pragma once
#pragma unmanaged

#include <BWAPI\Client\Client.h>

#pragma managed

namespace BroodWar
{
	namespace Api
	{
		namespace Client
		{
			//ref class GameData;

			public ref class Client abstract sealed
			{
			public:
				static property bool IsConnected { bool get(); }
				static bool Connect();
				static void Disconnect();
				static void Update();
				//static property GameData^ Data
				//{
				//	GameData^ get();
				//	void set(GameData^ value);
				//}
			};
		}
	}
}
