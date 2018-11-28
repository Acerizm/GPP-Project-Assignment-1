#include "player.h"

Player::Player() {

};

Player::~Player() {
	//destroy the damn player here
}

void Player::shootBullet(VECTOR2 player) {
	//create the bullet here
	Bullet *newBullet = new Bullet();


};

void Player::initialize(Graphics *graphics, const char* filepath, TextureManager &texture, Image &image) {
	if (!texture.initialize(graphics, PLAYER_SHOOTING_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
	if (!image.initialize(graphics, PLAYER_SHOOTING_WIDTH, PLAYER_SHOOTING_HEIGHT, PLAYER_SHOOTING_COLS, &texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing "));
}