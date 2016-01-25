namespace BroodwarFSharp

[<Measure>] type pixel
[<Measure>] type walk
[<Measure>] type tile

module Position =
    type Position<[<Measure>] 'u> = Pos of int<'u> * int<'u> with
        static member inline (+) (Pos (x1, y1), Pos (x2, y2)) = Pos (x1 + x2, y1 + y2)
        static member inline (-) (Pos (x1, y1), Pos (x2, y2)) = Pos (x1 - x2, y1 - y2)
        static member inline (*) (Pos (x, y), f) = Pos (x * f, y * f)
        static member inline (/) (Pos (x, y), d) = Pos (x / d, y / d)

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
