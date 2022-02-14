#include "DeAcceleration.h"

#include "../sdlutils/SDLUtils.h"
#include "Container.h"
void DeAcceleration::update(Container* o)
{
	o->getVel().set(o->getVel()*deaccelValue_);
}
