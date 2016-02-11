namespace BroodwarFSharp

open Position

type UnitType = BroodWar.Api.UnitType

[<AbstractClass; Sealed>]
type UnitTypeExt =
    static member inline TileSize (unitType:UnitType) = Position.apiToTile unitType.TileSize
