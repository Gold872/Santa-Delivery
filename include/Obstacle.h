#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "Entity.h"
#include "Math.h"

class Obstacle : public Entity {
public:
	Obstacle(Vector2f position, Vector2f scale, int w, int h, std::shared_ptr<SDL_Texture> texture);

	void update(double deltaX, double deltaY) override;
	void setCollided(bool val) {
		collided = val;
	}
	bool hasCollided();

private:
	bool collided = false;
};
