#include <SDL2/SDL.h>

#include "Obstacle.h"

Obstacle::Obstacle(Vector2f position, Vector2f scale, int w, int h,
		std::shared_ptr<SDL_Texture> texture) :
		Entity(position, scale, w, h, texture) {

}

void Obstacle::update(double deltaX, double deltaY) {
	getPosition().setX(getX() + deltaX);
	getPosition().setY(getY() + deltaY);
}

bool Obstacle::hasCollided() {
	return collided;
}
