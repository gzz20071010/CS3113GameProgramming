//
//  control.h
//  HW2
//
//  Created by shengxiang guo on 2/15/15.
//

#ifndef HW2_control_h
#define HW2_control_h
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <cmath>

const Uint8 *keys = SDL_GetKeyboardState(NULL);

void pongControl(float elapsed) {   //W & S
    if (keys[SDL_SCANCODE_W]) {
        if (paddleCollisionCheck(paddleLeft) != 1) {
            paddleLeft.y += (elapsed * paddleLeft.speed);
        }
    }
    else if (keys[SDL_SCANCODE_S]) {
        if (paddleCollisionCheck(paddleLeft) != 2) {
            paddleLeft.y -= (elapsed * paddleLeft.speed);
        }
    }
    
    if (keys[SDL_SCANCODE_UP]) {      //up & down
        if (paddleCollisionCheck(paddleRight) != 1) {
            paddleRight.y += (elapsed * paddleRight.speed);
        }
    }
    else if (keys[SDL_SCANCODE_DOWN]){
        if (paddleCollisionCheck(paddleRight) != 2) {
            paddleRight.y -= (elapsed * paddleRight.speed);
        }
    }
}



#endif
