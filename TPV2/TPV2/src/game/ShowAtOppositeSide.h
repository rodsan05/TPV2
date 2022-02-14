#pragma once
#include "PhysicsComponent.h"
class ShowAtOppositeSide :
    public PhysicsComponent
{
public:
    ShowAtOppositeSide();
    virtual ~ShowAtOppositeSide();

    void update(Container* o) override;
};

