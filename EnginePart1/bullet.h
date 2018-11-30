#pragma once
#ifndef _BULLET_H             // prevent multiple definitions if this 
#define _BULLET_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#include "image.h"

class Bullet {
	private:
		//textureManager BULLET_TEXTURE;
		Image BULLET_IMAGE;
		friend class LastManStanding;
	public:
		//Image BULLET_IMAGE;

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

		void setPositionVector(Image &image,float playerXCenter, float playerYCenter) {
			image.setX(playerXCenter + 10);
			image.setY(playerYCenter);
			image.setScale(BULLET_SCALE);
			image.setFrames(BULLET_START_FRAME, BULLET_END_FRAME);
		}

		void move(Image &bulletImage, Image &playerImage, float gameWidth,float frameTime) {
			if (bulletImage.getX() > gameWidth) {
				//setPositionVector(bulletImage, playerImage.getCenterX(), playerImage.getCenterY());
				//SAFE_DELETE(*bulletImage);
				//need to do something here
			}
			else {
				if (bulletImage.getX() < playerImage.getCenterX()) {
					setPositionVector(bulletImage, playerImage.getCenterX(), playerImage.getCenterY());
				}
				else {
					bulletImage.setX(bulletImage.getX() + frameTime * BULLET_SPEED);
				}
			}
		}

		/*Image getBulletImage() {
			return BULLET_IMAGE;
		}*/







};




#endif