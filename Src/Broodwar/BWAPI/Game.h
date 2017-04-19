#pragma once
#pragma unmanaged

#include <BWAPI\Game.h>
#pragma make_public(BWAPI::Game)

#pragma managed

//#include "Error.h"
#include "Event.h"
#include "Enum\Flag.h"
#include "Enum\GameType.h"
#include "Race.h"
#include "Region.h"
#include "Enum\OrderType.h"
#include "Enum\Latency.h"
#include "Position.h"
#include "UnitType.h"
#include "Tech.h"
#include "Upgrade.h"
#include "Enum\MouseButton.h"
#include "Enum\Key.h"
#include "Enum\ErrorType.h"
#include "UnitCommand.h"
#include "Enum\CoordinateType.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;

namespace BroodWar
{
    namespace Api
    {
        ref class Force;
        ref class Player;
        ref class Unit;
        ref class Bullet;

        /// <summary>
        /// The abstract Game class is implemented by BWAPI and offers many methods for retrieving information about the current Broodwar game,
        /// including the set of players, units, map information, as well as information about the user, such as mouse position, screen position,
        /// and the current selection of units
        /// </summary>
        public ref class Game abstract sealed
        {
        private:
            static BWAPI::Game* instance;
            
        internal:
            static Game();
            
            static void Rebind();
        public:
            /// <summary>
            /// Returns the set of all forces in the match
            /// </summary>
            static property HashSet<Force^>^ Forces { HashSet<Force^>^ get(); }
            
            /// <summary>
            /// Returns the set of all players in the match. Note that this includes the Neutral player, which owns all the neutral units such as
            /// minerals, critters, etc
            /// </summary>
            static property HashSet<Player^>^ Players { HashSet<Player^>^ get(); }
            
            /// <summary>
            /// Returns all the visible units. If Flag::CompleteMapInformation is enabled, the set of all units is returned, not just visible ones.
            /// Note that units inside refineries are not included in this set yet
            /// </summary>
            static property HashSet<Unit^>^ AllUnits { HashSet<Unit^>^ get(); }
            
            /// <summary>
            /// Returns the set of all accessible mineral patches
            /// </summary>
            static property HashSet<Unit^>^ Minerals { HashSet<Unit^>^ get(); }
            
            /// <summary>
            /// Returns the set of all accessible vespene geysers
            /// </summary>
            static property HashSet<Unit^>^ Geysers { HashSet<Unit^>^ get(); }
            
            /// <summary>
            /// Returns the set of all accessible neutral units
            /// </summary>
            static property HashSet<Unit^>^ NeutralUnits { HashSet<Unit^>^ get(); }
            
            /// <summary>
            /// Returns the set of all mineral patches (including mined out and other inaccessible ones)
            /// </summary>
            static property HashSet<Unit^>^ StaticMinerals { HashSet<Unit^>^ get(); }
            
            /// <summary>
            /// Returns the set of all vespene geysers (including mined out and other inaccessible ones)
            /// </summary>
            static property HashSet<Unit^>^ StaticGeysers { HashSet<Unit^>^ get(); }
            
            /// <summary>
            /// Returns the set of all neutral units (including mined out and other inaccessible ones)
            /// </summary>
            static property HashSet<Unit^>^ StaticNeutralUnits { HashSet<Unit^>^ get(); }
            
            /// <summary>
            /// Returns all visible bullets. If Flag::CompleteMapInformation is enabled, the set of all bullets is returned, not just visible ones
            /// </summary>
            static property HashSet<Bullet^>^ Bullets { HashSet<Bullet^>^ get(); }
            
            /// <summary>
            /// Returns all visible nuke dots. If Flag::CompleteMapInformation is enabled, the set of all nuke dots is returned, not just visible ones
            /// </summary>
            static property List<Position^>^ NukeDots { List<Position^>^ get(); }
            
            /// <summary>
            /// Returns the list of events
            /// </summary>
            static property List<Event^>^ Events { List<Event^>^ get(); }
            
            /// <summary>
            /// Returns the force with the given ID, or NULL if no force has the given ID
            /// </summary>
            static Force^ GetForceById(int forceId);
            
            /// <summary>
            /// Returns the player with the given ID, or NULL if no player has the given ID
            /// </summary>
            static Player^ GetPlayerById(int playerId);
            
            /// <summary>
            /// Returns the unit with the given ID, or NULL if no unit has the given ID
            /// </summary>
            static Unit^ GetUnitById(int unitId);
            
            /// <summary>
            /// Returns a pointer to a Unit given an index
            /// </summary>
            static Unit^ IndexToUnit(int unitIndex);
            
            /// <summary>
            /// Returns the Region with the given ID, or NULL if no region has the given ID
            /// </summary>
            static Region^ Region(int regionId);
            
            /// <summary>
            /// Returns the game type
            /// </summary>
            static property Api::Enum::GameType GameType { Api::Enum::GameType get(); }
            
            /// <summary>
            /// Returns the amount of latency the current game has. Currently only returns Latency::SinglePlayer, Latency::LanLow,
            /// Latency::LanMedium, or Latency::LanHigh
            /// </summary>
            static property int Latency { int get(); }
            
            /// <summary>
            /// Returns the number of logical frames since the match started. If the game is paused, Game::getFrameCount will not increase however
            /// AIModule::onFrame will still be called while paused. On Fastest, there are about 23.8 - 24 frames per second
            /// </summary>
            static property int FrameCount { int get(); }
            
            /// <summary>
            /// Returns the Frames Per Second (FPS) that the game is currently running at
            /// </summary>
            static property int Fps { int get(); }
            
            /// <summary>
            /// Returns the Frames Per Second (FPS) that the game is currently running at
            /// </summary>
            static property double AverageFps { double get(); }
            
            /// <summary>
            /// Returns the position of the mouse on the screen. Returns Positions::Unknown if Flag::UserInput is disabled
            /// </summary>
            static property Position^ MousePosition { Position^ get(); }
            
            /// <summary>
            /// Returns true if the specified mouse button is pressed. Returns false if Flag::UserInput is disabled
            /// </summary>
            static bool GetMouseState(MouseButton button);
            
            /// <summary>
            /// Returns true if the specified key is pressed. Returns false if Flag::UserInput is disabled. Unfortunately this does not read the
            /// raw keyboard input yet - when you hold down a key, the getKeyState function is true for a frame, then false for a few frames, and
            /// then alternates between true and false (as if you were holding down the key in a text box). Hopefully this will be fixed in a later version
            /// </summary>
            static bool GetKeyState(Key key);
            
            /// <summary>
            /// Returns the position of the top left corner of the screen on the map. Returns Positions::Unknown if Flag::UserInput is disabled
            /// </summary>
            static property Position^ ScreenPosition { Position^ get(); }
            
            /// <summary>
            /// Moves the screen to the given position on the map. The position specified where the top left corner of the screen will be
            /// </summary>
            static void SetScreenPosition(int x, int y);
            
            /// <summary>
            /// Moves the screen to the given position on the map. The position specified where the top left corner of the screen will be
            /// </summary>
            static void SetScreenPosition(Position^ p);
             
            /// <summary>
            /// Pings the given position on the minimap
            /// </summary>
            static void PingMinimap(int x, int y);
            
            /// <summary>
            /// Pings the given position on the minimap
            /// </summary>
            static void PingMinimap(Position^ p);
            
            /// <summary>
            /// Returns true if the given flag has been enabled. Note that flags can only be enabled at the beginning of a match, during the AIModule::onStart callback
            /// </summary>
            static bool IsFlagEnabled(Flag flag);
            
            /// <summary>
            /// Enables the specified flag. Note that flags can only be enabled at the beginning of a match, during the AIModule::onStart callback
            /// </summary>
            static void EnableFlag(Flag flag);
            
            /// <summary>
            /// Returns the set of accessible units that are on the given build tile
            /// </summary>
            static HashSet<Unit^>^ GetUnitsOnTile(int tileX, int tileY);

            /// <summary>
            /// Returns the set of accessible units that are on the given build tile
            /// </summary>
            static HashSet<Unit^>^ GetUnitsOnTile(TilePosition^ p);
            
            /// <summary>
            /// Returns the set of accessible units that are in or overlapping the given rectangle
            /// </summary>
            static HashSet<Unit^>^ GetUnitsInRectangle(int left, int top, int right, int bottom);
            
            /// <summary>
            /// Returns the set of accessible units that are in or overlapping the given rectangle
            /// </summary>
            static HashSet<Unit^>^ GetUnitsInRectangle(Position^ topLeft, Position^ bottomRight);

            /// <summary>
            /// Returns the set of accessible units within or overlapping a circle at the given point with the given radius
            /// </summary>
            static HashSet<Unit^>^ GetUnitsInRadius(int x, int y, int radius);

            /// <summary>
            /// Returns the set of accessible units within or overlapping a circle at the given point with the given radius
            /// </summary>
            static HashSet<Unit^>^ GetUnitsInRadius(Position^ center, int radius);
            
            /// <summary>
            /// Returns the last error that was set. If you try to order enemy units around, or morph bunkers into lurkers, BWAPI will set error codes,
            /// which can be retrieved using this function
            /// </summary>
            static property Api::Enum::ErrorType LastError { Api::Enum::ErrorType get(); void set(Api::Enum::ErrorType type); }
            
            /// <summary>
            /// Returns the width of the current map, in build tile units. To get the width of the current map in walk tile units, multiply by 4.
            /// To get the width of the current map in Position units, multiply by TILE_SIZE (which is 32)
            /// </summary>
            static property int MapWidth { int get(); }
            
            /// <summary>
            /// Returns the height of the current map, in build tile units. To get the height of the current map in walk tile units, multiply by 4.
            /// To get the height of the current map in Position units, multiply by TILE_SIZE (which is 32)
            /// </summary>
            static property int MapHeight { int get(); }
            
            /// <summary>
            /// Returns the file name of the current map
            /// </summary>
            static property String^ MapFileName { String^ get(); }
            
            /// <summary>
            /// Returns the full path name of the current map
            /// </summary>
            static property String^ MapPathName { String^ get(); }
            
            /// <summary>
            /// Returns the name/title of the current map
            /// </summary>
            static property String^ MapName { String^ get(); }
            
            /// <summary>
            /// Returns the SHA-1 hash of the map file
            /// </summary>
            static property String^ MapHash { String^ get(); }
            
            /// <summary>
            /// Returns true if the specified walk tile is walkable. The values of x and y are in walk tile coordinates (different from build tile coordinates).
            /// Note that this just uses the static map data. You will also need to make sure no ground units are on the coresponding build tile to see if its
            /// currently walkable. To do this, see unitsOnTile
            /// </summary>
            static bool IsWalkable(int walkX, int walkY);

            /// <summary>
            /// Returns true if the specified walk tile is walkable. The values of x and y are in walk tile coordinates (different from build tile coordinates).
            /// Note that this just uses the static map data. You will also need to make sure no ground units are on the coresponding build tile to see if its
            /// currently walkable. To do this, see unitsOnTile
            /// </summary>
            static bool IsWalkable(WalkPosition^ p);
            
            /// <summary>
            /// Returns the ground height of the given build tile. 0 = normal, 1 = high ground. 2 = very high ground
            /// </summary>
            static int GetGroundHeight(int tileX, int tileY);

            /// <summary>
            /// Returns the ground height of the given build tile. 0 = normal, 1 = high ground. 2 = very high ground
            /// </summary>
            static int GetGroundHeight(TilePosition^ position);
            
            /// <summary>
            /// Returns true if the specified build tile is buildable. Note that this just uses the static map data. You will also need to make sure no ground units
            /// on the tile to see if its currently buildable. To do this, see unitsOnTile
            /// </summary>
            static bool IsBuildable(int tileX, int tileY, bool includeBuildings);
            
            /// <summary>
            /// Returns true if the specified build tile is buildable. Note that this just uses the static map data. You will also need to make sure no ground units
            /// on the tile to see if its currently buildable. To do this, see unitsOnTile
            /// </summary>
            static bool IsBuildable(TilePosition^ position, bool includeBuildings);
            
            /// <summary>
            /// Returns true if the specified build tile is visible. If the tile is concealed by fog of war, the function will return false
            /// </summary>
            static bool IsVisible(int tileX, int tileY);
            
            /// <summary>
            /// Returns true if the specified build tile is visible. If the tile is concealed by fog of war, the function will return false
            /// </summary>
            static bool IsVisible(TilePosition^ position);
             
            /// <summary>
            /// Returns true if the specified build tile has been explored (i.e. was visible at some point in the match)
            /// </summary>
            static bool IsExplored(int tileX, int tileY);
            
            /// <summary>
            /// Returns true if the specified build tile has been explored (i.e. was visible at some point in the match)
            /// </summary>
            static bool IsExplored(TilePosition^ position);
             
            /// <summary>
            /// Returns true if the specified build tile has zerg creep on it. If the tile is concealed by fog of war, the function will return false
            /// </summary>
            static bool HasCreep(int tileX, int tileY);
            
            /// <summary>
            /// Returns true if the specified build tile has zerg creep on it. If the tile is concealed by fog of war, the function will return false
            /// </summary>
            static bool HasCreep(TilePosition^ position);
             
            /// <summary>
            /// Returns true if the given build location is powered by a nearby friendly pylon
            /// </summary>
            static bool HasPower(int tileX, int tileY, Api::Enum::UnitType unitType);
            
            /// <summary>
            /// Returns true if the given build location is powered by a nearby friendly pylon
            /// </summary>
             static bool HasPower(TilePosition^ position, Api::Enum::UnitType unitType);
             
            /// <summary>
            /// Returns true if the given build location is powered by a nearby friendly pylon
            /// </summary>
            static bool HasPower(int tileX, int tileY, int tileWidth, int tileHeight, Api::Enum::UnitType unitType);
            
            /// <summary>
            /// Returns true if the given build location is powered by a nearby friendly pylon
            /// </summary>
            static bool HasPower(TilePosition^ position, int tileWidth, int tileHeight, Api::Enum::UnitType unitType);
             
            /// <summary>
            /// Returns true if the given pixel location is powered by a nearby friendly pylon
            /// </summary>
            static bool HasPowerPrecise(int x, int y, Api::Enum::UnitType unitType);
            
            /// <summary>
            /// Returns true if the given pixel location is powered by a nearby friendly pylon
            /// </summary>
            static bool HasPowerPrecise(Position^ position, Api::Enum::UnitType unitType);
            
            /// <summary>
            /// Returns true if the given unit type can be built at the given build tile position. Note the tile position specifies the top left tile
            /// of the building. If builder is not null, the unit will be discarded when determining whether or not any ground units are blocking the build location
            /// </summary>
            static bool CanBuildHere(TilePosition^ position, Api::Enum::UnitType type, Unit^ builder, bool checkExplored);
            
            /// <summary>
            /// Returns true if the AI player has enough resources, supply, tech, and required units in order to make the given unit type. If builder is not null,
            /// canMake will return true only if the builder unit can build the given unit type
            /// </summary>
            static bool CanMake(Api::Enum::UnitType type, Unit^ builder);
            
            /// <summary>
            /// Returns true if the AI player has enough resources required to research the given tech type. If unit is not null, canResearch will return true
            /// only if the given unit can research the given tech type
            /// </summary>
            static bool CanResearch(Api::Enum::TechType type, Unit^ unit, bool checkCanIssueCommand);
            
            /// <summary>
            /// Returns true if the AI player has enough resources required to upgrade the given upgrade type. If unit is not null, canUpgrade will return true
            /// only if the given unit can upgrade the given upgrade type
            /// </summary>
            static bool CanUpgrade(Api::Enum::UpgradeType type, Unit^ unit, bool checkCanIssueCommand);
            
            /// <summary>
            /// Returns the set of starting locations for the given map. To determine the starting location for the players in the current match,
            /// see Player::getStartLocation
            /// </summary>
            static property List<TilePosition^>^ StartLocations { List<TilePosition^>^ get(); }
            
            /// <summary>
            /// Prints text on the screen. Text is not sent to other players in multiplayer games
            /// </summary>
            static void Write(String^ format, ... cli::array<Object^>^ args);
            
            /// <summary>
            /// Sends text to other players - as if it were entered in chat. In single player games and replays, this will just print the text on the screen.
            /// If the game is a single player match and not a replay, then this function can be used to execute cheat codes, i.e. Broodwar->sendText("show me the money")
            /// </summary>
            static void SendText(String^ format, ... cli::array<Object^>^ args);
            
            /// <summary>
            /// Sends text to other players - as if it were entered in chat. In single player games and replays, this will just print the text on the screen.
            /// If the game is a single player match and not a replay, then this function can be used to execute cheat codes, i.e. Broodwar->sendText("show me the money")
            /// </summary>
            static void SendText(bool toAllies, String^ format, ... cli::array<Object^>^ args);
            
            /// <summary>
            /// Returns true if Broodwar is in a game. Returns false for lobby and menu screens
            /// </summary>
            static property bool IsInGame { bool get(); }

            /// <summary>
            /// Returns true if Broodwar is in a multiplayer game. Returns false for single player games and replays
            /// </summary>
            static property bool IsMultiplayer { bool get(); }
            
            /// <summary>
            /// Returns true if Broodwar is in a BNet multiplayer game
            /// </summary>
            static property bool IsBattleNet { bool get(); }
            
            /// <summary>
            /// Returns true if Broodwar is paused. If the game is paused, Game::getFrameCount will continue to increase and AIModule::onFrame will still
            /// be called while paused
            /// </summary>
            static property bool IsPaused { bool get(); }
            
            /// <summary>
            /// Returns true if Broodwar is in a replay
            /// </summary>
            static property bool IsReplay { bool get(); }
            
            /// <summary>
            /// Pauses the game. If the game is paused, Game::getFrameCount will not increase however AIModule::onFrame will still be called while paused
            /// </summary>
            static void PauseGame();
            
            /// <summary>
            /// Resumes the game
            /// </summary>
            static void ResumeGame();
            
            /// <summary>
            /// Leaves the current match and goes to the after-game stats screen
            /// </summary>
            static void LeaveGame();
            
            /// <summary>
            /// Restarts the match. Works the same way as if you restarted the match from the menu screen. Only available in single player mode
            /// </summary>
            static void RestartGame();
            
            /// <summary>
            /// Sets the speed of the game to the given number. Lower numbers are faster. 0 is the fastest speed StarCraft can handle (which is about as
            /// fast as the fastest speed you can view a replay at). Any negative value will reset the speed to the StarCraft default
            /// </summary>
            static void SetLocalSpeed(int speed);
            
            /// <summary>
            /// Issues a command to a group of units
            /// </summary>
            static bool IssueCommand(List<Unit^>^ units, UnitCommand^ command);
            
            /// <summary>
            /// Returns the set of units currently selected by the user in the GUI. If Flag?::UserInput? was not enabled during the AIModule::onStart callback,
            /// this function will always return an empty set
            /// </summary>
            static property HashSet<Unit^>^ GetSelectedUnits { HashSet<Unit^>^ get(); }
            
            /// <summary>
            /// Returns a pointer to the player that BWAPI controls. In replays this will return null
            /// </summary>
            static property Player^ Self { Player^ get(); }
            
            /// <summary>
            /// Returns a pointer to the enemy player. If there is more than one enemy, this returns a pointer to just one enemy (see enemies to get all enemies
            /// still in game). In replays this will return NULL
            /// </summary>
            static property Player^ Enemy { Player^ get(); }
            
            /// <summary>
            /// Returns a pointer to the neutral player
            /// </summary>
            static property Player^ Neutral { Player^ get(); }
            
            /// <summary>
            /// Returns a set of all the ally players that have not left or been defeated. Does not include self
            /// </summary>
            static property HashSet<Player^>^ Allies { HashSet<Player^>^ get(); }
            
            /// <summary>
            /// Returns a set of all the enemy players that have not left or been defeated
            /// </summary>
            static property HashSet<Player^>^ Enemies { HashSet<Player^>^ get(); }
            
            /// <summary>
            /// Returns a set of all the observer players that have not left
            /// </summary>
            static property HashSet<Player^>^ Observers { HashSet<Player^>^ get(); }
            
            //static void SetTextSize(int size);
            
            /// <summary>
            /// Draws text on the screen at the given position. Text can be drawn in different colors by using the following control characters: TODO: add image from wiki
            /// </summary>
            static void DrawText(Position^ p, String^ format, ... cli::array<Object^>^ args);

            static void DrawTextCType(Api::Enum::CoordinateType ctype, int x, int y, String^ format, ... cli::array<Object^>^ args);
            
            static void DrawTextMap(int x, int y, String^ format, ... cli::array<Object^>^ args);
            
            static void DrawTextMouse(int x, int y, String^ format, ... cli::array<Object^>^ args);
            
            static void DrawTextScreen(int x, int y, String^ format, ... cli::array<Object^>^ args);
            
            /// <summary>
            /// Draws a box on the screen, with the given color. If isSolid is true, the entire box will be rendered, otherwise just the outline will be drawn
            /// </summary>
            static void DrawBox(Position^ topLeft, Position^ bottomRight, Color color, bool isSolid);

            static void DrawBoxCType(Api::Enum::CoordinateType ctype, int left, int top, int right, int bottom, Color color, bool isSolid);
            
            static void DrawBoxMap(int left, int top, int right, int bottom, Color color, bool isSolid);
            
            static void DrawBoxMouse(int left, int top, int right, int bottom, Color color, bool isSolid);
            
            static void DrawBoxScreen(int left, int top, int right, int bottom, Color color, bool isSolid);
            
            /// <summary>
            /// Draws a triangle on the screen. If isSolid is true, a solid triangle is drawn, otherwise just the outline of the triangle will be drawn
            /// </summary>
            static void DrawTriangle(Position^ a, Position^ b, Position^ c, Color color, bool isSolid);

            static void DrawTriangleCType(Api::Enum::CoordinateType ctype, int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid);
            
            static void DrawTriangleMap(int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid);
            
            static void DrawTriangleMouse(int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid);
            
            static void DrawTriangleScreen(int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid);
            
            /// <summary>
            /// Draws a circle on the screen, with the given color. If isSolid is true, a solid circle is drawn, otherwise just the outline of a circle will be drawn
            /// </summary>
            static void DrawCircle(Position^ center, int radius, Color color, bool isSolid);

            static void DrawCircleCType(Api::Enum::CoordinateType ctype, int x, int y, int radius, Color color, bool isSolid);
            
            static void DrawCircleMap(int x, int y, int radius, Color color, bool isSolid);
            
            static void DrawCircleMouse(int x, int y, int radius, Color color, bool isSolid);
            
            static void DrawCircleScreen(int x, int y, int radius, Color color, bool isSolid);
            
            /// <summary>
            /// Draws an ellipse on the screen, with the given color. If isSolid is true, a solid ellipse is drawn, otherwise just the outline of an ellipse will be drawn
            /// </summary>
            static void DrawEllipse(Position^ center, int xrad, int yrad, Color color, bool isSolid);

            static void DrawEllipseCType(Api::Enum::CoordinateType ctype, int x, int y, int xrad, int yrad, Color color, bool isSolid);
            
            static void DrawEllipseMap(int x, int y, int xrad, int yrad, Color color, bool isSolid);
            
            static void DrawEllipseMouse(int x, int y, int xrad, int yrad, Color color, bool isSolid);
            
            static void DrawEllipseScreen(int x, int y, int xrad, int yrad, Color color, bool isSolid);
            
            /// <summary>
            /// Draws a dot on the screen at the given position with the given color
            /// </summary>
            static void DrawDot(Position^ p, Color color);

            static void DrawDotCType(Api::Enum::CoordinateType ctype, int x, int y, Color color);
            
            static void DrawDotMap(int x, int y, Color color);
            
            static void DrawDotMouse(int x, int y, Color color);
            
            static void DrawDotScreen(int x, int y, Color color);
            
            /// <summary>
            /// Draws a line on the screen from a to b with the given color
            /// </summary>
            static void DrawLine(Position^ a, Position^ b, Color color);

            static void DrawLineCType(Api::Enum::CoordinateType ctype, int x1, int y1, int x2, int y2, Color color);
            
            static void DrawLineMap(int x1, int y1, int x2, int y2, Color color);
            
            static void DrawLineMouse(int x1, int y1, int x2, int y2, Color color);
            
            static void DrawLineScreen(int x1, int y1, int x2, int y2, Color color);
            
            /// <summary>
            /// Retrieves latency values for the game. Includes latency, speed, and mode
            /// </summary>
            static property int LatencyFrames { int get(); }
            
            static property int LatencyTime { int get(); }
            
            static property int RemainingLatencyFrames { int get(); }
            
            static property int RemainingLatencyTime { int get(); }
            
            /// <summary>
            /// Retrieves the current revision of BWAPI
            /// </summary>
            static property int Revision { int get(); }
            
            /// <summary>
            /// Retrieves the debug state of the BWAPI build
            /// </summary>
            static property bool IsDebug { bool get(); }
            
            /// <summary>
            /// Returns true if latency compensation is enabled
            /// </summary>
            static property bool IsLatComEnabled { bool get(); }
            
            /// <summary>
            /// Use to enable or disable latency compensation. Default: Enabled
            /// </summary>
            static void SetLatCom(bool isEnabled);
            
            /// <summary>
            /// Retrieves the number of frames in the replay
            /// </summary>
            static property int ReplayFrameCount { int get(); }
            
            /// <summary>
            /// Sets the rendering state of the Starcraft GUI
            /// </summary>
            static void SetGui(bool enabled);
            
            /// <summary>
            /// Retrieves the instance number recorded by BWAPI to identify which instance an AI module belongs to
            /// </summary>
            static property int InstanceNumber { int get(); }
            
            /// <summary>
            /// Retrieves the bot's APM. Can include or exclude select commands
            /// </summary>
            static int GetApm(bool includeSelects);
            
            /// <summary>
            /// Changes the map to the one specified. Changes do not take effect unless the game is restarted
            /// </summary>
            static bool SetMap(String^ mapFileName);
            
            /// <summary>
            /// Sets the frame skip value. 1 = normal
            /// </summary>
            static void SetFrameSkip(int frameSkip);
            
            /// <summary>
            /// Returns true if Starcraft can find a path from the source to the destination
            /// </summary>
            static bool HasPath(Position^ source, Position^ destination);
            
            /// <summary>
            /// Sets the BWAPI player's alliance with another player
            /// </summary>
            static bool SetAlliance(Player^ player, bool allied, bool alliedVictory);
            
            /// <summary>
            /// Sets the BWAPI player's vision with another player
            /// </summary>
            static bool SetVision(Player^ player, bool enabled);
            
            /// <summary>
            /// Returns the elapsed game time in seconds
            /// </summary>
            static property int ElapsedTime { int get(); }
            
            /// <summary>
            /// Sets the level of command optimizations.
            /// 0 = No optimization.
            /// 1 = Some optimization    (Stop, Hold Position, Siege, Burrow, etc.).
            /// 2 = More optimization    (Train, Set Rally, Lift, [multi-select buildings]).
            /// 3 = Maximum optimization (Attack/Move to position, use ability at position, etc.)
            /// </summary>
            static void SetCommandOptimizationLevel(int level);
            
            /// <summary>
            /// Returns the remaining countdown time in seconds
            /// </summary>
            static property int CountdownTimer { int get(); }
            
            /// <summary>
            /// Returns the set of all map regions
            /// </summary>
            static property HashSet<Api::Region^>^ AllRegions { HashSet<Api::Region^>^ get(); }
            
            /// <summary>
            /// Returns the region at a position
            /// </summary>
            static Api::Region^ GetRegionAt(int x, int y);
            
            /// <summary>
            /// Returns the region at a position
            /// </summary>
            static Api::Region^ GetRegionAt(Position^ position);
            
            /// <summary>
            /// Returns the time taken to perform the previous event call. Used for tournament management
            /// </summary>
            static property int LastEventTime { int get(); }
            
            /// <summary>
            /// Enables or disables the Fog of War in a replay
            /// </summary>
            static bool SetRevealAll(bool reveal);

            /// <summary>
            /// Gets a build location for a unit type near a position within a range, on or off creep
            /// </summary>
            static TilePosition^ GetBuildLocation(UnitType^ type, TilePosition^ desiredPosition, int maxRange, bool creep);

            /// <summary>
            /// Gets the damage from a unit to another (usually yours)
            /// </summary>
            static int GetDamageFrom(UnitType^ fromType, UnitType^ toType, Player^ fromPlayer, Player^ toPlayer);

            /// <summary>
            /// Gets the damage to a unit from another (usually yours)
            /// </summary>
            static int GetDamageTo(UnitType^ toType, UnitType^ fromType, Player^ toPlayer, Player^ fromPlayer);
        };
    }
}
