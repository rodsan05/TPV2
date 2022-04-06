#pragma once
#include "../ecs/Component.h"
#include <cassert>

struct Transform;
class Texture;

struct FramedImage : public ecs::Component
{
	__CMPID_DECL__(ecs::_IMAGE)

	FramedImage(Texture* text, int rows_, int columns, int timeBetweenFrames, int nFrames, int frame = 0) : text_(text), currentFrame_(frame),
		columns_(columns), rows_(rows_), timeBetweenFrames_(timeBetweenFrames), lastTimeFrameChanged_(0), nFrames_(nFrames) {
	
		assert(text_ != nullptr);

		frameHeight_ = text->height() / rows_;
		frameWidth_ = text->width() / columns_;
	};
	virtual ~FramedImage() {};

	void setTexture(Texture* text) {
		text_ = text;
	}

	Texture* text_;

	float frameHeight_;
	float frameWidth_;

	int nFrames_;

	int columns_;
	int rows_;
	int currentFrame_;

	int timeBetweenFrames_;

	int lastTimeFrameChanged_;
};

