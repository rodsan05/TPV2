#include "ShowAtOppositeSide.h"

#include "../sdlutils/SDLUtils.h"
#include "Container.h"

ShowAtOppositeSide::ShowAtOppositeSide()
{
}

ShowAtOppositeSide::~ShowAtOppositeSide()
{
}

void ShowAtOppositeSide::update(Container* o)
{
	Vector2D pos = o->getPos();
	int width = sdlutils().width();
	int height = sdlutils().height();

	if (pos.getX() > sdlutils().width()) o->getPos().set(Vector2D(0, pos.getY()));
	else if (pos.getX() - width < 0) o->getPos().set(Vector2D(width, pos.getY()));

	if (pos.getY() > sdlutils().height()) o->getPos().set(Vector2D(pos.getX(), 0));
	else if (pos.getY() - height < 0) o->getPos().set(Vector2D(pos.getX(), height));
}
