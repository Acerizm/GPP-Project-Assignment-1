#include "bullet.h"
#pragma once
#include "textureManager.h"
#include "graphics.h"
using namespace std;


	
//initialize the damn bullet immediately
// pass by pointer here using pointer as we want to use the original graphics addr
// pass by address here for the filepath as the file is an adrress xd

Bullet::Bullet() {

};

Bullet::~Bullet() {
	//safe delete here

}

void Bullet::initialize(Graphics *graphics,TextureManager &texture,Image &image,float currentAngle) {
//	//implement the LEVEl1_TILE_TEXTURE texture here
//	if (!BULLET_TEXTURE.initialize(graphics, BULLET_TILE))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
//
//	//implement the LEVEL1_TILE_IMAGE image here
//	if (!BULLET_IMAGE.initialize(graphics, BULLET_WIDTH, BULLET_HEIGHT, 0, &BULLET_TEXTURE))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing "));
	if (!texture.initialize(graphics, BULLET_TILE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
	if (!image.initialize(graphics, BULLET_WIDTH, BULLET_HEIGHT, 0, &texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing "));
	this->currentAngle = currentAngle;
}

//test rendering of bullets

