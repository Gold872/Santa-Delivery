#include <memory>

#include "House.h"

House::House(Vector2f position, Vector2f scale, int w, int h,
		std::shared_ptr<SDL_Texture> texture) :
		Entity(position, scale, w, h, texture) {
	chimneyWidth = 62;
	chimneyHeight = 15;
}

void House::update(double deltaTime) {
	setPosition(getPosition().getX() - deltaTime, getPosition().getY());
	chimneyX = getPosition().getX() + 63;
	chimneyY = getPosition().getY() + 40;
}

int House::getChimneyX() {
	return chimneyX;
}

int House::getChimneyY() {
	return chimneyY;
}

int House::getChimneyWidth() {
	return chimneyWidth;
}

int House::getChimneyHeight() {
	return chimneyHeight;
}
