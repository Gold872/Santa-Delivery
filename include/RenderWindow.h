#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "Entity.h"
#include "Math.h"

class RenderWindow {
public:
	RenderWindow(const char *title, int width, int height);
	std::shared_ptr<SDL_Texture> loadTexture(const char *filePath);
	void cleanUp();
	void clear();
	void fillScreen(int r, int g, int b);
	void render(Entity &entity);
	void render(int x, int y, std::shared_ptr<SDL_Texture> texture);
	void render(Vector2f position, Vector2f scale, int w, int h, std::shared_ptr<SDL_Texture> texture);
	void render(Vector2f position, const char *text, TTF_Font *font, SDL_Color textColor);
	void renderCenter(Vector2f position, const char *text, TTF_Font *font, SDL_Color textColor);
	void display();
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
};
