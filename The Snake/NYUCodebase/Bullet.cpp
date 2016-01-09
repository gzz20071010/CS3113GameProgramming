//
//  Bullet.cpp
//  HW1
//
//  Created by shengxiang guo on 5/8/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "Bullet.h"


Bullet::Bullet(){
    x = 1.5f;
    y = 1.5f;
    width = 0.2f;
    height = 0.2f;
};

void Bullet::Draw(){
    if (visiable){
       // sprite.Draw3( x,  y,  scale,  rotation);
        sprite.Draw(width, height, x, y, rotation);
    }
}

void Bullet::Update(float elapsed){
    y += vy * elapsed;
    x += vx * elapsed;
}