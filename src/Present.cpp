#include <memory>

#include "Present.h"
#include "Entity.h"

Present::Present(Vector2f position, Vector2f scale, int w, int h,
		std::shared_ptr<SDL_Texture> texture) :
		Entity(position, scale, w, h, texture) {
	dropping = false;
}

void Present::update(double deltaTime) {
	setPosition(getPosition().getX(), getPosition().getY() + deltaTime);
}
