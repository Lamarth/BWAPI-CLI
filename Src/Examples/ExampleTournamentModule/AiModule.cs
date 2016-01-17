using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using BroodWar;
using BroodWar.Api;
using BroodWar.Api.Enum;
using Microsoft.Win32;
using UnitType = BroodWar.Api.Enum.UnitType;

namespace ExampleTournamentModule
{
	public class AiModule : AiBase
	{
		private static readonly Regex s_speedRegex = new Regex(@"TRNSPD (?<Speed>\d+)", RegexOptions.Compiled);
		private readonly string _path;
		private int _maxApm;
		
		public AiModule()
		{
			_path = GetScPath(Registry.CurrentUser) ?? GetScPath(Registry.LocalMachine);
		}

		public override void OnStart()
		{
			// Set the command optimization level (reduces high APM, size of bloated replays, etc)
			Game.SetCommandOptimizationLevel(Events.MinimumCommandOptimization);
			Game.EnableFlag(Flag.UserInput);

			var szTmp = new StringBuilder();
			Events.GetPrivateProfileString("auto_menu", "map", "", szTmp, 8, Path.Combine(_path, @"bwapi-data\bwapi.ini"));
			if(szTmp.Length == 0)
				Events.IsJoiner = true;

			Events.GetPrivateProfileString("ai", "ai", "UNKNOWN", szTmp, 260, Path.Combine(_path, @"bwapi-data\bwapi.ini"));
			Events.BotName = szTmp.ToString();
			Events.Self = Game.Self;

			Game.SetLocalSpeed(0);
			Game.SetFrameSkip(64);

			Events.Add(Position.Rescale(Events.Self.StartLocation + new TilePosition(64, 48)), 100, 100, null);
		}

		public override void OnEnd(bool isWinner)
		{
			//save maxAPM or something
		}

		public override void OnFrame()
		{
			if(Game.FrameCount < 64)
				return;
			Game.SetLocalSpeed(Game.Enemy.AllUnitCount(UnitType.AllUnits) > 0 ? 30 : 0);

			var thisApm = Game.GetApm(false);
			if (thisApm > _maxApm)
				_maxApm = thisApm;

			int hcolor;
			if (_maxApm < 500)
				hcolor = 7;
			else if (_maxApm < 1500)
				hcolor = 4;
			else if (_maxApm < 2500)
				hcolor = 3;
			else
				hcolor = 6;

			int color;
			if ( thisApm < 500 )
				color = 7;
			else if ( thisApm < 1500 )
				color = 4;
			else if ( thisApm < 2500 )
				color = 3;
			else
				color = 6;

            //Game.SetTextSize(3);
			Game.DrawTextScreen(4, 4, "\x13\x07{0}", Events.BotName);
            //Game.SetTextSize(0);

			Game.DrawTextScreen(2, 2, "\x04{0}\n\x07APM: {1}{2}\n\x07Highest APM: {3}{4}", Game.MapName, color, thisApm, hcolor, _maxApm);
			// draw supplies
			if (Events.IsJoiner)
				Game.DrawTextScreen(560, 40, "\x07Supply: {0}/{1}", Game.Self.SupplyUsed / 2, Game.Self.SupplyTotal / 2);

			foreach(var unit in Events.Self.Units.Where(u => u.Exists))
			{
				if(unit.IsStartingAttack)
					Events.Add(unit.Position, 20, 30, null);
				if(unit.IsUnderAttack)
					Events.Add(unit.Position, 20, 50, null);
				if(unit.IsCompleted && unit.UnitType.IsBuilding && !unit.IsInvincible && unit.IsUnderStorm)
					Events.Add(unit.Position, 100, 50, null);
				if (unit.IsCompleted && unit.UnitType.MaxHitPoints > 0 && unit.HitPoints * 100 / unit.UnitType.MaxHitPoints <= 2)
				{
					var enemy = unit.UnitsInRadius(512).Any(u => u.Exists && u.Player == Game.Enemy);
					if(!enemy)
						Events.Add(unit.Position, 20, 30, null);
				}

				var o = unit.Order;

				//states
				if (o.HasFlag(OrderType.BuildingLiftOff)
					|| o.HasFlag(OrderType.BuildingLand)
					|| o.HasFlag(OrderType.Burrowing)
					|| o.HasFlag(OrderType.Unburrowing)
					|| o.HasFlag(OrderType.Sieging)
					|| o.HasFlag(OrderType.Unsieging)
					|| o.HasFlag(OrderType.OpenDoor)
					|| o.HasFlag(OrderType.CloseDoor)
					|| o.HasFlag(OrderType.Cloak)
					|| o.HasFlag(OrderType.Decloak))
					Events.Add(unit.Position, 5, 15, null);

				// abilities
				if (o.HasFlag(OrderType.CastConsume)
					|| o.HasFlag(OrderType.CastDarkSwarm)
					|| o.HasFlag(OrderType.CastDefensiveMatrix)
					|| o.HasFlag(OrderType.CastDisruptionWeb)
					|| o.HasFlag(OrderType.CastEmpShockwave)
					|| o.HasFlag(OrderType.CastEnsnare)
					|| o.HasFlag(OrderType.CastFeedback)
					|| o.HasFlag(OrderType.CastHallucination)
					|| o.HasFlag(OrderType.CastInfestation)
					|| o.HasFlag(OrderType.CastIrradiate)
					|| o.HasFlag(OrderType.CastLockdown)
					|| o.HasFlag(OrderType.CastMaelstrom)
					|| o.HasFlag(OrderType.CastMindControl)
					|| o.HasFlag(OrderType.CastOpticalFlare)
					|| o.HasFlag(OrderType.CastParasite)
					|| o.HasFlag(OrderType.CastPlague)
					|| o.HasFlag(OrderType.CastPsionicStorm)
					|| o.HasFlag(OrderType.CastRecall)
					|| o.HasFlag(OrderType.CastRestoration)
					|| o.HasFlag(OrderType.CastSpawnBroodlings)
					|| o.HasFlag(OrderType.CastStasisField)
					|| o.HasFlag(OrderType.FireYamatoGun)
					|| o.HasFlag(OrderType.RechargeShieldsUnit))
				{
					Events.Add(unit.Target != null ? unit.Target.Position : unit.OrderTargetPosition, 30, 50, null);
				}

				// scanner
				if (o == OrderType.CastScannerSweep && unit.LastCommand.TypeEquals(UnitCommandType.UseTechPosition) && unit.LastCommand.Tech.TypeEquals(TechType.Scanner_Sweep))
					Events.Add(unit.LastCommand.TargetPosition, 100, 50, null);

				// more abilities
				if (o == OrderType.PlaceMine)
					Events.Add(unit.Position, 2, 10, null);

				// other
				if (o.HasFlag(OrderType.EnterNydusCanal)
					//|| o.HasFlag(OrderType.EnterTransport)
					|| o.HasFlag(OrderType.GuardianAspect)
					|| o.HasFlag(OrderType.MoveUnload)
					|| o.HasFlag(OrderType.PickupBunker)
					|| o.HasFlag(OrderType.PickupTransport)
					|| o.HasFlag(OrderType.PlaceAddon)
					|| o.HasFlag(OrderType.SelfDestructing)
					|| o.HasFlag(OrderType.Unload)
					|| o.HasFlag(OrderType.ZergBirth))
					Events.Add(unit.Position, 50, 40, null);
			}

			Events.Run();
		}

