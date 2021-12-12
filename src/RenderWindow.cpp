#include "RenderWindow.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

RenderWindow::RenderWindow(const char *title, int width, int height) {

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		std::cout << "Failed to Create Window " << SDL_GetError() << std::endl;
	}

	SDL_Surface *icon = IMG_Load("res/images/santa_sleigh_icon.png");
	if (icon == NULL) {
		std::cout << "Error Loading Image Icon" << SDL_GetError() << std::endl;
	}
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		std::cout << "Failed to Create Renderer " << SDL_GetError()
				<< std::endl;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0) {
		std::cout << "Failed to Initialize SDL2 Library " << SDL_GetError()
				<< std::endl;
	}

	if (IMG_Init(IMG_INIT_PNG) < 0) {
		std::cout << "Failed to Initialize SDL2 Image Library "
				<< SDL_GetError() << std::endl;
	}

	if (TTF_Init() < 0) {
		std::cout << "Failed to Initialize SDL2 TTF Library " << SDL_GetError()
				<< std::endl;
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

std::shared_ptr<SDL_Texture> RenderWindow::loadTexture(const char *filePath) {
//	std::shared_ptr<SDL_Texture> texture = nullptr;
//	texture = IMG_LoadTexture(renderer, filePath);

	return std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderer, filePath),
			SDL_DestroyTexture);
}

void RenderWindow::clear() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}

void RenderWindow::fillScreen(int r, int g, int b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity &entity) {
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = entity.getFrame().w;
	source.h = entity.getFrame().h;

	SDL_Rect destination;
	destination.x = entity.getPosition().getX();
	destination.y = entity.getPosition().getY();
	destination.w = entity.getScale().getX();
	destination.h = entity.getScale().getY();

	SDL_RenderCopyEx(renderer, entity.getTexture().get(), &source, &destination,
			0, 0, SDL_FLIP_NONE);
}

void RenderWindow::render(int x, int y, std::shared_ptr<SDL_Texture> texture) {
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = 100;
	source.h = 100;

	SDL_QueryTexture(texture.get(), NULL, NULL, &source.w, &source.h);

	SDL_Rect destination;
	destination.x = x;
	destination.y = y;
	destination.w = source.w;
	destination.h = source.h;

	SDL_RenderCopy(renderer, texture.get(), &source, &destination);
}

void RenderWindow::render(Vector2f position, Vector2f scale, int w, int h,
		std::shared_ptr<SDL_Texture> texture) {
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = w;
	source.h = h;

	SDL_Rect destination;
	destination.x = position.x;
	destination.y = position.y;
	destination.w = scale.x;
	destination.h = scale.y;

	SDL_RenderCopy(renderer, texture.get(), &source, &destination);
}

void RenderWindow::render(Vector2f position, const char *text, TTF_Font *font,
		SDL_Color textColor) {
	SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, text, textColor);
	SDL_Texture *message = SDL_CreateTextureFromSurface(renderer,
			surfaceMessage);

	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = surfaceMessage->w;
	source.h = surfaceMessage->h;

	SDL_Rect destination;
	destination.x = position.getX();
	destination.y = position.getY();
	destination.w = source.w;
	destination.h = source.h;

	SDL_RenderCopy(renderer, message, &source, &destination);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void RenderWindow::renderCenter(Vector2f position, const char *text,
		TTF_Font *font, SDL_Color textColor) {
	SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, text, textColor);
	SDL_Texture *message = SDL_CreateTextureFromSurface(renderer,
			surfaceMessage);

	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = surfaceMessage->w;
	source.h = surfaceMessage->h;

	SDL_Rect destination;
	destination.x = position.getX() / 2 - source.w / 2;
	destination.y = position.getY() / 2 - source.h / 2;
	destination.w = source.w;
	destination.h = source.h;

	SDL_RenderCopy(renderer, message, &source, &destination);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void RenderWindow::playAudio(Mix_Chunk *audioChunk) {

	Mix_PlayChannel(-1, audioChunk, 0);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}
