//
//  setup.h
//  HW2
//
//  Created by shengxiang guo on 2/15/15.
//

#ifndef HW2_setup_h
#define HW2_setup_h
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <cmath>

SDL_Window* displayWindow;

Entity pong;
Entity paddleLeft;
Entity paddleRight;
Entity upWall;
Entity botWall;
Entity winLogo;


GLuint LoadTexture(const char *image_path) {
    SDL_Surface *surface = IMG_Load(image_path);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surface);
    
    return textureID;
}

void pongSetup(){
    
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow(" PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    
    pong.textureID = LoadTexture("transparentLight26.png");
    paddleLeft.textureID = LoadTexture("wall.png");
    paddleRight.textureID = LoadTexture("wall.png");;
    upWall.textureID = LoadTexture("whitewall.png");
    botWall.textureID = LoadTexture("whitewall.png");
    winLogo.textureID = LoadTexture("winner.png");
}





#endif
