

#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "SpriteSheet.h"
#include "Matrix.h"

class Entity {
public:
	Entity();
	~Entity();

    void Update(float elapsed);
    void Render();
	void buildMatrix();

	SpriteSheet sprite;

	float x;
	float y;
	float scale_x;
	float scale_y;
    float rotation;

    float velocity_x;
    float velocity_y;
    float acceleration_x;
    float acceleration_y;
    float friction_x;
    float friction_y;
    float mass;

	bool isStatic = false;
	bool collidedTop = false;
	bool collidedBottom = false;
	bool collidedLeft = false;
	bool collidedRight = false;

	bool isPlayer = false;
	bool isEnemy = false;

	Matrix matrix;
	Vector TL;
	Vector TR;
	Vector BL;
	Vector BR;
};