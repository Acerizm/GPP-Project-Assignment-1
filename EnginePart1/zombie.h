#pragma once
#ifndef _ZOMBIE_H
#define _ZOMBIE_H
#include "image.h"
using namespace std;


class Zombie 
{
private:
	Image ZOMBIE_MOVING_IMAGE;
	friend class LastManStanding;

public:
	Zombie();
	~Zombie();
	void initialize(Graphics *graphics, TextureManager &texture, Image &image);
	void setPositionVector(Image &image, float GAME_WIDTH, float GAME_HEIGHT, float zombieScale, int zombieStartFrame, int zombieEndFrame, float zombieFrameDelay) {

		//change the setX and setY according to my game design algorithm later
		image.setX(50);
		image.setY(50);
		image.setScale(zombieScale);
		image.setFrames(zombieStartFrame, zombieEndFrame);
		image.setFrameDelay(zombieFrameDelay);
	}
};

#endif