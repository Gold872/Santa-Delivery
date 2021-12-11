#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "Math.h"

class Entity {
public:
	Entity(Vector2f position, Vector2f scale, int w, int h,
			std::shared_ptr<SDL_Texture> texture); //The scale Vector2f is what it will be scaled down to
	virtual ~Entity();
	virtual void update(double deltaTime);
	Vector2f& getPosition() {
		return position;
	}
	void setPosition(float x, float y);
	Vector2f& getScale() {
		return scale;
	}
	void setScale();
	std::shared_ptr<SDL_Texture> getTexture();
	void setTexture(std::shared_ptr<SDL_Texture> texture);
	float getX();
	float getY();
	SDL_Rect getFrame();
private:
	Vector2f position;
	Vector2f scale;
	SDL_Rect frame;
	std::shared_ptr<SDL_Texture> texture = nullptr;
};
