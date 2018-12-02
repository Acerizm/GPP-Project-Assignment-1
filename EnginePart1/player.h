#pragma once
#ifndef _PLAYER_H             // prevent multiple definitions if this 
#define _PLAYER_H             // ..file is included in more than one place

//#include "game.h"
//#include "textureManager.h"
//#include "image.h"
//#include "lastManStanding.h"
#include "bullet.h"
#include <list>
#include "entity.h"
#define VECTOR2 D3DXVECTOR2
using namespace std;

namespace playerNS
{
	const int PLAYER_SHOOTING_START_FRAME = 0;
	const int PLAYER_SHOOTING_END_FRAME = 2;
	const float PLAYER_SHOOTING_ANIMATION_DELAY = 0.2f;
	const int PLAYER_SHOOTING_COLS = 3;
	const int PLAYER_SHOOTING_HEIGHT = 206;
	const int PLAYER_SHOOTING_WIDTH = 312;
	const float PLAYER_SHOOTING_SCALE = 0.3f;
}


class Player : public Entity
{
private:
	TextureManager PLAYER_SHOOTING_TEXTURE;
	Image PLAYER_SHOOTING_IMAGE;
	//vector<Bullet*> bulletList;
	Bullet* newBullet;
	list<Bullet*> BULLET_LIST;

	//take in lastManStanding to use graphics xd
	//LastManStanding last_Man_Standing;

public:
	Player();
	~Player();
	void shootBullet(Graphics*graphics,TextureManager &texture,Image &image);
	void moveBullet(Image &playerImage, float gameWidth, float frameTime);
	void drawBullets();
	void initialize(Graphics *graphics, TextureManager &texture, Image &image);
	void setPositionVector(Image &image, float GAME_WIDTH,float GAME_HEIGHT,float playerScale, int playerStartFrame,int playerEndFrame,float playerFrameDelay) {
		image.setX(GAME_WIDTH / 2);
		image.setY(GAME_HEIGHT / 2);
		image.setScale(playerScale);
		image.setFrames(playerStartFrame, playerEndFrame);
		image.setFrameDelay(playerFrameDelay);
	}
};




#endif