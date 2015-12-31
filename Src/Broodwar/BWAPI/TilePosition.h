#pragma once
#pragma unmanaged

#include <BWAPI\Position.h>
//#pragma make_public(BWAPI::Point)

#pragma managed

namespace BroodWar
{
    // Can't use templates, because they're hard to consume in C#
    // Can't use generics, because BWAPI::Point needs to be hidden away
    // Probably should codegen somehow, to keep the copies in sync
    namespace Api
	{
        ref class Position;

        public ref class TilePosition
        {
        internal:
            BWAPI::TilePosition *instance;
            bool dispose;

            TilePosition(BWAPI::TilePosition *position, bool takeOwnership);
            TilePosition(BWAPI::TilePosition position);
            ~TilePosition();
            !TilePosition();

        public:
            TilePosition();
            TilePosition(TilePosition^ copy);
            TilePosition(int x, int y);

            property int X { int get(); }
            property int Y { int get(); }
            property bool IsValid { bool get(); }
            double CalcDistance(TilePosition^ position);
            int CalcApproximateDistance(TilePosition^ position);
            double CalcLength();
            void MakeValid();
            property bool IsInvalid { bool get(); }
            property bool IsNone { bool get(); }
            property bool IsUnknown { bool get(); }

            virtual int GetHashCode() override;
            virtual bool Equals(Object^ o) override;
            bool Equals(TilePosition^ other);

            static bool operator == (TilePosition^ first, TilePosition^ second);
            static bool operator != (TilePosition^ first, TilePosition^ second);
            static bool operator < (TilePosition^ first, TilePosition^ second);
            static TilePosition^ operator + (TilePosition^ first, TilePosition^ second);
            static TilePosition^ operator - (TilePosition^ first, TilePosition^ second);
            static TilePosition^ operator * (TilePosition^ first, int second);
            static TilePosition^ operator / (TilePosition^ first, int second);
            static TilePosition^ operator += (TilePosition^ first, TilePosition^ second);
            static TilePosition^ operator -= (TilePosition^ first, TilePosition^ second);
            static TilePosition^ operator *= (TilePosition^ first, int second);
            static TilePosition^ operator /= (TilePosition^ first, int second);

            static TilePosition^ Rescale(Position^ position);
        };

        BWAPI::TilePosition ConvertTilePosition(TilePosition^ position);
        TilePosition^ ConvertTilePosition(BWAPI::TilePosition position);
        TilePosition^ ConvertTilePosition(BWAPI::TilePosition* position);
    }
}
