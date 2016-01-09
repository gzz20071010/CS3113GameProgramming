

#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class SpriteSheet{
public:
	SpriteSheet();
	SpriteSheet(GLuint textureID, float u, float v, float width, float height);
	void Draw(float scale_x, float scale_y);
    void Drawpoints();
    float genRandomNum(float min, float max);

	GLuint textureID;
	float u;
	float v;
	float width;
	float height;
};
GLuint LoadTexture(const char *image_path);