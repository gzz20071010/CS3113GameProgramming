//
//  spaceInvader.cpp
//  HW3
//
//  Created by shengxiang guo on 2/22/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "spaceInvader.h"

GLuint LoadTexture(const char *image_path){
    SDL_Surface *surface = IMG_Load(image_path);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surface);
    
    return textureID;
}

SpaceInvader::SpaceInvader(){
    Init();
};

void SpaceInvader::Init(){
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    
    background = LoadTexture("doge.png");
    background2 = LoadTexture("back2.png");
    background3 = LoadTexture("Kitty-looking-so-cute-with-ear-cap.png");
    entity = LoadTexture("sheet.png");
    font = LoadTexture("font2.png");
    
    SpriteSheet backgroundSpriteSheet = SpriteSheet(background, 0.0f, 0.0f,  1920.0f/1920.0f,  900.0f/1080.0f);
    Entity* main_menu = new Entity(backgroundSpriteSheet, 0.0f, 0.0f, 1.33f, 0.0f, 0.0f, 0.0f, 0.0f);
    backgrounds.push_back(main_menu);
    
    SpriteSheet gamelevelSprite = SpriteSheet(background2, 0.0f, 0.0f,  1920.0f/1920.0f,  850.0f/1080.0f);
    Entity* game_level = new Entity(gamelevelSprite, 0.0f, 0.0f, 1.33f, 0.0f, 0.0f, 0.0f, 0.0f);
    backgrounds.push_back(game_level);
    
    SpriteSheet gameoverBackground = SpriteSheet(background3, 0.0f, 0.0f,  1920.0f/1920.0f,  900.0f/1080.0f);
    Entity* game_over = new Entity(gameoverBackground, 0.0f, 0.0f, 1.33f, 0.0f, 0.0f, 0.0f, 0.0f);
    backgrounds.push_back(game_over);
    
    SpriteSheet entitySpriteSheet = SpriteSheet(entity, 112.0/1024.0f, 791.0/1024.0f,  112.0/1024.0f,  75.0f/1024.0f);
    Entity* player = new Entity(entitySpriteSheet, 0.0f, -0.8f, 1.33f, 0.0f, 0.1f, 5.0f, 1.0f);
    entities.push_back(player);
    
    SpriteSheet enemySpriteSheet = SpriteSheet(entity, 222.0/1024.0f, 0.0/1024.0f,  103.0/1024.0f,  84.0/1024.0f);
    for (int i =0; i < 40; i++){
        if(i < 6){
            Entity* enemy = new Entity(enemySpriteSheet, -i*0.2, 0.8f, 0.5f, 180.0f, 0.0f, 0.2f, 0.1f);
            entities.push_back(enemy);
        }else if (i <10 && i>=6){
            Entity* enemy = new Entity(enemySpriteSheet, (i-5)*0.2, 0.8f, 0.5f, 180.0f, 0.0f, 0.2f, 0.1f);
            entities.push_back(enemy);
        }else if (i >=10 && i < 16){
            Entity* enemy = new Entity(enemySpriteSheet, -(i-10)*0.2, 0.7f, 0.5f, 180.0f, 0.0f, 0.2f, 0.1f);
            entities.push_back(enemy);
        }
        else if (i >=16 && i < 20){
            Entity* enemy = new Entity(enemySpriteSheet, (i-15)*0.2, 0.7f, 0.5f, 180.0f, 0.0f, 0.2f, 0.1f);
            entities.push_back(enemy);
        } else if (i >= 20&& i < 26){
            Entity* enemy = new Entity(enemySpriteSheet, -(i-20)*0.2, 0.6f, 0.5f, 180.0f, 0.0f, 0.2f, 0.1f);
            entities.push_back(enemy);
        } else if (i >= 26&& i < 30){
            Entity* enemy = new Entity(enemySpriteSheet, (i-25)*0.2, 0.6f, 0.5f, 180.0f, 0.0f, 0.2f, 0.1f);
            entities.push_back(enemy);
        }else if (i >= 30&& i < 36){
            Entity* enemy = new Entity(enemySpriteSheet, -(i-30)*0.2, 0.5f, 0.5f, 180.0f, 0.0f, 0.2f, 0.1f);
            entities.push_back(enemy);
        }else if (i >= 36&& i <= 40){
            Entity* enemy = new Entity(enemySpriteSheet, (i-35)*0.2, 0.5f, 0.5f, 180.0f, 0.0f, 0.2f, 0.1f);
            entities.push_back(enemy);
        }

    }
    bullet = LoadTexture("sheet.png");
}

SpaceInvader::~SpaceInvader() {
    SDL_Quit();
}


bool SpaceInvader::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    Update(elapsed);
    Render();
    return done;
}

void SpaceInvader::Render(){
    glClear(GL_COLOR_BUFFER_BIT);

    switch(state){
        case TITLE_SCREEN:
            RenderMainMenu();
            break;
        case GAME:
            RenderGameLevel();
            break;
        case GAME_OVER:
            RenderGameOver();
            break;
     }
}

void SpaceInvader::Update(float elapsed){
    
    switch(state){
        case TITLE_SCREEN:
            UpdateMainMenu(elapsed);
            break;
        case GAME:
            UpdateGameLevel(elapsed);
            break;
        case GAME_OVER:
            UpdateGameOver(elapsed);
            break;
    }
}

