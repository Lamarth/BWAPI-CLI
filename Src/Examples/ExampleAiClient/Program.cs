using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Security.Principal;
using System.Threading;
using System.Windows.Forms;
using BroodWar.Api;
using BroodWar.Api.Client;
using BroodWar.Api.Enum;

namespace ExampleAiClient
{
	static class Program
	{
		private static bool _showBullets;
		private static bool _showVisibilityData;
        //private static bool _analyzed;
        //private static BwRegion _home;
        //private static BackgroundWorker _terrainAnalyzer;

		static void Main()
		{
			if (!new WindowsPrincipal(WindowsIdentity.GetCurrent()).IsInRole(WindowsBuiltInRole.Administrator))
			{
				MessageBox.Show("In order to use shared memory you must run this application as administrator");
				return;
			}
			Console.WriteLine("Connecting...");
			Reconnect();
			while (true)
			{
				Console.WriteLine("Waiting to enter match");
				while (!Game.IsInGame)
				{
					Client.Update();
					if (Client.IsConnected)
						continue;
					Console.WriteLine("Reconnecting...");
					Reconnect();
				}
				Console.WriteLine("Starting match");
				Game.SendText("Hello world!");
				Game.Write("The map is {0}, a {1} player map", Game.MapName, Game.StartLocations.Count);
				// Enable some cheat flags
				Game.EnableFlag(Flag.Max);
                //TerrainAnalyzer.ReadMap();
                //_analyzed = false;
                //_terrainAnalyzer = new BackgroundWorker();
                //_terrainAnalyzer.DoWork += DoAnalyze;
                //_terrainAnalyzer.RunWorkerCompleted += AnalysisComplete;
                //Game.Write("Analyzing map... this may take a minute");
                //_terrainAnalyzer.RunWorkerAsync();

				if (Game.IsReplay)
				{
					Game.Write("The following players are in this replay:");
					foreach (var player in Game.Players.Where(player => player.Units.Any() && !player.IsNeutral))
					{
						Game.Write("{0}, playing as {1}", player.Name, player.Race.Type);
					}
				}
				else
				{
					Game.Write("The match up is {0} v {1}", Game.Self.Race.Type, Game.Enemy.Race.Type);

					//send each worker to the mineral field that is closest to it
					foreach (var unit in Game.Self.Units)
					{
						if (unit.UnitType.IsWorker)
						{
							var closestMineral = Game.Minerals.OrderBy(unit.Distance).FirstOrDefault();
							if (closestMineral != null)
								unit.RightClick(closestMineral, false);
						}
						else if (unit.UnitType.IsResourceDepot)
						{
							//if this is a center, tell it to build the appropiate type of worker
							if (unit.UnitType.Race.Type != RaceType.Zerg)
							{
								unit.Train(Game.Self.Race.Worker.Type);
							}
							else //if we are Zerg, we need to select a larva and morph it into a drone
							{
								var larva = unit.Larva.FirstOrDefault();
								if (larva != null)
									larva.Morph(BroodWar.Api.Enum.UnitType.Zerg_Drone);
							}
						}
					}
				}
				while (Game.IsInGame)
				{
					foreach (var e in Game.Events)
					{
						switch (e.Type)
						{
							case EventType.MatchEnd:
								Console.WriteLine(e.IsWinner ? "I won the game" : "I didn't win the game");
								break;
							case EventType.SendText:
								switch (e.Text)
								{
									case "/show bullets":
										_showBullets = !_showBullets;
										break;
									case "/show players":
										ShowPlayers();
										break;
									case "/show forces":
										ShowForces();
										break;
									case "/show visibility":
										_showVisibilityData = !_showVisibilityData;
										break;
									default:
										Game.Write("You typed '{0}'!", e.Text);
										Game.SendText("{0}", e.Text);
										break;
								}
								break;
							case EventType.ReceiveText:
								Game.Write("{0} said '{1}'", e.Player.Name, e.Text);
								break;
							case EventType.PlayerLeft:
								Game.SendText("{0} left the game.", e.Player.Name);
								break;
							case EventType.NukeDetect:
								if (!e.Position.IsUnknown)
									Game.Write("Nuclear Launch Detected at ({0}, {1])", e.Position.X, e.Position.Y);
								else
									Game.Write("Nuclear Launch Detected");
								break;
							case EventType.UnitDiscover:
								if (!Game.IsReplay && Game.FrameCount > 1)
									Game.SendText("A {0} [{1}] has been discovered at ({2},{3})", e.Unit.UnitType.Type, e.Unit, e.Unit.Position.X, e.Unit.Position.Y);
								break;
							case EventType.UnitEvade:
								if (!Game.IsReplay && Game.FrameCount > 1)
									Game.SendText("A {0} [{1}] was left accessible at ({2},{3})", e.Unit.UnitType.Type, e.Unit, e.Unit.Position.X, e.Unit.Position.Y);
								break;
							case EventType.UnitShow:
								if (!Game.IsReplay && Game.FrameCount > 1)
									Game.SendText("A {0} [{1}] has been spotted at ({2},{3})", e.Unit.UnitType.Type, e.Unit, e.Unit.Position.X, e.Unit.Position.Y);
								break;
							case EventType.UnitHide:
								if (!Game.IsReplay && Game.FrameCount > 1)
									Game.SendText("A {0} [{1}] was last seen at ({2},{3})", e.Unit.UnitType.Type, e.Unit, e.Unit.Position.X, e.Unit.Position.Y);
								break;
							case EventType.UnitCreate:
								if (Game.FrameCount > 1)
								{
									if (!Game.IsReplay)
										Game.SendText("A {0} [{1}] has been created at ({2},{3})", e.Unit.UnitType.Type, e.Unit, e.Unit.Position.X, e.Unit.Position.Y);
									else
									{
										//if we are in a replay, then we will print out the build order (just of the buildings, not the units).
										if (e.Unit.UnitType.IsBuilding && !e.Unit.Player.IsNeutral)
										{
											var seconds = Game.FrameCount / 24;
											var minutes = seconds / 60;
											seconds %= 60;
											Game.SendText("{0:2}:{1:2}: {3} creates a {4}", minutes, seconds, e.Unit.Player.Name, e.Unit.UnitType.Type);
										}
									}
								}
								break;
							case EventType.UnitDestroy:
								if (!Game.IsReplay && Game.FrameCount > 1)
									Game.SendText("A {0} [{1}] has been destroyed at ({2},{3})", e.Unit.UnitType.Type, e.Unit, e.Unit.Position.X, e.Unit.Position.Y);
								break;
							case EventType.UnitMorph:
								if (!Game.IsReplay)
									Game.SendText("A {0} [{1}] has been morphed at ({2},{3})", e.Unit.UnitType.Type, e.Unit, e.Unit.Position.X,
										e.Unit.Position.Y);
								else
								{
									//if we are in a replay, then we will print out the build order (just of the buildings, not the units).
									if (e.Unit.UnitType.IsBuilding && !e.Unit.Player.IsNeutral)
									{
										var seconds = Game.FrameCount / 24;
										var minutes = seconds / 60;
										seconds %= 60;
										Game.SendText("{0:2}:{1:2}: {3} morphs a {4}", minutes, seconds, e.Unit.Player.Name, e.Unit.UnitType.Type);
									}
								}
								break;
							case EventType.UnitRenegade:
								if (!Game.IsReplay)
									Game.SendText("A {0} [{1}] is now owned by {2}", e.Unit.UnitType.Type, e.Unit, e.Unit.Player.Name);
								break;
							case EventType.SaveGame:
								Game.Write("The game was saved to \"{0}\".", e.Text);
								break;
						}
					}

					if (_showBullets)
						DrawBullets();

					if (_showVisibilityData)
						DrawVisibilityData();

					if (!Game.IsReplay)
					{
						DrawStats();
                        //if (_analyzed && Game.FrameCount % 30 == 0)
                        //{
                        //    //order one of our workers to guard our chokepoint.
                        //    var worker = Game.Self.Units.First(u => u.UnitType.IsWorker);

                        //    var choke = _home.Chokepoints.OrderBy(c => c.Width).FirstOrDefault();
                        //    if (choke != null)
                        //        worker.RightClick(choke.Center, false);
                        //}
                        //if (_analyzed)
                        //    DrawTerrainData();
					}

					Client.Update();
					if (Client.IsConnected)
						continue;
					Console.WriteLine("Reconnecting...");
					Reconnect();
				}
				Console.WriteLine("Game ended");
			}
		}

