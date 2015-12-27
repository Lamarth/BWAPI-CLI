using System.ComponentModel;
using System.Drawing;
using System.Linq;
using BroodWar;
using BroodWar.Api;
using BroodWar.Api.Enum;

namespace ExampleAIModule
{
	public class ExampleAiModule : AiBase
	{
		private bool _showBullets;
		private bool _showVisibilityData;
        //private bool _analized;
        //private BwRegion _home;
        //private BwRegion _enemyBase;
        //private BackgroundWorker _terrainAnalyzer;

		public override void OnStart()
		{
			Game.SendText("Hello World!");
			Game.Write("The map is {0}, a {1} player map", Game.MapName, Game.StartLocations.Count);

			// Enable some cheat flags
			Game.EnableFlag(Flag.UserInput);

			// Uncomment to enable complete map information
			Game.EnableFlag(Flag.CompleteMapInformation);

            ////read map information into BWTA so terrain analysis can be done in another thread
            //TerrainAnalyzer.ReadMap();
            //_analized = false;
            //_terrainAnalyzer = new BackgroundWorker();
            //_terrainAnalyzer.DoWork += DoAnalyze;
            //_terrainAnalyzer.RunWorkerCompleted += AnalysisComplete;
            //Game.Write("Analyzing map... this may take a minute");
            //_terrainAnalyzer.RunWorkerAsync();

			if(Game.IsReplay)
			{
				Game.Write("The following players are in this replay:");
				foreach(var player in Game.Players.Where(player => player.Units.Any() && !player.IsNeutral))
				{
					Game.Write("{0}, playing as {1}", player.Name, player.Race.Type);
				}
			}
			else
			{
				Game.Write("The match up is {0} v {1}", Game.Self.Race.Type, Game.Enemy.Race.Type);

				//send each worker to the mineral field that is closest to it
				foreach(var unit in Game.Self.Units)
				{
					if(unit.UnitType.IsWorker)
					{
						var closestMineral = Game.Minerals.OrderBy(unit.Distance).FirstOrDefault();
						if(closestMineral != null)
							unit.RightClick(closestMineral, false);
					}
					else if(unit.UnitType.IsResourceDepot)
					{
						//if this is a center, tell it to build the appropiate type of worker
						if(unit.UnitType.Race.Type != RaceType.Zerg)
						{
							unit.Train(Game.Self.Race.Worker.Type);
						}
						else //if we are Zerg, we need to select a larva and morph it into a drone
						{
							var larva = unit.Larva.FirstOrDefault();
							if(larva != null)
								larva.Morph(BroodWar.Api.Enum.UnitType.Zerg_Drone);
						}
					}
				}
			}
		}

		public override void OnEnd(bool isWinner)
		{
			if(isWinner)
			{
				//log win to file
			}
		}

		public override void OnFrame()
		{
			if(_showVisibilityData)
				DrawVisibilityData();

			if(_showBullets)
				DrawBullets();

			if(Game.IsReplay)
				return;

			var workerType = Game.Self.Race.Worker;
			var price = workerType.Price;
			var depot = Game.Self.Units.FirstOrDefault(u => u.UnitType.IsResourceDepot);
			//if our depot queue is empty and we have enouth supply and less than 16 workers
			if(depot != null
				&& !depot.TrainingQueue.Any()
				&& Game.Self.SupplyTotal - Game.Self.SupplyUsed >= price.Supply
				&& Game.Self.Units.Count(u => u.UnitType == workerType) < 16)
			{
				if(depot.UnitType.Race.Type != RaceType.Zerg)
				{
					depot.Train(workerType.Type);
				}
				else
				{
					var larva = depot.Larva.FirstOrDefault();
					if(larva != null)
						larva.Morph(workerType.Type);
				}
			}

			DrawStats();
            //if(_analized && Game.FrameCount % 30 == 0)
            //{
            //    //order one of our workers to guard our chokepoint.
            //    var worker = Game.Self.Units.First(u => u.UnitType.IsWorker);

            //    var choke = _home.Chokepoints.OrderBy(c => c.Width).FirstOrDefault();
            //    if(choke != null)
            //        worker.RightClick(choke.Center, false);
            //}
            //if(_analized)
            //    DrawTerrainData();
		}

		public override void OnSendText(string text)
		{
			switch(text)
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
					Game.Write("You typed '{0}'!", text);
					Game.SendText(text);
					break;
			}
		}

