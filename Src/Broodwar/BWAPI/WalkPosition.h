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
        ref class TilePosition;

        public ref class WalkPosition
        {
        internal:
            BWAPI::WalkPosition *instance;
            bool dispose;

            WalkPosition(BWAPI::WalkPosition *position, bool takeOwnership);
            WalkPosition(BWAPI::WalkPosition position);
            ~WalkPosition();
            !WalkPosition();

        public:
            WalkPosition();
            WalkPosition(WalkPosition^ copy);
            WalkPosition(int x, int y);

            property int X { int get(); }
            property int Y { int get(); }
            property bool IsValid { bool get(); }
            double CalcDistance(WalkPosition^ position);
            int CalcApproximateDistance(WalkPosition^ position);
            double CalcLength();
            void MakeValid();
            property bool IsInvalid { bool get(); }
            property bool IsNone { bool get(); }
            property bool IsUnknown { bool get(); }

            virtual int GetHashCode() override;
            virtual bool Equals(Object^ o) override;
            bool Equals(WalkPosition^ other);

            static bool operator == (WalkPosition^ first, WalkPosition^ second);
            static bool operator != (WalkPosition^ first, WalkPosition^ second);
            static bool operator < (WalkPosition^ first, WalkPosition^ second);
            static WalkPosition^ operator + (WalkPosition^ first, WalkPosition^ second);
            static WalkPosition^ operator - (WalkPosition^ first, WalkPosition^ second);
            static WalkPosition^ operator * (WalkPosition^ first, int second);
            static WalkPosition^ operator / (WalkPosition^ first, int second);
            static WalkPosition^ operator += (WalkPosition^ first, WalkPosition^ second);
            static WalkPosition^ operator -= (WalkPosition^ first, WalkPosition^ second);
            static WalkPosition^ operator *= (WalkPosition^ first, int second);
            static WalkPosition^ operator /= (WalkPosition^ first, int second);

            static WalkPosition^ Rescale(Position^ position);
            static WalkPosition^ Rescale(TilePosition^ position);
        };

        BWAPI::WalkPosition ConvertWalkPosition(WalkPosition^ position);
        WalkPosition^ ConvertWalkPosition(BWAPI::WalkPosition position);
        WalkPosition^ ConvertWalkPosition(BWAPI::WalkPosition* position);
    }
}
