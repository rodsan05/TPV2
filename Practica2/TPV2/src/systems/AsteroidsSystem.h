// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"
#include "../ecs/ecs.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/VirtualTimer.h"

#include <SDL_stdinc.h>

struct Transform;

namespace ecs {
	class Entity;
}

class AsteroidsSystem: public ecs::System {
public:
	__SYSID_DECL__(ecs::_sys_ASTEROIDS)

	void receive(const Message& m) override;
	AsteroidsSystem();
	virtual ~AsteroidsSystem();


	void initSystem() override;
	void update() override;
private:
	
	const float ASTEROID_HEIGHT = 5.0;
	
	const int TIME_BETWEEN_ASTEROIDS = 5000;

	// Para gestionar el mensaje de que ha habido un choque entre una bala y un
	// asteroide. Desactivar la bala “b”.
	void onCollision_AsteroidBullet(ecs::Entity* a);

	void onRoundOver();

	void onRoundStart();

	void createAsteroids(int n);
	void createAsteroid(int type, int gens, int x = -1, int y = -1, Vector2D vel = Vector2D(0, 0));

	void addAsteroidFrequently();
	void destroyAllAsteroids();

	bool active_;

	Uint8 numOfAsteroids_;

	Transform* fighterTr_;

	VirtualTimer asteroidsTimer_;
};

