//
//  collision.h
//  HW2
//
//  Created by shengxiang guo on 2/15/15.
//

#ifndef HW2_collision_h
#define HW2_collision_h
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <cmath>

int pongCollisionCheck() {
    float pongWidth = (pong.width * pong.scale);
    float pongHeight = (pong.height * pong.scale);
    
    // Check for a collision between the pong and paddleLeft
    if ((pong.x - pongWidth) <= (paddleLeft.x + (paddleLeft.width * paddleLeft.scale / 2))) {
        if (( (pong.y - pongHeight*pong.scale) <= (paddleLeft.y + (paddleLeft.height * paddleLeft.scale / 2))) && ( (pong.y + pongHeight*pong.scale) >= (paddleLeft.y - (paddleLeft.height * paddleLeft.scale / 2)))) {
            return 1;
        }
    }
    
    // Check for a collision between the pong and paddleRight
    else if ( (pong.x + pongWidth) >= (paddleRight.x - (paddleRight.width * paddleRight.scale / 2))) {
        if (( (pong.y - pongHeight*pong.scale) <= (paddleRight.y + (paddleRight.height * paddleRight.scale / 2))) && ( (pong.y + pongHeight*pong.scale) >= (paddleRight.y - (paddleRight.height * paddleRight.scale / 2)))) {
            return 2;
        }
    }
    
    // Check for a collision between the pong and one of the walls
    else if ((pong.y + pongHeight) >= (upWall.y - (upWall.height * upWall.scale))) {
        return 3;
    }
    else if ((pong.y - pongHeight) <= (botWall.y - (botWall.height * botWall.scale))) {
        return 3;
    }
    
    return 0;
};

int paddleCollisionCheck(Entity paddle) {
    //check collision with top and bottom
    if ((paddle.y + ((paddle.height * paddle.scale) / 2)) > upWall.y) {
        return 1;
    }
    else if ((paddle.y - ((paddle.height * paddle.scale) / 2)) < botWall.y) {
        return 2;
    }
    return 0;
}

#endif
