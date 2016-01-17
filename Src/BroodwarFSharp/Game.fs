namespace BroodwarFSharp

open Position

type Gm = BroodWar.Api.Game

[<AbstractClass; Sealed>]
type Game = 
    /// Returns the set of all forces in the match
    static member Forces = Gm.Forces
    
    /// Returns the set of all players in the match. Note that this includes the Neutral player, which owns all the neutral units such as
    /// minerals, critters, etc
    static member Players = Gm.Players
    
    /// Returns all the visible units. If Flag::CompleteMapInformation is enabled, the set of all units is returned, not just visible ones.
    /// Note that units inside refineries are not included in this set yet
    static member AllUnits = Gm.AllUnits
    
    /// Returns the set of all accessible mineral patches
    static member Minerals = Gm.Minerals
    
    /// Returns the set of all accessible vespene geysers
    static member Geysers = Gm.Geysers
    
    /// Returns the set of all accessible neutral units
    static member NeutralUnits = Gm.NeutralUnits
    
    /// Returns the set of all mineral patches (including mined out and other inaccessible ones)
    static member StaticMinerals = Gm.StaticMinerals
    
    /// Returns the set of all vespene geysers (including mined out and other inaccessible ones)
    static member StaticGeysers = Gm.StaticGeysers
    
    /// Returns the set of all neutral units (including mined out and other inaccessible ones)
    static member StaticNeutralUnits = Gm.StaticNeutralUnits
    
    /// Returns all visible bullets. If Flag::CompleteMapInformation is enabled, the set of all bullets is returned, not just visible ones
    static member Bullets = Gm.Bullets
    
    /// Returns all visible nuke dots. If Flag::CompleteMapInformation is enabled, the set of all nuke dots is returned, not just visible ones
    static member NukeDots = Gm.NukeDots
    
    /// Returns the list of events
    static member Events = Gm.Events
    
    /// Returns the force with the given ID, or NULL if no force has the given ID
    static member GetForceById(forceId) = Gm.GetForceById(forceId)
    
    /// Returns the player with the given ID, or NULL if no player has the given ID
    static member GetPlayerById(playerId) = Gm.GetPlayerById(playerId)
    
    /// Returns the unit with the given ID, or NULL if no unit has the given ID
    static member GetUnitById(unitId) = Gm.GetUnitById(unitId)
    
    /// Returns a pointer to a Unit given an index
    static member IndexToUnit(unitIndex) = Gm.IndexToUnit(unitIndex)
    
    /// Returns the Region with the given ID, or NULL if no region has the given ID
    static member Region(regionId) = Gm.Region(regionId)
    
    /// Returns the game type
    static member GameType = Gm.GameType
    
    /// Returns the amount of latency the current game has. Currently only returns Latency::SinglePlayer, Latency::LanLow,
    /// Latency::LanMedium, or Latency::LanHigh
    static member Latency = Gm.Latency
    
    /// Returns the number of logical frames since the match started. If the game is paused, Game::getFrameCount will not increase however
    /// AIModule::onFrame will still be called while paused. On Fastest, there are about 23.8 - 24 frames per second
    static member FrameCount = Gm.FrameCount
    
    /// Returns the Frames Per Second (FPS) that the game is currently running at
    static member Fps = Gm.Fps
    
    /// Returns the Frames Per Second (FPS) that the game is currently running at
    static member AverageFps = Gm.AverageFps
    
    /// Returns the position of the mouse on the screen. Returns Positions::Unknown if Flag::UserInput is disabled
    static member MousePosition = Gm.MousePosition
    
    /// Returns true if the specified mouse button is pressed. Returns false if Flag::UserInput is disabled
    static member GetMouseState(button) = Gm.GetMouseState(button)
    
    /// Returns true if the specified key is pressed. Returns false if Flag::UserInput is disabled. Unfortunately this does not read the
    /// raw keyboard input yet - when you hold down a key, the getKeyState function is true for a frame, then false for a few frames, and
    /// then alternates between true and false (as if you were holding down the key in a text box). Hopefully this will be fixed in a later version
    static member GetKeyState(key) = Gm.GetKeyState(key)
    
    /// Returns the position of the top left corner of the screen on the map. Returns Positions::Unknown if Flag::UserInput is disabled
    static member ScreenPosition =
        let pos = Gm.ScreenPosition
        Pos (pos.X * 1<pixel>, pos.Y * 1<pixel>)
    
    /// Moves the screen to the given position on the map. The position specified where the top left corner of the screen will be
    static member SetScreenPosition(Pos (x, y):Position<pixel>) = Gm.SetScreenPosition(int x, int y)
    
    /// Pings the given position on the minimap
    static member PingMinimap(Pos (x, y):Position<pixel>) = Gm.PingMinimap(int x, int y)
    
    /// Returns true if the given flag has been enabled. Note that flags can only be enabled at the beginning of a match, during the AIModule::onStart callback
    static member IsFlagEnabled(flag) = Gm.IsFlagEnabled(flag)
    
    /// Enables the specified flag. Note that flags can only be enabled at the beginning of a match, during the AIModule::onStart callback
    static member EnableFlag(flag) = Gm.EnableFlag(flag)
    
    /// Returns the set of accessible units that are on the given build tile
    static member GetUnitsOnTile(Pos (x, y):Position<tile>) = Gm.GetUnitsOnTile(int x, int y)
    
    /// Returns the set of accessible units that are in or overlapping the given rectangle
    static member GetUnitsInRectangle(Pos (left, top):Position<pixel>, Pos (bottom, right):Position<pixel>) = Gm.GetUnitsInRectangle(int left, int top, int right, int bottom)
    
    /// Returns the set of accessible units within or overlapping a circle at the given point with the given radius
    static member GetUnitsInRadius(Pos (x, y):Position<pixel>, radius:int<pixel>) = Gm.GetUnitsInRadius(int x, int y, int radius)
    
    /// Returns the last error that was set. If you try to order enemy units around, or morph bunkers into lurkers, BWAPI will set error codes,
    /// which can be retrieved using this function
    static member LastError with get() = Gm.LastError and set(value) = Gm.LastError <- value
    
    /// Returns the width of the current map, in build tile units. To get the width of the current map in walk tile units, multiply by 4.
    /// To get the width of the current map in Position units, multiply by TILE_SIZE (which is 32)
    static member MapWidth = Gm.MapWidth
    
    /// Returns the height of the current map, in build tile units. To get the height of the current map in walk tile units, multiply by 4.
    /// To get the height of the current map in Position units, multiply by TILE_SIZE (which is 32)
    static member MapHeight = Gm.MapHeight
    
    /// Returns the file name of the current map
    static member MapFileName = Gm.MapFileName
    
    /// Returns the full path name of the current map
    static member MapPathName = Gm.MapPathName
    
    /// Returns the name/title of the current map
    static member MapName = Gm.MapName
    
    /// Returns the SHA-1 hash of the map file
    static member MapHash = Gm.MapHash
    
    /// Returns true if the specified walk tile is walkable. The values of x and y are in walk tile coordinates (different from build tile coordinates).
    /// Note that this just uses the static map data. You will also need to make sure no ground units are on the coresponding build tile to see if its
    /// currently walkable. To do this, see unitsOnTile
    static member IsWalkable(Pos (x, y):Position<walk>) = Gm.IsWalkable(int x, int y)
    
    /// Returns the ground height of the given build tile. 0 = normal, 1 = high ground. 2 = very high ground
    static member GetGroundHeight(Pos (x, y):Position<tile>) = Gm.GetGroundHeight(int x, int y)
    
    /// Returns true if the specified build tile is buildable. Note that this just uses the static map data. You will also need to make sure no ground units
    /// on the tile to see if its currently buildable. To do this, see unitsOnTile
    static member IsBuildable(Pos (x, y):Position<tile>, includeBuildings) = Gm.IsBuildable(int x, int y, includeBuildings)
    
    /// Returns true if the specified build tile is visible. If the tile is concealed by fog of war, the function will return false
    static member IsVisible(Pos (x, y):Position<tile>) = Gm.IsVisible(int x, int y)
     
    /// Returns true if the specified build tile has been explored (i.e. was visible at some point in the match)
    static member IsExplored(Pos (x, y):Position<tile>) = Gm.IsExplored(int x, int y)
     
    /// Returns true if the specified build tile has zerg creep on it. If the tile is concealed by fog of war, the function will return false
    static member HasCreep(Pos (x, y):Position<tile>) = Gm.HasCreep(int x, int y)
     
    /// Returns true if the given build location is powered by a nearby friendly pylon
    static member HasPower(Pos (x, y):Position<tile>, unitType) = Gm.HasPower(int x, int y, unitType)
     
    /// Returns true if the given build location is powered by a nearby friendly pylon
    static member HasPower(Pos (x, y):Position<tile>, width:int<tile>, height:int<tile>, unitType) = Gm.HasPower(int x, int y, int width, int height, unitType)
     
    /// Returns true if the given pixel location is powered by a nearby friendly pylon
    static member HasPowerPrecise(Pos (x, y):Position<pixel>, unitType) = Gm.HasPowerPrecise(int x, int y, unitType)
    
    /// Returns true if the given unit type can be built at the given build tile position. Note the tile position specifies the top left tile
    /// of the building. If builder is not null, the unit will be discarded when determining whether or not any ground units are blocking the build location
    static member CanBuildHere(Pos (x, y):Position<tile>, unitType, builder, checkExplored) = Gm.CanBuildHere(new BroodWar.Api.TilePosition(int x, int y), unitType, builder, checkExplored)
    
    /// Returns true if the AI player has enough resources, supply, tech, and required units in order to make the given unit type. If builder is not null,
    /// canMake will return true only if the builder unit can build the given unit type
    static member CanMake(unitType, builder) = Gm.CanMake(unitType, builder)
    
    /// Returns true if the AI player has enough resources required to research the given tech type. If unit is not null, canResearch will return true
    /// only if the given unit can research the given tech type
    static member CanResearch(techType, unit, checkCanIssueCommand) = Gm.CanResearch(techType, unit, checkCanIssueCommand)
    
    /// Returns true if the AI player has enough resources required to upgrade the given upgrade type. If unit is not null, canUpgrade will return true
    /// only if the given unit can upgrade the given upgrade type
    static member CanUpgrade(upgradeType, unit, checkCanIssueCommand) = Gm.CanUpgrade(upgradeType, unit, checkCanIssueCommand)
    
    /// Returns the set of starting locations for the given map. To determine the starting location for the players in the current match,
    /// see Player::getStartLocation
    static member StartLocations = Gm.StartLocations
    
    /// Prints text on the screen. Text is not sent to other players in multiplayer games
    static member Write format = Printf.ksprintf Gm.Write format
    
    /// Sends text to other players - as if it were entered in chat. In single player games and replays, this will just print the text on the screen.
    /// If the game is a single player match and not a replay, then this function can be used to execute cheat codes, i.e. Broodwar->sendText("show me the money")
    static member SendText format = Printf.ksprintf Gm.SendText format
    
    /// Sends text to other players - as if it were entered in chat. In single player games and replays, this will just print the text on the screen.
    /// If the game is a single player match and not a replay, then this function can be used to execute cheat codes, i.e. Broodwar->sendText("show me the money")
    static member SendText (toAllies:bool, format) = Printf.ksprintf (fun str -> Gm.SendText(toAllies, str)) format
    
    /// Returns true if Broodwar is in a game. Returns false for lobby and menu screens
    static member IsInGame = Gm.IsInGame

    /// Returns true if Broodwar is in a multiplayer game. Returns false for single player games and replays
    static member IsMultiplayer = Gm.IsMultiplayer
    
    /// Returns true if Broodwar is in a BNet multiplayer game
    static member IsBattleNet = Gm.IsBattleNet
    
    /// Returns true if Broodwar is paused. If the game is paused, Game::getFrameCount will continue to increase and AIModule::onFrame will still
    /// be called while paused
    static member IsPaused = Gm.IsPaused
    
    /// Returns true if Broodwar is in a replay
    static member IsReplay = Gm.IsReplay
    
    /// Pauses the game. If the game is paused, Game::getFrameCount will not increase however AIModule::onFrame will still be called while paused
    static member PauseGame() = Gm.PauseGame()
    
    /// Resumes the game
    static member ResumeGame() = Gm.ResumeGame()
    
    /// Leaves the current match and goes to the after-game stats screen
    static member LeaveGame() = Gm.LeaveGame()
    
    /// Restarts the match. Works the same way as if you restarted the match from the menu screen. Only available in single player mode
    static member RestartGame() = Gm.RestartGame()
    
    /// Sets the speed of the game to the given number. Lower numbers are faster. 0 is the fastest speed StarCraft can handle (which is about as
    /// fast as the fastest speed you can view a replay at). Any negative value will reset the speed to the StarCraft default
    static member SetLocalSpeed(speed) = Gm.SetLocalSpeed(speed)
    
    /// Issues a command to a group of units
    static member IssueCommand(units, command) = Gm.IssueCommand(units, command)
    
    /// Returns the set of units currently selected by the user in the GUI. If Flag?::UserInput? was not enabled during the AIModule::onStart callback,
    /// this function will always return an empty set
    static member GetSelectedUnits = Gm.GetSelectedUnits
    
    /// Returns a pointer to the player that BWAPI controls. In replays this will return null
    static member Self = Gm.Self
    
    /// Returns a pointer to the enemy player. If there is more than one enemy, this returns a pointer to just one enemy (see enemies to get all enemies
    /// still in game). In replays this will return NULL
    static member Enemy = Gm.Enemy
    
    /// Returns a pointer to the neutral player
    static member Neutral = Gm.Neutral
    
    /// Returns a set of all the ally players that have not left or been defeated. Does not include self
    static member Allies = Gm.Allies
    
    /// Returns a set of all the enemy players that have not left or been defeated
    static member Enemies = Gm.Enemies
    
    /// Returns a set of all the observer players that have not left
    static member Observers = Gm.Observers
    
    //static member SetTextSize(size) = Gm.SetTextSize(size)
    
    /// Draws text on the screen at the given position. Text can be drawn in different colors by using the following control characters: TODO: add image from wiki
    static member DrawText(Pos (x, y):Position<pixel>, format) = Printf.ksprintf (fun str -> Gm.DrawTextMap(int x, int y, str)) format

    static member DrawTextCType(ctype, Pos (x, y):Position<pixel>, format) = Printf.ksprintf (fun str -> Gm.DrawTextCType(ctype, int x, int y, str)) format
    
    static member DrawTextMouse(Pos (x, y):Position<pixel>, format) = Printf.ksprintf (fun str -> Gm.DrawTextMouse(int x, int y, str)) format
    
    static member DrawTextScreen(Pos (x, y):Position<pixel>, format) = Printf.ksprintf (fun str -> Gm.DrawTextScreen(int x, int y, str)) format
    
    /// Draws a box on the screen, with the given color. If isSolid is true, the entire box will be rendered, otherwise just the outline will be drawn
    static member DrawBox(Pos (left, top):Position<pixel>, Pos (right, bottom):Position<pixel>, color, isSolid) = Gm.DrawBoxMap(int left, int top, int right, int bottom, color, isSolid)

    static member DrawBoxCType(ctype, Pos (left, top):Position<pixel>, Pos (right, bottom):Position<pixel>, color, isSolid) = Gm.DrawBoxCType(ctype, int left, int top, int right, int bottom, color, isSolid)
    
    static member DrawBoxMouse(Pos (left, top):Position<pixel>, Pos (right, bottom):Position<pixel>, color, isSolid) = Gm.DrawBoxMouse(int left, int top, int right, int bottom, color, isSolid)
    
    static member DrawBoxScreen(Pos (left, top):Position<pixel>, Pos (right, bottom):Position<pixel>, color, isSolid) = Gm.DrawBoxScreen(int left, int top, int right, int bottom, color, isSolid)
    
    /// Draws a triangle on the screen. If isSolid is true, a solid triangle is drawn, otherwise just the outline of the triangle will be drawn
    static member DrawTriangle(Pos (ax, ay):Position<pixel>, Pos (bx, by):Position<pixel>, Pos (cx, cy):Position<pixel>, color, isSolid) = Gm.DrawTriangleMap(int ax, int ay, int bx, int by, int cx, int cy, color, isSolid)

    static member DrawTriangleCType(ctype, Pos (ax, ay):Position<pixel>, Pos (bx, by):Position<pixel>, Pos (cx, cy):Position<pixel>, color, isSolid) = Gm.DrawTriangleCType(ctype, int ax, int ay, int bx, int by, int cx, int cy, color, isSolid)
    
    static member DrawTriangleMouse(Pos (ax, ay):Position<pixel>, Pos (bx, by):Position<pixel>, Pos (cx, cy):Position<pixel>, color, isSolid) = Gm.DrawTriangleMouse(int ax, int ay, int bx, int by, int cx, int cy, color, isSolid)
    
    static member DrawTriangleScreen(Pos (ax, ay):Position<pixel>, Pos (bx, by):Position<pixel>, Pos (cx, cy):Position<pixel>, color, isSolid) = Gm.DrawTriangleScreen(int ax, int ay, int bx, int by, int cx, int cy, color, isSolid)
    
    /// Draws a circle on the screen, with the given color. If isSolid is true, a solid circle is drawn, otherwise just the outline of a circle will be drawn
    static member DrawCircle(Pos (x, y):Position<pixel>, radius:int<pixel>, color, isSolid) = Gm.DrawCircleMap(int x, int y, int radius, color, isSolid)

    static member DrawCircleCType(ctype, x, y, radius:int<pixel>, color, isSolid) = Gm.DrawCircleCType(ctype, int x, int y, int radius, color, isSolid)
    
    static member DrawCircleMouse(Pos (x, y):Position<pixel>, radius:int<pixel>, color, isSolid) = Gm.DrawCircleMouse(int x, int y, int radius, color, isSolid)
    
    static member DrawCircleScreen(Pos (x, y):Position<pixel>, radius:int<pixel>, color, isSolid) = Gm.DrawCircleScreen(int x, int y, int radius, color, isSolid)
    
    /// Draws an ellipse on the screen, with the given color. If isSolid is true, a solid ellipse is drawn, otherwise just the outline of an ellipse will be drawn
    static member DrawEllipse(Pos (x, y):Position<pixel>, xrad:int<pixel>, yrad:int<pixel>, color, isSolid) = Gm.DrawEllipseMap(int x, int y, int xrad, int yrad, color, isSolid)

    static member DrawEllipseCType(ctype, Pos (x, y):Position<pixel>, xrad:int<pixel>, yrad:int<pixel>, color, isSolid) = Gm.DrawEllipseCType(ctype, int x, int y, int xrad, int yrad, color, isSolid)
    
    static member DrawEllipseMouse(Pos (x, y):Position<pixel>, xrad:int<pixel>, yrad:int<pixel>, color, isSolid) = Gm.DrawEllipseMouse(int x, int y, int xrad, int yrad, color, isSolid)
    
    static member DrawEllipseScreen(Pos (x, y):Position<pixel>, xrad:int<pixel>, yrad:int<pixel>, color, isSolid) = Gm.DrawEllipseScreen(int x, int y, int xrad, int yrad, color, isSolid)
    
    /// Draws a dot on the screen at the given position with the given color
    static member DrawDot(Pos (x, y):Position<pixel>, color) = Gm.DrawDotMap(int x, int y, color)

    static member DrawDotCType(ctype, x, y, color) = Gm.DrawDotCType(ctype, int x, int y, color)
    
    static member DrawDotMouse(Pos (x, y):Position<pixel>, color) = Gm.DrawDotMouse(int x, int y, color)
    
    static member DrawDotScreen(Pos (x, y):Position<pixel>, color) = Gm.DrawDotScreen(int x, int y, color)
    
    /// Draws a line on the screen from a to b with the given color
    static member DrawLine(Pos (x1, y1):Position<pixel>, Pos (x2, y2):Position<pixel>, color) = Gm.DrawLineMap(int x1, int y1, int x2, int y2, color)

    static member DrawLineCType(ctype, Pos (x1, y1):Position<pixel>, Pos (x2, y2):Position<pixel>, color) = Gm.DrawLineCType(ctype, int x1, int y1, int x2, int y2, color)
    
    static member DrawLineMouse(Pos (x1, y1):Position<pixel>, Pos (x2, y2):Position<pixel>, color) = Gm.DrawLineMouse(int x1, int y1, int x2, int y2, color)
    
    static member DrawLineScreen(Pos (x1, y1):Position<pixel>, Pos (x2, y2):Position<pixel>, color) = Gm.DrawLineScreen(int x1, int y1, int x2, int y2, color)
    
    /// Retrieves latency values for the game. Includes latency, speed, and mode
    static member LatencyFrames = Gm.LatencyFrames
    
    static member LatencyTime = Gm.LatencyTime
    
    static member RemainingLatencyFrames = Gm.RemainingLatencyFrames
    
    static member RemainingLatencyTime = Gm.RemainingLatencyTime
    
    /// Retrieves the current revision of BWAPI
    static member Revision = Gm.Revision
    
    /// Retrieves the debug state of the BWAPI build
    static member IsDebug = Gm.IsDebug
    
    /// Returns true if latency compensation is enabled
    static member IsLatComEnabled = Gm.IsLatComEnabled
    
    /// Use to enable or disable latency compensation. Default: Enabled
    static member SetLatCom(isEnabled) = Gm.SetLatCom(isEnabled)
    
    /// Retrieves the number of frames in the replay
    static member ReplayFrameCount = Gm.ReplayFrameCount
    
    /// Sets the rendering state of the Starcraft GUI
    static member SetGui(isEnabled) = Gm.SetGui(isEnabled)
    
    /// Retrieves the instance number recorded by BWAPI to identify which instance an AI module belongs to
    static member InstanceNumber = Gm.InstanceNumber
    
    /// Retrieves the bot's APM. Can include or exclude select commands
    static member GetApm(includeSelects) = Gm.GetApm(includeSelects)
    
    /// Changes the map to the one specified. Changes do not take effect unless the game is restarted
    static member SetMap(mapFileName) = Gm.SetMap(mapFileName)
    
    /// Sets the frame skip value. 1 = normal
    static member SetFrameSkip(frameSkip) = Gm.SetFrameSkip(frameSkip)
    
    /// Returns true if Starcraft can find a path from the start to the finish
    static member HasPath(Pos (startX, startY):Position<pixel>, Pos (finishX, finishY):Position<pixel>) = Gm.HasPath(new BroodWar.Api.Position(int startX, int startY), new BroodWar.Api.Position(int finishX, int finishY))
    
    /// Sets the BWAPI player's alliance with another player
    static member SetAlliance(player, allied, alliedVictory) = Gm.SetAlliance(player, allied, alliedVictory)
    
    /// Sets the BWAPI player's vision with another player
    static member SetVision(player, isEnabled) = Gm.SetVision(player, isEnabled)
    
    /// Returns the elapsed game time in seconds
    static member ElapsedTime = Gm.ElapsedTime
    
    /// Sets the level of command optimizations.
    /// 0 = No optimization.
    /// 1 = Some optimization    (Stop, Hold Position, Siege, Burrow, etc.).
    /// 2 = More optimization    (Train, Set Rally, Lift, [multi-select buildings]).
    /// 3 = Maximum optimization (Attack/Move to position, use ability at position, etc.)
    static member SetCommandOptimizationLevel(level) = Gm.SetCommandOptimizationLevel(level)
    
    /// Returns the remaining countdown time in seconds
    static member CountdownTimer = Gm.CountdownTimer
    
    /// Returns the set of all map regions
    static member AllRegions = Gm.AllRegions
    
    /// Returns the region at a position
    static member GetRegionAt(Pos (x, y):Position<pixel>) = Gm.GetRegionAt(int x, int y)
    
    /// Returns the time taken to perform the previous event call. Used for tournament management
    static member LastEventTime = Gm.LastEventTime
    
    /// Enables or disables the Fog of War in a replay
    static member SetRevealAll(reveal) = Gm.SetRevealAll(reveal)

    /// Gets a build location for a unit type near a position within a range, on or off creep
    static member GetBuildLocation(unitType, Pos (desiredX, desiredY):Position<tile>, maxRange:int<tile>, onCreep) = Gm.GetBuildLocation(unitType, new BroodWar.Api.TilePosition(int desiredX, int desiredY), int maxRange, onCreep)

    /// Gets the damage from a unit to another (usually yours)
    static member GetDamageFrom(fromType, toType, fromPlayer, toPlayer) = Gm.GetDamageFrom(fromType, toType, fromPlayer, toPlayer)

    /// Gets the damage to a unit from another (usually yours)
    static member GetDamageTo(toType, fromType, toPlayer, fromPlayer) = Gm.GetDamageTo(toType, fromType, toPlayer, fromPlayer)
