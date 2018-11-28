#pragma once
#ifndef _BULLET_H             // prevent multiple definitions if this 
#define _BULLET_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#include "image.h"

class Bullet {
	private:
		/*TextureManager BULLET_TEXTURE;
		Image BULLET_IMAGE;*/

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
		void initialize(Graphics *graphics, const char* filepath, TextureManager &texture, Image &image);

		/*Image getBulletImage() {
			return BULLET_IMAGE;
		}*/

		void setPositionVector(Image &image) {
			image.setX(GAME_WIDTH / 10);
			image.setY(GAME_WIDTH / 10);
			image.setScale(BULLET_SCALE);
			image.setFrames(BULLET_START_FRAME, BULLET_END_FRAME);
		}





};




#endif