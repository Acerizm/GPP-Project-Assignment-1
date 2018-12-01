#include "zombie.h"
#include "graphics.h"

Zombie::Zombie() {


}

Zombie::~Zombie() {

}

void Zombie::initialize(Graphics *graphics, TextureManager &texture, Image &image) {
	if (!texture.initialize(graphics, ZOMBIE_MOVING_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
	if (!image.initialize(graphics, ZOMBIE_MOVING_WIDTH, ZOMBIE_MOVING_HEIGHT, ZOMBIE_MOVING_COLS, &texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing image"));
}