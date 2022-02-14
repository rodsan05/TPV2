#pragma once
#include "InputComponent.h"

#include <SDL.h>
class FighterCtrl :
    public InputComponent
{
public:
    FighterCtrl(float speed, float thrust, float speedLimit){
        rotationSpeed_ = speed;
        thrust_ = thrust;
        speedLimit_ = speedLimit;
    }
    virtual ~FighterCtrl() {
    }

    void handleInput(Container* o) override;
private:

    float rotationSpeed_;
    float thrust_;
    float speedLimit_;
};

