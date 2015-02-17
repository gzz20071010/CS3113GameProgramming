//
//  update.h
//  HW2
//
//  Created by shengxiang guo on 2/15/15.
//

#ifndef HW2_update_h
#define HW2_update_h
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <cmath>

void pongUpdate(float elapsed ){
    
    if (pongCollisionCheck() == 1) {                  // pong colliding with paddleLeft
        pong.velocity_x *= -1.0f;					// Reverse the x velocity
        pong.x += pong.velocity_x / 150.0f;			// Add in an offset
    }

    else if (pongCollisionCheck() == 2) {
        pong.velocity_x *= -1.0f;
        pong.x += pong.velocity_x / 150.0f;
    }
    
    else if (pongCollisionCheck() == 3) {           // pong collided with wall
        pong.velocity_y *= -1.0f;					// Reverse the y velocity
        pong.y += pong.velocity_y / 90.0f;
    }
    
    pong.x += pong.velocity_x * elapsed;               //move pong
    pong.y += pong.velocity_y * elapsed;
}

#endif
