//
//  bullet.h
//  HW1
//
//  Created by shengxiang guo on 2/22/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __HW1__bullet__
#define __HW1__bullet__

#include <stdio.h>
#include <iostream>
#include "SpriteSheet.h"
using namespace std;

class Bullet{
public:
    Bullet();
    Bullet(SpriteSheet sprite, float x, float y, bool visiable, float textureID, float speed);
    float x;
    float y;
    bool visiable;
    int textureID;
    float width;
    float height;
    SpriteSheet sprite;
    float speed;
    float rotation = 0;
    float angle;
    float timeAlive;
    float direction_x;
    float direction_y;
    float scale = 1.0;
    void Draw();
    void Update(float elapsed);

};

#endif /* defined(__HW1__bullet__) */
