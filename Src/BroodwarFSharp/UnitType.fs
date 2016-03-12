namespace BroodwarFSharp

open Position

type UnitType = BroodWar.Api.UnitType

type UnitMark = { UnitId:int; Frame:int; Position:Position<pixel>; UnitType:UnitType; Player:BroodWar.Api.Player }

[<AbstractClass; Sealed>]
type UnitTypeExt =
    static member inline TileSize (unitType:UnitType) = Position.apiToTile unitType.TileSize
