#pragma once

namespace BroodWar
{
	namespace Api
	{
		namespace Client
		{
			public enum class CommandType
			{
				None,
				SetScreenPosition,
				PingMinimap,
				EnableFlag,
				Printf,
				SendText,
				ChangeRace,
				StartGame,
				PauseGame,
				ResumeGame,
				LeaveGame,
				RestartGame,
				SetLocalSpeed,
				SetLatCom,
				SetGui,
				SetFrameSkip,
				SetMap,
				SetAllies,
				SetVision,
				SetCommandOptimizerLevel,
				SetReplayVision,
				SetRevealAll,
			};
		}
	}
}
