#include "Gun.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "Image.h"
#include "DisableOnExit.h"

Gun::Gun() : tr_(), lastTimeShooted_(0)
{
}

Gun::~Gun()
{
}

void Gun::initComponent()
{
	tr_ = ent_->getComponent<Transform>();

	assert(tr_ != nullptr);
}

void Gun::update()
{
	auto& ihdlr = ih();

	if (ihdlr.keyDownEvent()) {

		if (ihdlr.isKeyDown(SDLK_s)) {
			
			shoot();
		}
	}
}

void Gun::shoot()
{
	int time = sdlutils().currRealTime();

	if (time - lastTimeShooted_ >= TIME_BETWEEN_SHOTS) {
	
		createBullet();
		lastTimeShooted_ = time;
	}
}

void Gun::createBullet()
{
	auto pos = tr_->getPos();

	auto bullet = mngr_->addEntity(ecs::_grp_BULLETS);

	auto tr =  bullet->addComponent<Transform>();

	auto w = tr_->getWidth();
	auto h = tr_->getHeight();
	auto posB = pos + Vector2D(w / 2.0f, h / 2.0f) - Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(tr_->getRot()) - Vector2D(2.0f, 10.0f);
	auto bVel = Vector2D(0.0f, -1.0f).rotate(tr_->getRot()) * (tr_->getVel().magnitude() + 5.0f);
	tr->init(posB, bVel, BULLET_HEIGHT, BULLET_WIDTH, tr_->getRot());

	bullet->addComponent<Image>(&sdlutils().images().at("fire"));
	bullet->addComponent<DisableOnExit>();
}