void SpaceInvader::RenderGameLevel(){
    //backgrounds[1]->Render();
    for(int i = 0; i < entities.size(); i++){
        entities[i]->Render();
    }
    DrawText(font, "score: " + to_string(score) , 0.1f, -0.06, 1.0, 0.5, 0.5, 1.0, -1.0, 0.9);
    for (int i = 0; i < MAX_BULLETS; i++){
        bullets[i].Draw();
    }
    SDL_GL_SwapWindow(displayWindow);
}
void SpaceInvader::RenderGameOver(){
    backgrounds[2]->Render();
    DrawText(font, "gameover", 0.3f, -0.06, 1.0, 0.5, 0.5, 1.0, -0.7, 0.0);
    SDL_GL_SwapWindow(displayWindow);
}
void SpaceInvader::RenderMainMenu(){
   // backgrounds[0]->Render();
    DrawText(font, "Press ENTER to start Space Invader", 0.1f, -0.04, 0.5, 0.5, 0.5, 1.0, -1.0, 0.5);
    DrawText(font, "A: left  D: right ", 0.1f, -0.04, 1.0, 0.5, 0.5, 1.0, -0.45, -0.0);
    DrawText(font, "Too many bullets ", 0.1f, -0.04, 1.0, 0.5, 0.5, 1.0, -0.45, -0.5);

    SDL_GL_SwapWindow(displayWindow);
}


void SpaceInvader::UpdateMainMenu(float elapsed) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                state = GAME;
            }
        }
    }
}
void SpaceInvader::UpdateGameLevel(float elapsed) {
    while (SDL_PollEvent(&event)) {
       // shootBullet(elapsed);
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        else if (event.type == SDL_KEYDOWN){
            if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                if ((entities[0]->x) > (-1.2f)) {
                    entities[0]->x -= (elapsed*entities[0]->velocity_x);
                }
                shootBullet(elapsed);

            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                if ((entities[0]->x) < (1.2f)) {
                    entities[0]->x += (entities[0]->speed);
                }
                shootBullet(elapsed);

            }
//            else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE){
//                shootBullet(elapsed);
//            }
        }
    }
    
    for (int i = 1; i < entities.size(); i++){
        if ((entities[i]->x> 1.25) || (entities[i]->x < -1.25)) {
            for (int j = 1; j < entities.size(); j++){
                entities[j]->velocity_x *= -1.0f;
                entities[j]->y -= entities[j]->velocity_y;
            }
            break;
        }

        //delete enemy
        for (int j = 0; j < 30; j++){
            if (bullets[j].visiable && CollisionDetect(*entities[i], bullets[j])) {
                score += 10;
                bullets[j].visiable = false;
                delete entities[i];
                entities.erase(entities.begin() + i);
                break;
            }
        }
    }
    
    for (int i = 1; i < entities.size(); i++){
        entities[i]->Update(elapsed);
    }
    
    for (int i = 0; i < MAX_BULLETS; i++){
        bullets[i].Update(elapsed);
    }
    
    if (entities.size() <= 1) {
        win = true;
        state = GAME_OVER;
    }
}

void SpaceInvader::UpdateGameOver(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true; }
    }
}

void SpaceInvader::shootBullet(float elapsed){
    SpriteSheet bulletsSprite = SpriteSheet(bullet, 674.0/1024.0f, 262.0/1024.0f,  22.0/1024.0f,  21.0/1024.0f);
    bullets[bulletIndex].sprite = bulletsSprite;
    bullets[bulletIndex].visiable = true;
    bullets[bulletIndex].x = entities[0]->x;
    bullets[bulletIndex].y = entities[0]->y;
    bullets[bulletIndex].scale = 1.0;
    bullets[bulletIndex].speed = 4.0f;
    bulletIndex++;
    if(bulletIndex > MAX_BULLETS-1) {
        bulletIndex = 0;
    }
}

bool SpaceInvader::CollisionDetect(Entity& entity, Bullet& bullet) {
    float entity_top = entity.y + (entity.sprite.height / 2.0f);
    float entity_bot = entity.y - (entity.sprite.height / 2.0f);
    float entity_right = entity.x + (entity.sprite.width / 2.0f);
    float entity_left = entity.x - (entity.sprite.width / 2.0f);
    float bullet_top = bullet.y + (bullet.sprite.height / 2.0f);
    float bullet_bot = bullet.y - (bullet.sprite.height / 2.0f);
    float bullet_right = bullet.x + (bullet.sprite.width / 2.0f);
    float bullet_left = bullet.x - (bullet.sprite.width / 2.0f);
    
    if (entity_bot > bullet_top||entity_top < bullet_bot||entity_left > bullet_right||entity_right < bullet_left) {
        return false;
    }
return true;
}

void SpaceInvader::DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x, float y) {
    glBindTexture(GL_TEXTURE_2D, fontTexture);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();

    float texture_size = 1.0/16.0f;
    vector<float> vertexData;
    vector<float> texCoordData;
    vector<float> colorData;
    for(int i=0; i < text.size(); i++) {
        float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
        float texture_y = (float)(((int)text[i]) / 16) / 16.0f;
        colorData.insert(colorData.end(), {r,g,b,a, r,g,b,a, r,g,b,a, r,g,b,a});
        vertexData.insert(vertexData.end(), {((size+spacing) * i) + (-0.5f * size), 0.5f * size, ((size+spacing) * i) +
            (-0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), 0.5f
            * size});
        texCoordData.insert(texCoordData.end(), {texture_x, texture_y, texture_x, texture_y + texture_size, texture_x +
            texture_size, texture_y + texture_size, texture_x + texture_size, texture_y});
    }
    glColorPointer(4, GL_FLOAT, 0, colorData.data());
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTranslated(x, y, 1);
    glDrawArrays(GL_QUADS, 0, (float)text.size() * 4);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
}

