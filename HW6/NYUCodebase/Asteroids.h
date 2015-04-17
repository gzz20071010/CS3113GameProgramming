

#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <math.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include "Entity.h"

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6

using namespace std;

class Asteroids{
public:
	Asteroids();
	~Asteroids();

	void Init();
	void Update(float elapsed);
	void updateGameLevel(float elapsed);
	void FixedUpdate();

	void Render();
	void renderGameLevel();

	bool UpdateAndRender();

	bool collision(Entity* entity1, Entity* entity2);

	float lerp(float v0, float v1, float t);
    float genRandomNum(float min, float max);

private:
    
    GLuint spriteSheetTexture;
    GLuint fontSheetTexture;
    SDL_Window* displayWindow;
    
	bool done;
	float lastFrameTicks;
	float timeLeftOver;

	vector<Entity*> entities;

};