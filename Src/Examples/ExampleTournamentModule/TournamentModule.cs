using System;
using BroodWar;
using BroodWar.Api;
using BroodWar.Api.Enum;

namespace ExampleTournamentModule
{
	public class TournamentModule : TournamentBase
	{
		public override bool OnAction(TournamentAction action, IntPtr parameter)
		{
			switch (action)
			{
				case TournamentAction.EnableFlag:
					switch ((Flag)parameter.ToInt32())
					{
						case Flag.CompleteMapInformation:
						case Flag.UserInput:
							// Disallow these two flags
							return false;
					}
					// Allow other flags if we add more that don't affect gameplay specifically
					return true;
				case TournamentAction.PauseGame:
				case TournamentAction.RestartGame:
				case TournamentAction.ResumeGame:
				case TournamentAction.SetFrameSkip:
				case TournamentAction.SetGUI:
				case TournamentAction.SetLocalSpeed:
				case TournamentAction.SetMap:
					return false; // Disallow these actions
				case TournamentAction.LeaveGame:
				case TournamentAction.ChangeRace:
				case TournamentAction.SetLatCom:
				case TournamentAction.SetTextSize:
				case TournamentAction.SendText:
				case TournamentAction.Printf:
					return true; // Allow these actions
				case TournamentAction.SetCommandOptimizationLevel:
					return parameter.ToInt32() > Events.MinimumCommandOptimization;
					// Set a minimum command optimization level
					// to reduce APM with no action loss
			}
			return true;
		}

		public override void OnFirstAdvertisement()
		{
			Events.IsLeader = true;
			Game.SendText("Welcome to tournament!");
			Game.SendText("Brought to you by <sponsors>.");
		}
	}
}
