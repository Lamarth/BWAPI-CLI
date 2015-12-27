#pragma unmanaged

#include <BWAPI.h>

#pragma managed

#include "AIModule.h"
#include "TournamentModule.h"

#pragma unmanaged

extern "C" __declspec(dllexport) void gameInit(BWAPI::Game* game)
{
    //Hack to properly locate Broodwar.dll assembly
    Preload();
    LoadGameInstance(game);
}

extern "C" __declspec(dllexport)
BWAPI::AIModule* newAIModule(BWAPI::Game* game)
{
	return new AIModule();
}

extern "C" __declspec(dllexport)
BWAPI::TournamentModule* newTournamentModule()
{
	return new TournamentModule();
}
