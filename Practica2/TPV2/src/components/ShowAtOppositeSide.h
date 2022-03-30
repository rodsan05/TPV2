#pragma once
#include "../ecs/Component.h"

class Transform;

class ShowAtOppositeSide : public ecs::Component
{
public:
    __CMPID_DECL__(ecs::_ONBORDER)

    ShowAtOppositeSide();
    virtual ~ShowAtOppositeSide();

    void initComponent() override;
    void update() override;

private:
    Transform* tr_;
};

