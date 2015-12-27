#pragma once

namespace BroodWar
{
	namespace Loader
	{
		private ref class AIManaged abstract sealed
		{
		private:
			static AiBase^ aiBase;
		internal:
			static AIManaged();

			static void Start();
			static void End(bool isWinner);
			static void Frame();
			static void SendText(System::String^ text);
			static void ReceiveText(BWAPI::Player player, System::String^ text);
			static void PlayerLeft(BWAPI::Player player);
			static void NukeDetect(BWAPI::Position target);
			static void UnitDiscover(BWAPI::Unit unit);
			static void UnitEvade(BWAPI::Unit unit);
			static void UnitShow(BWAPI::Unit unit);
			static void UnitHide(BWAPI::Unit unit);
			static void UnitCreate(BWAPI::Unit unit);
			static void UnitDestroy(BWAPI::Unit unit);
			static void UnitMorph(BWAPI::Unit unit);
			static void UnitRenegade(BWAPI::Unit unit);
			static void SaveGame(System::String^ gameName);
			static void UnitComplete(BWAPI::Unit unit);
			static void PlayerDropped(BWAPI::Player player);
		};
	}
}
