// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h>
#include "../sdlutils/Texture.h"
#include <cassert>

struct Image: public ecs::Component {

	__CMPID_DECL__(ecs::_IMAGE)

	Image() : tex_() {}
	Image(Texture* tex) : tex_(tex) {}
	virtual ~Image() {}

	void setTexture(Texture *tex) {
		tex_ = tex;
	}

	/*void render() {

		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getWidth(),
			tr_->getHeight());

		assert(tex_ != nullptr);
		tex_->render(dest, tr_->getRot());
	}*/

	Texture *tex_;
};

