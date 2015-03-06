
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>
#include <String>
#include "spaceInvader.h"
#include <iostream>

int main(int argc, char *argv[])
{

    SpaceInvader invader;
    while(!invader.UpdateAndRender()){};
    cout<<"game over"<<endl;
    return 0;
}