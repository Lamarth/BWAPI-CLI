namespace BroodwarFSharp

open Position

[<Sealed>]
type Game() =
    do Unit.NewGame ()
    let mutable _UnitsFrame = -1
    let mutable _AllUnits = [||]
    let mutable _OwnUnits = [||]
    let mutable _EnemyUnits = [||]

    let renewUnits () =
        if _UnitsFrame <> Gm.FrameCount then
            _UnitsFrame <- Gm.FrameCount
            _AllUnits <- Gm.AllUnits |> Seq.map Unit.convert |> Array.ofSeq
            _OwnUnits <- _AllUnits |> Array.filter (fun unit -> unit.Player = Gm.Self)
            _EnemyUnits <- _AllUnits |> Array.filter (fun unit -> Gm.Self.IsEnemy(unit.Player))

    let mutable _MineralsFrame = -1
    let mutable _Minerals = [||]

    let mutable _GeysersFrame = -1
    let mutable _Geysers = [||]

    let mutable _NeutralUnitsFrame = -1
    let mutable _NeutralUnits = [||]

    let _StaticMinerals = Gm.StaticMinerals |> Seq.map Unit.convert |> Array.ofSeq
    let _StaticGeysers = Gm.StaticGeysers |> Seq.map Unit.convert |> Array.ofSeq
    let _StaticNeutralUnits = Gm.StaticNeutralUnits |> Seq.map Unit.convert |> Array.ofSeq

    let widthTiles = Gm.MapWidth * 1<tile>
    let heightTiles = Gm.MapHeight * 1<tile>
    let widthWalks = widthTiles * WalkPerTile
    let heightWalks = heightTiles * WalkPerTile
    let widthPixels = widthTiles * PixelPerTile
    let heightPixels = heightTiles * PixelPerTile

    /// Returns the width of the current map, in build tile units.
    member game.WidthTiles = widthTiles
    /// Returns the height of the current map, in build tile units.
    member game.HeightTiles = heightTiles
    /// Returns the width of the current map, in walk units.
    member game.WidthWalks = widthWalks
    /// Returns the height of the current map, in walk units.
    member game.HeightWalks = heightWalks
    /// Returns the width of the current map, in pixel units.
    member game.WidthPixels = widthPixels
    /// Returns the height of the current map, in pixel units.
    member game.HeightPixels = heightPixels

    /// Returns true if the tile position fits on the map.
    member game.isValidTile (Pos (x, y)) = x >= 0<tile> && y >= 0<tile> && x < widthTiles && y < heightTiles
    /// Returns true if the walk position fits on the map.
    member game.isValidWalk (Pos (x, y)) = x >= 0<walk> && y >= 0<walk> && x < widthWalks && y < heightWalks
    /// Returns true if the pixel position fits on the map.
    member game.isValidPixel (Pos (x, y)) = x >= 0<pixel> && y >= 0<pixel> && x < widthPixels && y < heightPixels

    /// Returns the set of all forces in the match
    member inline game.Forces = Gm.Forces
    
    /// Returns the set of all players in the match. Note that this includes the Neutral player, which owns all the neutral units such as
    /// minerals, critters, etc
    member inline game.Players = Gm.Players
    
    /// Returns all the visible units. If Flag::CompleteMapInformation is enabled, the set of all units is returned, not just visible ones.
    /// Note that units inside refineries are not included in this set yet
    member game.AllUnits =
        renewUnits ()
        _AllUnits
    
    /// Returns all the visible units owned by the current player. If Flag::CompleteMapInformation is enabled, the set of all units is returned, not just visible ones.
    /// Note that units inside refineries are not included in this set yet
    member game.OwnUnits =
        renewUnits ()
        _OwnUnits
    
    /// Returns all the visible units owned by enemies of the current player. If Flag::CompleteMapInformation is enabled, the set of all units is returned, not just visible ones.
    /// Note that units inside refineries are not included in this set yet
    member game.EnemyUnits =
        renewUnits ()
        _EnemyUnits
    
    /// Returns the set of all accessible mineral patches
    member game.Minerals =
        if _MineralsFrame <> Gm.FrameCount then
            _MineralsFrame <- Gm.FrameCount
            _Minerals <- Gm.Minerals |> Seq.map Unit.convert |> Array.ofSeq
        _Minerals
    
    /// Returns the set of all accessible vespene geysers
    member game.Geysers =
        if _GeysersFrame <> Gm.FrameCount then
            _GeysersFrame <- Gm.FrameCount
            _Geysers <- Gm.Geysers |> Seq.map Unit.convert |> Array.ofSeq
        _Geysers
    
    /// Returns the set of all accessible neutral units
    member game.NeutralUnits =
        if _NeutralUnitsFrame <> Gm.FrameCount then
            _NeutralUnitsFrame <- Gm.FrameCount
            _NeutralUnits <- Gm.NeutralUnits |> Seq.map Unit.convert |> Array.ofSeq
        _NeutralUnits
    
    /// Returns the set of all mineral patches (including mined out and other inaccessible ones)
    member game.StaticMinerals = _StaticMinerals
    
    /// Returns the set of all vespene geysers (including mined out and other inaccessible ones)
    member game.StaticGeysers = _StaticGeysers
    
    /// Returns the set of all neutral units (including mined out and other inaccessible ones)
    member game.StaticNeutralUnits = _StaticNeutralUnits
    
    /// Returns all visible bullets. If Flag::CompleteMapInformation is enabled, the set of all bullets is returned, not just visible ones
    member inline game.Bullets = Gm.Bullets
    
    /// Returns all visible nuke dots. If Flag::CompleteMapInformation is enabled, the set of all nuke dots is returned, not just visible ones
    member inline game.NukeDots = Gm.NukeDots
    
    /// Returns the list of events
    member inline game.Events = Gm.Events
    
    /// Returns the force with the given ID, or NULL if no force has the given ID
    member inline game.GetForceById(forceId) = Gm.GetForceById(forceId)
    
    /// Returns the player with the given ID, or NULL if no player has the given ID
    member inline game.GetPlayerById(playerId) = Gm.GetPlayerById(playerId)
    
    /// Returns the unit with the given ID, or None if no unit has the given ID
    member inline game.GetUnitById(unitId) = Gm.GetUnitById(unitId) |> Unit.tryConvert
    
    /// Returns a pointer to a Unit given an index
    member inline game.IndexToUnit(unitIndex) = Gm.IndexToUnit(unitIndex)
    
    /// Returns the Region with the given ID, or NULL if no region has the given ID
    member inline game.Region(regionId) = Gm.Region(regionId)
    
    /// Returns the game type
    member inline game.GameType = Gm.GameType
    
    /// Returns the amount of latency the current game has. Currently only returns Latency::SinglePlayer, Latency::LanLow,
    /// Latency::LanMedium, or Latency::LanHigh
    member inline game.Latency = Gm.Latency
    
    /// Returns the number of logical frames since the match started. If the game is paused, Game::getFrameCount will not increase however
    /// AIModule::onFrame will still be called while paused. On Fastest, there are about 23.8 - 24 frames per second
    member inline game.FrameCount = Gm.FrameCount
    
    /// Returns the Frames Per Second (FPS) that the game is currently running at
    member inline game.Fps = Gm.Fps
    
    /// Returns the Frames Per Second (FPS) that the game is currently running at
    member inline game.AverageFps = Gm.AverageFps
    
    /// Returns the position of the mouse on the screen. Returns Positions::Unknown if Flag::UserInput is disabled
    member inline game.MousePosition = Gm.MousePosition
    
    /// Returns true if the specified mouse button is pressed. Returns false if Flag::UserInput is disabled
    member inline game.GetMouseState(button) = Gm.GetMouseState(button)
    
    /// Returns true if the specified key is pressed. Returns false if Flag::UserInput is disabled. Unfortunately this does not read the
    /// raw keyboard input yet - when you hold down a key, the getKeyState function is true for a frame, then false for a few frames, and
    /// then alternates between true and false (as if you were holding down the key in a text box). Hopefully this will be fixed in a later version
    member inline game.GetKeyState(key) = Gm.GetKeyState(key)
    
    /// Returns the position of the top left corner of the screen on the map. Returns Positions::Unknown if Flag::UserInput is disabled
    member inline game.ScreenPosition = Gm.ScreenPosition |> Position.apiToPixel
    
    /// Moves the screen to the given position on the map. The position specified where the top left corner of the screen will be
    member inline game.SetScreenPosition(Pos (x, y)) = Gm.SetScreenPosition(x * 1<1/pixel>, y * 1<1/pixel>)
    
    /// Pings the given position on the minimap
    member inline game.PingMinimap(Pos (x, y)) = Gm.PingMinimap(x * 1<1/pixel>, y * 1<1/pixel>)
    
    /// Returns true if the given flag has been enabled. Note that flags can only be enabled at the beginning of a match, during the AIModule::onStart callback
    member inline game.IsFlagEnabled(flag) = Gm.IsFlagEnabled(flag)
    
    /// Enables the specified flag. Note that flags can only be enabled at the beginning of a match, during the AIModule::onStart callback
    member inline game.EnableFlag(flag) = Gm.EnableFlag(flag)
    
    /// Returns the set of accessible units that are on the given build tile
    member inline game.GetUnitsOnTile(pos) = game.GetUnitsInRectangle (Position.tileToPixel pos, Position.tileToPixel (pos + Pos (1<tile>, 1<tile>)))
    
    /// Returns the set of accessible units that are in or overlapping the given rectangle
    member game.GetUnitsInRectangle(tileRect) = game.AllUnits |> Array.filter (fun unit -> tileRect |><| unit.Rectangle)
    
    /// Returns the set of accessible units within or overlapping a circle at the given point with the given radius
    member inline game.GetUnitsInRadius(pos, radius) = game.AllUnits |> Array.filter (fun unit -> (pos, pos) |~~| unit.Rectangle <= radius)
    
    /// Returns the last error that was set. If you try to order enemy units around, or morph bunkers into lurkers, BWAPI will set error codes,
    /// which can be retrieved using this function
    member inline game.LastError with get() = Gm.LastError and set(value) = Gm.LastError <- value
    
    /// Returns the file name of the current map
    member inline game.MapFileName = Gm.MapFileName
    
    /// Returns the full path name of the current map
    member inline game.MapPathName = Gm.MapPathName
    
    /// Returns the name/title of the current map
    member inline game.MapName = Gm.MapName
    
    /// Returns the SHA-1 hash of the map file
    member inline game.MapHash = Gm.MapHash
    
    /// Returns true if the specified walk tile is walkable. The values of x and y are in walk tile coordinates (different from build tile coordinates).
    /// Note that this just uses the static map data. You will also need to make sure no ground units are on the coresponding build tile to see if its
    /// currently walkable. To do this, see unitsOnTile
    member inline game.IsWalkable(Pos (x, y)) = Gm.IsWalkable(x * 1<1/walk>, y * 1<1/walk>)
    
    /// Returns the ground height of the given build tile. 0 = normal, 1 = high ground. 2 = very high ground
    member inline game.GetGroundHeight(Pos (x, y)) = Gm.GetGroundHeight(x * 1<1/tile>, y * 1<1/tile>)
    
    /// Returns true if the specified build tile is buildable. Note that this just uses the static map data. You will also need to make sure no ground units
    /// on the tile to see if its currently buildable. To do this, see unitsOnTile
    member inline game.IsBuildable(Pos (x, y), includeBuildings) = Gm.IsBuildable(x * 1<1/tile>, y * 1<1/tile>, includeBuildings)
    
    /// Returns true if the specified build tile is visible. If the tile is concealed by fog of war, the function will return false
    member inline game.IsVisible(Pos (x, y)) = Gm.IsVisible(x * 1<1/tile>, y * 1<1/tile>)
     
    /// Returns true if the specified build tile has been explored (i.e. was visible at some point in the match)
    member inline game.IsExplored(Pos (x, y)) = Gm.IsExplored(x * 1<1/tile>, y * 1<1/tile>)
     
    /// Returns true if the specified build tile has zerg creep on it. If the tile is concealed by fog of war, the function will return false
    member inline game.HasCreep(Pos (x, y)) = Gm.HasCreep(x * 1<1/tile>, y * 1<1/tile>)
     
    /// Returns true if the given build location is powered by a nearby friendly pylon
    member inline game.HasPower(Pos (x, y), unitType) = Gm.HasPower(x * 1<1/tile>, y * 1<1/tile>, unitType)
     
    /// Returns true if the given build location is powered by a nearby friendly pylon
    member inline game.HasPower(Pos (x, y), width, height, unitType) = Gm.HasPower(x * 1<1/tile>, y * 1<1/tile>, width * 1<1/tile>, height * 1<1/tile>, unitType)
     
    /// Returns true if the given pixel location is powered by a nearby friendly pylon
    member inline game.HasPowerPrecise(Pos (x, y), unitType) = Gm.HasPowerPrecise(x * 1<1/pixel>, y * 1<1/pixel>, unitType)
    
    /// Returns true if the given unit type can be built at the given build tile position. Note the tile position specifies the top left tile
    /// of the building. If builder is not null, the unit will be discarded when determining whether or not any ground units are blocking the build location
    member inline game.CanBuildHere(pos, unitType, builder, checkExplored) = Gm.CanBuildHere(Position.tileToApi pos, unitType, builder, checkExplored)
    
    /// Returns true if the AI player has enough resources, supply, tech, and required units in order to make the given unit type. If builder is not null,
    /// canMake will return true only if the builder unit can build the given unit type
    member inline game.CanMake(unitType, builder) = Gm.CanMake(unitType, builder)
    
    /// Returns true if the AI player has enough resources required to research the given tech type. If unit is not null, canResearch will return true
    /// only if the given unit can research the given tech type
    member inline game.CanResearch(techType, unit, checkCanIssueCommand) = Gm.CanResearch(techType, unit, checkCanIssueCommand)
    
    /// Returns true if the AI player has enough resources required to upgrade the given upgrade type. If unit is not null, canUpgrade will return true
    /// only if the given unit can upgrade the given upgrade type
    member inline game.CanUpgrade(upgradeType, unit, checkCanIssueCommand) = Gm.CanUpgrade(upgradeType, unit, checkCanIssueCommand)
    
    /// Returns the set of starting locations for the given map. To determine the starting location for the players in the current match,
    /// see Player::getStartLocation
    member inline game.StartLocations = Seq.map Position.apiToTile Gm.StartLocations |> Array.ofSeq
    
    /// Prints text on the screen. Text is not sent to other players in multiplayer games
    member inline game.Write format = Printf.ksprintf Gm.Write format
    
    /// Sends text to other players - as if it were entered in chat. In single player games and replays, this will just print the text on the screen.
    /// If the game is a single player match and not a replay, then this function can be used to execute cheat codes, i.e. Broodwar->sendText("show me the money")
    member inline game.SendText format = Printf.ksprintf Gm.SendText format
    
    /// Sends text to other players - as if it were entered in chat. In single player games and replays, this will just print the text on the screen.
    /// If the game is a single player match and not a replay, then this function can be used to execute cheat codes, i.e. Broodwar->sendText("show me the money")
    member inline game.SendText (toAllies:bool, format) = Printf.ksprintf (fun str -> Gm.SendText(toAllies, str)) format
    
    /// Returns true if Broodwar is in a game. Returns false for lobby and menu screens
    member inline game.IsInGame = Gm.IsInGame

    /// Returns true if Broodwar is in a multiplayer game. Returns false for single player games and replays
    member inline game.IsMultiplayer = Gm.IsMultiplayer
    
    /// Returns true if Broodwar is in a BNet multiplayer game
    member inline game.IsBattleNet = Gm.IsBattleNet
    
    /// Returns true if Broodwar is paused. If the game is paused, Game::getFrameCount will continue to increase and AIModule::onFrame will still
    /// be called while paused
    member inline game.IsPaused = Gm.IsPaused
    
    /// Returns true if Broodwar is in a replay
    member inline game.IsReplay = Gm.IsReplay
    
    /// Pauses the game. If the game is paused, Game::getFrameCount will not increase however AIModule::onFrame will still be called while paused
    member inline game.PauseGame() = Gm.PauseGame()
    
    /// Resumes the game
    member inline game.ResumeGame() = Gm.ResumeGame()
    
    /// Leaves the current match and goes to the after-game stats screen
    member inline game.LeaveGame() = Gm.LeaveGame()
    
    /// Restarts the match. Works the same way as if you restarted the match from the menu screen. Only available in single player mode
    member inline game.RestartGame() = Gm.RestartGame()
    
    /// Sets the speed of the game to the given number. Lower numbers are faster. 0 is the fastest speed StarCraft can handle (which is about as
    /// fast as the fastest speed you can view a replay at). Any negative value will reset the speed to the StarCraft default
    member inline game.SetLocalSpeed(speed) = Gm.SetLocalSpeed(speed)
    
    /// Issues a command to a group of units
    member inline game.IssueCommand(units, command) = Gm.IssueCommand(units, command)
    
    /// Returns the set of units currently selected by the user in the GUI. If Flag?::UserInput? was not enabled during the AIModule::onStart callback,
    /// this function will always return an empty set
    member inline game.GetSelectedUnits = Gm.GetSelectedUnits
    
    /// Returns a pointer to the player that BWAPI controls. In replays this will return null
    member inline game.Self = Gm.Self
    
    /// Returns a pointer to the enemy player. If there is more than one enemy, this returns a pointer to just one enemy (see enemies to get all enemies
    /// still in game). In replays this will return NULL
    member inline game.Enemy = Gm.Enemy
    
    /// Returns a pointer to the neutral player
    member inline game.Neutral = Gm.Neutral
    
    /// Returns a set of all the ally players that have not left or been defeated. Does not include self
    member inline game.Allies = Gm.Allies
    
    /// Returns a set of all the enemy players that have not left or been defeated
    member inline game.Enemies = Gm.Enemies
    
    /// Returns a set of all the observer players that have not left
    member inline game.Observers = Gm.Observers
    
    //member inline game.SetTextSize(size) = Gm.SetTextSize(size)
    
    /// Draws text on the screen at the given position. Text can be drawn in different colors by using the following control characters: \1 through \31
    /// Related: http://bwapi.googlecode.com/svn/wiki/colorPalette.gif
    member inline game.DrawText (Pos (x, y)) format = Printf.ksprintf (fun str -> Gm.DrawTextMap(x * 1<1/pixel>, y * 1<1/pixel>, str)) format

    member inline game.DrawTextCType (ctype, Pos (x, y)) format = Printf.ksprintf (fun str -> Gm.DrawTextCType(ctype, x * 1<1/pixel>, y * 1<1/pixel>, str)) format
    
    member inline game.DrawTextMouse (Pos (x, y)) format = Printf.ksprintf (fun str -> Gm.DrawTextMouse(x * 1<1/pixel>, y * 1<1/pixel>, str)) format
    
    member inline game.DrawTextScreen (Pos (x, y)) format = Printf.ksprintf (fun str -> Gm.DrawTextScreen(x * 1<1/pixel>, y * 1<1/pixel>, str)) format
    
    /// Draws a box on the screen, with the given color. If isSolid is true, the entire box will be rendered, otherwise just the outline will be drawn
    member inline game.DrawBox(Pos (left, top), Pos (right, bottom), color, isSolid) = Gm.DrawBoxMap(left * 1<1/pixel>, top * 1<1/pixel>, right * 1<1/pixel>, bottom * 1<1/pixel>, color, isSolid)

    member inline game.DrawBoxCType(ctype, Pos (left, top), Pos (right, bottom), color, isSolid) = Gm.DrawBoxCType(ctype, left * 1<1/pixel>, top * 1<1/pixel>, right * 1<1/pixel>, bottom * 1<1/pixel>, color, isSolid)
    
    member inline game.DrawBoxMouse(Pos (left, top), Pos (right, bottom), color, isSolid) = Gm.DrawBoxMouse(left * 1<1/pixel>, top * 1<1/pixel>, right * 1<1/pixel>, bottom * 1<1/pixel>, color, isSolid)
    
    member inline game.DrawBoxScreen(Pos (left, top), Pos (right, bottom), color, isSolid) = Gm.DrawBoxScreen(left * 1<1/pixel>, top * 1<1/pixel>, right * 1<1/pixel>, bottom * 1<1/pixel>, color, isSolid)
    
    /// Draws a triangle on the screen. If isSolid is true, a solid triangle is drawn, otherwise just the outline of the triangle will be drawn
    member inline game.DrawTriangle(Pos (ax, ay), Pos (bx, by), Pos (cx, cy), color, isSolid) = Gm.DrawTriangleMap(ax * 1<1/pixel>, ay * 1<1/pixel>, bx * 1<1/pixel>, by * 1<1/pixel>, cx * 1<1/pixel>, cy * 1<1/pixel>, color, isSolid)

    member inline game.DrawTriangleCType(ctype, Pos (ax, ay), Pos (bx, by), Pos (cx, cy), color, isSolid) = Gm.DrawTriangleCType(ctype, ax * 1<1/pixel>, ay * 1<1/pixel>, bx * 1<1/pixel>, by * 1<1/pixel>, cx * 1<1/pixel>, cy * 1<1/pixel>, color, isSolid)
    
    member inline game.DrawTriangleMouse(Pos (ax, ay), Pos (bx, by), Pos (cx, cy), color, isSolid) = Gm.DrawTriangleMouse(ax * 1<1/pixel>, ay * 1<1/pixel>, bx * 1<1/pixel>, by * 1<1/pixel>, cx * 1<1/pixel>, cy * 1<1/pixel>, color, isSolid)
    
    member inline game.DrawTriangleScreen(Pos (ax, ay), Pos (bx, by), Pos (cx, cy), color, isSolid) = Gm.DrawTriangleScreen(ax * 1<1/pixel>, ay * 1<1/pixel>, bx * 1<1/pixel>, by * 1<1/pixel>, cx * 1<1/pixel>, cy * 1<1/pixel>, color, isSolid)
    
    /// Draws a circle on the screen, with the given color. If isSolid is true, a solid circle is drawn, otherwise just the outline of a circle will be drawn
    member inline game.DrawCircle(Pos (x, y), radius, color, isSolid) = Gm.DrawCircleMap(x * 1<1/pixel>, y * 1<1/pixel>, radius * 1<1/pixel>, color, isSolid)

    member inline game.DrawCircleCType(ctype, x, y, radius, color, isSolid) = Gm.DrawCircleCType(ctype, x * 1<1/pixel>, y * 1<1/pixel>, radius * 1<1/pixel>, color, isSolid)
    
    member inline game.DrawCircleMouse(Pos (x, y), radius, color, isSolid) = Gm.DrawCircleMouse(x * 1<1/pixel>, y * 1<1/pixel>, radius * 1<1/pixel>, color, isSolid)
    
    member inline game.DrawCircleScreen(Pos (x, y), radius, color, isSolid) = Gm.DrawCircleScreen(x * 1<1/pixel>, y * 1<1/pixel>, radius * 1<1/pixel>, color, isSolid)
    
    /// Draws an ellipse on the screen, with the given color. If isSolid is true, a solid ellipse is drawn, otherwise just the outline of an ellipse will be drawn
    member inline game.DrawEllipse(Pos (x, y), xrad, yrad, color, isSolid) = Gm.DrawEllipseMap(x * 1<1/pixel>, y * 1<1/pixel>, xrad * 1<1/pixel>, yrad * 1<1/pixel>, color, isSolid)

    member inline game.DrawEllipseCType(ctype, Pos (x, y), xrad, yrad, color, isSolid) = Gm.DrawEllipseCType(ctype, x * 1<1/pixel>, y * 1<1/pixel>, xrad * 1<1/pixel>, yrad * 1<1/pixel>, color, isSolid)
    
    member inline game.DrawEllipseMouse(Pos (x, y), xrad, yrad, color, isSolid) = Gm.DrawEllipseMouse(x * 1<1/pixel>, y * 1<1/pixel>, xrad * 1<1/pixel>, yrad * 1<1/pixel>, color, isSolid)
    
    member inline game.DrawEllipseScreen(Pos (x, y), xrad, yrad, color, isSolid) = Gm.DrawEllipseScreen(x * 1<1/pixel>, y * 1<1/pixel>, xrad * 1<1/pixel>, yrad * 1<1/pixel>, color, isSolid)
    
    /// Draws a dot on the screen at the given position with the given color
    member inline game.DrawDot(Pos (x, y), color) = Gm.DrawDotMap(x * 1<1/pixel>, y * 1<1/pixel>, color)

    member inline game.DrawDotCType(ctype, x, y, color) = Gm.DrawDotCType(ctype, x * 1<1/pixel>, y * 1<1/pixel>, color)
    
    member inline game.DrawDotMouse(Pos (x, y), color) = Gm.DrawDotMouse(x * 1<1/pixel>, y * 1<1/pixel>, color)
    
    member inline game.DrawDotScreen(Pos (x, y), color) = Gm.DrawDotScreen(x * 1<1/pixel>, y * 1<1/pixel>, color)
    
    /// Draws a line on the screen from a to b with the given color
    member inline game.DrawLine(Pos (x1, y1), Pos (x2, y2), color) = Gm.DrawLineMap(x1 * 1<1/pixel>, y1 * 1<1/pixel>, x2 * 1<1/pixel>, y2 * 1<1/pixel>, color)

    member inline game.DrawLineCType(ctype, Pos (x1, y1), Pos (x2, y2), color) = Gm.DrawLineCType(ctype, x1 * 1<1/pixel>, y1 * 1<1/pixel>, x2 * 1<1/pixel>, y2 * 1<1/pixel>, color)
    
    member inline game.DrawLineMouse(Pos (x1, y1), Pos (x2, y2), color) = Gm.DrawLineMouse(x1 * 1<1/pixel>, y1 * 1<1/pixel>, x2 * 1<1/pixel>, y2 * 1<1/pixel>, color)
    
    member inline game.DrawLineScreen(Pos (x1, y1), Pos (x2, y2), color) = Gm.DrawLineScreen(x1 * 1<1/pixel>, y1 * 1<1/pixel>, x2 * 1<1/pixel>, y2 * 1<1/pixel>, color)
    
    /// Retrieves latency values for the game. Includes latency, speed, and mode
    member inline game.LatencyFrames = Gm.LatencyFrames
    
    member inline game.LatencyTime = Gm.LatencyTime
    
    member inline game.RemainingLatencyFrames = Gm.RemainingLatencyFrames
    
    member inline game.RemainingLatencyTime = Gm.RemainingLatencyTime
    
    /// Retrieves the current revision of BWAPI
    member inline game.Revision = Gm.Revision
    
    /// Retrieves the debug state of the BWAPI build
    member inline game.IsDebug = Gm.IsDebug
    
    /// Returns true if latency compensation is enabled
    member inline game.IsLatComEnabled = Gm.IsLatComEnabled
    
    /// Use to enable or disable latency compensation. Default: Enabled
    member inline game.SetLatCom(isEnabled) = Gm.SetLatCom(isEnabled)
    
    /// Retrieves the number of frames in the replay
    member inline game.ReplayFrameCount = Gm.ReplayFrameCount
    
    /// Sets the rendering state of the Starcraft GUI
    member inline game.SetGui(isEnabled) = Gm.SetGui(isEnabled)
    
    /// Retrieves the instance number recorded by BWAPI to identify which instance an AI module belongs to
    member inline game.InstanceNumber = Gm.InstanceNumber
    
    /// Retrieves the bot's APM. Can include or exclude select commands
    member inline game.GetApm(includeSelects) = Gm.GetApm(includeSelects)
    
    /// Changes the map to the one specified. Changes do not take effect unless the game is restarted
    member inline game.SetMap(mapFileName) = Gm.SetMap(mapFileName)
    
    /// Sets the frame skip value. 1 = normal
    member inline game.SetFrameSkip(frameSkip) = Gm.SetFrameSkip(frameSkip)
    
    /// Returns true if Starcraft can find a path from the start to the finish
    member inline game.HasPath(start, finish) = Gm.HasPath(Position.pixelToApi start, Position.pixelToApi finish)
    
    /// Sets the BWAPI player's alliance with another player
    member inline game.SetAlliance(player, allied, alliedVictory) = Gm.SetAlliance(player, allied, alliedVictory)
    
    /// Sets the BWAPI player's vision with another player
    member inline game.SetVision(player, isEnabled) = Gm.SetVision(player, isEnabled)
    
    /// Returns the elapsed game time in seconds
    member inline game.ElapsedTime = Gm.ElapsedTime
    
    /// Sets the level of command optimizations.
    /// 0 = No optimization.
    /// 1 = Some optimization    (Stop, Hold Position, Siege, Burrow, etc.).
    /// 2 = More optimization    (Train, Set Rally, Lift, [multi-select buildings]).
    /// 3 = Maximum optimization (Attack/Move to position, use ability at position, etc.)
    member inline game.SetCommandOptimizationLevel(level) = Gm.SetCommandOptimizationLevel(level)
    
    /// Returns the remaining countdown time in seconds
    member inline game.CountdownTimer = Gm.CountdownTimer
    
    /// Returns the set of all map regions
    member inline game.AllRegions = Gm.AllRegions
    
    /// Returns the region at a position
    member inline game.GetRegionAt(Pos (x, y)) = Gm.GetRegionAt(x * 1<1/pixel>, y * 1<1/pixel>)
    
    /// Returns the time taken to perform the previous event call. Used for tournament management
    member inline game.LastEventTime = Gm.LastEventTime
    
    /// Enables or disables the Fog of War in a replay
    member inline game.SetRevealAll(reveal) = Gm.SetRevealAll(reveal)

    /// Gets a build location for a unit type near a position within a range, on or off creep
    member inline game.GetBuildLocation(unitType, desired, maxRange, onCreep) = Position.apiToTile <| Gm.GetBuildLocation(unitType, Position.tileToApi desired, maxRange * 1<1/tile>, onCreep)

    /// Gets the damage from a unit to another (usually yours)
    member inline game.GetDamageFrom(fromType, toType, fromPlayer, toPlayer) = Gm.GetDamageFrom(fromType, toType, fromPlayer, toPlayer)

    /// Gets the damage to a unit from another (usually yours)
    member inline game.GetDamageTo(toType, fromType, toPlayer, fromPlayer) = Gm.GetDamageTo(toType, fromType, toPlayer, fromPlayer)
