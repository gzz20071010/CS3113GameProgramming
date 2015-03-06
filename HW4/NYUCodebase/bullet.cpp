//
//  bullet.cpp
//  HW1
//
//  Created by shengxiang guo on 2/22/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "bullet.h"

Bullet::Bullet(){
    x = 1.5f;
    y = 1.5f;
};

void Bullet::Draw(){
    if (visiable){
        sprite.Draw(x, y, scale, rotation, true);
        cout<<"bullet draw";
    }
}

void Bullet::Update(float elapsed){
    y += speed * elapsed;
}