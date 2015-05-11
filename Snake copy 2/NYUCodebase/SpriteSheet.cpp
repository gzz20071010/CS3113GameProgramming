
#include "SpriteSheet.h"

SpriteSheet::SpriteSheet() {}

SpriteSheet::SpriteSheet(GLuint textureID, unsigned int spriteX, unsigned int spriteY, unsigned int index): textureID(textureID), spriteX(spriteX), spriteY(spriteY), index(index) {}
SpriteSheet::SpriteSheet(GLuint textureID, float u, float v, float width, float height):textureID(textureID),u(u),v(v),width(width),height(height) {}


void SpriteSheet::Draw(float width, float height, float x, float y, float rotation) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);

	float u = (float)(((int)index) % spriteX) / (float)spriteX;
	float v = (float)(((int)index) / spriteX) / (float)spriteY;

	float spriteWidth = 1.0f / (float)spriteX;
	float spriteHeight = 1.0f / (float)spriteY;

	GLfloat quad[] = { -width * 0.5f, height * 0.5f, -width * 0.5f, -height * 0.5f, width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = { u, v, u, v + spriteHeight, u + spriteWidth, v + spriteHeight, u + spriteWidth, v };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void SpriteSheet::Draw2(float scale_x, float scale_y) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glMatrixMode(GL_MODELVIEW);

    
    GLfloat quad[] = { -width * scale_x, height * scale_y, -width * scale_x, -height * scale_y, width * scale_x, -height * scale_y, width * scale_x, height * scale_y };
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = { u, v, u, v + height, u + width, v + height, u + width, v };
    
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void SpriteSheet::Draw3(float x=1.0f, float y=1.0f, float scale=1.0f, float rotation=0.0f){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    GLfloat quad[] = {-width * scale , height * scale, -width * scale, -height * scale,
        width * scale, -height * scale, width * scale, height * scale};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {u, v, u, v+height, u+width, v+height, u+width, v};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    

    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    
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