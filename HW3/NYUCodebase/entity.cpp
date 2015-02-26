//
//  entity.cpp
//  HW1
//
//  Created by shengxiang guo on 2/22/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "entity.h"
Entity::Entity(SpriteSheet sprite, float x, float y, float scale, float rotation, float speed, float velocity_x, float velocity_y) : sprite(sprite), x(x), y(y), scale(scale), rotation(rotation), speed(speed), velocity_x(velocity_x), velocity_y(velocity_y) {}


void Entity::Render() {
    sprite.Draw(x, y, scale, rotation);
}
void Entity::Update(float elapsed) {
        x += (velocity_x * elapsed);
}

