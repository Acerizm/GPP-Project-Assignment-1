#include "zombie.h"
#include "graphics.h"

Zombie::Zombie() {
	zombieHpText = new TextDX();

}

Zombie::~Zombie() {

}

void Zombie::initialize(Graphics *graphics, TextureManager &texture, Image &image) {
	if (!texture.initialize(graphics, ZOMBIE_MOVING_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
	if (!image.initialize(graphics, ZOMBIE_MOVING_WIDTH, ZOMBIE_MOVING_HEIGHT, ZOMBIE_MOVING_COLS, &texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing image"));
	
	if(!healthBarRedTexture.initialize(graphics,HEALTHBARRED_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarRed texture"));

	if(!healthBarRed.initialize(graphics,256,32,1,&healthBarRedTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarRed"));

	if (!enemyHealthBarBackGroundTexture.initialize(graphics, HEALTHBARBACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarBackGround texture"));

	if (!enemyHealthBarBackGround.initialize(graphics, 256, 32, 1, &enemyHealthBarBackGroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarBackGround"));

	if (zombieHpText->initialize(graphics, 15, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hpText font"));
	zombieCurrentHP = zombieMaxHp;
	healthBarRed.setScale(0.5f);
	enemyHealthBarBackGround.setScale(0.5f);
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
		zombieImage.setX(zombieImage.getX() + unitVectorXCor*frameTime*50.0f);
		zombieImage.setY(zombieImage.getY() + unitVectorYCor*frameTime*50.0f);

		//healthBarRed.setRect();
		healthBarRed.setX(zombieImage.getX()- 8);
		healthBarRed.setY(zombieImage.getY() - 5);
		enemyHealthBarBackGround.setX(zombieImage.getX() - 8);
		enemyHealthBarBackGround.setY(zombieImage.getY() - 5);
		zombieHpText->setFontColor(graphicsNS::WHITE);
		
		

	}
}