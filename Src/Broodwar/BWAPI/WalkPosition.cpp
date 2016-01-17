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
        BWAPI::WalkPosition ConvertWalkPosition(WalkPosition^ position)
        {
            if (position == nullptr)
                return BWAPI::WalkPositions::None;
            return *(position->instance);
        }

        WalkPosition^ ConvertWalkPosition(BWAPI::WalkPosition position)
        {
            return gcnew WalkPosition(position);
        }

        WalkPosition^ ConvertWalkPosition(BWAPI::WalkPosition* position)
        {
            if (position == NULL)
                return nullptr;
            return gcnew WalkPosition(position, false);
        }

        WalkPosition::WalkPosition(BWAPI::WalkPosition *position, bool takeOwnership)
        {
            instance = position;
            dispose = takeOwnership;
        }
        WalkPosition::WalkPosition(BWAPI::WalkPosition position)
        {
            instance = new BWAPI::WalkPosition(position);
            dispose = true;
        }
        WalkPosition::~WalkPosition()
        {
            if (dispose)
                delete instance;
        }
        WalkPosition::!WalkPosition()
        {
            if (dispose)
                delete instance;
        }

        WalkPosition::WalkPosition()
        {
            instance = new BWAPI::WalkPosition();
            dispose = true;
        }
        WalkPosition::WalkPosition(WalkPosition^ copy)
        {
            instance = new BWAPI::WalkPosition(*(copy->instance));
            dispose = true;
        }
        WalkPosition::WalkPosition(int x, int y)
        {
            instance = new BWAPI::WalkPosition(x, y);
            dispose = true;
        }

        int WalkPosition::X::get() { return instance->x; }
        int WalkPosition::Y::get() { return instance->y; }
        bool WalkPosition::IsValid::get() { return instance->isValid(); }
        double WalkPosition::CalcDistance(WalkPosition^ position) { return instance->getDistance(*(position->instance)); }
        int WalkPosition::CalcApproximateDistance(WalkPosition^ position) { return instance->getApproxDistance(*(position->instance)); }
        double WalkPosition::CalcLength() { return instance->getLength(); }
        void WalkPosition::MakeValid() { instance->makeValid(); }
        bool WalkPosition::IsInvalid::get() { return *instance == BWAPI::WalkPositions::Invalid; }
        bool WalkPosition::IsNone::get() { return *instance == BWAPI::WalkPositions::None; }
        bool WalkPosition::IsUnknown::get() { return *instance == BWAPI::WalkPositions::Unknown; }

        int WalkPosition::GetHashCode()
        {
            return instance->x * 397 ^ instance->y;
        }
        bool WalkPosition::Equals(Object^ o)
        {
            WalkPosition^ other = dynamic_cast<WalkPosition^>(o);
            return this->Equals(other);
        }
        bool WalkPosition::Equals(WalkPosition^ other)
        {
            if (ReferenceEquals(nullptr, other))
                return false;
            if (ReferenceEquals(this, other))
                return true;
            return this->instance->x == other->instance->x
                && this->instance->y == other->instance->y;
        }

        bool WalkPosition::operator == (WalkPosition^ first, WalkPosition^ second)
        {
            if (ReferenceEquals(first, second))
                return true;
            if (ReferenceEquals(nullptr, first) || ReferenceEquals(nullptr, second))
                return false;
            return *(first->instance) == *(second->instance);
        }
        bool WalkPosition::operator != (WalkPosition^ first, WalkPosition^ second)
        {
            if (ReferenceEquals(first, second))
                return false;
            if (ReferenceEquals(nullptr, first) || ReferenceEquals(nullptr, second))
                return true;
            return *(first->instance) != *(second->instance);
        }
        bool WalkPosition::operator < (WalkPosition^ first, WalkPosition^ second)
        {
            return *(first->instance) < *(second->instance);
        }
        WalkPosition^ WalkPosition::operator + (WalkPosition^ first, WalkPosition^ second)
        {
            return ConvertWalkPosition(*(first->instance) + *(second->instance));
        }
        WalkPosition^ WalkPosition::operator - (WalkPosition^ first, WalkPosition^ second)
        {
            return ConvertWalkPosition(*(first->instance) - *(second->instance));
        }
        WalkPosition^ WalkPosition::operator * (WalkPosition^ first, int second)
        {
            return ConvertWalkPosition(*(first->instance) * second);
        }
        WalkPosition^ WalkPosition::operator / (WalkPosition^ first, int second)
        {
            return ConvertWalkPosition(*(first->instance) / second);
        }
        WalkPosition^ WalkPosition::operator += (WalkPosition^ first, WalkPosition^ second)
        {
            *(first->instance) += *(second->instance);
            return first;
        }
        WalkPosition^ WalkPosition::operator -= (WalkPosition^ first, WalkPosition^ second)
        {
            *(first->instance) -= *(second->instance);
            return first;
        }
        WalkPosition^ WalkPosition::operator *= (WalkPosition^ first, int second)
        {
            *(first->instance) *= second;
            return first;
        }
        WalkPosition^ WalkPosition::operator /= (WalkPosition^ first, int second)
        {
            *(first->instance) /= second;
            return first;
        }

        WalkPosition^ WalkPosition::Rescale(Position^ position)
        {
            return gcnew WalkPosition(new BWAPI::WalkPosition(*(position->instance)), true);
        }

        WalkPosition^ WalkPosition::Rescale(TilePosition^ position)
        {
            return gcnew WalkPosition(new BWAPI::WalkPosition(*(position->instance)), true);
        }
    }
}
