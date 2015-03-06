#include "spaceInvader.h"

GLuint LoadTexture(const char *image_path){
    SDL_Surface *surface = IMG_Load(image_path);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surface);
    
    return textureID;
}

SpaceInvader::SpaceInvader(){
    Init();
};

float SpaceInvader::lerp(float v0, float v1, float t){
    return ( 1.0f - t )* v0 + t * v1;
}

void SpaceInvader::Init(){
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33*2.0, 1.33*2.0, -1.0*2.0, 1.0*2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    
    

   // background2 = LoadTexture("emma-studying.png");
//    entity = LoadTexture("sheet.png");
    derpkid = LoadTexture("spritesheet_elements.png");
    entity2 = LoadTexture("p1_spritesheet.png");
    font = LoadTexture("font1.png");
    
    SpriteSheet gamelevelSprite = SpriteSheet(background2, 0.0f/2048.0f, 0.0f/2048.0f,  1.0f,  0.80f);
    Entity* game_level = new Entity(gamelevelSprite, 0.0f, 0.0f, 2.66f, 0.0f, 0.0f, 0.0f, 0.0f, true);
    backgrounds.push_back(game_level);
    
    SpriteSheet player =  SpriteSheet(entity2, 438.0f/508.0f, 73.0f/228.0f, 67.0f/508.0f, 94.0f/290.0f);
    Entity* derpKidEntity = new Entity(player, -1.6, 2.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, false);
    entities.push_back(derpKidEntity);
    

    
    
       //	<SubTexture name="elementGlass021.png" x="1840" y="1710" width="70" height="220"/>

//    SpriteSheet wallLeftSpriteSheet = SpriteSheet(derpkid, 1840.0f/2048.0f, 1710.0f/2048.0f,  70.0f/2048.0f,  220.0f/2048.0f );
//    Entity* wallLeft = new Entity(wallLeftSpriteSheet, -3, 0, 20.0f, 0.0f, 0.1f, 0.0f, 0.0f,true);
//    entities.push_back(wallLeft);
//    Entity* wallRight = new Entity(wallLeftSpriteSheet, 3, 0, 20.0f, 0.0f, 0.1f, 0.0f, 0.0f,true);
//    entities.push_back(wallRight);
    
    for ( float i = 0.0f; i < 2.0f; i= i+0.2f) {
        cout<<"==================";

        SpriteSheet stage2 = SpriteSheet(derpkid, 0.0f/2048.0f, 0.0f/2048.0f,  220.0f/2048.0f,  70.0f/2048.0f );
        cout<<"==================";
        entities.push_back(new Entity(stage2, i, -i, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, true));
        cout<<"==================";

        cout<<i<<endl;
        if( -i == -0.2f){
            cout<<"========================="<<endl;
            cout<<"creating entity[2] (0.2,0.2)"<<endl;
            cout<<"value i should be 0.2: "<<i<<endl;
            cout<<"value -i should be -0.2: "<<-i<<endl;
        }
        
    }
    for ( float j = 0.2f; j < 2.0f; j= j+0.2f ){
        cout<<"==================";

        SpriteSheet stage2 = SpriteSheet(derpkid, 0.0f/2048.0f, 0.0f/2048.0f,  220.0f/2048.0f,  70.0f/2048.0f );
        cout<<"==================";

        entities.push_back(new Entity(stage2, (-j), (-j), 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, true));
        cout<<"==================";

    }
    //p1_front = 0 196 66 92

    SpriteSheet friends =  SpriteSheet(entity2, 0.0f/508.0f, 150.0f/228.0f, 66.0f/508.0f, 92.0f/290.0f);
    Entity* derpKidFriends = new Entity(friends, 1.6, 0.2f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, false);
    entities.push_back(derpKidFriends);
    
}

SpaceInvader::~SpaceInvader() {
    SDL_Quit();
}


bool SpaceInvader::UpdateAndRender() {
    
    float x_speed = 50.0f * FIXED_TIMESTEP;
    
    // First we update the timing of the game
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_A]) {
        // Move Left                              //so what is x_speed. it is 50* time_step. why. time_step is 0.0166 * 50 = 0.8
        entities[0]->velocity_x = -1.0f * x_speed;// 0.8 is x_speed, a somewhat small number.
                                                  //so when we press A, velocity_x from 1.0 become -0.8 so it turns to left direction and slower.
    }
    if (keys[SDL_SCANCODE_D]) {                         //yet i still dont understand why movement is so smooth now.
        // Move Right                             //velocity_x = x_speed which is 0.8 so its actually slower.
        entities[0]->velocity_x = x_speed;        //
    }
    if (keys[SDL_SCANCODE_S]) {
        entities[0]->velocity_x = 0.0f;
        //entities[0]->acceleration_x = 0.0f;
    }
    if (keys[SDL_SCANCODE_W]) {
        if (entities[0]->collidedBot) {           //gravity apply now.
            entities[0]->Jump();                  //
        }
    }
    
    float fixedElapsed = elapsed + timeLeftOver;
    
    while (fixedElapsed >= FIXED_TIMESTEP){
        FixedUpdate();
        fixedElapsed -= FIXED_TIMESTEP;
    }
    timeLeftOver = fixedElapsed;
    
    Update(elapsed);	// Handle collisions
    Render();
    
    return done;
}

