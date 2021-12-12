#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "Entity.h"
#include "Math.h"

class Santa : public Entity {
public:
	Santa(Vector2f position, Vector2f scale, int w, int h, std::shared_ptr<SDL_Texture> texture);
	void update(double deltaX, double deltaY) override;
	void setMovingX(bool val);
	void setMovingY(bool val);
	void setDeltaTimeX(double deltaX);
	double getDeltaTimeX();
	double getDeltaTimeY();
	bool isMovingX();
	bool isMovingY();
private:
	double currentDeltaTimeX = 0, currentDeltaTimeY = 0;
	bool movingX = false;
	bool movingY = false;
};
