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
    float x ;
    float y;
    float scale ;
    float rotation ;
    
    // Variables used for moving the Entity
    float speed ;
    float velocity_x ;
    float velocity_y ;
    
    void Render();
    void Update(float elapsed);
    void fire();
};

#endif /* defined(__HW1__entity__) */
