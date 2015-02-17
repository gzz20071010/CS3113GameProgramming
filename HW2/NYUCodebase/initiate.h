//
//  initiate.h
//  HW2
//
//  Created by shengxiang guo on 2/15/15.
//

#ifndef HW2_initiate_h
#define HW2_initiate_h

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <cmath>

void pongInitiate(){
    
    // pong Settings
    pong.scale = 0.2f;
    pong.velocity_x = 3.0f;
    pong.velocity_y = 0.5f;
    
    // Paddle Settings
    paddleLeft.height = 5.5f;
    paddleLeft.width = 0.5f;
    paddleLeft.scale = 0.1f;
    paddleLeft.speed = 2.0f;
    paddleLeft.x = -1.20f;
    
    paddleRight.height = 5.5f;
    paddleRight.width = 0.5f;
    paddleRight.scale = 0.1f;
    paddleRight.speed = 2.0f;
    paddleRight.x = 1.20f;
    
    // Wall Settings
    upWall.width = 20.0f;
    upWall.scale = 0.1f;
    upWall.height = 0.1f;
    upWall.y = 0.9f;
    
    botWall.width = 20.0f;
    botWall.scale = 0.1f;
    botWall.height = 0.1f;
    botWall.y = -0.9f;
}

#endif
