#include "lastManStanding.h"
//=============================================================================
// Constructor
//=============================================================================
LastManStanding::LastManStanding()
{}

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
	// this is where i implement the painter's algorithm here
	Game::initialize(hwnd); // throws GameError

	//implement the LEVEl1_TILE_TEXTURE texture here
	if (!LEVEL1_TILE_TEXTURE.initialize(graphics, LEVEL1_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	//implement the LEVEL1_TILE_IMAGE image here
	if (!LEVEL1_TILE_IMAGE.initialize(graphics, LEVEL1_TILE_WIDTH, LEVEL1_TILE_HEIGHT, 0, &LEVEL1_TILE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing "));

	//implement the player's texture here
	if(!PLAYER_SHOOTING_TILE_TEXTURE.initialize(graphics,PLAYER_SHOOTING_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	//implement the player's image here
	if (!PLAYER_SHOOTING_TILE_IMAGE.initialize(graphics, PLAYER_SHOOTING_WIDTH, PLAYER_SHOOTING_HEIGHT, PLAYER_SHOOTING_COLS, &PLAYER_SHOOTING_TILE_TEXTURE))
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

	//implement the player's reloading texture here
	if (!PLAYER_RELOADING_TEXTURE.initialize(graphics, PLAYER_RELOADING_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	
	//implement the player's reloading image here
	if (!PLAYER_RELOADING_IMAGE.initialize(graphics, PLAYER_RELOADING_WIDTH, PLAYER_RELOADING_HEIGHT, PLAYER_RELOADING_COLS, &PLAYER_RELOADING_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing "));

	//implement the zombie's moving texture here
	if (!ZOMBIE_MOVING_TEXTURE.initialize(graphics,ZOMBIE_MOVING_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	//implement the zombie's moving image here
	if (!ZOMBIE_MOVING_IMAGE.initialize(graphics, ZOMBIE_MOVING_HEIGHT,ZOMBIE_MOVING_WIDTH,ZOMBIE_MOVING_COLS,&ZOMBIE_MOVING_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing image"));

	//set x or set y for the initial position vector of the object
	LEVEL1_TILE_IMAGE.setScale(LEVEL1_TILE_SCALE);
	PLAYER_SHOOTING_TILE_IMAGE.setScale(PLAYER_SHOOTING_SCALE);
	PLAYER_SHOOTING_TILE_IMAGE.setX(GAME_WIDTH / 4);
	PLAYER_SHOOTING_TILE_IMAGE.setY(GAME_WIDTH / 4);
	PLAYER_SHOOTING_TILE_IMAGE.setFrames(PLAYER_SHOOTING_START_FRAME, PLAYER_SHOOTING_END_FRAME);
	PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(PLAYER_SHOOTING_ANIMATION_DELAY);

	PLAYER_RELOADING_IMAGE.setX(GAME_WIDTH / 6);
	PLAYER_RELOADING_IMAGE.setY(GAME_WIDTH / 6);
	PLAYER_RELOADING_IMAGE.setScale(PLAYER_RELOADING_SCALE);
	PLAYER_RELOADING_IMAGE.setFrames(PLAYER_RELOADING_START_FRAME, PLAYER_RELOADING_END_FRAME);
	PLAYER_RELOADING_IMAGE.setFrameDelay(PLAYER_RELOADING_ANIMATION_DELAY);

	healthBarGreen.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
	healthBarGreen.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);
	healthBarBackGround.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
	healthBarBackGround.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);
	healthBarGreen.setScale(0.5f);
	healthBarBackGround.setScale(0.5f);

	//set the zombie's mock location
	ZOMBIE_MOVING_IMAGE.setX(GAME_WIDTH / 10);
	ZOMBIE_MOVING_IMAGE.setY(GAME_WIDTH / 2);
	ZOMBIE_MOVING_IMAGE.setScale(ZOMBIE_MOVING_SCALE);
	ZOMBIE_MOVING_IMAGE.setFrames(ZOMBIE_MOVING_START_FRAME, ZOMBIE_MOVING_END_FRAME);
	ZOMBIE_MOVING_IMAGE.setFrameDelay(ZOMBIE_MOVING_ANIMATION_DELAY);

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
	ZOMBIE_MOVING_IMAGE.update(frameTime);
	if (input->isKeyDown(VK_LEFT))  //left arrow key is pressed down
	{
		PLAYER_SHOOTING_TILE_IMAGE.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - frameTime * PLAYER_MOVEMENTSPEED);
		PLAYER_SHOOTING_TILE_IMAGE.setDegrees(180);
		
	}
	else if (input->isKeyDown(VK_RIGHT)) //right arrow key is pressed down
	{
		PLAYER_SHOOTING_TILE_IMAGE.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() + frameTime * PLAYER_MOVEMENTSPEED);
		PLAYER_SHOOTING_TILE_IMAGE.setDegrees(0);
	}
	else if (input->isKeyDown(VK_UP)) // up arrow key is pressed down
	{
		PLAYER_SHOOTING_TILE_IMAGE.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - frameTime * PLAYER_MOVEMENTSPEED);
		PLAYER_SHOOTING_TILE_IMAGE.setDegrees(270);
	}
	else if (input->isKeyDown(VK_DOWN))// down arrow key is pressed down
	{
		PLAYER_SHOOTING_TILE_IMAGE.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() + frameTime * PLAYER_MOVEMENTSPEED);
		PLAYER_SHOOTING_TILE_IMAGE.setDegrees(90);
	}
	else
	{
		PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(999);
	}
	healthBarGreen.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
	healthBarGreen.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);
	healthBarBackGround.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
	healthBarBackGround.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);
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
	ZOMBIE_MOVING_IMAGE.draw();
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
