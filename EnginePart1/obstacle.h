#pragma once
#ifndef _OBSTACLE_H
#define _OBSTACLE_H
#include "image.h"
#include "entity.h"
#include "player.h"
#include <cmath>
#include "textDX.h"
using namespace std;

namespace obstacleNS {
	//add the spriteData stuff here
	const int BARREL_START_FRAME = 0;
	const int BARREL_END_FRAME = 0;
	const float BARREL_ANIMATION_DELAY = 0.0;
	const int BARREL_COLS = 0;
	const int BARREL_HEIGHT = 173;
	const int BARREL_WIDTH = 154;
	const float BARREL_SCALE = 0.5f;
}


class Obstacle : public Entity
{
private:
	Image OBSTACLE_IMAGE;
	friend class LastManStanding;

public:
	Obstacle();
	~Obstacle();
	//void initialize(Graphics *graphics, TextureManager &texture, Image &image);
	virtual bool initialize(Game *gamePtr,TextureManager *textureM, int ObstacleType);

	float getSpriteDataX() {
		return spriteData.x;
	}

	void setSpriteDataX(float x) {
		spriteData.x = x;
	}

	float getSpriteDataY() {
		return spriteData.y;
	}

	void setSpriteDataY(float y) {
		spriteData.y = y;
	}

};

#endif
