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

void Bullet::initialize(Graphics *graphics, const char* filepath) {
	//implement the LEVEl1_TILE_TEXTURE texture here
	if (!BULLET_TEXTURE.initialize(graphics, LEVEL1_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	//implement the LEVEL1_TILE_IMAGE image here
	if (!BULLET_IMAGE.initialize(graphics, LEVEL1_TILE_WIDTH, LEVEL1_TILE_HEIGHT, 0, &BULLET_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing "));
}

//test rendering of bullets

