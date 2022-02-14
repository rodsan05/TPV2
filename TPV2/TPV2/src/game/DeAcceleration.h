#pragma once
#include "PhysicsComponent.h"
class DeAcceleration :
    public PhysicsComponent
{
public:
    DeAcceleration(float deaccelValue){
        deaccelValue_ = deaccelValue;
    };
    virtual ~DeAcceleration() {};

    void update(Container* o) override;

private:

    float deaccelValue_;
};

