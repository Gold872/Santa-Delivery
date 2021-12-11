#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "Entity.h"
#include "Math.h"

class House : public Entity {
public:
	House(Vector2f position, Vector2f scale, int w, int h, std::shared_ptr<SDL_Texture> texture);
	void update(double deltaTime) override;
	int getChimneyWidth();
	int getChimneyHeight();
	int getChimneyX();
	int getChimneyY();
private:
	int chimneyWidth, chimneyHeight;
	int chimneyX, chimneyY;
};
