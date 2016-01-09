//
//  entity.h
//  HW1
//
//  Created by shengxiang guo on 2/22/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __HW1__entity__
#define __HW1__entity__

#include <stdio.h>
#include <iostream>
#include "SpriteSheet.h"
#define FIXED_TIMESTEP 0.0166666f
using namespace std;
class Entity {
public:
    Entity(SpriteSheet sprite, float x, float y, float scale, float rotation, float speed, float velocity_x, float velocity_y, bool dynamic);
    ~Entity();
    SpriteSheet sprite;
    float x;
    float y = 0.2f;
    float scale ;
    float rotation ;
    float speed ;
    float velocity_x ;
    float velocity_y ;
    float acceleration_x;
    float acceleration_y;
    float friction_x = 10;
    float friction_y;
    float mass;
    bool isStatic; //是否固定物体
    float gravity_y = 8.0f;
    
    bool collidedTop;
    bool collidedBot;
    bool collidedRight;
    bool collidedLeft;
    
    bool isPlayer;
    bool isEnemy;
    bool inJump;
    bool playerDead= false;
    bool enemyDead= false;
    bool isLoot = false;
    bool looted = true;
    int score;
    
    void Render();
    void Update(float elapsed);
    bool collidesWith(Entity* entity);
    void FixedUpdate();
    void Jump();
    void fire();
    void resetFlags();
    
};

#endif /* defined(__HW1__entity__) */
