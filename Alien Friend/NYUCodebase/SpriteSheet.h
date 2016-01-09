//
//  SpriteSheet.h
//  HW1
//
//  Created by shengxiang guo on 2/22/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __HW1__SpriteSheet__
#define __HW1__SpriteSheet__

#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class SpriteSheet{
public:
    SpriteSheet();
    SpriteSheet(GLuint textureID, float u, float v, float width, float height);
    
    void Draw(float x, float y, float scale, float rotation);
    //void DrawText(int fontTexture, std::string text, float size, float spacing, float r, float g, float b, float a);
    GLuint textureID;
    float u;
    float v;
    float width;
    float height;
};
#endif /* defined(__HW1__SpriteSheet__) */
