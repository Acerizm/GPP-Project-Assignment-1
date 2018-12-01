#include "zombie.h"
#include "graphics.h"

Zombie::Zombie() {


}

Zombie::~Zombie() {

}

void Zombie::initialize(Graphics *graphics, TextureManager &texture, Image &image) {
	if (!texture.initialize(graphics, ZOMBIE_MOVING_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
	if (!image.initialize(graphics, ZOMBIE_MOVING_WIDTH, ZOMBIE_MOVING_HEIGHT, ZOMBIE_MOVING_COLS, &texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing image"));
}

void Zombie::attackPlayer(Graphics *graphics, Image &zombieImage, Image &playerImage,float frameTime) 
{
	//get the unit vector in the direction of the player's position
	getUnitVectorCordinates(zombieImage, playerImage);

	//2. move the zombie to the playerImage
	if (zombieImage.getX() > GAME_WIDTH) {
		zombieImage.setX(0);
	}
	else
	{
		zombieImage.setX(zombieImage.getX() + unitVectorXCor*frameTime*100.0f);
		zombieImage.setY(zombieImage.getY() + unitVectorXCor*frameTime*100.0f);

	}
}