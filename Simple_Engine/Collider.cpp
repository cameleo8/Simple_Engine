#include "Collider.h"

bool AABBCollider::IsColliding(Collider* pOther) {
    if (auto* aabb = dynamic_cast<AABBCollider*>(pOther)) {
        return !(xMax < aabb->xMin || xMin > aabb->xMax ||
            yMax < aabb->yMin || yMin > aabb->yMax);
    }
    
    return false;
    return 0;
}