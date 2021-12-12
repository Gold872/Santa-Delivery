#pragma once

#include "Entity.h"
#include "Present.h"
#include "House.h"
#include "Obstacle.h"
#include <vector>

class Game {
public:
	void init();
	void checkInput();
	void updateFPS(int startTick);
	void checkXVelocity(double deltaX, double deltaY);
	void checkYVelocity(double deltaX, double deltaY);
	void checkCollisions();
	void checkSantaCollisions();
	void checkPresentCollisions();
	void checkHouseCollisions();
	void checkObstacleCollisions();
	void mainLoop();
	void draw();
	void drop();
	void spawnNewObstacle(int houseOffset);

	bool isColliding(float a_x, float a_y, float a_w, float a_h, float b_x,
			float b_y, float b_w, float b_h);

	bool isRunning() {
		return running;
	}
	bool isPaused() {
		return paused;
	}
	void setPaused(bool val) {
		paused = val;
	}

	enum gameState {
		MENU, GAME
	};
	gameState state = MENU;

	void setState(gameState state) {
		this->state = state;
	}

	int score = 0;
	int presentsDropped = 0;
	int obstaclesHit = 0;

	std::vector<House> houses;
	std::vector<Present> presents;
	std::vector<Obstacle> obstacles;

	std::vector<Vector2f> presentCoordinates;

private:
	int lastFrame, lastTime, frameCount, timerFPS, fps;
	bool running = true;
	bool paused = false;
};
