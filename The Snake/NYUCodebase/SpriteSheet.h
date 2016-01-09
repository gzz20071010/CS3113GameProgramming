

#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class SpriteSheet{
public:
	SpriteSheet();
    SpriteSheet(GLuint textureID, float u, float v, float width, float height);
	SpriteSheet(GLuint textureID, unsigned int spriteX, unsigned int spriteY, unsigned int index);

	// draws whatever is passed in on the screen
	void Draw(float width, float height, float x, float y, float rotation);
    void Draw2(float scale_x, float scale_y);
    void Draw3(float x, float y, float scale, float rotation);


	// owned variables
	GLuint textureID;
	unsigned int spriteX;
	unsigned int spriteY;
	unsigned int index;

    float u;
    float v;
    float width;
    float height;
    float scale = 1.0f;
};

// function for loading textures
GLuint LoadTexture(const char *image_path);