#pragma unmanaged

#include <BWAPI.h>

#include "TournamentModule.h"

#pragma managed

#include "TournamentManaged.h"

using namespace BroodWar::Loader;

bool TournamentModule::onAction(int actionType, void* parameter)
{
	return TournamentManaged::Action(actionType, parameter);
}

void TournamentModule::onFirstAdvertisement()
{
	TournamentManaged::FirstAdvertisement();
}
