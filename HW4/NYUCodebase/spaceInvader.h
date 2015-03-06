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
#include <iostream>
#include "SpriteSheet.h"
#include "entity.h"
#include "bullet.h"
using namespace std;
#define MAX_BULLETS 30
#define MAX_TIMESTEPS 6
#define  MAX_LOOT 15

class SpaceInvader{
public:
    SpaceInvader();
    ~SpaceInvader();
    
    
    void Init();
    bool UpdateAndRender();
    void Render();
    void Update(float elapsed);
    void DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x, float y);
    bool CollisionDetect(Entity& entity, Entity& bullet);
    float lerp(float v0, float v1, float t);
    void FixedUpdate();
    
   
    void shootBullet(float elapsed);
    bool shouldRemoveBullet(Bullet bullet);

    bool done;
    float lastFrameTicks = 0.0;
    float timeLeftOver = 0.0f;
    SDL_Window* displayWindow;
    
    GLuint background;
    GLuint background2;
    GLuint stair2;
    GLuint entity;
    GLuint derpkid;
    GLuint font;
    GLuint entity2;
    GLuint bullet;
    GLuint apple;
    
    int score = 0;
    int bulletIndex = 0;
    bool win = false;
    int numLoot = 0;
    float spawnTimer = 0.0f;
    int points =50;
    float gravity_y= 4.0f;
    float elapsed;
    float friction_x=4.0f;
    
    vector<Entity*> backgrounds;	// Vector to hold backgrounds used in various game states
    vector<Entity*> entities;		// Vector to hold the player and alien ships
    vector<Entity*> scene;			// Vector to load in elements required for the game over scenes
};

#endif /* defined(__HW3__spaceInvader__) */
