#include "lastManStanding.h"
#include "player.h"
#include "zombie.h"
//=============================================================================
// Constructor
//=============================================================================
LastManStanding::LastManStanding()
{
	mainPlayer = NULL;
	testZombie = NULL;
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
	mainPlayer->setPositionVector(PLAYER_SHOOTING_TILE_IMAGE, GAME_WIDTH, GAME_HEIGHT, PLAYER_SHOOTING_SCALE, PLAYER_SHOOTING_START_FRAME, PLAYER_SHOOTING_END_FRAME, PLAYER_SHOOTING_ANIMATION_DELAY);

	//create zombie here
	testZombie = new Zombie();
	testZombie->initialize(graphics, ZOMBIE_MOVING_TEXTURE, testZombie->ZOMBIE_MOVING_IMAGE);
	testZombie->setPositionVector(testZombie->ZOMBIE_MOVING_IMAGE, GAME_WIDTH, GAME_HEIGHT, ZOMBIE_MOVING_SCALE, ZOMBIE_MOVING_START_FRAME, ZOMBIE_MOVING_END_FRAME, ZOMBIE_MOVING_ANIMATION_DELAY);


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

	//set x or set y for the initial position vector of the object
	LEVEL1_TILE_IMAGE.setScale(LEVEL1_TILE_SCALE);


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
	//update the animation here
	PLAYER_RELOADING_IMAGE.update(frameTime);
	PLAYER_SHOOTING_TILE_IMAGE.update(frameTime);
	healthBarBackGround.update(frameTime);
	healthBarRed.update(frameTime);
	PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(PLAYER_SHOOTING_ANIMATION_DELAY);
	(testZombie->ZOMBIE_MOVING_IMAGE).update(frameTime);
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
	}
	else
	{ 
		PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(999);
	}

	
	
	healthBarGreen.setRect();
	healthBarGreen.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
	healthBarGreen.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);
	healthBarBackGround.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
	healthBarBackGround.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);

	//edit here to chnage the direction of the bullet
	mainPlayer->moveBullet(PLAYER_SHOOTING_TILE_IMAGE, GAME_WIDTH, frameTime);
	testZombie->attackPlayer(graphics, testZombie->ZOMBIE_MOVING_IMAGE, PLAYER_SHOOTING_TILE_IMAGE, frameTime);

	///////////////////////////////////////////////////////////////////////////////
}


//=============================================================================
// Artificial Intelligence
//=============================================================================
void LastManStanding::ai()
{
	//add more zombies here


}

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
	testZombie->ZOMBIE_MOVING_IMAGE.draw();
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

