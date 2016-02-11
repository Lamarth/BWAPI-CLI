namespace BroodwarFSharp

[<Measure>] type pixel
[<Measure>] type walk
[<Measure>] type tile
[<Measure>] type frame

module Position =
    let (||~||) x y =
        let largeDist, smallDist = max x y, min x y
        if smallDist < (largeDist >>> 2) then largeDist
        else
            let smallCalc = (3*smallDist) >>> 3
            ((smallCalc >>> 5) + smallCalc + largeDist - (largeDist >>> 4) - (largeDist >>> 6))

    type Position<[<Measure>] 'u> = Pos of int<'u> * int<'u> with
        static member inline (+) (Pos (x1, y1), Pos (x2, y2)) = Pos (x1 + x2, y1 + y2)
        static member inline (-) (Pos (x1, y1), Pos (x2, y2)) = Pos (x1 - x2, y1 - y2)
        static member inline (*) (Pos (x, y), f) = Pos (x * f, y * f)
        static member inline (/) (Pos (x, y), d) = Pos (x / d, y / d)
        // getApproxDistance as per Starcraft: Broodwar
        static member (|~|) (Pos (x1:int<'u>, y1), Pos (x2, y2)) = (abs (x1 - x2) |> int) ||~|| (abs (y1 - y2) |> int) |> LanguagePrimitives.Int32WithMeasure<'u>
        // Precise length calc - may be slow
        static member inline (|-|) (Pos (x1, y1), Pos (x2, y2)) =
            pown (x1 - x2) 2 + pown (y1 - y2) 2 |> float |> sqrt
    
    // Approx distance between two rectangles
    let (|~~|) (Pos (l1:int<'u>, t1), Pos (r1, b1)) (Pos (l2, t2), Pos (r2, b2)) =
        let x1, x2 = l1 - r2, l2 - r1
        let y1, y2 = t1 - b2, t2 - b1
        ((max x1 x2 |> int) - 1 |> max 0) ||~|| ((max y1 y2 |> int) - 1 |> max 0) |> LanguagePrimitives.Int32WithMeasure<'u>
    // Test if two rectangles intersect
    let (|><|) (Pos (l1:int<'u>, t1), Pos (r1, b1)) (Pos (l2, t2), Pos (r2, b2)) = (l1 <= r2) && (l2 <= r1) && (t1 <= b2) && (t2 <= b1)

    let inline posx (Pos (_x, _)) = _x
    let inline posy (Pos (_, _y)) = _y

    let PixelPerWalk : int<pixel/walk> = 8<pixel/walk>
    let PixelPerTile : int<pixel/tile> = 32<pixel/tile>
    let WalkPerTile : int<walk/tile> = 4<walk/tile>

    let inline walkToPixel (pos:Position<_>) = pos * PixelPerWalk
    let inline tileToPixel (pos:Position<_>) = pos * PixelPerTile

    let inline pixelToWalk (pos:Position<_>) = pos / PixelPerWalk
    let inline tileToWalk (pos:Position<_>) = pos * WalkPerTile

    let inline pixelToTile (pos:Position<_>) = pos / PixelPerTile
    let inline walkToTile (pos:Position<_>) = pos / WalkPerTile

    let inline pixelToApi (Pos (x, y)) = new BroodWar.Api.Position(x * 1<1/pixel>, y * 1<1/pixel>)
    let inline walkToApi (Pos (x, y)) = new BroodWar.Api.WalkPosition(x * 1<1/walk>, y * 1<1/walk>)
    let inline tileToApi (Pos (x, y)) = new BroodWar.Api.TilePosition(x * 1<1/tile>, y * 1<1/tile>)

    let inline apiToPixel (pos:BroodWar.Api.Position) = Pos (pos.X * 1<pixel>, pos.Y * 1<pixel>)
    let inline apiToWalk (pos:BroodWar.Api.WalkPosition) = Pos (pos.X * 1<walk>, pos.Y * 1<walk>)
    let inline apiToTile (pos:BroodWar.Api.TilePosition) = Pos (pos.X * 1<tile>, pos.Y * 1<tile>)

    let invalidPixel = Pos (32000<pixel>, 32000<pixel>)
    let nonePixel = Pos (32000<pixel>, 32032<pixel>)
    let unknownPixel = Pos (32000<pixel>, 32064<pixel>)
    let invalidWalk = pixelToWalk invalidPixel
    let noneWalk = pixelToWalk nonePixel
    let unknownWalk = pixelToWalk unknownPixel
    let invalidTile = pixelToTile invalidPixel
    let noneTile = pixelToTile nonePixel
    let unknownTile = pixelToTile unknownPixel
