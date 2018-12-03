#include "zombie.h"
#include "graphics.h"

Zombie::Zombie() {
	collisionType = entityNS::CIRCLE;
	spriteData.width = zombieNS::ZOMBIE_MOVING_WIDTH;
	spriteData.height = zombieNS::ZOMBIE_MOVING_HEIGHT;
	spriteData.scale = zombieNS::ZOMBIE_MOVING_SCALE;
	spriteData.x = 0;
	spriteData.y = 0;
	//radius = 1000;
	//spriteData.rect.bottom
}

Zombie::~Zombie() {
}

//void Zombie::initialize(Graphics *graphics, TextureManager &texture, Image &image) {
//	if (!texture.initialize(graphics, ZOMBIE_MOVING_TILE))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
//	if (!image.initialize(graphics, zombieNS::ZOMBIE_MOVING_WIDTH, zombieNS::ZOMBIE_MOVING_HEIGHT, zombieNS::ZOMBIE_MOVING_COLS, &texture))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing image"));
//}

bool Zombie::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	this->setFrames(zombieNS::ZOMBIE_MOVING_START_FRAME, zombieNS::ZOMBIE_MOVING_END_FRAME);
	this->setCurrentFrame(zombieNS::ZOMBIE_MOVING_START_FRAME);
	this->setFrameDelay(zombieNS::ZOMBIE_MOVING_ANIMATION_DELAY);
	this->setLoop(true);                  // do not loop animation
	//this->spriteData.x = 
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Zombie::setPositionVector(float x, float y) 
{
	this->setX(x);
	spriteData.x = x;
	this->setY(y);
	spriteData.y = y;
}


//void Zombie::attackPlayer(Graphics *graphics, Image &zombieImage, Image &playerImage,float frameTime) 
//{
//	//get the unit vector in the direction of the player's position
//	getUnitVectorCordinates(zombieImage, playerImage);
//
//	//2. move the zombie to the playerImage
//	if (zombieImage.getX() > GAME_WIDTH) {
//		zombieImage.setX(0);
//	}
//	else
//	{
//		zombieImage.setX(zombieImage.getX() + unitVectorXCor*frameTime*50.0f);
//		zombieImage.setY(zombieImage.getY() + unitVectorYCor*frameTime*50.0f);
//
//	}
//}

void Zombie::attackPlayer(Player *mainPlayer, float frameTime) {

	//1. get the unit vector in the direction of the player's position

	// ...add code here
	getUnitVectorCoordinates(mainPlayer);

	//2. move the zombie to the player image
	if (this->getX() > GAME_WIDTH) {
		this->setX(0);
	}
	else {
		// ... add code here later
		this->setX(this->getX() + unitVectorXCor * frameTime*50.0f);
		spriteData.x = this->getX() + unitVectorXCor * frameTime*50.0f;
		this->setY(this->getY() + unitVectorYCor * frameTime*50.0f);
		spriteData.y = (this->getY() + unitVectorYCor * frameTime*50.0f);
	}
}

void Zombie::getUnitVectorCoordinates(Player *mainPlayer) 
{
		//check which part of the quadrant the zombie is in

		//ZP (Zombie to Player) == OP - OZ
		
		float currentZombieXCor = this->getX();
		float currentZombieYCor = this->getY();

		float currentPlayerXCor = mainPlayer->getCenterX();
		float currentPlayerYCor = mainPlayer->getCenterY();

		float ZPXCor = currentPlayerXCor - currentZombieXCor;
		float ZPYCor = currentPlayerYCor - currentZombieYCor;

		float magnitudeOfZP = sqrt((ZPXCor*ZPXCor) + (ZPYCor*ZPYCor));

		unitVectorXCor = ZPXCor / magnitudeOfZP;
		unitVectorYCor = ZPYCor / magnitudeOfZP;

		//find the coordinates of ZP'
		// where p' is 90 degrees above P
		float PprimeXCor = currentPlayerXCor;
		float PprimeYCor = currentZombieYCor;

		//ZP' = OP' - OZ
		float ZPprimeXCor = PprimeXCor - currentZombieXCor;
		float ZPprimeYCor = PprimeYCor - currentZombieYCor;

		//get the scalar product to find the angle
		// dot product of ZP' * ZP = 
		float dotProdutValue = (ZPprimeXCor*ZPXCor) + (ZPprimeYCor*ZPYCor);
		//get the magnitude of ZP'
		float magnitudeOfZPrime = sqrt((ZPprimeXCor*ZPprimeXCor) + (ZPprimeYCor*ZPprimeYCor));
		float angle = acos(dotProdutValue / (magnitudeOfZPrime*magnitudeOfZP)) * (180/PI);

		//change the direction of the image here
		//1st quadrant
		if (this->getX() < mainPlayer->getX() && this->getY() < mainPlayer->getY()) 
		{
			this->setDegrees(angle);
		}
		//2nd quadrant
		else if (this->getX() > mainPlayer->getX() && this->getY() < mainPlayer->getY()) 
		{
			this->flipHorizontal(true);
			this->setDegrees(-angle);
		}
		//3rd quadrant
		else if (this->getX() > mainPlayer->getX() && this->getY() > mainPlayer->getY()) 
		{
			this->flipHorizontal(true);
			this->setDegrees(angle);
		}
		//4th quadrant
		else if (this->getX() < mainPlayer->getX() && this->getY() > mainPlayer->getY()) 
		{
			this->flipHorizontal(false);
			this->setDegrees(-angle);
		}
}