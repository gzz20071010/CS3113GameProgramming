//
//  Bullet.h
//  HW1
//
//  Created by shengxiang guo on 5/8/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __HW1__Bullet__
#define __HW1__Bullet__
#include "SpriteSheet.h"
#include <stdio.h>

class Bullet{
public:
    Bullet();
    Bullet(SpriteSheet sprite, float x, float y, bool visiable, float textureID, float speed);
    float x;
    float y;
    bool visiable = false;
    int textureID;
    float width;
    float height;
    SpriteSheet sprite;
    
    float speed;
    float vx;
    float vy;
    
    float rotation = 0;
    float angle;
    float timeAlive;
    float direction_x;
    float direction_y;
    float scale = 2.0;
    void Draw();
    void Update(float elapsed);
    
    float cd = 0.0f;
};
#endif /* defined(__HW1__Bullet__) */
