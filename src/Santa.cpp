#include <memory>

#include "Santa.h"

int maxSpeed = 6;

Santa::Santa(Vector2f position, Vector2f scale, int w, int h,
		std::shared_ptr<SDL_Texture> texture) :
		Entity(position, scale, w, h, texture) {
}

void Santa::update(double deltaX, double deltaY) {
	//Doesn't let deltaX get above Max Speed
	if (deltaX >= maxSpeed) {
		deltaX = maxSpeed;
	}
	//Doesn't let deltaY get above Max Speed
	if (deltaY >= maxSpeed) {
		deltaY = maxSpeed;
	}
	//Doesn't let deltaX get below Max Speed
	if (deltaX <= -maxSpeed) {
		deltaX = -maxSpeed;
	}
	//Doesn't let deltaY get below Max Speed
	if (deltaY <= -maxSpeed) {
		deltaY = -maxSpeed;
	}

	currentDeltaTimeX = deltaX;
	currentDeltaTimeY = deltaY;
	setPosition(getPosition().getX() + deltaX,
			getPosition().getY() + deltaY);
}

void Santa::setMovingX(bool val) {
	movingX = val;
}

bool Santa::isMovingX() {
	return movingX;
}

void Santa::setMovingY(bool val) {
	movingY = val;
}
bool Santa::isMovingY() {
	return movingY;
}

double Santa::getDeltaTimeX() {
	return currentDeltaTimeX;
}
double Santa::getDeltaTimeY() {
	return currentDeltaTimeY;
}
