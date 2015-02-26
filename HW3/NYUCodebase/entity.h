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
#include "SpriteSheet.h"
class Entity {
public:
    Entity(SpriteSheet sprite, float x, float y, float scale, float rotation, float speed, float velocity_x, float velocity_y);
   // ~Entity();
    SpriteSheet sprite;
    float x = 0.0f;
    float y = 0.0f;
    float scale = 1.0f;
    float rotation = 0.0f;
    
    // Variables used for moving the Entity
    float speed = 0.1f;
    float velocity_x = 0.3f;
    float velocity_y = 0.2f;
    
    void Render();
    void Update(float elapsed);
};

#endif /* defined(__HW1__entity__) */
