#include "lastManStanding.h"
#include "player.h"
#include "textDX.h"
#include <string>
#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;
//=============================================================================
// Constructor
//=============================================================================
LastManStanding::LastManStanding()
{
	mainPlayer = NULL;
	hpText = new TextDX();
	isPaused = false;
	pausedText = new TextDX();
	isDead = false;
	deadText = new TextDX();
}

//=============================================================================
// Destructor
//=============================================================================
LastManStanding::~LastManStanding()
{
	releaseAll();           // call onLostDevice() for every graphics item
}
//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void LastManStanding::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	//create player here
	mainPlayer = new Player();
	
	mainPlayer->initialize(graphics, PLAYER_SHOOTING_TILE_TEXTURE, PLAYER_SHOOTING_TILE_IMAGE);

	//implement the LEVEl1_TILE_TEXTURE texture here
	if (!LEVEL1_TILE_TEXTURE.initialize(graphics, LEVEL1_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	//implement the LEVEL1_TILE_IMAGE image here
	if (!LEVEL1_TILE_IMAGE.initialize(graphics, LEVEL1_TILE_WIDTH, LEVEL1_TILE_HEIGHT, 0, &LEVEL1_TILE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing "));
	
	if(!healthBarRedTexture.initialize(graphics,HEALTHBARRED_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarRed texture"));

	if(!healthBarRed.initialize(graphics,256,32,1,&healthBarRedTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarRed"));

	if (!healthBarGreenTexture.initialize(graphics, HEALTHBARGREEN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarGreen texture"));

	if (!healthBarGreen.initialize(graphics, 256, 32, 1, &healthBarGreenTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarGreen"));

	if (!healthBarBackGroundTexture.initialize(graphics, HEALTHBARBACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarBackGround texture"));

	if (!healthBarBackGround.initialize(graphics, 256, 32, 1, &healthBarBackGroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarBackGround"));

	if (hpText->initialize(graphics, 15, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hpText font"));

	if (pausedText->initialize(graphics, 30, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pausedText font"));
	if (deadText->initialize(graphics, 30, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pausedText font"));

	mciSendString("open \"audio\\deathSong.wav\" type waveaudio alias sound", NULL, 0, NULL);
	mciSendString("open \"audio\\backGroundMusic.wav\" type waveaudio alias backGroundMusic", NULL, 0, NULL);

	//set x or set y for the initial position vector of the object
	LEVEL1_TILE_IMAGE.setScale(LEVEL1_TILE_SCALE);

	mainPlayer->setPositionVector(PLAYER_SHOOTING_TILE_IMAGE, GAME_WIDTH, GAME_HEIGHT, PLAYER_SHOOTING_SCALE, PLAYER_SHOOTING_START_FRAME, PLAYER_SHOOTING_END_FRAME,PLAYER_SHOOTING_ANIMATION_DELAY);


	currentHP = PLAYER_MAXHP;

	healthBarGreen.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
	healthBarGreen.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);
	healthBarBackGround.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
	healthBarBackGround.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);
	healthBarGreen.setScale(0.5f);
	healthBarBackGround.setScale(0.5f);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void LastManStanding::update()
{
	mciSendString("play backGroundMusic", NULL, 0, NULL);
	if (isPaused)
	{
		if (input->wasKeyPressed(VK_F2))
		{
			isPaused = !isPaused;
		}
	}
	else if (isDead)
	{
		mciSendString("stop backGroundMusic", NULL, 0, NULL);
		mciSendString("play sound", NULL, 0, NULL);
		
		//PlaySound("audio\\deathSong.wav", NULL, SND_FILENAME);
		if (input->wasKeyPressed(VK_ESCAPE))
		{
			PostQuitMessage(0);
		}
		
	}
	else
	{
		//update the animation here
		PLAYER_RELOADING_IMAGE.update(frameTime);
		PLAYER_SHOOTING_TILE_IMAGE.update(frameTime);
		healthBarBackGround.update(frameTime);
		healthBarRed.update(frameTime);
		PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(PLAYER_SHOOTING_ANIMATION_DELAY);



		////////////////////////////////////////////////////////////////////////////
		if (input->isKeyDown(VK_LEFT))  //left arrow key is pressed down
		{
			PLAYER_SHOOTING_TILE_IMAGE.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - frameTime * PLAYER_MOVEMENTSPEED);
			PLAYER_SHOOTING_TILE_IMAGE.setDegrees(180);

			if (input->isKeyDown(VK_SPACE))
			{
				PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(0.05f);
			}

		}
		else if (input->isKeyDown(VK_RIGHT)) //right arrow key is pressed down
		{
			PLAYER_SHOOTING_TILE_IMAGE.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() + frameTime * PLAYER_MOVEMENTSPEED);
			PLAYER_SHOOTING_TILE_IMAGE.setDegrees(0);


			if (input->isKeyDown(VK_SPACE))
			{
				PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(0.05f);
			}
		}
		else if (input->isKeyDown(VK_UP)) // up arrow key is pressed down
		{
			PLAYER_SHOOTING_TILE_IMAGE.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - frameTime * PLAYER_MOVEMENTSPEED);
			PLAYER_SHOOTING_TILE_IMAGE.setDegrees(270);

			if (input->isKeyDown(VK_SPACE))
			{
				PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(0.05f);
			}
		}
		else if (input->isKeyDown(VK_DOWN))// down arrow key is pressed down
		{
			PLAYER_SHOOTING_TILE_IMAGE.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() + frameTime * PLAYER_MOVEMENTSPEED);
			PLAYER_SHOOTING_TILE_IMAGE.setDegrees(90);

			if (input->isKeyDown(VK_SPACE))
			{
				PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(0.05f);
			}
		}
		else if (input->wasKeyPressed(VK_SPACE))
		{
			//Shooting animation
			PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(0.05f);
			//To minus HP of Player by 5.
			currentHP = currentHP - 5;
			float currentHpBarPercentage = currentHP / PLAYER_MAXHP;
			healthBarGreen.setPercentage(currentHpBarPercentage);

			mainPlayer->shootBullet(graphics, BULLET_TEXTURE, PLAYER_SHOOTING_TILE_IMAGE);

		}
		else if (input->wasKeyPressed(VK_F2))
		{
			//To Recover 5 health.
			currentHP = currentHP + 5;
			float currentHpBarPercentage = currentHP / PLAYER_MAXHP;
			healthBarGreen.setPercentage(currentHpBarPercentage);
			isPaused = !isPaused;
		}
		else
		{
			PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(999);
		}


		if (currentHP <= 0)
		{
			isDead = true;
		}
		else
		{
			isDead = false;
		}
		healthBarGreen.setRect();
		healthBarGreen.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
		healthBarGreen.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);
		healthBarBackGround.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
		healthBarBackGround.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);

		//edit here to chnage the direction of the bullet
		mainPlayer->moveBullet(PLAYER_SHOOTING_TILE_IMAGE, GAME_WIDTH, frameTime);
	}

	///////////////////////////////////////////////////////////////////////////////
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void LastManStanding::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void LastManStanding::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void LastManStanding::render()
{
	// need to de-structure the method here as the player has multiple animations
	// aka need to render again?

	graphics->spriteBegin();                // begin drawing sprites

	LEVEL1_TILE_IMAGE.draw();
	PLAYER_SHOOTING_TILE_IMAGE.draw();
	PLAYER_RELOADING_IMAGE.draw();
	healthBarBackGround.draw();
	healthBarGreen.draw();
	mainPlayer->drawBullets();
	hpText->setFontColor(graphicsNS::WHITE);
	hpText->print(to_string((int)(currentHP)) + "/" + to_string((int)(PLAYER_MAXHP)), PLAYER_SHOOTING_TILE_IMAGE.getX(), PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);
	if (isPaused)
	{
		pausedText->setFontColor(graphicsNS::RED);
		pausedText->print("Game is Paused Press F2 to Resume", 0,0);
	}
	if (isDead)
	{
		deadText->setFontColor(graphicsNS::RED);
		deadText->print("YOU DIED! Press Esc to close game", 0, 0);
	}
	graphics->spriteEnd();                  // end drawing sprites


}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void LastManStanding::releaseAll()
{
	LEVEL1_TILE_TEXTURE.onLostDevice();

	Game::releaseAll();
	return;

}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void LastManStanding::resetAll()
{
	LEVEL1_TILE_TEXTURE.onResetDevice();

	Game::resetAll();
	return;

}
bool LastManStanding::checkIsDead()
{
	return isDead;
}

