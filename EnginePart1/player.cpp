#include "player.h"
#include "graphics.h"
#include "entity.h"

Player::Player() :Entity()
{
	collisionType = entityNS::CIRCLE;
	spriteData.width = playerNS::PLAYER_SHOOTING_WIDTH;
	spriteData.height = playerNS::PLAYER_SHOOTING_HEIGHT;
	spriteData.scale = playerNS::PLAYER_SHOOTING_SCALE;
	spriteData.x = 0;
	spriteData.y = 0;
	//spriteData.
};

Player::~Player() {
	//destroy the damn player here
}

//void Player::shootBullet(Graphics *graphics, TextureManager &texture, Image &playerImage) {
//	//create the bullet here
//	newBullet = new Bullet();
//	
//	newBullet->initialize(graphics, texture, newBullet->BULLET_IMAGE,playerImage.getDegrees());
//	BULLET_LIST.push_back(newBullet);
//	//this is to set the original location of the bullet when the user presses a button
//	// which should be near the player's gun tip
//	newBullet->setPositionVector(newBullet->BULLET_IMAGE, playerImage.getCenterX(), playerImage.getCenterY());
//
//
//};

void Player::shootBullet(TextureManager &bulletTexture, Player *mainPlayer, Game *gamePtr, float playerAngle) 
{
	//create the bullet here
	newBullet = new Bullet();

	newBullet->initialize(gamePtr, bulletNS::BULLET_WIDTH, bulletNS::BULLET_HEIGHT, 0, &bulletTexture, playerAngle);
	BULLET_LIST.push_back(newBullet);
	newBullet->setPositionVector(mainPlayer->getCenterX(), mainPlayer->getCenterY());

}

//void Player::moveBullet(Image &playerImage, float gameWidth, float frameTime) 
//{
//	for each(Bullet* bullet in BULLET_LIST)
//	{
//		bullet->move(bullet->BULLET_IMAGE, playerImage, GAME_WIDTH, frameTime);
//
//	}
//}

void Player::moveBullet(float frameTime) {
	for each (Bullet * bullet in BULLET_LIST) {
		bullet->move(frameTime);
	}
}



//void Player::drawBullets() {
//	if (BULLET_LIST.size() != 0) {
//		for (list<Bullet*>::iterator it = BULLET_LIST.begin(); it != BULLET_LIST.end(); ) {
//			if ((*it)->BULLET_IMAGE.getX() > GAME_WIDTH || (*it)->BULLET_IMAGE.getX() < 0 || (*it)->BULLET_IMAGE.getY() > GAME_HEIGHT || (*it)->BULLET_IMAGE.getY() < 0)
//			{
//				SAFE_DELETE(*it);
//				it = BULLET_LIST.erase(it);
//				//just to check here
//				int check = BULLET_LIST.size();
//				//bool test = false;
//			}
//			else {
//				it++;
//			}
//		}
//
//		//when all okay go and draw the bullet
//		for each(Bullet* bullet in BULLET_LIST)
//		{
//			(bullet->BULLET_IMAGE).draw();
//		}
//	}
//}

void Player::drawBullets() 
{
	try {
		if (BULLET_LIST.size() != 0) {
			for (list<Bullet*>::iterator it = BULLET_LIST.begin(); it != BULLET_LIST.end(); ) {
				if ((*it)->BULLET_IMAGE.getX() > GAME_WIDTH || (*it)->BULLET_IMAGE.getX() < 0 || (*it)->BULLET_IMAGE.getY() > GAME_HEIGHT || (*it)->BULLET_IMAGE.getY() < 0)
				{
					SAFE_DELETE(*it);
					it = BULLET_LIST.erase(it);
					//just to check here
					int check = BULLET_LIST.size();
					//bool test = false;
				}
				else {
					it++;
				}
			}

			//when all okay go and draw the bullet
			for each(Bullet* bullet in BULLET_LIST)
			{
				bullet->draw();
			}
		}
	}
	catch (exception e) {
		throw(e);
	}

}

//void Player::initialize(Graphics *graphics, TextureManager &texture, Image &image) {
//	if (!texture.initialize(graphics, PLAYER_SHOOTING_TILE))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
//	if (!image.initialize(graphics, playerNS::PLAYER_SHOOTING_WIDTH, playerNS::PLAYER_SHOOTING_HEIGHT, playerNS::PLAYER_SHOOTING_COLS, &texture))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing "));
//}


bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//PLAYER_SHOOTING_IMAGE.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	this->setFrames(playerNS::PLAYER_SHOOTING_START_FRAME, playerNS::PLAYER_SHOOTING_END_FRAME);
	this->setCurrentFrame(playerNS::PLAYER_SHOOTING_START_FRAME);
	this->setFrameDelay(playerNS::PLAYER_SHOOTING_ANIMATION_DELAY);
	this->setLoop(true);                  // do not loop animation
	zombieKillCount = 0;
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Player::draw() {
	this->graphics->spriteBegin();
	Image::draw();
}

void Player::update(float frameTime) 
{
	Entity::update(frameTime);
}

void Player::setSpriteDataXnY(float x, float y) 
{
	spriteData.x = x;
	spriteData.y = y;
}