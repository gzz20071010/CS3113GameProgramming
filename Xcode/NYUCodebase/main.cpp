
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

SDL_Window* displayWindow;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
    
	bool done = false;
	
	SDL_Event event;
    
        glViewport(0, 0, 800, 600); //sets the pixel size and offset of redering area.
        glMatrixMode(GL_PROJECTION);
        glMatrixMode(GL_MODELVIEW);
        glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0); // multiplies the currently selected amtrix with and orthographic projection matrix
    
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        GLfloat triangle[] = {0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f}; //triagnle position
        glVertexPointer(2, GL_FLOAT, 0, triangle);
        glEnableClientState(GL_VERTEX_ARRAY);//enable
        GLfloat triangleColors[] = {1.0, 0.0, 0.0,0.0, 1.0,0.0,0.0,0.0,1.0};//triangle color
        glColorPointer(3, GL_FLOAT, 0, triangleColors);
        glEnableClientState(GL_COLOR_ARRAY);//ENABLE
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glLoadIdentity();
        glTranslatef(0.5 , 0.5, 0.0);
        glRotated(45.0f, 0.0, 0.0, 1.0);
        glScalef(2.0, 1.0, 1.0);
        glClearColor(0.4f, 0.2f, 0.8f, 1.0f); //set the clear color of screen
        //glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(displayWindow);
	}
    
	SDL_Quit();
	return 0;
}