void SpaceInvader::Render(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    //backgrounds[0]->Render();
    DrawText(font, "Find little alien friend",  0.3, -0.21, 1.0, 1.0, 1.0, 1.0, -0.9f, 1.5);
    DrawText(font, "control: W-> jump A-> left D-> right",  0.3, -0.19, 1.0, 1.0, 1.0, 1.0, -1.8f, 1.3);

    for (int i=0; i<entities.size(); i++) {
        entities[i]->Render();
        if(i==2){
           // cout<<entities[2]->x<<"entities[2]->x "<<entities[2]->y<<" entities[2]->y "<<endl;
           // cout<<"stair # 2 where did you go?"<<endl;
        }
        //cout<<"entity #"<<i<<" rendered"<<endl;
    }
    if (win == true){
        DrawText(font, "Hello", 0.3, -0.2, 1.0f, 0.0, 0.0, 1.0, 1.6,  -1.4);
            //void SpaceInvader::DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x, float y) {
        
    }

    SDL_GL_SwapWindow(displayWindow);
}

void SpaceInvader::Update(float elapsed){
    for(int i =0 ; i<entities.size(); i++){
    }
}


//void SpaceInvader::shootBullet(float elapsed){
//    SpriteSheet bulletsSprite = SpriteSheet(bullet, 674.0/1024.0f, 262.0/1024.0f,  22.0/1024.0f,  21.0/1024.0f);
//    bullets[bulletIndex].sprite = bulletsSprite;
//    bullets[bulletIndex].visiable = true;
//    bullets[bulletIndex].x = entities[0]->x;
//    bullets[bulletIndex].y = entities[0]->y;
//    bullets[bulletIndex].scale = 1.0;
//    bullets[bulletIndex].speed = 4.0f;
//    bulletIndex++;
//    if(bulletIndex > MAX_BULLETS-1) {
//        bulletIndex = 0;
//    }
//}

bool SpaceInvader::CollisionDetect(Entity& entity, Entity& bullet) {
    float entity_top = entity.y + (entity.sprite.height / 2.0f);
    float entity_bot = entity.y - (entity.sprite.height / 2.0f);
    float entity_right = entity.x + (entity.sprite.width/ 2.0f);
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
    glLoadIdentity();
    glLoadIdentity();
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
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
}

