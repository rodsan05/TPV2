#include "ShowAtOppositeSide.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

ShowAtOppositeSide::ShowAtOppositeSide() :
	tr_() {
}

ShowAtOppositeSide::~ShowAtOppositeSide()
{
}

void ShowAtOppositeSide::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void ShowAtOppositeSide::update()
{
	auto& pos = tr_->getPos();
	int width = sdlutils().width();
	int height = sdlutils().height();

	if (pos.getX() > sdlutils().width()) pos.set(Vector2D(0, pos.getY()));
	else if (pos.getX() + tr_->getWidth() < 0) pos.set(Vector2D(width, pos.getY()));

	if (pos.getY() > sdlutils().height()) pos.set(Vector2D(pos.getX(), 0));
	else if (pos.getY() + tr_->getHeight() < 0) pos.set(Vector2D(pos.getX(), height));
}
