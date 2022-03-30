#pragma once
#include "../ecs/Component.h"

class Transform;

struct Gun : public ecs::Component
{
	__CMPID_DECL__(ecs::_GUN)

	Gun() : lastTimeShooted_(0) {}
	virtual ~Gun() {}

	const float BULLET_HEIGHT = 5.0;
	const float BULLET_WIDTH = 20.0;

	const int TIME_BETWEEN_SHOTS = 250;
	const float BULLET_SPEED = 10.0;

	/*void shoot() {
		int time = sdlutils().currRealTime();

		if (time - lastTimeShooted_ >= TIME_BETWEEN_SHOTS) {

			createBullet();
			lastTimeShooted_ = time;
		}
	}
	void createBullet() {
		auto pos = tr_->getPos();

		auto bullet = mngr_->addEntity(ecs::_grp_BULLETS);

		auto tr = bullet->addComponent<Transform>();

		auto w = tr_->getWidth();
		auto h = tr_->getHeight();
		auto posB = pos + Vector2D(w / 2.0f, h / 2.0f) - Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(tr_->getRot()) - Vector2D(2.0f, 10.0f);
		auto bVel = Vector2D(0.0f, -1.0f).rotate(tr_->getRot()) * (tr_->getVel().magnitude() + 5.0f);
		tr->init(posB, bVel, BULLET_HEIGHT, BULLET_WIDTH, tr_->getRot());

		bullet->addComponent<Image>(&sdlutils().images().at("fire"));
		bullet->addComponent<DisableOnExit>();
	}*/

	int lastTimeShooted_;
};

