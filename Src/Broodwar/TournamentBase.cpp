#pragma managed

#include "TournamentBase.h"

namespace BroodWar
{
	bool TournamentBase::OnAction(TournamentAction action, IntPtr parameter) { return true; }

	void TournamentBase::OnFirstAdvertisement() { }
}
