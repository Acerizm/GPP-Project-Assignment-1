#pragma once
#include "player.h"
#ifndef _BULLET_H             // prevent multiple definitions if this 
#define _BULLET_H             // ..file is included in more than one place
#include "textureManager.h"
#include "graphics.h"


class Bullet {
	private:
		TextureManager BULLET_TEXTURE;
		Image BULLET_IMAGE;

	public:
		//constructor
		Bullet();

		//de-stuctor
		virtual ~Bullet();

		//what the heck does the bullet need to store?
		//1. need to store the texture here
		//2. need to store the image here
		//3. handle collision here also

		//initialize the damn bullet
		//pass by reference here btw
		void initialize(Graphics *graphics, const char* filepath );





};




#endif