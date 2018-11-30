#include "player.h"
#include "graphics.h"

Player::Player() {

};

Player::~Player() {
	//destroy the damn player here
}

void Player::shootBullet(Graphics *graphics, TextureManager &texture, Image &playerImage) {
	//create the bullet here
	newBullet = new Bullet();
	BULLET_LIST.push_back(newBullet);
	newBullet->initialize(graphics, texture, newBullet->BULLET_IMAGE);
	//this is to set the original location of the bullet when the user presses a button
	// which should be near the player's gun tip
	newBullet->setPositionVector(newBullet->BULLET_IMAGE, playerImage.getCenterX(), playerImage.getCenterY());


};

void Player::moveBullet(Image &playerImage, float gameWidth, float frameTime) 
{
	//if (BULLET_LIST.size() != 0) {
	//	for (list<Bullet*>::iterator it = BULLET_LIST.begin(); it != BULLET_LIST.end(); ) {
	//		if ((*it)->BULLET_IMAGE.getX() > GAME_WIDTH)
	//		{
	//			SAFE_DELETE(*it);
	//			it = BULLET_LIST.erase(it);
	//			int check = BULLET_LIST.size();
	//			//bool test = false;
	//		}
	//		else {
	//			it++;
	//		}
	//	}

	//	for each(Bullet* bullet in BULLET_LIST)
	//	{
	//		bullet->move(bullet->BULLET_IMAGE, playerImage, GAME_WIDTH, frameTime);

	//	}

	//}
	for each(Bullet* bullet in BULLET_LIST)
	{
		bullet->move(bullet->BULLET_IMAGE, playerImage, GAME_WIDTH, frameTime);

	}
}

void Player::drawBullets() {
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
			(bullet->BULLET_IMAGE).draw();
		}
	}
}


void Player::initialize(Graphics *graphics, TextureManager &texture, Image &image) {
	if (!texture.initialize(graphics, PLAYER_SHOOTING_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
	if (!image.initialize(graphics, PLAYER_SHOOTING_WIDTH, PLAYER_SHOOTING_HEIGHT, PLAYER_SHOOTING_COLS, &texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing "));
}