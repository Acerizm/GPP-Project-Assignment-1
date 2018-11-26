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
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	//implement the spacship image here
	if (!LEVEL1_TILE_IMAGE.initialize(graphics, LEVEL1_TILE_WIDTH, LEVEL1_TILE_HEIGHT, 0, &LEVEL1_TILE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship"));

	//set x or set y for the initial position vector of the object
	LEVEL1_TILE_IMAGE.setScale(LEVEL1_TILE_SCALE);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void LastManStanding::update()
{
	//update the animation here

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
	graphics->spriteBegin();                // begin drawing sprites

	LEVEL1_TILE_IMAGE.draw();

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
