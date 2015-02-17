//
//  
//  ponggame
//
//  Created by shengxiang guo on 2/15/15.
//

#ifndef HW2_entity_h
#define HW2_entity_h
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <cmath>



class Entity {
public:
    void DrawSprite();
    void Draw();
    float x = 0.0;
    float y = 0.0;
    float scale = 1.0f;
    
    int textureID;
    
    float width = 1.0f;
    float height = 1.0f;
    float speed = 1.0f;
    float velocity_x;
    float velocity_y;
};

#endif
