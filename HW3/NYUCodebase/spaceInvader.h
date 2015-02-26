//
//  spaceInvader.h
//  HW3
//
//  Created by shengxiang guo on 2/22/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __HW3__spaceInvader__
#define __HW3__spaceInvader__

#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <cmath>
#include <vector>
#include <string>
#include "SpriteSheet.h"
#include "entity.h"
#include "bullet.h"
using namespace std;
#define MAX_BULLETS 30


class SpaceInvader{
public:
    SpaceInvader();
    ~SpaceInvader();
    
    
    void Init();
    bool UpdateAndRender();

    void Render();
    void RenderMainMenu();
    void RenderGameLevel();
    void RenderGameOver();

    void Update(float elapsed);
    void UpdateGameLevel(float elapsed);
    void UpdateMainMenu(float elapsed);
    void UpdateGameOver(float elapsed);
    
    void shootBullet(float elapsed);
    bool shouldRemoveBullet(Bullet bullet);
    bool CollisionDetect(Entity& entity, Bullet& bullet);
    void DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x, float y);

    bool done;
    float lastFrameTicks;
    SDL_Window* displayWindow;
    SDL_Event event;
    
    GLuint background;
    GLuint background2;
    GLuint background3;
    GLuint entity;
    GLuint font;
    GLuint bullet;
    
    //vector<Entity> backgrounds;
    Bullet bullets[MAX_BULLETS];
    enum GameState { TITLE_SCREEN, GAME, GAME_OVER};
    int state = TITLE_SCREEN;
    int score = 0;
    int bulletIndex = 0;
    bool win = false;
    vector<Entity*> backgrounds;	// Vector to hold backgrounds used in various game states
    vector<Entity*> entities;		// Vector to hold the player and alien ships
    vector<Entity*> scene;			// Vector to load in elements required for the game over scenes
};

#endif /* defined(__HW3__spaceInvader__) */