		public override void OnReceiveText(Player player, string text)
		{
			Game.Write("{0} said '{1}'", player.Name, text);
		}

		public override void OnPlayerLeft(Player player)
		{
			Game.SendText("{0} left the game.", player.Name);
		}

		public override void OnNukeDetect(Position target)
		{
			if(!target.IsUnknown)
				Game.Write("Nuclear Launch Detected at ({0},{1})", target.X, target.Y);
			else
				Game.Write("Nuclear Launch Detected");
		}

		public override void OnUnitDiscover(Unit unit)
		{
			if(!Game.IsReplay && Game.FrameCount > 1)
				Game.SendText("A {0} [{1}] has been discovered at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y);
		}

		public override void OnUnitEvade(Unit unit)
		{
			if(!Game.IsReplay && Game.FrameCount > 1)
				Game.SendText("A {0} [{1}] was left accessible at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y);
		}

		public override void OnUnitShow(Unit unit)
		{
			if(!Game.IsReplay && Game.FrameCount > 1)
				Game.SendText("A {0} [{1}] has been spotted at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y);
		}

		public override void OnUnitHide(Unit unit)
		{
			if(!Game.IsReplay && Game.FrameCount > 1)
				Game.SendText("A {0} [{1}] was last seen at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y);
		}

		public override void OnUnitCreate(Unit unit)
		{
			if(Game.FrameCount <= 1)
				return;

			if(!Game.IsReplay)
				Game.SendText("A {0} [{1}] has been created at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y);
			else
			{
				//if we are in a replay, then we will print out the build order (just of the buildings, not the units).
				if(unit.UnitType.IsBuilding && !unit.Player.IsNeutral)
				{
					var seconds = Game.FrameCount / 24;
					var minutes = seconds / 60;
					seconds %= 60;
					Game.SendText("{0:2}:{1:2}: {3} creates a {4}", minutes, seconds, unit.Player.Name, unit.UnitType.Type);
				}
			}
		}

		public override void OnUnitDestroy(Unit unit)
		{
			if(!Game.IsReplay && Game.FrameCount > 1)
				Game.SendText("A {0} [{1}] has been destroyed at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X, unit.Position.Y);
		}

		public override void OnUnitMorph(Unit unit)
		{
			if(!Game.IsReplay)
				Game.SendText("A {0} [{1}] has been morphed at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X,
					unit.Position.Y);
			else
			{
				//if we are in a replay, then we will print out the build order (just of the buildings, not the units).
				if(unit.UnitType.IsBuilding && !unit.Player.IsNeutral)
				{
					var seconds = Game.FrameCount / 24;
					var minutes = seconds / 60;
					seconds %= 60;
					Game.SendText("{0:2}:{1:2}: {3} morphs a {4}", minutes, seconds, unit.Player.Name, unit.UnitType.Type);
				}
			}
		}

		public override void OnUnitRenegade(Unit unit)
		{
			if(!Game.IsReplay)
				Game.SendText("A {0} [{1}] is now owned by {2}", unit.UnitType.Type, unit, unit.Player.Name);
		}

		public override void OnSaveGame(string gameName)
		{
			Game.Write("The game was saved to \"{0}\".", gameName);
		}

		public override void OnUnitComplete(Unit unit)
		{
			if(Game.FrameCount <= 1 || Game.IsReplay)
				return;

			Game.SendText("A {0} [{1}] has been completed at ({2},{3})", unit.UnitType.Type, unit, unit.Position.X,
				unit.Position.Y);
			if(!unit.UnitType.IsWorker || unit.Player.Id != Game.Self.Id)
				return;

			var closestMineral = Game.Minerals.OrderBy(unit.Distance).FirstOrDefault();
			if(closestMineral != null)
				unit.RightClick(closestMineral, false);
		}

		private void DrawStats()
		{
			var myUnits = Game.Self.Units;
			Game.DrawTextScreen(5, 0, "I have {0} units:", myUnits.Count);
			var groups = myUnits.GroupBy(u => u.UnitType).ToDictionary(u => u.Key, u => u.Count());
			var line = 1;
			foreach(var group in groups)
			{
				Game.DrawTextScreen(5, 16 * line, "{0} {1}s", group.Value, group.Key.Type);
				line++;
			}
		}

		private void DrawBullets()
		{
			var bullets = Game.Bullets;
			foreach(var bullet in bullets)
			{
				var position = bullet.Position;
				var velocityX = bullet.VelocityX;
				var velocityY = bullet.VelocityY;
				if(bullet.Player == Game.Self)
				{
					Game.DrawLineMap(position.X, position.Y, (int) (position.X + velocityX), (int) (position.Y + velocityY), Color.Green);
					Game.DrawTextMap(position.X, position.Y, "{0}", bullet.Type);
				}
				else
				{
					Game.DrawLineMap(position.X, position.Y, (int) (position.X + velocityX), (int) (position.Y + velocityY), Color.Red);
					Game.DrawTextMap(position.X, position.Y, "{0}", bullet.Type);
				}
			}
		}

		private void DrawVisibilityData()
		{
			for(var x = 0; x < Game.MapWidth; x++)
			{
				for(var y = 0; y < Game.MapHeight; y++)
				{
					if(Game.IsExplored(x, y))
					{
						Game.DrawDotMap(x * 32 + 16, y * 32 + 16, Game.IsVisible(x, y) ? Color.Green : Color.Blue);
					}
					else
						Game.DrawDotMap(x * 32 + 16, y * 32 + 16, Color.Red);
				}
			}
		}

		/*private void DrawTerrainData()
		{
			//we will iterate through all the base locations, and draw their outlines
			foreach(var baseLocation in TerrainAnalyzer.BaseLocations)
			{
				var t = baseLocation.TilePosition;

				//draw outline of center location
				Game.DrawBoxMap(t.X * 32, t.Y * 32, t.X * 32 + 4 * 32, t.Y * 32 + 3 * 32, Color.Blue, false);

				//draw a circle at each mineral patch
				foreach(var pos in baseLocation.StaticMinerals.Select(mineral => mineral.Position))
					Game.DrawCircleMap(pos.X, pos.Y, 30, Color.Cyan, false);
				

				//draw the outlines of vespene geysers
				foreach(var tp in baseLocation.Geysers.Select(geyser => geyser.InitialTilePosition))
					Game.DrawBoxMap(tp.X * 32, tp.Y * 32, tp.X * 32 + 4 * 32, tp.Y * 32 + 2 * 32, Color.Orange, false);

				//if this is an island expansion, draw a yellow circle around the base location
				if(!baseLocation.IsIsland)
					continue;

				var p = baseLocation.Position;
				Game.DrawCircleMap(p.X, p.Y, 80, Color.Yellow, false);
			}

			//we will iterate through all the regions and draw the polygon outline of it in green.
			foreach(var proj in TerrainAnalyzer.Regions
				.SelectMany(region => region.Polygon.Project((p1, p2) => new {p1, p2})))
			{
				Game.DrawLineMap(proj.p1.X, proj.p1.Y, proj.p2.X, proj.p2.Y, Color.Green);
			}

			//we will visualize the chokepoints with red lines
			foreach(var chokepoint in TerrainAnalyzer.Regions.SelectMany(region => region.Chokepoints))
			{
				var p1 = chokepoint.Sides.Item1;
				var p2 = chokepoint.Sides.Item2;
				Game.DrawLineMap(p1.X, p1.Y, p2.X, p2.Y, Color.Red);
			}
		}*/

		private void ShowPlayers()
		{
			foreach(var player in Game.Players)
			{
				Game.Write("Player [{0}]: {1} is in force: {2}", player.Id, player.Name, player.Force.Name);
			}
		}

		private void ShowForces()
		{
			foreach(var force in Game.Forces)
			{
				Game.Write("Force {0} has the following players:", force.Name);
				foreach(var player in force.Players)
				{
					Game.Write("  - Player [{0}]: {1}", player.Id, player.Name);
				}
			}
		}

		/*private void DoAnalyze(object sender, DoWorkEventArgs args)
		{
			TerrainAnalyzer.Analyze();
		}

		private void AnalysisComplete(object sender, RunWorkerCompletedEventArgs args)
		{
			////self start location only available if the map has base locations
			var homeLocation = TerrainAnalyzer.PlayerStartLocation(Game.Self);
			if(homeLocation != null)
				_home = homeLocation.Region;

			//enemy start location only available if Complete Map Information is enabled.
			var enemyLocation = TerrainAnalyzer.PlayerStartLocation(Game.Enemy);
			if(enemyLocation != null)
				_enemyBase = enemyLocation.Region;

			_analized = true;
			Game.Write("Finished analyzing map.");
		}*/
	}
}
