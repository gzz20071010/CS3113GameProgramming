//
//  process.h
//  HW2
//
//  Created by shengxiang guo on 2/15/15.
//

#ifndef HW2_process_h
#define HW2_process_h
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <cmath>

bool ProcessEvents(){
    
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            return false;
        }
        return true;
    }
    return true;
}

void pongRender(bool winCheck){
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (winCheck) { //display win logo
        winLogo.DrawSprite();
    }
    
    else {  //no winner, game continue
        pong.DrawSprite();
        paddleLeft.Draw();
        paddleRight.Draw();
        upWall.DrawSprite();
        botWall.DrawSprite();
    }
    
    SDL_GL_SwapWindow(displayWindow);
}

bool pongStatus(){
    //game over when pong passes paddle return true
    if ((pong.x > (1.40)) || (pong.x < (-1.40))) {
        return true;
    }
    return false;
}


#endif
