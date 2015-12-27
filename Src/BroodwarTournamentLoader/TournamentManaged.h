#pragma once

namespace BroodWar
{
	namespace Loader
	{
		private ref class TournamentManaged abstract sealed
		{
		private:
			static TournamentBase^ tournamentBase;
		internal:
			static TournamentManaged();

			static bool Action(int action, void* parameter);
			
			static void FirstAdvertisement();
		};
	}
}