void SpaceInvader::FixedUpdate(){
//   // for (int i =0; i< entities.size(); i++){                 // so game starts, its moving to right because x = Vx * time_step;
//        entities[0]->y+= entities[0]->velocity_y*FIXED_TIMESTEP;
//        entities[0]->x+= entities[0]->velocity_x*FIXED_TIMESTEP;
//        if(!(entities[0]->isStatic)){                        //whats going on here. if entity this not static, then velocity_y reduce by gravity.
//            entities[0]->velocity_y -= gravity_y * FIXED_TIMESTEP;
//            cout<<"\n"<<entities[0]->velocity_y<<"\n";
//            entities[0]->velocity_x = lerp(entities[0]->velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
//
//        }
//        entities[0]->collidesWith(entities[1]);
//        if(entities[0]->collidedTop||entities[0]->collidedBot){          //what should we do now. ->figure out what happened when we press S or A.
//            entities[0]->velocity_y=0.0f;
//            cout<<"returning collision\n";
//            float yPenetration = s(s(entities[1]->y - entities[0]->y) - entities[0]->sprite.height *entities[0]->scale/ 2.0f - entities[1]->scale*entities[1]->sprite.height / 2.0f);
//            cout<<"ypenetration:"<<yPenetration<<endl;

//            entities[0]->y += yPenetration + 0.001f;
//            
    //        }                        DrawText(font, "hello", 0.3, -0.2, 1.0, 0.5, 0.5, 0.5, 1.4, -1.1);

    for (size_t i = 0; i < entities.size(); i++) {

        if (entities[i]->collidedBot) {
            entities[i]->inJump = false;	// the entity is no longer jumping
            entities[i]->velocity_y = 0.0f; // stop the entity
            entities[i]->acceleration_y = 0.0f;
        }
        if (entities[i]->collidedTop) {
            entities[i]->velocity_y = 0.0f; // Let gravity take over
            entities[i]->acceleration_y = 0.0f;
        }
        if (entities[i]->collidedLeft) {
           // cout<<"whats there on the left?"<<endl;
            entities[i]->velocity_x = 0.0f;
            entities[i]->acceleration_x = 0.0f;
        }
        if (entities[i]->collidedRight) {
            //cout<<"whats there on the right?"<<endl;

            entities[i]->velocity_x = 0.0f; // prevent the entity from going through wall
            entities[i]->acceleration_x = 0.0f;
        }
        
        entities[i]->resetFlags();
        
        if (!(entities[i]->isStatic)) {
            entities[i]->velocity_y -= gravity_y * FIXED_TIMESTEP;
        }
        
        entities[i]->velocity_x = lerp(entities[i]->velocity_x, 0.0f, FIXED_TIMESTEP * entities[i]->friction_x);
        entities[i]->velocity_y = lerp(entities[i]->velocity_y, 0.0f, FIXED_TIMESTEP * entities[i]->friction_y);
        
        entities[i]->velocity_x += entities[i]->acceleration_x * FIXED_TIMESTEP;
        entities[i]->velocity_y += entities[i]->acceleration_y * FIXED_TIMESTEP;
        
        entities[i]->y += entities[i]->velocity_y * FIXED_TIMESTEP;
        
        if (!(entities[i]->isStatic)){
            for (size_t j = 0; j < entities.size(); j++){
                if (CollisionDetect(*entities[i], *entities[j]) && (entities[i] != entities[j])) {
                    // There is a collision and it's not the entity interacting with itself
                 //   cout<<"Still alive!!!"<<endl;
                    float yPenetration = fabs(fabs(entities[j]->y - entities[i]->y)
                                              - (entities[i]->sprite.height  *0.5)
                                              - entities[j]->sprite.height   *0.5);
                    if(i ==0 && j == 20){
                        cout<<"||||||||||||hello||||||||||||"<<endl;
                        win = true;
                        //void SpaceInvader::DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x, float y) {
                    }
                    if (entities[i]->y > entities[j]->y) {
                        entities[i]->y += yPenetration + 0.001f;
                        entities[i]->collidedBot = true;
                    }
                    else if(entities[i]->y <entities[j]->y) {
                        entities[i]->y -= yPenetration + 0.001f;
                        entities[i]->collidedTop = true;
                        
                    }
                }
            }
        }
        
        entities[i]->x += entities[i]->velocity_x * FIXED_TIMESTEP;
        
        if (!(entities[i]->isStatic)){
            for (size_t j = 0; j < entities.size(); j++){
                if (CollisionDetect(*entities[i], *entities[j]) && (entities[i] != entities[j]) && (entities[i] != entities[j])) {
                    float xPenetration = fabs(fabs(entities[j]->x - entities[i]->x)
                                              - (entities[i]->sprite.width  *0.5)
                                              - (entities[j]->sprite.width *0.5));
//                    cout<<"entity i scale is :"<<entities[i]->scale<<endl;
//                    cout<<"entity j scale is :"<<entities[j]->scale<<endl;
//                    cout<<"entity i width is :"<<entities[i]->sprite.width<<endl;
//                    cout<<"entity j width is :"<<entities[j]->sprite.width<<endl;
//                    cout<<"entity i x is :"<<entities[i]->x<<endl;
//                    cout<<"entity j x is :"<<entities[j]->x<<endl;

                    if(i ==0 && j == 20){

                        cout<<"||||||||||||hello||||||||||||"<<endl;
                        win =true;
                        //void SpaceInvader::DrawText(int fontTexture, string text, float size, float spacing, float r, float g, float b, float a, float x, float y) {
                    }
                    
                    if (entities[i]->x > entities[j]->x) {
                        entities[i]->x += xPenetration + 0.001f;
                        entities[i]->collidedLeft = true;
                        
                                           }
                    else if (entities[i]->x < entities[j]->x) {
                        entities[i]->x -= xPenetration + 0.001f;
                        entities[i]->collidedRight = true;
                                          }
                }
            }
        }
    }
        //make player move. the problem is what is speed, velocity. speed initial 1.0, velocity initial 1.0;
        
                                                             //so reduce by 2 * time_step which is 0.0032 a really small number lets see what happens.
  //  }                                                        //nothtign i assume its too small make gravity 50. nothing happened.
                                                             //i didnt write y dir movement yet lol. NOW so slow.
}                                                            // its not right. why so slow. velovity_y is initially 0.2.
                                                        //Found new problem. collision check is not working very well.
                                                             //so i decide to make velocity_y initially 0. and increase gravity. like real drop.
                                                             //why is it still using gravity = 2.0. 