		private static void DrawStats()
		{
			var myUnits = Game.Self.Units;
			Game.DrawTextScreen(5, 0, "I have {0} units:", myUnits.Count);
			var groups = myUnits.GroupBy(u => u.UnitType).ToDictionary(u => u.Key, u => u.Count());
			var line = 1;
			foreach (var group in groups)
			{
				Game.DrawTextScreen(5, 16 * line, "{0} {1}s", group.Value, group.Key);
				line++;
			}
		}

		private static void DrawBullets()
		{
			var bullets = Game.Bullets;
			foreach (var bullet in bullets)
			{
				var position = bullet.Position;
				var velocityX = bullet.VelocityX;
				var velocityY = bullet.VelocityY;
				if (bullet.Player == Game.Self)
				{
					Game.DrawLineMap(position.X, position.Y, (int)(position.X + velocityX), (int)(position.Y + velocityY), Color.Green);
					Game.DrawTextMap(position.X, position.Y, "{0}", bullet.Type);
				}
				else
				{
					Game.DrawLineMap(position.X, position.Y, (int)(position.X + velocityX), (int)(position.Y + velocityY), Color.Red);
					Game.DrawTextMap(position.X, position.Y, "{0}", bullet.Type);
				}
			}
		}

		private static void DrawVisibilityData()
		{
            Position tileMid = new Position(16, 16);
            for (var x = 0; x < Game.MapWidth; x++)
            {
                for (var y = 0; y < Game.MapHeight; y++)
                {
                    TilePosition pos = new TilePosition(x, y);
                    if (Game.IsExplored(pos))
                        Game.DrawDot(Position.Rescale(pos) + tileMid, Game.IsVisible(pos) ? Color.Green : Color.Blue);
                    else
                        Game.DrawDot(Position.Rescale(pos) + tileMid, Color.Red);
                }
            }
        }

/*		private static void DrawTerrainData()
		{
			//we will iterate through all the base locations, and draw their outlines
			foreach (var baseLocation in TerrainAnalyzer.BaseLocations)
			{
				var t = baseLocation.TilePosition;

				//draw outline of center location
				Game.DrawBoxMap(t.X * 32, t.Y * 32, t.X * 32 + 4 * 32, t.Y * 32 + 3 * 32, Color.Blue, false);

				//draw a circle at each mineral patch
				foreach (var pos in baseLocation.StaticMinerals.Select(mineral => mineral.Position))
					Game.DrawCircleMap(pos.X, pos.Y, 30, Color.Cyan, false);


				//draw the outlines of vespene geysers
				foreach (var tp in baseLocation.Geysers.Select(geyser => geyser.InitialTilePosition))
					Game.DrawBoxMap(tp.X * 32, tp.Y * 32, tp.X * 32 + 4 * 32, tp.Y * 32 + 2 * 32, Color.Orange, false);

				//if this is an island expansion, draw a yellow circle around the base location
				if (!baseLocation.IsIsland)
					continue;

				var p = baseLocation.Position;
				Game.DrawCircleMap(p.X, p.Y, 80, Color.Yellow, false);
			}

			//we will iterate through all the regions and draw the polygon outline of it in green.
			foreach (var proj in TerrainAnalyzer.Regions
				.SelectMany(region => region.Polygon.Project((p1, p2) => new { p1, p2 })))
			{
				Game.DrawLineMap(proj.p1.X, proj.p1.Y, proj.p2.X, proj.p2.Y, Color.Green);
			}

			//we will visualize the chokepoints with red lines
			foreach (var chokepoint in TerrainAnalyzer.Regions.SelectMany(region => region.Chokepoints))
			{
				var p1 = chokepoint.Sides.Item1;
				var p2 = chokepoint.Sides.Item2;
				Game.DrawLineMap(p1.X, p1.Y, p2.X, p2.Y, Color.Red);
			}
		}*/

