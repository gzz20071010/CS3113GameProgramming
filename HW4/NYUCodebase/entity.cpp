//
//  entity.cpp
//  HW1
//
//  Created by shengxiang guo on 2/22/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "entity.h"
Entity::Entity(SpriteSheet sprite, float x, float y, float scale, float rotation, float speed, float velocity_x, float velocity_y, bool isStatic) : sprite(sprite), x(x), y(y), scale(scale), rotation(rotation), speed(speed), velocity_x(velocity_x), velocity_y(velocity_y), isStatic(isStatic) {}

Entity::~Entity(){};
void Entity::Render() {
    sprite.Draw(this->x, this->y, scale, rotation);
}
void Entity::Update(float elapsed) {
   // x += velocity_x * FIXED_TIMESTEP;
  //  y += velocity_y * FIXED_TIMESTEP;
}

void Entity::Jump(){
    inJump = true;
    velocity_y = 100.0f*FIXED_TIMESTEP;
    collidedBot = false;
}

bool Entity::collidesWith(Entity* entity){
    
    
    float entity_top = y + (sprite.height / 2.0f);
    float entity_bot = y - (sprite.height / 2.0f);
    float entity_right = x + (sprite.width / 2.0f);
    float entity_left = x - (sprite.width / 2.0f);
    
    float bullet_top = entity->y + (entity->sprite.height / 2.0f);
    float bullet_bot = entity->y - (entity->sprite.height/ 2.0f);
    float bullet_right = entity->x + (entity->sprite.width / 2.0f);
    float bullet_left = entity->x - (entity->sprite.width / 2.0f);
    
    // Based on the rules for collision detection we have:
    if (entity_bot > bullet_top||entity_top < bullet_bot||entity_left > bullet_right||entity_right < bullet_left) {
        return false;
    }
    // A true is returned if there has been a collision
    return true;
}

void Entity::resetFlags(){
    collidedBot = false;
    collidedTop = false;
    collidedLeft = false;
    collidedRight = false;
}