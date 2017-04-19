#include <vcclr.h>
#include <cliext\set>

#include <BWAPI.h>

#include "Game.h"
#include "Force.h"
#include "Player.h"
#include "Bullet.h"
#include "Race.h"
#include "Region.h"
#include "Position.h"
#include "TilePosition.h"
#include "WalkPosition.h"
#include "Event.h"
#include "Unit.h"

#include "..\EnumMapping.h"
#include "..\Util.h"

using namespace System::Runtime::InteropServices;
using namespace BroodWar;

extern BWAPI::Game *BWAPI::BroodwarPtr;

bool isInitialised = false;

namespace BroodWar
{
    namespace Api
    {
        Game::Game()
        {
            Rebind();
        }

        void Game::Rebind()
        {
            instance = BWAPI::BroodwarPtr;
        }
            
        HashSet<Api::Force^>^ Game::Forces::get()
        {
            return ToHashSet<BWAPI::Force, Force^>(instance->getForces(), &ConvertForce);
        }
            
        HashSet<Api::Player^>^ Game::Players::get()
        {
            return ToHashSet<BWAPI::Player, Player^>(instance->getPlayers(), &ConvertPlayer);
        }
            
        HashSet<Api::Unit^>^ Game::AllUnits::get()
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getAllUnits(), &ConvertUnit);
        }
            
        HashSet<Api::Unit^>^ Game::Minerals::get()
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getMinerals(), &ConvertUnit);
        }
            
        HashSet<Api::Unit^>^ Game::Geysers::get()
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getGeysers(), &ConvertUnit);
        }
            
        HashSet<Api::Unit^>^ Game::NeutralUnits::get()
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getNeutralUnits(), &ConvertUnit);
        }
            
        HashSet<Api::Unit^>^ Game::StaticMinerals::get()
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getStaticMinerals(), &ConvertUnit);
        }
            
        HashSet<Api::Unit^>^ Game::StaticGeysers::get()
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getStaticGeysers(), &ConvertUnit);
        }
            
        HashSet<Api::Unit^>^ Game::StaticNeutralUnits::get()
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getStaticNeutralUnits(), &ConvertUnit);
        }
        
        HashSet<Api::Bullet^>^ Game::Bullets::get()
        {
            return ToHashSet<BWAPI::Bullet, Bullet^>(instance->getBullets(), &ConvertBullet);
        }
            
        List<Api::Position^>^ Game::NukeDots::get()
        {
            return ToList<BWAPI::Position, Position^>(instance->getNukeDots(), &ConvertPosition);
        }
            
        List<Api::Event^>^ Game::Events::get()
        {
            return ToList<BWAPI::Event, Event^>(instance->getEvents(), &ConvertEvent);
        }
        
        Api::Force^ Game::GetForceById(int forceId)
        {
            return ConvertForce(instance->getForce(forceId));
        }
            
        Api::Player^ Game::GetPlayerById(int playerId)
        {
            return ConvertPlayer(instance->getPlayer(playerId));
        }
            
        Api::Unit^ Game::GetUnitById(int unitId)
        {
            return ConvertUnit(instance->getUnit(unitId));
        }
            
        Api::Unit^ Game::IndexToUnit(int unitIndex) 
        {
            return ConvertUnit(instance->indexToUnit(unitIndex));
        }
        
        Api::Region^ Game::Region(int regionId)
        {
            return ConvertRegion(instance->getRegion(regionId));
        }
            
        Api::Enum::GameType Game::GameType::get()
        {
            return EnumMapping::GameType->Managed(instance->getGameType());
        }
            
        int Game::Latency::get()
        {
            return instance->getLatency();
        }
            
        int Game::FrameCount::get()
        {
            return instance->getFrameCount();
        }
        
        int Game::Fps::get()
        {
            return instance->getFPS();
        }
            
        double Game::AverageFps::get()
        {
            return instance->getAverageFPS();
        }
            
        Api::Position^ Game::MousePosition::get()
        {
            return ConvertPosition(instance->getMousePosition());
        }
            
        bool Game::GetMouseState(Api::Enum::MouseButton button)
        {
            return instance->getMouseState(static_cast<BWAPI::MouseButton>(button));
        }
            
        bool Game::GetKeyState(Api::Enum::Key key)
        {
            return instance->getKeyState(static_cast<BWAPI::Key>(key));
        }
            
        Api::Position^ Game::ScreenPosition::get()
        {
            return ConvertPosition(instance->getScreenPosition());
        }
            
        void Game::SetScreenPosition(int x, int y)
        {
            instance->setScreenPosition(x, y);
        }

        void Game::SetScreenPosition(Api::Position^ p)
        {
            instance->setScreenPosition(*(p->instance));
        }
            
        void Game::PingMinimap(int x, int y)
        {
            instance->pingMinimap(x, y);
        }

        void Game::PingMinimap(Api::Position^ p)
        {
            instance->pingMinimap(*(p->instance));
        }
            
        bool Game::IsFlagEnabled(Api::Enum::Flag flag)
        {
            return instance->isFlagEnabled(static_cast<int>(flag));
        }
            
        void Game::EnableFlag(Api::Enum::Flag flag)
        {
            instance->enableFlag(static_cast<int>(flag));
        }

        HashSet<Api::Unit^>^ Game::GetUnitsOnTile(int tileX, int tileY)
         {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getUnitsOnTile(tileX, tileY), &ConvertUnit);
        }

        HashSet<Api::Unit^>^ Game::GetUnitsOnTile(Api::TilePosition^ p)
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getUnitsOnTile(*(p->instance)), &ConvertUnit);
        }
            
        HashSet<Api::Unit^>^ Game::GetUnitsInRectangle(int left, int top, int right, int bottom)
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getUnitsInRectangle(left, top, right, bottom), &ConvertUnit);
        }
            
        HashSet<Api::Unit^>^ Game::GetUnitsInRectangle(Api::Position^ topLeft, Api::Position^ bottomRight)
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getUnitsInRectangle(*(topLeft->instance), *(bottomRight->instance)), &ConvertUnit);
        }

        HashSet<Api::Unit^>^ Game::GetUnitsInRadius(int x, int y, int radius)
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getUnitsInRadius(x, y, radius), &ConvertUnit);
        }

        HashSet<Api::Unit^>^ Game::GetUnitsInRadius(Api::Position^ center, int radius)
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getUnitsInRadius(*(center->instance), radius), &ConvertUnit);
        }
            
        Api::Enum::ErrorType Game::LastError::get()
        {
            return EnumMapping::ErrorType->Managed(instance->getLastError());
        }
            
        void Game::LastError::set(Api::Enum::ErrorType e)
        {
            instance->setLastError(EnumMapping::ErrorType->Native(e));
        }
            
        int Game::MapWidth::get()
        {
            return instance->mapWidth();
        }
            
        int Game::MapHeight::get()
        {
            return instance->mapHeight();
        }
            
        String^ Game::MapFileName::get()
        {
            return gcnew String(instance->mapFileName().c_str());
        }
            
        String^ Game::MapPathName::get()
        {
            return gcnew String(instance->mapPathName().c_str());
        }
            
        String^ Game::MapName::get()
        {
            return gcnew String(instance->mapName().c_str());
        }
            
        String^ Game::MapHash::get()
        {
            return gcnew String(instance->mapHash().c_str());
        }

        bool Game::IsWalkable(int walkX, int walkY)
        {
            return instance->isWalkable(walkX, walkY);
        }

        bool Game::IsWalkable(Api::WalkPosition^ p)
        {
            return instance->isWalkable(*(p->instance));
        }

        int Game::GetGroundHeight(int tileX, int tileY)
        {
            return instance->getGroundHeight(tileX, tileY);
        }

        int Game::GetGroundHeight(Api::TilePosition^ position)
        {
            return instance->getGroundHeight(*(position->instance));
        }
            
        bool Game::IsBuildable(int tileX, int tileY, bool includeBuildings)
        {
            return instance->isBuildable(tileX, tileY, includeBuildings);
        }
            
        bool Game::IsBuildable(Api::TilePosition^ position, bool includeBuildings)
        {
            return instance->isBuildable(ConvertTilePosition(position), includeBuildings);
        }
             
        bool Game::IsVisible(int tileX, int tileY)
        {
            return instance->isVisible(tileX, tileY);
        }
            
        bool Game::IsVisible(Api::TilePosition^ position)
        {
            return instance->isVisible(ConvertTilePosition(position));
        }
             
        bool Game::IsExplored(int tileX, int tileY)
        {
            return instance->isExplored(tileX, tileY);
        }
            
        bool Game::IsExplored(Api::TilePosition^ position)
        {
            return instance->isExplored(ConvertTilePosition(position));
        }
             
        bool Game::HasCreep(int tileX, int tileY)
        {
            return instance->hasCreep(tileX, tileY);
        }
            
        bool Game::HasCreep(Api::TilePosition^ position)
        {
            return instance->hasCreep(ConvertTilePosition(position));
        }
             
        bool Game::HasPower(int tileX, int tileY, Api::Enum::UnitType unitType)
        {
            return instance->hasPower(tileX, tileY, EnumMapping::UnitType->Native(unitType));
        }
            
        bool Game::HasPower(Api::TilePosition^ position, Api::Enum::UnitType unitType)
        {
            return instance->hasPower(ConvertTilePosition(position), EnumMapping::UnitType->Native(unitType));
        }
             
        bool Game::HasPower(int tileX, int tileY, int tileWidth, int tileHeight, Api::Enum::UnitType unitType)
        {
            return instance->hasPower(tileX, tileY, tileWidth, tileHeight, EnumMapping::UnitType->Native(unitType));
        }
            
        bool Game::HasPower(Api::TilePosition^ position, int tileWidth, int tileHeight, Api::Enum::UnitType unitType)
        {
            return instance->hasPower(ConvertTilePosition(position), tileWidth, tileHeight, EnumMapping::UnitType->Native(unitType));
        }
             
        bool Game::HasPowerPrecise(int x, int y, Api::Enum::UnitType unitType)
        {
            return instance->hasPowerPrecise(x, y, EnumMapping::UnitType->Native(unitType));
        }
            
        bool Game::HasPowerPrecise(Api::Position^ position, Api::Enum::UnitType unitType)
        {
            return instance->hasPowerPrecise(ConvertPosition(position), EnumMapping::UnitType->Native(unitType));
        }
            
        bool Game::CanBuildHere(Api::TilePosition^ position, Api::Enum::UnitType type, Api::Unit^ builder, bool checkExplored)
        {
            return instance->canBuildHere(ConvertTilePosition(position), EnumMapping::UnitType->Native(type), ConvertUnit(builder), checkExplored);
        }
            
        bool Game::CanMake(Api::Enum::UnitType type, Api::Unit^ builder)
        {
            return instance->canMake(EnumMapping::UnitType->Native(type), ConvertUnit(builder));
        }
            
        bool Game::CanResearch(Api::Enum::TechType type, Api::Unit^ unit, bool checkCanIssueCommand)
        {
            return instance->canResearch(EnumMapping::TechType->Native(type), ConvertUnit(unit), checkCanIssueCommand);
        }
            
        bool Game::CanUpgrade(Api::Enum::UpgradeType type, Api::Unit^ unit, bool checkCanIssueCommand)
        {
            return instance->canUpgrade(EnumMapping::UpgradeType->Native(type), ConvertUnit(unit), checkCanIssueCommand);
        }
            
        List<Api::TilePosition^>^ Game::StartLocations::get()
        {
            return ToList<BWAPI::TilePosition, TilePosition^>(instance->getStartLocations(), &ConvertTilePosition);
        }
            
        void Game::Write(String^ format, ... cli::array<Object^>^ args)
        {
            IntPtr str = Marshal::StringToHGlobalAnsi(String::Format(format, args));
            instance->printf((const char*)str.ToPointer());
            Marshal::FreeHGlobal(str);
        }
            
        void Game::SendText(String^ format, ... cli::array<Object^>^ args)
        {
            IntPtr str = Marshal::StringToHGlobalAnsi(String::Format(format, args));
            instance->sendText((const char*)str.ToPointer());
            Marshal::FreeHGlobal(str);
        }
            
        void Game::SendText(bool toAllies, String^ format, ... cli::array<Object^>^ args)
        {
            IntPtr str = Marshal::StringToHGlobalAnsi(String::Format(format, args));
            instance->sendTextEx(toAllies, (const char*)str.ToPointer());
            Marshal::FreeHGlobal(str);
        }
            
        bool Game::IsInGame::get()
        {
            return instance->isInGame();
        }
            
        bool Game::IsMultiplayer::get()
        {
            return instance->isMultiplayer();
        }
            
        bool Game::IsBattleNet::get()
        {
            return instance->isBattleNet();
        }
            
        bool Game::IsPaused::get()
        {
            return instance->isPaused();
        }
            
        bool Game::IsReplay::get()
        {
            return instance->isReplay();
        }
            
        void Game::PauseGame()
        {
            instance->pauseGame();
        }
            
        void Game::ResumeGame()
        {
            instance->resumeGame();
        }
            
        void Game::LeaveGame()
        {
            instance->leaveGame();
        }
            
        void Game::RestartGame()
        {
            instance->restartGame();
        }
            
        void Game::SetLocalSpeed(int speed )
        {
            instance->setLocalSpeed(speed);
        }
            
        bool Game::IssueCommand(List<Api::Unit^>^ units, Api::UnitCommand^ command)
        {
            BWAPI::Unitset unitset = ToUnitset(units, &ConvertUnit);
            return instance->issueCommand(unitset, ConvertUnitCommand(command));
        }
            
        HashSet<Api::Unit^>^ Game::GetSelectedUnits::get()
        {
            return ToHashSet<BWAPI::Unit, Unit^>(instance->getSelectedUnits(), &ConvertUnit);
        }
            
        Api::Player^ Game::Self::get()
        {
            return ConvertPlayer(instance->self());
        }
            
        Api::Player^ Game::Enemy::get()
        {
            return ConvertPlayer(instance->enemy());
        }
            
        Api::Player^ Game::Neutral::get()
        {
            return ConvertPlayer(instance->neutral());
        }
            
        HashSet<Api::Player^>^ Game::Allies::get()
        {
            return ToHashSet<BWAPI::Player, Player^>(instance->allies(), &ConvertPlayer);
        }
            
        HashSet<Api::Player^>^ Game::Enemies::get()
        {
            return ToHashSet<BWAPI::Player, Player^>(instance->enemies(), &ConvertPlayer);
        }
            
        HashSet<Api::Player^>^ Game::Observers::get()
        {
            return ToHashSet<BWAPI::Player, Player^>(instance->observers(), &ConvertPlayer);
        }
            
        //void Game::SetTextSize(int size)
        //{
        //    instance->setTextSize(size);
        //}

        void Game::DrawText(Position^ p, String^ format, ... cli::array<Object^>^ args)
        {
            IntPtr str = Marshal::StringToHGlobalAnsi(String::Format(format, args));
            instance->drawTextMap(*(p->instance), (const char*)str.ToPointer());
            Marshal::FreeHGlobal(str);
        }

        void Game::DrawTextCType(Api::Enum::CoordinateType ctype, int x, int y, String^ format, ... cli::array<Object^>^ args)
        {
            IntPtr str = Marshal::StringToHGlobalAnsi(String::Format(format, args));
            instance->drawText(static_cast<BWAPI::CoordinateType::Enum>(ctype), x, y, (const char*)str.ToPointer());
            Marshal::FreeHGlobal(str);
        }
            
        void Game::DrawTextMap(int x, int y, String^ format, ... cli::array<Object^>^ args)
        {
            IntPtr str = Marshal::StringToHGlobalAnsi(String::Format(format, args));
            instance->drawTextMap(x, y, (const char*)str.ToPointer());
            Marshal::FreeHGlobal(str);
        }
            
        void Game::DrawTextMouse(int x, int y, String^ format, ... cli::array<Object^>^ args)
        {
            IntPtr str = Marshal::StringToHGlobalAnsi(String::Format(format, args));
            instance->drawTextMouse(x, y, (const char*)str.ToPointer());
            Marshal::FreeHGlobal(str);
        }
            
        void Game::DrawTextScreen(int x, int y, String^ format, ... cli::array<Object^>^ args)
        {
            IntPtr str = Marshal::StringToHGlobalAnsi(String::Format(format, args));
            instance->drawTextScreen(x, y, (const char*)str.ToPointer());
            Marshal::FreeHGlobal(str);
        }

        void Game::DrawBox(Position^ topLeft, Position^ bottomRight, Color color, bool isSolid)
        {
            instance->drawBoxMap(*(topLeft->instance), *(bottomRight->instance), EnumMapping::ToBwColor(color), isSolid);
        }

        void Game::DrawBoxCType(Api::Enum::CoordinateType ctype, int left, int top, int right, int bottom, Color color, bool isSolid)
        {
            instance->drawBox(static_cast<BWAPI::CoordinateType::Enum>(ctype), left, top, right, bottom, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawBoxMap(int left, int top, int right, int bottom, Color color, bool isSolid)
        {
            instance->drawBoxMap(left, top, right, bottom, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawBoxMouse(int left, int top, int right, int bottom, Color color, bool isSolid)
        {
            instance->drawBoxMouse(left, top, right, bottom, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawBoxScreen(int left, int top, int right, int bottom, Color color, bool isSolid)
        {
            instance->drawBoxScreen(left, top, right, bottom, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawTriangle(Position^ a, Position^ b, Position^ c, Color color, bool isSolid)
        {
            instance->drawTriangleMap(*(a->instance), *(b->instance), *(c->instance), EnumMapping::ToBwColor(color), isSolid);
        }

        void Game::DrawTriangleCType(Api::Enum::CoordinateType ctype, int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid)
        {
            instance->drawTriangle(static_cast<BWAPI::CoordinateType::Enum>(ctype), ax, ay, bx, by, cx, cy, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawTriangleMap(int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid)
        {
            instance->drawTriangleMap(ax, ay, bx, by, cx, cy, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawTriangleMouse(int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid)
        {
            instance->drawTriangleMouse(ax, ay, bx, by, cx, cy, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawTriangleScreen(int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid)
        {
            instance->drawTriangleScreen(ax, ay, bx, by, cx, cy, EnumMapping::ToBwColor(color), isSolid);
        }

        void Game::DrawCircle(Position^ center, int radius, Color color, bool isSolid)
        {
            instance->drawCircleMap(*(center->instance), radius, EnumMapping::ToBwColor(color), isSolid);
        }

        void Game::DrawCircleCType(Api::Enum::CoordinateType ctype, int x, int y, int radius, Color color, bool isSolid)
        {
            instance->drawCircle(static_cast<BWAPI::CoordinateType::Enum>(ctype), x, y, radius, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawCircleMap(int x, int y, int radius, Color color, bool isSolid)
        {
            instance->drawCircleMap(x, y, radius, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawCircleMouse(int x, int y, int radius, Color color, bool isSolid)
        {
            instance->drawCircleMouse(x, y, radius, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawCircleScreen(int x, int y, int radius, Color color, bool isSolid)
        {
            instance->drawCircleScreen(x, y, radius, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawEllipse(Position^ center, int xrad, int yrad, Color color, bool isSolid)
        {
            instance->drawEllipseMap(*(center->instance), xrad, yrad, EnumMapping::ToBwColor(color), isSolid);
        }

        void Game::DrawEllipseCType(Api::Enum::CoordinateType ctype, int x, int y, int xrad, int yrad, Color color, bool isSolid)
        {
            instance->drawEllipse(static_cast<BWAPI::CoordinateType::Enum>(ctype), x, y, xrad, yrad, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawEllipseMap(int x, int y, int xrad, int yrad, Color color, bool isSolid)
        {
            instance->drawEllipseMap(x, y, xrad, yrad, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawEllipseMouse(int x, int y, int xrad, int yrad, Color color, bool isSolid)
        {
            instance->drawEllipseMouse(x, y, xrad, yrad, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawEllipseScreen(int x, int y, int xrad, int yrad, Color color, bool isSolid)
        {
            instance->drawEllipseScreen(x, y, xrad, yrad, EnumMapping::ToBwColor(color), isSolid);
        }
            
        void Game::DrawDot(Position^ p, Color color)
        {
            instance->drawDotMap(*(p->instance), EnumMapping::ToBwColor(color));
        }

        void Game::DrawDotCType(Api::Enum::CoordinateType ctype, int x, int y, Color color)
        {
            instance->drawDot(static_cast<BWAPI::CoordinateType::Enum>(ctype), x, y, EnumMapping::ToBwColor(color));
        }
            
        void Game::DrawDotMap(int x, int y, Color color)
        {
            instance->drawDotMap(x, y, EnumMapping::ToBwColor(color));
        }
            
        void Game::DrawDotMouse(int x, int y, Color color)
        {
            instance->drawDotMouse(x, y, EnumMapping::ToBwColor(color));
        }
            
        void Game::DrawDotScreen(int x, int y, Color color)
        {
            instance->drawDotScreen(x, y, EnumMapping::ToBwColor(color));
        }

        void Game::DrawLine(Position^ a, Position^ b, Color color)
        {
            instance->drawLineMap(*(a->instance), *(b->instance), EnumMapping::ToBwColor(color));
        }

        void Game::DrawLineCType(Api::Enum::CoordinateType ctype, int x1, int y1, int x2, int y2, Color color)
        {
            instance->drawLine(static_cast<BWAPI::CoordinateType::Enum>(ctype), x1, y1, x2, y2, EnumMapping::ToBwColor(color));
        }
            
        void Game::DrawLineMap(int x1, int y1, int x2, int y2, Color color)
        {
            instance->drawLineMap(x1, y1, x2, y2, EnumMapping::ToBwColor(color));
        }
            
        void Game::DrawLineMouse(int x1, int y1, int x2, int y2, Color color)
        {
            instance->drawLineMouse(x1, y1, x2, y2, EnumMapping::ToBwColor(color));
        }
            
        void Game::DrawLineScreen(int x1, int y1, int x2, int y2, Color color)
        {
            instance->drawLineScreen(x1, y1, x2, y2, EnumMapping::ToBwColor(color));
        }
            
        int Game::LatencyFrames::get()
        {
            return instance->getLatencyFrames();
        }
            
        int Game::LatencyTime::get()
        {
            return instance->getLatencyTime();
        }
            
        int Game::RemainingLatencyFrames::get()
        {
            return instance->getRemainingLatencyFrames();
        }
            
        int Game::RemainingLatencyTime::get()
        {
            return instance->getRemainingLatencyTime();
        }
            
        int Game::Revision::get()
        {
            return instance->getRevision();
        }
            
        bool Game::IsDebug::get()
        {
            return instance->isDebug();
        }
            
        bool Game::IsLatComEnabled::get()
        {
            return instance->isLatComEnabled();
        }
            
        void Game::SetLatCom(bool isEnabled)
        {
            instance->setLatCom(isEnabled);
        }
            
        int Game::ReplayFrameCount::get()
        {
            return instance->getReplayFrameCount();
        }
            
        void Game::SetGui(bool enabled)
        {
            instance->setGUI(enabled);
        }
            
        int Game::InstanceNumber::get()
        {
            return instance->getInstanceNumber();
        }
            
        int Game::GetApm(bool includeSelects)
        {
            return instance->getAPM(includeSelects);
        }
            
        bool Game::SetMap(String^ mapFileName)
        {
            IntPtr str = Marshal::StringToHGlobalAnsi(mapFileName);
            bool rez = instance->setMap((const char*)str.ToPointer());
            Marshal::FreeHGlobal(str);
            return rez;
        }
            
        void Game::SetFrameSkip(int frameSkip)
        {
            instance->setFrameSkip(frameSkip);
        }
            
        bool Game::HasPath(Api::Position^ source, Api::Position^ destination)
        {
            return instance->hasPath(ConvertPosition(source), ConvertPosition(destination));
        }
            
        bool Game::SetAlliance(Api::Player^ player, bool allied, bool alliedVictory)
        {
            return instance->setAlliance(ConvertPlayer(player), allied, alliedVictory);
        }
            
        bool Game::SetVision(Api::Player^ player, bool enabled)
        {
            return instance->setVision(ConvertPlayer(player), enabled);
        }
            
        int Game::ElapsedTime::get()
        {
            return instance->elapsedTime();
        }
            
        void Game::SetCommandOptimizationLevel(int level)
        {
            instance->setCommandOptimizationLevel(level);
        }
            
        int Game::CountdownTimer::get()
        {
            return instance->countdownTimer();
        }
            
        HashSet<Api::Region^>^ Game::AllRegions::get()
        {
            return ToHashSet<BWAPI::Region, Api::Region^>(instance->getAllRegions(), &ConvertRegion);
        }
            
        Api::Region^ Game::GetRegionAt(int x, int y)
        {
            return ConvertRegion(instance->getRegionAt(x, y));
        }
            
        Api::Region^ Game::GetRegionAt(Api::Position^ position)
        {
            return ConvertRegion(instance->getRegionAt(ConvertPosition(position)));
        }
            
        int Game::LastEventTime::get()
        {
            return instance->getLastEventTime();
        }
            
        bool Game::SetRevealAll(bool reveal)
        {
            return instance->setRevealAll(reveal);
        }

        TilePosition^ Game::GetBuildLocation(UnitType^ type, TilePosition^ desiredPosition, int maxRange, bool creep)
        {
            return ConvertTilePosition(instance->getBuildLocation(ConvertUnitType(type), ConvertTilePosition(desiredPosition), maxRange, creep));
        }

        int Game::GetDamageFrom(UnitType^ fromType, UnitType^ toType, Player^ fromPlayer, Player^ toPlayer)
        {
            return instance->getDamageFrom(ConvertUnitType(fromType), ConvertUnitType(toType), ConvertPlayer(fromPlayer), ConvertPlayer(toPlayer));
        }

        int Game::GetDamageTo(UnitType^ toType, UnitType^ fromType, Player^ toPlayer, Player^ fromPlayer)
        {
            return instance->getDamageTo(ConvertUnitType(toType), ConvertUnitType(fromType), ConvertPlayer(toPlayer), ConvertPlayer(fromPlayer));
        }
    }
}
