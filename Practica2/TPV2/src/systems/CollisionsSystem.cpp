// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/messages.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "GameCtrlSystem.h"

CollisionsSystem::CollisionsSystem() :
		fighterTr_(nullptr), active_(false) {
}

CollisionsSystem::~CollisionsSystem() {
}

void CollisionsSystem::initSystem() {
	
	fighterTr_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_FIGHTER));
	
	assert(fighterTr_ != nullptr);
}

void CollisionsSystem::receive(const Message& m) {
	
	switch (m.id) {
	case _m_ROUND_START:
		active_ = true;
		break;
	case _m_GAME_START:
		active_ = true;
		break;
	case _m_ROUND_OVER:
		active_ = false;
		break;
	case _m_GAME_OVER:
		active_ = false;
		break;
	default:
		break;
	}
}

void CollisionsSystem::update() {

	if (active_) {

		auto& asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);
		auto& bullets = mngr_->getEntities(ecs::_grp_BULLETS);

		auto n = asteroids.size();
		auto p = bullets.size();

		for (auto i = 0u; i < n; i++) {

			auto a = asteroids[i];
			if (mngr_->isAlive(a)) {

				//collision bullets
				auto aTr = mngr_->getComponent<Transform>(a);

				for (auto j = 0u; j < p; j++) {

					auto b = bullets[j];
					if (mngr_->isAlive(b)) {

						auto bTr = mngr_->getComponent<Transform>(b);

						if (Collisions::collidesWithRotation(aTr->pos_, aTr->width_, aTr->height_, aTr->rot_,
							bTr->pos_, bTr->width_, bTr->height_, bTr->rot_)) {

							Message m;

							m.collision_bullet_fighter.asteroid = a;
							m.collision_bullet_fighter.bullet = b;
							m.id = _m_BULLET_HIT_ASTEROID;

							mngr_->send(m);
						}
					}
				}

				//player
				if (Collisions::collidesWithRotation(aTr->pos_, aTr->width_, aTr->height_, aTr->rot_,
					fighterTr_->pos_, fighterTr_->width_, fighterTr_->height_, fighterTr_->rot_)) {

					Message m;

					m.id = _m_ASTEROID_HIT_FIGHTER;

					mngr_->send(m);
				}
			}
		}
	}
}