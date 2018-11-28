#include "lastManStanding.h"
#include "player.h"
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
	Game::initialize(hwnd); // throws GameError

	//create player here
	Player *newPlayer = new Player();
	
	/*newBullet = new Bullet();

	newBullet->initialize(graphics, BULLET_TILE,BULLET_TEXTURE,BULLET_IMAGE);*/


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

	currentHP = PLAYER_MAXHP;

	healthBarGreen.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
	healthBarGreen.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);
	healthBarBackGround.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - 8);
	healthBarBackGround.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - 5);
	healthBarGreen.setScale(0.5f);
	healthBarBackGround.setScale(0.5f);

	////test the bullet class here
	//newBullet->setPositionVector(BULLET_IMAGE);

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

	////////////////////////////////////////////////////////////////////////////
	//Test Logic
	//1 . Create the bullet here
	//2. If player does not key in anything or other than right key, the bullet continues moving with frametime
	//3. destroy the bullet if the bullet's x popsition is == 0 or == GAME_WIDTH
	//4. refactor all these codes into the player class after testing
	newBullet = new Bullet();
	newBullet->initialize(graphics, BULLET_TILE, BULLET_TEXTURE, BULLET_IMAGE);

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

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//implement the shooting here
		//test the bullet class here
		newBullet->setPositionVector(BULLET_IMAGE,PLAYER_SHOOTING_TILE_IMAGE.getCenterX(),PLAYER_SHOOTING_TILE_IMAGE.getCenterY());

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		input->clearAll();
		//Shooting animation
		PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(0.05f);
		//To minus HP of Player by 5.
		currentHP = currentHP - 5;
		float currentHpBarPercentage = currentHP / PLAYER_MAXHP;
		healthBarGreen.setPercentage(currentHpBarPercentage);
		input->clearAll();
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

	///////////////////////////////////////////////////////////////////////////////
	//Test Logic
	//1. Move the bullet according to frametime
	if (BULLET_IMAGE.getX() > GAME_WIDTH) {
		newBullet->setPositionVector(BULLET_IMAGE, PLAYER_SHOOTING_TILE_IMAGE.getCenterX(), PLAYER_SHOOTING_TILE_IMAGE.getCenterY());
	}
	else {
		if (BULLET_IMAGE.getX() < PLAYER_SHOOTING_TILE_IMAGE.getCenterX()) {
			newBullet->setPositionVector(BULLET_IMAGE, PLAYER_SHOOTING_TILE_IMAGE.getCenterX(), PLAYER_SHOOTING_TILE_IMAGE.getCenterY());
		}
		else {
			BULLET_IMAGE.setX(BULLET_IMAGE.getX() + frameTime * BULLET_SPEED);
		}
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
	/*newBullet->getBulletImage().draw();*/
	BULLET_IMAGE.draw();
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
