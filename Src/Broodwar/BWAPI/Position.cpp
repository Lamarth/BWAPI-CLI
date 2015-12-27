#pragma unmanaged

#include <stddef.h>

#pragma managed

#include "Position.h"
#include "TilePosition.h"

namespace BroodWar
{
	namespace Api
	{
        BWAPI::Position ConvertPosition(Position^ position)
        {
            if (position == nullptr)
                return BWAPI::Positions::None;
            return *(position->instance);
        }

        Position^ ConvertPosition(BWAPI::Position position)
        {
            return gcnew Position(position);
        }

        Position^ ConvertPosition(BWAPI::Position* position)
        {
            if (position == NULL)
                return nullptr;
            return gcnew Position(position, false);
        }

        Position::Position(BWAPI::Position *position, bool takeOwnership)
        {
            instance = position;
            dispose = takeOwnership;
        }
        Position::Position(BWAPI::Position position)
        {
            instance = new BWAPI::Position(position);
            dispose = true;
        }
        Position::~Position()
        {
            if (dispose)
                delete instance;
        }
        Position::!Position()
        {
            if (dispose)
                delete instance;
        }

        Position::Position()
        {
            instance = new BWAPI::Position();
            dispose = true;
        }
        Position::Position(Position^ copy)
        {
            instance = new BWAPI::Position(*(copy->instance));
            dispose = true;
        }
        Position::Position(int x, int y)
        {
            instance = new BWAPI::Position(x, y);
            dispose = true;
        }

        int Position::X::get() { return instance->x; }
        int Position::Y::get() { return instance->y; }
        bool Position::IsValid::get() { return instance->isValid(); }
        double Position::CalcDistance(Position^ position) { return instance->getDistance(*(position->instance)); }
        int Position::CalcApproximateDistance(Position^ position) { return instance->getApproxDistance(*(position->instance)); }
        double Position::CalcLength() { return instance->getLength(); }
        void Position::MakeValid() { instance->makeValid(); }
        bool Position::IsInvalid::get() { return *instance == BWAPI::Positions::Invalid; }
        bool Position::IsNone::get() { return *instance == BWAPI::Positions::None; }
        bool Position::IsUnknown::get() { return *instance == BWAPI::Positions::Unknown; }

        int Position::GetHashCode()
        {
            return instance->x * 397 ^ instance->y;
        }
        bool Position::Equals(Object^ o)
        {
            Position^ other = dynamic_cast<Position^>(o);
            return this->Equals(other);
        }
        bool Position::Equals(Position^ other)
        {
            if (ReferenceEquals(nullptr, other))
                return false;
            if (ReferenceEquals(this, other))
                return true;
            return this->instance->x == other->instance->x
                && this->instance->y == other->instance->y;
        }

        bool Position::operator == (Position^ first, Position^ second)
        {
            if (ReferenceEquals(first, second))
                return true;
            if (ReferenceEquals(nullptr, first) || ReferenceEquals(nullptr, second))
                return false;
            return *(first->instance) == *(second->instance);
        }
        bool Position::operator != (Position^ first, Position^ second)
        {
            if (ReferenceEquals(first, second))
                return false;
            if (ReferenceEquals(nullptr, first) || ReferenceEquals(nullptr, second))
                return true;
            return *(first->instance) != *(second->instance);
        }
        bool Position::operator < (Position^ first, Position^ second)
        {
            return *(first->instance) < *(second->instance);
        }
        Position^ Position::operator + (Position^ first, Position^ second)
        {
            return ConvertPosition(*(first->instance) + *(second->instance));
        }
        Position^ Position::operator - (Position^ first, Position^ second)
        {
            return ConvertPosition(*(first->instance) - *(second->instance));
        }
        Position^ Position::operator += (Position^ first, Position^ second)
        {
            *(first->instance) += *(second->instance);
            return first;
        }
        Position^ Position::operator -= (Position^ first, Position^ second)
        {
            *(first->instance) -= *(second->instance);
            return first;
        }

        Position^ Position::Rescale(TilePosition^ position)
        {
            return gcnew Position(new BWAPI::Position(*(position->instance)), true);
        }
    }
}
