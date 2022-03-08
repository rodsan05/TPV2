#include "FramedImage.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

FramedImage::FramedImage() : tr_(), text_(), frameHeight_(0), frameWidth_(0), currentFrame_(0), columns_(0), rows_(0), timeBetweenFrames_(0), 
							lastTimeFrameChanged_(0)
{
}

FramedImage::FramedImage(Texture* text, int rows_, int columns, int timeBetweenFrames, int frame) : tr_(), text_(text), currentFrame_(frame),
																									columns_(columns), rows_(rows_), 
																									timeBetweenFrames_(timeBetweenFrames),
																									lastTimeFrameChanged_(0)
{
	assert(text_ != nullptr);

	frameHeight_ = text->height() / rows_;
	frameWidth_ = text->width() / columns_;
}

FramedImage::~FramedImage()
{
}

void FramedImage::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void FramedImage::render()
{
	int column = currentFrame_ % columns_;
	int row = currentFrame_ / columns_;

	Vector2D* posSrc = new Vector2D(column, row);

	SDL_Rect src = build_sdlrect(*posSrc, frameWidth_, frameHeight_);
	SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getWidth(),
		tr_->getHeight());

	assert(text_ != nullptr);
	text_->render(src, dest, tr_->getRot());
}

void FramedImage::update()
{
	
}
