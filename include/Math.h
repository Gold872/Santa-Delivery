#pragma once

class Vector2f {
public:
	Vector2f(float point_x = 0, float point_y = 0) {
		this->x = point_x;
		this->y = point_y;
	}

	void setX(float x) {
		this->x = x;
	}

	void setY(float y) {
		this->y = y;
	}

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}

	float x, y;
};
