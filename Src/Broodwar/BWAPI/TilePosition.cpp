#pragma unmanaged

#include <stddef.h>

#pragma managed

#include "Position.h"
#include "TilePosition.h"
#include "WalkPosition.h"

namespace BroodWar
{
	namespace Api
	{
        BWAPI::TilePosition ConvertTilePosition(TilePosition^ position)
        {
            if (position == nullptr)
                return BWAPI::TilePositions::None;
            return *(position->instance);
        }

        TilePosition^ ConvertTilePosition(BWAPI::TilePosition position)
        {
            return gcnew TilePosition(position);
        }

        TilePosition^ ConvertTilePosition(BWAPI::TilePosition* position)
        {
            if (position == NULL)
                return nullptr;
            return gcnew TilePosition(position, false);
        }

        TilePosition::TilePosition(BWAPI::TilePosition *position, bool takeOwnership)
        {
            instance = position;
            dispose = takeOwnership;
        }
        TilePosition::TilePosition(BWAPI::TilePosition position)
        {
            instance = new BWAPI::TilePosition(position);
            dispose = true;
        }
        TilePosition::~TilePosition()
        {
            if (dispose)
                delete instance;
        }
        TilePosition::!TilePosition()
        {
            if (dispose)
                delete instance;
        }

        TilePosition::TilePosition()
        {
            instance = new BWAPI::TilePosition();
            dispose = true;
        }
        TilePosition::TilePosition(TilePosition^ copy)
        {
            instance = new BWAPI::TilePosition(*(copy->instance));
            dispose = true;
        }
        TilePosition::TilePosition(int x, int y)
        {
            instance = new BWAPI::TilePosition(x, y);
            dispose = true;
        }

        int TilePosition::X::get() { return instance->x; }
        int TilePosition::Y::get() { return instance->y; }
        bool TilePosition::IsValid::get() { return instance->isValid(); }
        double TilePosition::CalcDistance(TilePosition^ position) { return instance->getDistance(*(position->instance)); }
        int TilePosition::CalcApproximateDistance(TilePosition^ position) { return instance->getApproxDistance(*(position->instance)); }
        double TilePosition::CalcLength() { return instance->getLength(); }
        void TilePosition::MakeValid() { instance->makeValid(); }
        bool TilePosition::IsInvalid::get() { return *instance == BWAPI::TilePositions::Invalid; }
        bool TilePosition::IsNone::get() { return *instance == BWAPI::TilePositions::None; }
        bool TilePosition::IsUnknown::get() { return *instance == BWAPI::TilePositions::Unknown; }

        int TilePosition::GetHashCode()
        {
            return instance->x * 397 ^ instance->y;
        }
        bool TilePosition::Equals(Object^ o)
        {
            TilePosition^ other = dynamic_cast<TilePosition^>(o);
            return this->Equals(other);
        }
        bool TilePosition::Equals(TilePosition^ other)
        {
            if (ReferenceEquals(nullptr, other))
                return false;
            if (ReferenceEquals(this, other))
                return true;
            return this->instance->x == other->instance->x
                && this->instance->y == other->instance->y;
        }

        bool TilePosition::operator == (TilePosition^ first, TilePosition^ second)
        {
            if (ReferenceEquals(first, second))
                return true;
            if (ReferenceEquals(nullptr, first) || ReferenceEquals(nullptr, second))
                return false;
            return *(first->instance) == *(second->instance);
        }
        bool TilePosition::operator != (TilePosition^ first, TilePosition^ second)
        {
            if (ReferenceEquals(first, second))
                return false;
            if (ReferenceEquals(nullptr, first) || ReferenceEquals(nullptr, second))
                return true;
            return *(first->instance) != *(second->instance);
        }
        bool TilePosition::operator < (TilePosition^ first, TilePosition^ second)
        {
            return *(first->instance) < *(second->instance);
        }
        TilePosition^ TilePosition::operator + (TilePosition^ first, TilePosition^ second)
        {
            return ConvertTilePosition(*(first->instance) + *(second->instance));
        }
        TilePosition^ TilePosition::operator - (TilePosition^ first, TilePosition^ second)
        {
            return ConvertTilePosition(*(first->instance) - *(second->instance));
        }
        TilePosition^ TilePosition::operator * (TilePosition^ first, int second)
        {
            return ConvertTilePosition(*(first->instance) * second);
        }
        TilePosition^ TilePosition::operator / (TilePosition^ first, int second)
        {
            return ConvertTilePosition(*(first->instance) / second);
        }
        TilePosition^ TilePosition::operator += (TilePosition^ first, TilePosition^ second)
        {
            *(first->instance) += *(second->instance);
            return first;
        }
        TilePosition^ TilePosition::operator -= (TilePosition^ first, TilePosition^ second)
        {
            *(first->instance) -= *(second->instance);
            return first;
        }
        TilePosition^ TilePosition::operator *= (TilePosition^ first, int second)
        {
            *(first->instance) *= second;
            return first;
        }
        TilePosition^ TilePosition::operator /= (TilePosition^ first, int second)
        {
            *(first->instance) /= second;
            return first;
        }

        TilePosition^ TilePosition::Rescale(Position^ position)
        {
            return gcnew TilePosition(new BWAPI::TilePosition(*(position->instance)), true);
        }

        TilePosition^ TilePosition::Rescale(WalkPosition^ position)
        {
            return gcnew TilePosition(new BWAPI::TilePosition(*(position->instance)), true);
        }
    }
}
