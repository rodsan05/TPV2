#pragma once
#include "../ecs/Component.h"

class Transform;

class Gun : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::_GUN)

	Gun();
	virtual ~Gun();

	void initComponent() override;
	void update() override;

private:

	const float BULLET_HEIGHT = 5.0;
	const float BULLET_WIDTH = 20.0;

	const int TIME_BETWEEN_SHOTS = 250;
	const float BULLET_SPEED = 10.0;

	Transform* tr_;

	void shoot();
	void createBullet();

	int lastTimeShooted_;
};

