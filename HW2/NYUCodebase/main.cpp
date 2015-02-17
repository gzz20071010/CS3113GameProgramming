#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "entity.h"
#include <cmath>
#include "setup.h"
#include "collision.h"
#include "control.h"
#include "process.h"
#include "update.h"
#include "initiate.h"
#include "iostream"

int main(int argc, char *argv[]) {
    pongSetup();
    pongInitiate();
    
    float elapsed;
    float lastFrameTicks = 0.0f;
    
    while (ProcessEvents()) {
        float ticks		= (float)SDL_GetTicks() / 6000.0f;
        elapsed			= ticks - lastFrameTicks;
        lastFrameTicks	= ticks;
        pongControl(elapsed);
        pongUpdate(elapsed);
        pongRender(pongStatus()); //draw entities or win logo
    }
    SDL_Quit();
    return 0;
}