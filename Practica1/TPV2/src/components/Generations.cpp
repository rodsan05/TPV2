#include "Generations.h"

#include "../sdlutils/SDLUtils.h"

Generations::Generations()
{
    generations_ = sdlutils().rand().nextInt(1, 4);
}

Generations::Generations(int n)
{
    generations_ = n;
}

Generations::~Generations()
{
}

int Generations::nGenerations()
{
    return generations_;
}

void Generations::setGenerations(int n)
{
    generations_ = n;
}
