

#include "SpriteSheet.h"

SpriteSheet::SpriteSheet() {}
SpriteSheet::SpriteSheet(unsigned int textureID, float u, float v, float width, float height)
	: textureID(textureID), u(u), v(v), width(width), height(height) {}

void SpriteSheet::Drawpoints(){
    GLfloat points[4];
    for(int i =0; i<4; i++){
        float rand = genRandomNum(-4.33f, 3.33f);
        points[i] = (rand);
    }

    glPointSize(2.0f);
    glLoadIdentity();
    glVertexPointer(2, GL_FLOAT, 0, points);
    glEnableClientState(GL_VERTEX_ARRAY);

    glDrawArrays(GL_POINTS, 0, 2);
}

void SpriteSheet::Draw(float scale_x, float scale_y) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    GLfloat quad[] = { -width * scale_x, height * scale_y, -width * scale_x, -height * scale_y, width * scale_x, -height * scale_y, width * scale_x, height * scale_y };
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = { u, v, u, v + height, u + width, v + height, u + width, v };
    
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawArrays(GL_POLYGON, 0, 4);
    
    glDisable(GL_TEXTURE_2D);
    Drawpoints();

}

GLuint LoadTexture(const char *image_path) {
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	SDL_FreeSurface(surface);

	return textureID;
}

float SpriteSheet::genRandomNum(float min, float max) {
    return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}
