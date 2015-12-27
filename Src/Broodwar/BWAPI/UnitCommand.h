#pragma once
#pragma unmanaged

#include <BWAPI\UnitCommand.h>

#pragma managed

#include "Enum\UnitCommandType.h"
#include "Position.h"
#include "TilePosition.h"
#include "Tech.h"
#include "Upgrade.h"
#include "UnitType.h"

namespace BroodWar
{
	namespace Api
	{
		ref class Unit;

		public ref class UnitCommand sealed
		{
		internal:
			BWAPI::UnitCommand* instance;
			bool dispose;

			UnitCommand(BWAPI::UnitCommand* command);
			UnitCommand(BWAPI::UnitCommand command);
			~UnitCommand();
			!UnitCommand();

		public:
			UnitCommand();
			UnitCommand(Api::Unit^ unit, Api::Enum::UnitCommandType type, Api::Unit^ target, int x, int y, int extra);

			property Api::Enum::UnitCommandType Type { Api::Enum::UnitCommandType get(); }
			bool TypeEquals(Api::Enum::UnitCommandType type);
			property Api::Unit^ Unit { Api::Unit^ get(); }
			property Api::Unit^ Target { Api::Unit^ get(); }
			property Api::Position^ TargetPosition { Api::Position^ get(); }
			property Api::TilePosition^ TargetTilePosition { Api::TilePosition^ get(); }
			property Api::UnitType^ UnitType { Api::UnitType^ get(); }
			property Api::Tech^ Tech { Api::Tech^ get(); }
			property Api::Upgrade^ Upgrade { Api::Upgrade^ get(); }
			property int Slot { int get(); }
			property bool IsQueued { bool get(); }

			static UnitCommand^ Attack(Api::Unit^ unit, Api::Position^ target, bool shiftQueueCommand);
			static UnitCommand^ Attack(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand);
			static UnitCommand^ Build(Api::Unit^ unit, Api::TilePosition^ target, Api::UnitType^ type);
			static UnitCommand^ BuildAddon(Api::Unit^ unit, Api::UnitType^ type);
			static UnitCommand^ Train(Api::Unit^ unit, Api::UnitType^ type);
			static UnitCommand^ Morph(Api::Unit^ unit, Api::UnitType^ type);
			static UnitCommand^ Research(Api::Unit^ unit, Api::Tech^ tech);
			static UnitCommand^ PerformUpgrade(Api::Unit^ unit, Api::Upgrade^ upgrade);
			static UnitCommand^ SetRallyPoint(Api::Unit^ unit, Api::Position^ target);
			static UnitCommand^ SetRallyPoint(Api::Unit^ unit, Api::Unit^ target);
			static UnitCommand^ Move(Api::Unit^ unit, Api::Position^ target, bool shiftQueueCommand);
			static UnitCommand^ Patrol(Api::Unit^ unit, Api::Position^ target, bool shiftQueueCommand);
			static UnitCommand^ HoldPosition(Api::Unit^ unit, bool shiftQueueCommand);
			static UnitCommand^ Stop(Api::Unit^ unit, bool shiftQueueCommand);
			static UnitCommand^ Follow(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand);
			static UnitCommand^ Gather(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand);
			static UnitCommand^ ReturnCargo(Api::Unit^ unit, bool shiftQueueCommand);
			static UnitCommand^ Repair(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand);
			static UnitCommand^ Burrow(Api::Unit^ unit);
			static UnitCommand^ Unburrow(Api::Unit^ unit);
			static UnitCommand^ Cloak(Api::Unit^ unit);
			static UnitCommand^ Decloak(Api::Unit^ unit);
			static UnitCommand^ Siege(Api::Unit^ unit);
			static UnitCommand^ Unsiege(Api::Unit^ unit);
			static UnitCommand^ Lift(Api::Unit^ unit);
			static UnitCommand^ Land(Api::Unit^ unit, Api::TilePosition^ target);
			static UnitCommand^ Load(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand );
			static UnitCommand^ Unload(Api::Unit^ unit, Api::Unit^ target);
			static UnitCommand^ UnloadAll(Api::Unit^ unit, bool shiftQueueCommand);
			static UnitCommand^ UnloadAll(Api::Unit^ unit, Api::Position^ target, bool shiftQueueCommand);
			static UnitCommand^ RightClick(Api::Unit^ unit, Api::Position^ target, bool shiftQueueCommand);
			static UnitCommand^ RightClick(Api::Unit^ unit, Api::Unit^ target, bool shiftQueueCommand);
			static UnitCommand^ HaltConstruction(Api::Unit^ unit);
			static UnitCommand^ CancelConstruction(Api::Unit^ unit);
			static UnitCommand^ CancelAddon(Api::Unit^ unit);
			static UnitCommand^ CancelTrain(Api::Unit^ unit, int slot);
			static UnitCommand^ CancelMorph(Api::Unit^ unit);
			static UnitCommand^ CancelResearch(Api::Unit^ unit);
			static UnitCommand^ CancelUpgrade(Api::Unit^ unit);
			static UnitCommand^ UseTech(Api::Unit^ unit, Api::Tech^ tech);
			static UnitCommand^ UseTech(Api::Unit^ unit, Api::Tech^ tech, Api::Position^ target);
			static UnitCommand^ UseTech(Api::Unit^ unit, Api::Tech^ tech, Api::Unit^ target);
			static UnitCommand^ PlaceCop(Api::Unit^ unit, Api::TilePosition^ target);

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(UnitCommand^ other);
			
			static bool operator == (UnitCommand^ first, UnitCommand^ second);
			static bool operator != (UnitCommand^ first, UnitCommand^ second);
		};

		UnitCommand^ ConvertUnitCommand(BWAPI::UnitCommand command);
		BWAPI::UnitCommand ConvertUnitCommand(UnitCommand^ command);
	}
}
