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
        ref class TilePosition;

        public ref class Position
		{
        internal:
			BWAPI::Position *instance;
			bool dispose;

			Position(BWAPI::Position *position, bool takeOwnership);
			Position(BWAPI::Position position);
			~Position();
			!Position();

		public:
			Position();
			Position(Position^ copy);
            Position(int x, int y);

            property int X { int get(); }
			property int Y { int get(); }
			property bool IsValid { bool get(); }
			double CalcDistance(Position^ position);
			int CalcApproximateDistance(Position^ position);
            double CalcLength();
			void MakeValid();
			property bool IsInvalid { bool get(); }
			property bool IsNone { bool get(); }
			property bool IsUnknown { bool get(); }

			virtual int GetHashCode() override;
			virtual bool Equals(Object^ o) override;
			bool Equals(Position^ other);

			static bool operator == (Position^ first, Position^ second);
			static bool operator != (Position^ first, Position^ second);
			static bool operator < (Position^ first, Position^ second);
			static Position^ operator + (Position^ first, Position^ second);
			static Position^ operator - (Position^ first, Position^ second);
            static Position^ operator * (Position^ first, int second);
            static Position^ operator / (Position^ first, int second);
            static Position^ operator += (Position^ first, Position^ second);
			static Position^ operator -= (Position^ first, Position^ second);
            static Position^ operator *= (Position^ first, int second);
            static Position^ operator /= (Position^ first, int second);

            static Position^ Rescale(TilePosition^ position);
        };

		BWAPI::Position ConvertPosition(Position^ position);
        Position^ ConvertPosition(BWAPI::Position position);
        Position^ ConvertPosition(BWAPI::Position* position);
    }
}
