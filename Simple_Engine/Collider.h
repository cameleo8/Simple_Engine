#pragma once


class Collider {
public:
    float x, y;
    bool Solid = false;
    virtual bool IsColliding(Collider* pOther) = 0;
};

class AABBCollider : public Collider {
public:
    float xSize;
    float ySize;
    float xMin;
    float xMax;
    float yMin;
    float yMax;
    bool IsColliding(Collider* pOther) override;
};

