
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

SDL_Window* displayWindow;
GLuint LoadTexture(const char *image_path) {
    SDL_Surface *surface = IMG_Load(image_path);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surface);
    return textureID;
}

void DrawSprite(GLint texture, float x, float y, float rotation) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    GLfloat quad[] = {-0.1f, 0.1f, -0.1f, -0.1f, 0.1f, -0.1f, 0.1f, 0.1f};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}

void DrawTriangle(){
    GLfloat triangle[] = {-0.1f, 0.1f, -0.1f, -0.1f, 0.1f, -0.1};
    glTranslatef(-0.5, 0.5, 0);
    glVertexPointer(2, GL_FLOAT, 0, triangle);
    glEnableClientState(GL_VERTEX_ARRAY);
    GLfloat triangleColors[] = {-0.1f, 0.1f, -0.1f, -0.1f, 0.1f, -0.1};
    glColorPointer(3, GL_FLOAT, 0, triangleColors);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    bool done = false;
    
    float lastFrameTicks = 0.0f;
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    float rotation;
    
    SDL_Event event;

    
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
        }
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.8f, 0.8f, 0.6f, 1.0f);
        
        rotation += elapsed;
        DrawSprite(LoadTexture("transparentLight26.png"), 0.5, 0.5, rotation);
        DrawSprite(LoadTexture("transparentLight27.png"), -0.5, -0.5, rotation);
        DrawSprite(LoadTexture("transparentLight28.png"), -0.0, -0.0, rotation);
        DrawTriangle();


        SDL_GL_SwapWindow(displayWindow);
    }
    
    SDL_Quit();
    return 0;
}