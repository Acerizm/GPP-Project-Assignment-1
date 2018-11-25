
#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
	// this is where i implement the painter's algorithm here
    Game::initialize(hwnd); // throws GameError

	// nebula texture
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// planet texture
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	//implement the spaceship texture here
	if (!spaceship1Texture.initialize(graphics,SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// planet
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	//implement the spacship image here
	if (!spaceship1.initialize(graphics,SHIP_WIDTH,SHIP_HEIGHT,SHIP_COLS,&spaceship1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship"));

	// place planet in center of screen
	planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);
	
	//place the spaceship in the center of the screen
	spaceship1.setX(GAME_WIDTH/5);
	spaceship1.setY(GAME_HEIGHT/5);

	spaceship1.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);   // animation frames ship.setCurrentFrame(SHIP_START_FRAME);             // starting frame
	spaceship1.setFrameDelay(SHIP_ANIMATION_DELAY);
	spaceship1.setDegrees(90.0f);                             // angle of ship

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	// if (input->isKeyDown(SHIP_RIGHT_KEY))            // if move right
	{
		spaceship1.setX(spaceship1.getX() + frameTime * SHIP_SPEED);
		if (spaceship1.getX() > GAME_WIDTH)               // if off screen right
			spaceship1.setX((float)-spaceship1.getWidth());  // position off screen left
	}
	if (input->isKeyDown(SHIP_LEFT_KEY))             // if move left
	{
		spaceship1.setX(spaceship1.getX() - frameTime * SHIP_SPEED);
		if (spaceship1.getX() < -spaceship1.getWidth())         // if off screen left
			spaceship1.setX((float)GAME_WIDTH);      // position off screen right
	}
	if (input->isKeyDown(SHIP_UP_KEY))               // if move up
	{
		spaceship1.setY(spaceship1.getY() - frameTime * SHIP_SPEED);
		if (spaceship1.getY() < -spaceship1.getHeight())        // if off screen top
			spaceship1.setY((float)GAME_HEIGHT);     // position off screen bottom
	}
	if (input->isKeyDown(SHIP_DOWN_KEY))             // if move down
	{
		spaceship1.setY(spaceship1.getY() + frameTime * SHIP_SPEED);
		if (spaceship1.getY() > GAME_HEIGHT)              // if off screen bottom
			spaceship1.setY((float)-spaceship1.getHeight());    // position off screen top
	}

	spaceship1.update(frameTime);



}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	nebula.draw();                          // add the orion nebula to the scene
	planet.draw();                          // add the planet to the scene
	spaceship1.draw();						// add the spaceship to the scene

	graphics->spriteEnd();                  // end drawing sprites


}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();

	Game::releaseAll();
	return;

}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();

	Game::resetAll();
	return;

}
