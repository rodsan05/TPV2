// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"
#include "../ecs/ecs.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/VirtualTimer.h"

struct Transform;

namespace ecs {
	class Entity;
}

class BulletSystem: public ecs::System {
public:
	__SYSID_DECL__(ecs::_sys_BULLET)

	void receive(const Message& m) override;
	BulletSystem();
	virtual ~BulletSystem();


	void initSystem() override;
	void update() override;
private:
	
	const float BULLET_HEIGHT = 5.0;
	const float BULLET_WIDTH = 20.0;

	const int TIME_BETWEEN_SHOTS = 250;

	// Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
	// juego, como en la práctica 1. Recuerda que la rotación de la bala sería
	// vel.angle(Vector2D(0.0f,-1.0f))
	void shoot(Vector2D pos, Vector2D vel, double width, double height);

	// Para gestionar el mensaje de que ha habido un choque entre una bala y un
	// asteroide. Desactivar la bala “b”.
	void onCollision_BulletAsteroid(ecs::Entity* b);

	void onRoundOver();

	void onRoundStart();

	void checkShootInput();

	bool active_;

	ecs::Entity* fighter_;
	Transform* fighterTr_;

	VirtualTimer bulletTimer_;
};

