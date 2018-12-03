#pragma once
#ifndef _ZOMBIE_H
#define _ZOMBIE_H
#include "image.h"
#include "entity.h"
#include "player.h"
#include <cmath>
using namespace std;

namespace zombieNS {
	//add the spriteData stuff here
	const int ZOMBIE_MOVING_START_FRAME = 0;
	const int ZOMBIE_MOVING_END_FRAME = 9;
	const float ZOMBIE_MOVING_ANIMATION_DELAY = 0.2f;
	const int ZOMBIE_MOVING_COLS = 3;
	const int ZOMBIE_MOVING_HEIGHT = 311;
	const int ZOMBIE_MOVING_WIDTH = 288;
	const float ZOMBIE_MOVING_SCALE = 0.3f;
	const float ZOMBIE_SPEED = 100.0f;
}


class Zombie : public Entity
{
private:
	Image ZOMBIE_MOVING_IMAGE;
	friend class LastManStanding;
	float unitVectorXCor;
	float unitVectorYCor;

public:
	Zombie();
	~Zombie();
	//void initialize(Graphics *graphics, TextureManager &texture, Image &image);
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);

	/*void setPositionVector(Image &image, float x, float y, float zombieScale, int zombieStartFrame, int zombieEndFrame, float zombieFrameDelay) {
		image.setX(x);
		image.setY(y);
		image.setScale(zombieScale);
		image.setFrames(zombieStartFrame, zombieEndFrame);
		image.setFrameDelay(zombieFrameDelay);
	}*/
	void setPositionVector(float x, float y);

	//what the fk do i need here
	//1. the player current position
	//2. move the zombie to the player
	// 3. if hit - > zombie move to (0,0) and restart as test
	//void attackPlayer(Graphics *graphics, Image &zombieImage, Image &playerImage,float frameTime);
	void attackPlayer(Player *mainPlayer, float frameTime);

	void getUnitVectorCoordinates(Player *mainPlayer);


};

#endif