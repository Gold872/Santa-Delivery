#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <string>

#include "Game.h"
#include "RenderWindow.h"
#include "Present.h"
#include "Santa.h"
#include "Math.h"
#include <iostream>

int SCREEN_WIDTH = 1200, SCREEN_HEIGHT = 700;
int MAX_FPS = 60;
int MAX_HOUSES = 3; //The max amount of houses that will appear at once

RenderWindow window("Santa's Delivery", SCREEN_WIDTH, SCREEN_HEIGHT);

double acceleration = 0.4;

std::shared_ptr<SDL_Texture> presentTexture = window.loadTexture(
		"res/images/present.png");
std::shared_ptr<SDL_Texture> backgroundTexture = window.loadTexture(
		"res/images/background_gradient.png");
std::shared_ptr<SDL_Texture> mountainTexture = window.loadTexture(
		"res/images/mountains.png");
std::shared_ptr<SDL_Texture> snowTexture = window.loadTexture(
		"res/images/snow.png");
std::shared_ptr<SDL_Texture> santaTexture = window.loadTexture(
		"res/images/santa_sleigh.png");
std::shared_ptr<SDL_Texture> houseTexture1 = window.loadTexture(
		"res/images/house1.png");
std::shared_ptr<SDL_Texture> houseTexture2 = window.loadTexture(
		"res/images/house2.png");
std::shared_ptr<SDL_Texture> houseTexture3 = window.loadTexture(
		"res/images/house3.png");
std::shared_ptr<SDL_Texture> houseTexture4 = window.loadTexture(
		"res/images/house4.png");

TTF_Font *font84 = TTF_OpenFont("res/fonts/comic_sans.ttf", 84);
TTF_Font *font36 = TTF_OpenFont("res/fonts/comic_sans.ttf", 36);
TTF_Font *font24 = TTF_OpenFont("res/fonts/comic_sans.ttf", 24);
SDL_Color black = { 0, 0, 0 };

Present present(Vector2f(0, 0), Vector2f(50, 50), 2000, 1710, presentTexture);

int santaWidth = 1920, santaHeight = 1152;
Santa santa(Vector2f(100, 100), Vector2f(santaWidth / 6, santaHeight / 6),
		santaWidth, santaHeight, santaTexture);

int houseWidth = 704, houseHeight = 624;
House house(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT - 175),
		Vector2f(houseWidth / 1.75, houseHeight / 1.75), 704, 624,
		houseTexture1);

void Game::checkInput() {
	double deltaX = santa.getDeltaTimeX();
	double deltaY = santa.getDeltaTimeY();

	const Uint8 *keystates = SDL_GetKeyboardState(NULL);
	if (keystates[SDL_SCANCODE_LEFT] && state == GAME) {
		deltaX -= acceleration;
		santa.update(deltaX - acceleration, deltaY);
		santa.setMovingX(true);
	} else if (keystates[SDL_SCANCODE_RIGHT] && state == GAME) {
		deltaX += acceleration;
		santa.update(deltaX, deltaY);
		santa.setMovingX(true);
	}
	if (keystates[SDL_SCANCODE_UP] && state == GAME) {
		deltaY -= acceleration;
		santa.update(deltaX, deltaY);
		santa.setMovingY(true);
	} else if (keystates[SDL_SCANCODE_DOWN] && state == GAME) {
		deltaY += acceleration;
		santa.update(deltaX, deltaY);
		santa.setMovingY(true);
	}
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_SPACE:
				if ((e.key.repeat == 0)) {
					if (state == GAME) {
						drop();
						presentsDropped++;
					} else if (state == MENU) {
						setState(GAME);
					}
				}
				break;
			}
		} else if (e.type == SDL_QUIT) {
			running = false;
			SDL_Quit();
		}
	}
}

void Game::updateFPS(int startTick) {
	if (1000 / MAX_FPS > SDL_GetTicks() - startTick) {
		SDL_Delay(1000 / MAX_FPS - (SDL_GetTicks() - startTick));
	}
}

void Game::checkXVelocity(double deltaX, double deltaY) {
	if (!santa.isMovingX()) {
		//These if statements slowly make Santa slow down if he's not moving
		if (deltaX > 0) {
			deltaX -= acceleration;
			santa.update(deltaX, deltaY);
		}
		if (deltaX < 0) {
			deltaX += acceleration;
			santa.update(deltaX, deltaY);
		}
		//This makes Santa stop if his speed X is below one
		if (std::abs(deltaX) < 1) {
			deltaX = 0;
			santa.update(deltaX, deltaY);
		}
	}
}

void Game::checkYVelocity(double deltaX, double deltaY) {
	if (!santa.isMovingY()) {
		if (deltaY > 0) {
			deltaY -= acceleration;
			santa.update(deltaX, deltaY);
		}
		if (deltaY < 0) {
			deltaY += acceleration;
			santa.update(deltaX, deltaY);
		}

		//This makes Santa stop if his speed Y is below one
		if (std::abs(deltaY) < 1) {
			deltaY = 0;
			santa.update(deltaX, deltaY);
		}
	}
}

void Game::updatePresent(Vector2f &presentPosition, float deltaY) {
	presentPosition.setY(presentPosition.getY() + deltaY);
}

bool Game::isColliding(float a_x, float a_y, float a_w, float a_h, float b_x,
		float b_y, float b_w, float b_h) {
	return (a_x + a_w > b_x) && (a_x < b_x + b_w) && (a_y + a_h > b_y)
			&& (a_y < b_y + b_h);
}

