#pragma once
#ifndef _ZOMBIE_H
#define _ZOMBIE_H
#include "image.h"
#include <cmath>
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

		//check which quadrant the zombie is in
		//
		//change the setX and setY according to my game design algorithm later
		image.setX(GAME_WIDTH - 50);
		image.setY(GAME_HEIGHT - 50);
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

		//check which part of the quadrant the zombie is in

		//ZP (Zombie to Player) == OP - OZ
		
		float currentZombieXCor = zombieImage.getX();
		float currentZombieYCor = zombieImage.getY();

		float currentPlayerXCor = playerImage.getCenterX();
		float currentPlayerYCor = playerImage.getCenterY();

		float ZPXCor = currentPlayerXCor - currentZombieXCor;
		float ZPYCor = currentPlayerYCor - currentZombieYCor;

		float magnitudeOfZP = sqrt((ZPXCor*ZPXCor) + (ZPYCor*ZPYCor));

		unitVectorXCor = ZPXCor / magnitudeOfZP;
		unitVectorYCor = ZPYCor / magnitudeOfZP;

		//find the coordinates of ZP'
		// where p' is 90 degrees above P
		float PprimeXCor = currentPlayerXCor;
		float PprimeYCor = currentZombieYCor;

		//ZP' = OP' - OZ
		float ZPprimeXCor = PprimeXCor - currentZombieXCor;
		float ZPprimeYCor = PprimeYCor - currentZombieYCor;

		//get the scalar product to find the angle
		// dot product of ZP' * ZP = 
		float dotProdutValue = (ZPprimeXCor*ZPXCor) + (ZPprimeYCor*ZPYCor);
		//get the magnitude of ZP'
		float magnitudeOfZPrime = sqrt((ZPprimeXCor*ZPprimeXCor) + (ZPprimeYCor*ZPprimeYCor));
		float angle = acos(dotProdutValue / (magnitudeOfZPrime*magnitudeOfZP)) * (180/PI);

		zombieImage.setDegrees(angle);

	};


};

#endif