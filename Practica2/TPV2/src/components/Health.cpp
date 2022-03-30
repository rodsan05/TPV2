#include "Health.h"

#include <cassert>
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

Health::Health() : lives(INI_LIVES)
{
    text_ = &sdlutils().images().at("heart");
}

Health::~Health()
{
}

int Health::actualLives()
{
    return lives;
}

void Health::resetLives()
{
    lives = INI_LIVES;
}

void Health::doDamage(int dmg)
{
    lives -= dmg;
}

void Health::render()
{
    float heartPos = 5;

    assert(text_ != nullptr);

    for (int i = 0; i < lives; i++) {

        Vector2D* pos = new Vector2D(heartPos, 5);
        SDL_Rect dest = build_sdlrect(*pos, HEART_WIDTH, HEART_HEIGHT);
        text_->render(dest);

        heartPos += HEART_WIDTH + 5;
    }
}
