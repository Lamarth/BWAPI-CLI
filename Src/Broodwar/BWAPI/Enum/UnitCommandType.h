#pragma once

namespace BroodWar
{
	namespace Api
	{
		namespace Enum
		{
			public enum class UnitCommandType
			{
				AttackMove,
				AttackUnit,
				Build,
				BuildAddon,
				Train,
				Morph,
				Research,
				Upgrade,
				SetRallyPosition,
				SetRallyUnit,
				Move,
				Patrol,
				HoldPosition,
				Stop,
				Follow,
				Gather,
				ReturnCargo,
				Repair,
				Burrow,
				Unburrow,
				Cloak,
				Decloak,
				Siege,
				Unsiege,
				Lift,
				Land,
				Load,
				Unload,
				UnloadAll,
				UnloadAllPosition,
				RightClickPosition,
				RightClickUnit,
				HaltConstruction,
				CancelConstruction,
				CancelAddon,
				CancelTrain,
				CancelTrainSlot,
				CancelMorph,
				CancelResearch,
				CancelUpgrade,
				UseTech,
				UseTechPosition,
				UseTechUnit,
				PlaceCop,
				None,
				Unknown
			};
		}
	}
}
