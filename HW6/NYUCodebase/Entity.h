

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

	float x = 0.0f;
	float y = 0.0f;
	float scale_x = 1.0f;
	float scale_y = 1.0f;
	float rotation = 0.0f;

    float velocity_x = 0.0f;
	float velocity_y = 0.0f;
	float acceleration_x = 0.0f;
	float acceleration_y = 0.0f;
	float friction_x = 0.0f;
	float friction_y = 0.0f;
	float mass = 0.0f;

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