void Game::checkCollisions() {
	//If Santa is on the left edge, it doesn't let it go past it
	if (santa.getX() <= 0) {
		//Sets the X to left of the screen
		santa.getPosition().setX(0);
		//If Santa is on the right edge, it doesn't let him go past it
	} else if (santa.getX() >= SCREEN_WIDTH - santaWidth / 6) {
		//Sets the X to the very right of the screen
		santa.getPosition().setX(SCREEN_WIDTH - santaWidth / 6);
	}
	//If Santa is on the top edge, it doesn't let him go higher
	if (santa.getY() <= 0) {
		//Sets the Y position to the top of the screen
		santa.getPosition().setY(0);
		//If Santa is on the bottom edge, it doesn't let him go any lower
	} else if (santa.getY() >= 475 - santaHeight / 6) {
		//Sets the Y position to the bottom of the screen
		santa.getPosition().setY(475 - santaHeight / 6);
	}
	//Checks if a present lands in the chimney
	for (unsigned i = 0; i < presents.size(); i++) {
		for (unsigned j = 0; j < houses.size(); j++) {
			if (isColliding(presents[i].getX(), presents[i].getY(),
					presents[i].getScale().x, presents[i].getScale().y,
					houses[j].getChimneyX(), houses[j].getChimneyY(),
					houses[j].getChimneyWidth(),
					houses[j].getChimneyHeight())) {
				score++;
				presents.erase(presents.begin() + i);
			}
		}
		if (presents[i].getY() > SCREEN_HEIGHT) {
			presents.erase(presents.begin() + i);
		}
	}
	//Checks if the first house is off the screen
	if (houses[0].getX() + 352 < 0) {
		int randHouseOffset = rand() % 900 + 600;
		houses.erase(houses.begin() + 0);
		houses.push_back(house);
		houses[houses.size() - 1].setPosition(
				houses[houses.size() - 2].getX() + randHouseOffset,
				houses[0].getY());
		//Assigns the new house a random texture
		int randInt = rand() % 4;
		switch (randInt) {
		case 0:
			houses[houses.size() - 1].setTexture(houseTexture1);
			break;
		case 1:
			houses[houses.size() - 1].setTexture(houseTexture2);
			break;
		case 3:
			houses[houses.size() - 1].setTexture(houseTexture3);
			break;
		case 4:
			houses[houses.size() - 1].setTexture(houseTexture4);
			break;
		default:
			break;
		}
	}
}

void Game::drop() {
	presents.push_back(present);
	presents.back().setPosition(santa.getX() + 50, santa.getY() + 100);
}

void Game::draw() {
	window.clear();
	switch (state) {
	case MENU:
		window.render(0, 0, backgroundTexture);
		window.render(0, 0, mountainTexture);
		window.render(0, 0, snowTexture);
		window.renderCenter(Vector2f(SCREEN_WIDTH, sin(SDL_GetTicks()/100) * 2 + SCREEN_HEIGHT - 100),
				"Santa Delivery Game", font84, black);
		window.renderCenter(Vector2f(SCREEN_WIDTH, sin(SDL_GetTicks()/100) * 2 + SCREEN_HEIGHT + 100),
				"Help Santa Deliver His Presents", font36, black);
		window.renderCenter(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT + 300),
				"Press Space to Start", font24, black);
		break;
	case GAME:
		window.render(0, 0, backgroundTexture);
		window.render(0, 0, mountainTexture);
		window.render(0, 0, snowTexture);
		for (unsigned i = 0; i < presents.size(); i++) {
			window.render(presents[i]);
		}
		window.render(santa);
		for (unsigned i = 0; i < houses.size(); i++) {
			window.render(houses[i]);
		}
		std::string scoreNumber = "Score: " + std::to_string(score);
		std::string presentsDroppedNumber = "Presents Dropped: "
				+ std::to_string(presentsDropped);
		window.render(Vector2f(10, 10), scoreNumber.c_str(), font36, black);
		window.render(Vector2f(200, 10), presentsDroppedNumber.c_str(), font36,
				black);
		break;
	}
	window.display();
}

void Game::init() {
	srand(time(NULL));
	//Creates 3 new houses that are 600 pixels apart from each other
	for (int i = 0; i < MAX_HOUSES; i++) {
		int randHouseOffset = rand() % 900 + 600;
		houses.push_back(house);
		if (i != 0) {
			houses[i].setPosition(houses[i - 1].getX() + randHouseOffset,
					houses[i].getY());
			//Assigns a random texture to the houses
			int randInt = rand() % 4;
			switch (randInt) {
			case 0:
				houses[i].setTexture(houseTexture1);
				break;
			case 1:
				houses[i].setTexture(houseTexture2);
				break;
			case 3:
				houses[i].setTexture(houseTexture3);
				break;
			case 4:
				houses[i].setTexture(houseTexture4);
				break;
			default:
				break;
			}
		}
	}
}

void Game::mainLoop() {
	Uint32 starting_tick = SDL_GetTicks();
	checkInput();
	switch (state) {
	case MENU:
		draw();
		break;
	case GAME:
		checkXVelocity(santa.getDeltaTimeX(), santa.getDeltaTimeY());
		checkYVelocity(santa.getDeltaTimeX(), santa.getDeltaTimeY());
		for (unsigned i = 0; i < presents.size(); i++) {
			presents[i].update(10);
		}
		for (unsigned i = 0; i < houses.size(); i++) {
			houses[i].update(5);
		}
		draw();
		checkCollisions();
		santa.setMovingX(false);
		santa.setMovingY(false);
		break;
	}
	updateFPS(starting_tick);
}