		public override void OnSendText(string text)
		{
			if(text == "/freeze")
				while(true)
				{
					Thread.Sleep(100);
				}

			if (text.IndexOf("TRNSPD", StringComparison.OrdinalIgnoreCase) >= 0)
			{
				var match = s_speedRegex.Match(text);
				if (match.Success)
				{
					var speed = Convert.ToInt32(match.Groups["Speed"].Value);
					Game.SetLocalSpeed(speed);
					Game.SendText("TRNSPD {0}", speed);
					Game.SendText("Set speed to {0}", speed);
				}
			}
			else if (text.IndexOf("RACES", StringComparison.OrdinalIgnoreCase) >= 0)
			{
				foreach(var player in Game.Players)
				{
					Game.Write("{0}: {1}", player.Name, player.Race);
				}
			}
		}

		public override void OnReceiveText(Player player, string text)
		{
			if (player == Game.Self)
				return;
			var match = s_speedRegex.Match(text);
			if(!match.Success)
				return;
			var speed = Convert.ToInt32(match.Groups["Speed"].Value);
			Game.SetLocalSpeed(speed);
			Game.SendText("Set speed to {0}", speed);
		}

		public override void OnPlayerLeft(Player player)
		{
			Game.Write("{0} left", player.Name);
		}

		public override void OnPlayerDropped(Player player)
		{
			Game.Write("{0} DROPPED", player.Name);
		}

		public override void OnNukeDetect(Position target)
		{
			Events.Add(target, 1000, 100, null);
		}

		public override void OnUnitCreate(Unit unit)
		{
			if (unit.Player == Game.Self && unit.UnitType.IsBuilding)
				Events.Add(unit.Position, unit.UnitType.BuildScore / 10, 25, null);
		}

		public override void OnUnitDestroy(Unit unit)
		{
			if (unit.Player == Game.Self)
			{
			}
		}

		public override void OnUnitMorph(Unit unit)
		{

		}

		public override void OnUnitComplete(Unit unit)
		{

		}

		private string GetScPath(RegistryKey key)
		{
			var regKey = key.OpenSubKey(@"*\SOFTWARE\Blizzard Entertainment\Starcraft");
			if (regKey == null)
				return null;
			var value = regKey.GetValue("InstallPath") as string;
			regKey.Close();
			if(value == null)
				return null;
			return File.Exists(Path.Combine(value, "StarCraft.exe"))
				? value
				: null;
		}
	}
}
