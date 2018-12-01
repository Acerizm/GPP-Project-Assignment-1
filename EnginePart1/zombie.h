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
	float unitVectorXCor;
	float unitVectorYCor;
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

	//what the fk do i need here
	//1. the player current position
	//2. move the zombie to the player
	// 3. if hit - > zombie move to (0,0) and restart as test
	void attackPlayer(Graphics *graphics, Image &zombieImage, Image &playerImage,float frameTime);

	void getUnitVectorCordinates(Image &zombieImage, Image &playerImage) {
		//ZP (Zombie to Player) == OP - ZP
		
		float currentZombieXCor = zombieImage.getX();
		float currentZombieYCor = zombieImage.getY();

		float currentPlayerXCor = playerImage.getCenterX();
		float currentPlayerYCor = playerImage.getCenterY();

		float ZPXCor = currentPlayerXCor - currentZombieXCor;
		float ZPYCor = currentPlayerYCor - currentZombieYCor;

		float magnitudeOfZP = sqrt((ZPXCor*ZPXCor) + (ZPYCor*ZPYCor));

		unitVectorXCor = ZPXCor / magnitudeOfZP;
		unitVectorYCor = ZPYCor / magnitudeOfZP;
	};


};

#endif