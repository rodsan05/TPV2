#pragma once
#include "../ecs/Component.h"

class Transform;

class DeAcceleration : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::_DEACCELERATION)
	
	DeAcceleration();
	DeAcceleration(float deacceleration);
	~DeAcceleration();

	void initComponent() override;
	void update() override;

private:
	Transform* tr_;

	float deaccelValue_;
};