		private static void ShowPlayers()
		{
			foreach (var player in Game.Players)
			{
				Game.Write("Player [{0}]: {1} is in force: {2}", player.Id, player.Name, player.Force.Name);
			}
		}

		private static void ShowForces()
		{
			foreach (var force in Game.Forces)
			{
				Game.Write("Force {0} has the following players:", force.Name);
				foreach (var player in force.Players)
				{
					Game.Write("  - Player [{0}]: {1}", player.Id, player.Name);
				}
			}
		}

		/*private static void DoAnalyze(object sender, DoWorkEventArgs args)
		{
			TerrainAnalyzer.Analyze();
		}

		private static void AnalysisComplete(object sender, RunWorkerCompletedEventArgs args)
		{
			////self start location only available if the map has base locations
			var homeLocation = TerrainAnalyzer.PlayerStartLocation(Game.Self);
			if (homeLocation != null)
				_home = homeLocation.Region;

			_analyzed = true;
			Game.Write("Finished analyzing map.");
		}*/

		private static void Reconnect()
		{
			while (!Client.Connect())
			{
				Thread.Sleep(1000);
			}
		}

		private static IEnumerable<TResult> Project<TSource, TResult>(
			this IEnumerable<TSource> source,
			Func<TSource, TSource, TResult> projection)
		{
			using (var iterator = source.GetEnumerator())
			{
				if (!iterator.MoveNext())
				{
					yield break;
				}
				var first = iterator.Current;
				var previous = iterator.Current;
				while (iterator.MoveNext())
				{
					yield return projection(previous, iterator.Current);
					previous = iterator.Current;
				}
				yield return projection(previous, first);
			}
		}
	}
}
