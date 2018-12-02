
#ifndef _LASTMANSTANDING_H             // prevent multiple definitions if this 
#define _LASTMANSTANDING_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "bullet.h"
#include "player.h"
#include "textDX.h"
#include <list>
using namespace std;

//=============================================================================
// Create game class
//=============================================================================
class LastManStanding : public Game
{
protected:
	// variables
	Bullet *newBullet;

	//the textures & images here
	TextureManager LEVEL1_TILE_TEXTURE;
	Image LEVEL1_TILE_IMAGE;

	TextureManager PLAYER_SHOOTING_TILE_TEXTURE;
	Image PLAYER_SHOOTING_TILE_IMAGE;
	
	TextureManager PLAYER_RELOADING_TEXTURE;
	Image PLAYER_RELOADING_IMAGE;

	TextureManager healthBarRedTexture;
	Image healthBarRed;

	TextureManager healthBarGreenTexture;
	Image healthBarGreen;

	TextureManager healthBarBackGroundTexture;
	Image healthBarBackGround;

	TextureManager BULLET_TEXTURE;
	//Image BULLET_IMAGE;

	Player *mainPlayer;

	float currentHP;

	//there is a need for me to store multiple images inside the array
	list <Bullet*> bulletList;

	TextDX  *hpText;
	bool isPaused;
	bool isDead;
	TextDX *pausedText;
	TextDX *deadText;
public:
	// Constructor
	LastManStanding();

	// Destructor
	virtual ~LastManStanding();

	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
	bool LastManStanding::checkIsDead();
	//Image createNewTempImage();

};

#endif
