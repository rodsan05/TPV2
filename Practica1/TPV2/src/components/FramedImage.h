#pragma once
#include "../ecs/Component.h"

class Transform;
class Texture;

class FramedImage : public ecs::Component
{
public:

	__CMPID_DECL__(ecs::_IMAGE)

	FramedImage();
	FramedImage(Texture* text, int rows_, int columns, int timeBetweenFrames, int nFrames, int frame = 0);
	~FramedImage();

	void setTexture(Texture* text) {
		text_ = text;
	}

	void initComponent() override;
	void render() override;
	void update() override;

private:
	Transform* tr_;
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

