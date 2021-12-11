#include <memory>

#include "Entity.h"

Entity::Entity(Vector2f position, Vector2f scale, int w, int h, std::shared_ptr<SDL_Texture> texture) {
	frame.x = position.getX();
	frame.y = position.getY();
	frame.w = w;
	frame.h = h;

	this->scale = scale;
	this->position = position;
	this->texture = texture;
}

Entity::~Entity() {

}

void Entity::update(double deltaTime) {

}

std::shared_ptr<SDL_Texture> Entity::getTexture() {
	return texture;
}

void Entity::setTexture(std::shared_ptr<SDL_Texture> texture) {
	this->texture = texture;
}

void Entity::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

float Entity::getX() {
	return getPosition().getX();
}

float Entity::getY() {
	return getPosition().getY();
}

SDL_Rect Entity::getFrame() {
	return frame;
}
