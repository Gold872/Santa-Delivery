#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "Entity.h"
#include "Math.h"

class Present: public Entity {
public:
	Present(Vector2f position, Vector2f scale, int w, int h, std::shared_ptr<SDL_Texture> texture);

	bool isDropping() {
		return dropping;
	}
	void setDropping(bool val) {
		dropping = val;
	}
	void update(double deltaTime) override;
private:
	bool dropping;
};
