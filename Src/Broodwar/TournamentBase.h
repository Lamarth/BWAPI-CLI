#pragma once

#pragma managed

#include "BWAPI\Enum\TournamentAction.h"

using namespace System;
using namespace BroodWar::Api::Enum;

namespace BroodWar
{
	public ref class TournamentBase abstract
	{
	public:
		/// <summary>
		/// BWAPI calls this any time some Game-related functions are called. Return true to allow them,
		/// or false to disallow them. This includes functions like Game::pauseGame and Game::enableFlag
		/// </summary>
		virtual bool OnAction(TournamentAction action, IntPtr parameter);

		/// <summary>
		/// BWAPI calls this when this module was the first to send out its tournament advertisement. It
		/// can prevent both modules from performing the same task if it's necessary
		/// </summary>
		virtual void OnFirstAdvertisement();
	};
}
