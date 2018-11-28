#pragma once
#ifndef _PLAYER_H             // prevent multiple definitions if this 
#define _PLAYER_H             // ..file is included in more than one place

//#include "game.h"
//#include "textureManager.h"
//#include "image.h"
//#include "lastManStanding.h"
#include "bullet.h"
#include <vector>
#define VECTOR2 D3DXVECTOR2
using namespace std;

/*

*/

// what do i need to store in the player class?
// 1. the texture of the player
// 2. the image of the player
// 3. store the list of bullets into a dictionary

class Player 
{
private:
	TextureManager PLAYER_SHOOTING_TEXTURE;
	Image PLAYER_SHOOTING_IMAGE;
	vector<class Bullet*> bulletList;

public:
	Player();
	~Player();
	void shootBullet(VECTOR2 player);
	void initialize(Graphics *graphics, const char* filepath, TextureManager &texture, Image &image);
	void setPositionVector(Image &image, float GAME_WIDTH,float GAME_HEIGHT,float playerScale, int playerStartFrame,int playerEndFrame,float playerFrameDelay) {
		image.setX(GAME_WIDTH / 10);
		image.setY(GAME_HEIGHT / 10);
		image.setScale(playerScale);
		image.setFrames(playerStartFrame, playerEndFrame);
		image.setFrameDelay(playerFrameDelay);
	}
};



#endif