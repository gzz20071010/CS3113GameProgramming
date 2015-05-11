
#include "SideScroller.h"
#define NDEBUG
#include <assert.h>
//for read tile map, use absolute path


float SideScroller::genRandomNum(float low, float high) {
    return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}
float SideScroller::lerp(float v0, float v1, float t) {
	return (1.0f - t)*v0 + t*v1;
}
bool AlmostEqual2sComplement(float A, float B, int maxUlps){
    // Make sure maxUlps is non-negative and small enough that the
    // default NAN won't compare as equal to anything.
    assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);
    int aInt = *(int*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
    int bInt = *(int*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;
    int intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;
    return false;
}
int SideScroller::calculateIndex(int index){
    if(index ==0||index==12||index==24||index==36){
        index = 1;
    }else if(index ==2||index == 14||index ==26||index==38){
        index = 1;
    }else if(index ==1||index ==13||index==25||index==37){
        index = 1;
    }
    
    else if(index ==3||index==15||index==27||index==39){
        index = 4;
    }else if(index ==4||index == 16||index ==28||index==40){
        index = 4;
    }else if(index ==5||index ==17||index==29||index==41){
        index = 4;
    }
    
    else if(index ==6||index==18||index==30||index==42){
        index = 7;
    }else if(index ==7||index == 19||index ==31||index==43){
        index = 7;
    }else if(index ==8||index ==20||index==32||index==44){
        index = 7;
    }
    else if(index ==9||index==21||index==33||index==45){
        index = 10;
    }else if(index ==10||index == 22||index ==34||index==46){
        index = 10;
    }else if(index ==11||index ==23||index==35||index==47){
        index = 10;
    }
    
    else if(index ==48||index==60||index==72||index==84){
        index = 49;
    }else if(index ==49||index == 61||index ==73||index==85){
        index = 49;
    }else if(index ==50||index ==62||index==74||index==86){
        index = 49;
    }
    
    else if(index ==51||index==63||index==75||index==87){
        index = 52;
    }else if(index ==52||index == 64||index ==76||index==88){
        index = 52;
    }else if(index ==53||index ==65||index==77||index==89){
        index = 52;
    }
    
    else if(index ==54||index==66||index==78||index==90){
        index = 55;
    }else if(index ==55||index == 67||index ==79||index==91){
        index = 55;
    }else if(index ==56||index ==68||index==80||index==92){
        index = 55;
    }
    else if(index ==57||index==69||index==81||index==93){
        index = 58;
    }else if(index ==58||index == 70||index ==82||index==94){
        index = 58;
    }else if(index ==59||index ==71||index==83||index==95){
        index = 58;
    }
    return index;
}
void SideScroller::DrawText(GLuint fontTexture, string text, float size, float spacing, float r, float g, float b, float a) {
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float texture_size = 1.0 / 16.0f;
	vector<float> vertexData;
	vector<float> texCoordData;
	vector<float> colorData;

	for (size_t i = 0; i < text.size(); i++) {
		float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
		float texture_y = (float)(((int)text[i]) / 16) / 16.0f;

		colorData.insert(colorData.end(), { r, g, b, a, r, g, b, a, r, g, b, a, r, g, b, a });
		vertexData.insert(vertexData.end(), { ((size + spacing) * i) + (-0.5f* size), 0.5f* size, ((size + spacing) * i) + (-0.5f* size), -0.5f* size, ((size + spacing) * i) + (0.5f* size), -0.5f* size, ((size + spacing) * i) + (0.5f* size), 0.5f * size });
		texCoordData.insert(texCoordData.end(), { texture_x, texture_y, texture_x, texture_y + texture_size, texture_x + texture_size, texture_y + texture_size, texture_x + texture_size, texture_y });
	}

	glColorPointer(4, GL_FLOAT, 0, colorData.data());
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawArrays(GL_QUADS, 0, text.size() * 4.0f);
	glDisableClientState(GL_COLOR_ARRAY);
}

SideScroller::SideScroller() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Side-Scroller", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-2.66, 2.66, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);

	// general values
	done = false;
	lastFrameTicks = 0.0f;
	timeLeftOver = 0.0f;
    time(&timer);
	
	// setting gravity
	gravity_x = 0.0f;
	//gravity_y = -9.8f;
    gravity_y = 0.0f;
	// loading textures
	layoutSpriteSheetTexture = LoadTexture("sheet_4.png");
	characterSpriteSheetTexture = LoadTexture("characters_1.png");
    characterSpriteSheetTexture2 = LoadTexture("characters_2.png");
    characterSpriteSheetTexture3 = LoadTexture("characters_3.png");
    enemySheetTexture1 = LoadTexture("enemySheet.png");
	fontSheetTexture = LoadTexture("pixel_font.png");
    background_images = LoadTexture("bgp.jpg");
    background_images2 = LoadTexture("bgp3.jpg");
    equipment = LoadTexture("equipment.png");

	// setting state
	state = STATE_MAIN_MENU;
    enemyKilled = 0;
    enemyKilled2 = 0;

	Init();
}
SideScroller::~SideScroller() {
	SDL_Quit();
}

void SideScroller::Init() {
    
        
    
	// insert player as the first entity
	SpriteSheet playerSprite = SpriteSheet(characterSpriteSheetTexture, 12, 8, 1);
	Entity* player = new Entity();
	player->sprite = playerSprite;
	player->x = -4.0f;
	player->y = -2.5f;
	player->width = 0.4f;
	player->height = 0.4f;
	player->friction_x = 3.0f;
    player->friction_y = 3.0f;
	player->isPlayer = true;

	entities.push_back(player);
    
    //generate EOG team
    for(int i = 0; i<4; i++){
        SpriteSheet playerSprite3 = SpriteSheet(characterSpriteSheetTexture, 12, 8, (i)*3+1);
        Entity* player = new Entity();
        player->sprite = playerSprite3;
        player->x = i*0.4f;
        player->y = -.5f;
        player->width = 0.4f;
        player->height = 0.4f;
        player->friction_x = 3.0f;
        player->friction_y = 3.0f;
        player->isPlayer = true;
        
        EOGteam.push_back(player);
    }
    
    //background image
    SpriteSheet background_sprite = SpriteSheet(background_images, 0.0f,0.0f,1.0f,0.8f);
    background = new Entity();
    background->sprite = background_sprite;
    background->x = -1.0f;
    background->y = -1.0f;
    background->scale= 4.33f;
    
    SpriteSheet background_sprite2 = SpriteSheet(background_images2, 0.0f,0.0f,1.0f,0.8f);
    background2 = new Entity();
    background2->sprite = background_sprite2;
    background2->x = -1.0f;
    background2->y = -1.0f;
    background2->scale= 4.33f;
    
    
    //music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096 );
    shoot  = Mix_LoadWAV("pling9.wav");
    shoot1 = Mix_LoadWAV("pling1.wav");
    shoots.push_back(shoot1);
    shoot2 = Mix_LoadWAV("pling2.wav");
    shoots.push_back(shoot2);

    shoot3 = Mix_LoadWAV("pling3.wav");
    shoots.push_back(shoot3);

    shoot4 = Mix_LoadWAV("pling4.wav");
    shoots.push_back(shoot4);

    shoot5 = Mix_LoadWAV("pling5.wav");
    shoots.push_back(shoot5);

    shoot6 = Mix_LoadWAV("pling6.wav");
    shoots.push_back(shoot6);

    shoot7 = Mix_LoadWAV("pling7.wav");
    shoots.push_back(shoot7);

    shoot8 = Mix_LoadWAV("pling8.wav");
    shoots.push_back(shoot8);


    shoot10 = Mix_LoadWAV("pling10.wav");
    shoots.push_back(shoot10);

    shoot11 = Mix_LoadWAV("pling11.wav");
    shoots.push_back(shoot11);
    
    shoot12 = Mix_LoadWAV("pling12.wav");
    shoots.push_back(shoot12);

    pickUp = Mix_LoadWAV("pickup.wav");
    
    GroupEnemySound = Mix_LoadWAV("groupEnemy.wav");
    
    music = Mix_LoadMUS("juicybgm.mp3");
    
    gameover_sound = Mix_LoadWAV("gameover.wav");

	// build the level, aka read tile file and throw into leveldata
	buildLevel();
}

void SideScroller::generateEnemy(){
    time_t currentTime;
    time(&currentTime);
    float xt,yt;
    xt = genRandomNum(-4.2, 2.4);
    yt = genRandomNum(-4, -0.4);
    SpriteSheet playerSprite2;
    
    if((int)difftime(currentTime,timer)%2==0&&lastSecond!=currentTime){
        cout<<"generate enemy"<<endl;
        if(state==STATE_GAME_LEVEL){
            playerSprite2 = SpriteSheet(characterSpriteSheetTexture, 12, 8, 49+(switchs%3)*3);
        }else{
            playerSprite2 = SpriteSheet(enemySheetTexture1,12,8,49+(switchs%3)*3); //10
        }
        Entity* player2 = new Entity();
        player2->sprite = playerSprite2;
        player2->x = xt;
        player2->y = yt;
        player2->width = 0.4f;
        player2->height = 0.4f;
        player2->friction_x = 3.0f;
        player2->friction_y = 3.0f;
        player2->isPlayer = false;
        player2->isEnemy = true;
        if(player2->distance(entities[0])>=1){
            entities.push_back(player2);
        }
        switchs ++;
    }
    lastSecond = currentTime;
}
void SideScroller::generateGroupEnemy(){
    Mix_PlayChannel(-1, GroupEnemySound, 0);
    SpriteSheet playerSprite2;
    for(int i = 0; i<4; i++){
        if(state==STATE_GAME_LEVEL){
            playerSprite2 = SpriteSheet(characterSpriteSheetTexture, 12, 8, 49+i*3);

        }else if(state==STATE_GAME_LEVEL2){
            playerSprite2 = SpriteSheet(enemySheetTexture1, 12, 8, 49+i*3);
        }
        Entity* player2 = new Entity();
        player2->sprite = playerSprite2;
        player2->x = 1.0f+i*0.3;
        player2->y = -1.2f;
        player2->velocity_x = -0.8f;
        player2->velocity_y = 0.0f;
        player2->width = 0.4f;
        player2->height = 0.4f;
        player2->friction_x = 3.0f;
        player2->friction_y = 3.0f;
        player2->isPlayer = false;
        player2->isEnemy = true;
        if(player2->distance(entities[0])>=0.5){
            enemyTeam.push_back(player2);
        }
    }
    for(int i = 0; i<4; i++){
        if(state==STATE_GAME_LEVEL){
            playerSprite2 = SpriteSheet(characterSpriteSheetTexture, 12, 8, 49+i*3);
            
        }else if(state==STATE_GAME_LEVEL2){
            playerSprite2 = SpriteSheet(enemySheetTexture1, 12, 8, 49+i*3);
        }
        Entity* player2 = new Entity();
        player2->sprite = playerSprite2;
        player2->x = -1.2f-i*0.3;
        player2->y = -2.5f;
        player2->velocity_x = 0.8f;
        player2->velocity_y = 0.0f;
        player2->width = 0.4f;
        player2->height = 0.4f;
        player2->friction_x = 3.0f;
        player2->friction_y = 3.0f;
        player2->isPlayer = false;
        player2->isEnemy = true;
        if(player2->distance(entities[0])>=0.5){
            enemyTeam1.push_back(player2);
        }
    }
    
}
void SideScroller::generateAlly(){
    time_t currentTime;
    time(&currentTime);
    float xt,yt;
    xt = genRandomNum(-3.0, 1.5);
    yt = genRandomNum(-4, 1);
    
    if((int)difftime(currentTime,timer)%5==0&&lastSecond2!=currentTime){
        cout<<"generate ally"<<endl;
        SpriteSheet playerSprite2 = SpriteSheet(characterSpriteSheetTexture, 12, 8, 7);
        Entity* player2 = new Entity();
        player2->sprite = playerSprite2;
        player2->x = xt;
        player2->y = yt;
        player2->width = 0.4f;
        player2->height = 0.4f;
        player2->friction_x = 3.0f;
        player2->friction_y = 3.0f;
        player2->isPlayer = true;
        player2->isEnemy = false;
        entities.push_back(player2);
    }
    lastSecond2 = currentTime;
}
void SideScroller::generateBonusAlly(float x, float y){
    int iSecret;
    srand (time(NULL));
    /* generate secret number between 1 and 10: */
    iSecret = rand() % 9 + 1;
    switch (iSecret) {
            // 37 is floor
        case 1:{
            SpriteSheet playerSprite2 = SpriteSheet(characterSpriteSheetTexture, 12, 8, 7);
            Entity* player2 = new Entity();
            player2->sprite = playerSprite2;
            player2->x = x;
            player2->y = y;
            
            player2->width = 0.4f;
            player2->height = 0.4f;
            player2->friction_x = 3.0f;
            player2->friction_y = 3.0f;
            player2->isPlayer = true;
            player2->isEnemy = false;
            entities.push_back(player2);

            break;
        }
        case 2:{
            SpriteSheet playerSprite2 = SpriteSheet(characterSpriteSheetTexture3, 12, 8, 4);
            Entity* player2 = new Entity();
            player2->sprite = playerSprite2;
            player2->x = x;
            player2->y = y;
            
            player2->width = 0.4f;
            player2->height = 0.4f;
            player2->friction_x = 3.0f;
            player2->friction_y = 3.0f;
            player2->isPlayer = true;
            player2->isEnemy = false;
            entities.push_back(player2);
            
            break;
        }
        case 3:{
            SpriteSheet playerSprite2 = SpriteSheet(characterSpriteSheetTexture3, 12, 8, 7);
            Entity* player2 = new Entity();
            player2->sprite = playerSprite2;
            player2->x = x;
            player2->y = y;
            
            player2->width = 0.4f;
            player2->height = 0.4f;
            player2->friction_x = 3.0f;
            player2->friction_y = 3.0f;
            player2->isPlayer = true;
            player2->isEnemy = false;
            entities.push_back(player2);
            
            break;
        }
        case 4:{
            SpriteSheet playerSprite2 = SpriteSheet(characterSpriteSheetTexture3, 12, 8, 10);
            Entity* player2 = new Entity();
            player2->sprite = playerSprite2;
            player2->x = x;
            player2->y = y;
            
            player2->width = 0.4f;
            player2->height = 0.4f;
            player2->friction_x = 3.0f;
            player2->friction_y = 3.0f;
            player2->isPlayer = true;
            player2->isEnemy = false;
            entities.push_back(player2);
            
            break;
        }
        case 5:{
            SpriteSheet playerSprite2 = SpriteSheet(characterSpriteSheetTexture2, 12, 8, 1);
            Entity* player2 = new Entity();
            player2->sprite = playerSprite2;
            player2->x = x;
            player2->y = y;
            
            player2->width = 0.4f;
            player2->height = 0.4f;
            player2->friction_x = 3.0f;
            player2->friction_y = 3.0f;
            player2->isPlayer = true;
            player2->isEnemy = false;
            entities.push_back(player2);
            
            break;
        }
        case 6:{
            SpriteSheet playerSprite2 = SpriteSheet(characterSpriteSheetTexture2, 12, 8, 4);
            Entity* player2 = new Entity();
            player2->sprite = playerSprite2;
            player2->x = x;
            player2->y = y;
            
            player2->width = 0.4f;
            player2->height = 0.4f;
            player2->friction_x = 3.0f;
            player2->friction_y = 3.0f;
            player2->isPlayer = true;
            player2->isEnemy = false;
            entities.push_back(player2);
            
            break;
        }
        case 7:{
            SpriteSheet playerSprite2 = SpriteSheet(characterSpriteSheetTexture2, 12, 8, 7);
            Entity* player2 = new Entity();
            player2->sprite = playerSprite2;
            player2->x = x;
            player2->y = y;
            
            player2->width = 0.4f;
            player2->height = 0.4f;
            player2->friction_x = 3.0f;
            player2->friction_y = 3.0f;
            player2->isPlayer = true;
            player2->isEnemy = false;
            entities.push_back(player2);
            
            break;
        }
        case 8:{
            SpriteSheet playerSprite2 = SpriteSheet(characterSpriteSheetTexture2, 12, 8, 10);
            Entity* player2 = new Entity();
            player2->sprite = playerSprite2;
            player2->x = x;
            player2->y = y;
            
            player2->width = 0.4f;
            player2->height = 0.4f;
            player2->friction_x = 3.0f;
            player2->friction_y = 3.0f;
            player2->isPlayer = true;
            player2->isEnemy = false;
            entities.push_back(player2);
            
            break;
        }
            
        case 9:{
            SpriteSheet playerSprite2 = SpriteSheet(equipment, 16, 48, 565);
            Entity* player2 = new Entity();
            player2->sprite = playerSprite2;
            player2->x = x;
            player2->y = y;
            
            player2->width = 0.6f;
            player2->height = 0.6f;
            player2->friction_x = 3.0f;
            player2->friction_y = 3.0f;
            player2->isPlayer = false;
            player2->isEnemy = false;
            player2->isTreasure = true;
            entities.push_back(player2);
            
            break;
        }
            

            
            // rest are trees
            
        default:{
            break;
        }
    }
    
};
void SideScroller::generateDiamonds(){
    time(&dimaondTimer);
     for(int i = 0; i<30; i++){
        float xt,yt;
        xt = genRandomNum(-4.2, 2.4);
        yt = genRandomNum(-4, -0.4);
         
        SpriteSheet playerSprite2 = SpriteSheet(equipment, 16, 48, 456+i%4);
        Entity* player2 = new Entity();
        player2->sprite = playerSprite2;
        player2->x = xt;
        player2->y = yt;
        player2->width = 0.4f;
        player2->height = 0.4f;
        player2->friction_x = 3.0f;
        player2->friction_y = 3.0f;
        player2->isPlayer = false;
        player2->isEnemy = false;
        player2->isDiamond = true;
        diamonds.push_back(player2);
    }

}

void SideScroller::buildLevel() {
	// read tile file
    
    //i used the line below to call infile with absolute path
    //ifstream infile("/Users/shengxiangguo/Documents/XCODE/snake/NYUCodebase/untitled.txt");
    ifstream infile("untitled.txt");
    if(!infile.is_open()){
        cout<<"file not open"<<endl;
    }
	string line;
	while (getline(infile, line)) {
		if (line == "[header]") {
			if (!readHeader(infile)) {
				return;
			}
		}
		else if (line == "[layer]") {
			readLayerData(infile);
		}
	}
}
bool SideScroller::readHeader(ifstream& stream) {
	string line;
	mapWidth = -1;
	mapHeight = -1;
	while (getline(stream, line)) {
		if (line == "") { break; }

		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);

		if (key == "width") {
			mapWidth = atoi(value.c_str());
		}
		else if (key == "height"){
			mapHeight = atoi(value.c_str());
		}
	}

	if (mapWidth == -1 || mapHeight == -1) {
		return false;
	}
	else {
		levelData = new unsigned char*[mapHeight];
		for (int i = 0; i < mapHeight; ++i) {
			levelData[i] = new unsigned char[mapWidth];
		}
		return true;
	}
}
bool SideScroller::readLayerData(ifstream& stream) {
	string line;
	while (getline(stream, line)) {
		if (line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if (key == "data") {
			for (int y = 0; y < mapHeight; y++) {
				getline(stream, line);
				istringstream lineStream(line);
				string tile;

				for (int x = 0; x < mapWidth; x++) {
					getline(lineStream, tile, ',');
					unsigned char val = (unsigned char)atoi(tile.c_str());
					if (val > 0) {
						levelData[y][x] = val-1;
					}
					else {
						levelData[y][x] = 0;
					}
				}

			}
		}
	}
	return true;
}

bool SideScroller::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    // -.-h
    elapsed1 = elapsed;
    
    float fixedElapsed = elapsed + timeLeftOver;
    if (fixedElapsed > FIXED_TIMESTEP* MAX_TIMESTEPS) {
        fixedElapsed = FIXED_TIMESTEP* MAX_TIMESTEPS;
    }
    while (fixedElapsed >= FIXED_TIMESTEP&&(state == STATE_GAME_LEVEL||state== STATE_GAME_LEVEL2)) {
        fixedElapsed -= FIXED_TIMESTEP;
        FixedUpdate();
    }
    timeLeftOver = fixedElapsed;
    
    Update(elapsed);
    Render();
    return done;
}
void SideScroller::FixedUpdate() {
    
    //clean up entities vector
    if(state==STATE_GAME_LEVEL2&&!entitiesCleaned){
        for(int i=0; i<entities.size(); i++){
            if(!entities[i]->follow||entities[i]->isEnemy){
                delete entities[i];
                entities.erase(entities.begin()+i);
            }
        }
        entitiesCleaned = true;
    }
    
    //head join team
    if(entities[0]->follow==false){
        team.push_back(entities[0]);
        entities[0]->follow=true;
    }
    // collision
    if (entities[0]->collidedBottom) {
        entities[0]->velocity_y = 0.0f;
    }
    if (entities[0]->collidedTop){
        entities[0]->velocity_y = 0.0f;
    }
    if (entities[0]->collidedLeft){
        entities[0]->velocity_x = 0.0f;
    }
    if (entities[0]->collidedRight){
        entities[0]->velocity_x = 0.0f;
    }
    
    // reset
    entities[0]->collidedBottom = false;
    entities[0]->collidedTop = false;
    entities[0]->collidedLeft = false;
    entities[0]->collidedRight = false;
    
    //wall collision
    collisionY(entities[0]);
    collisionX(entities[0]);
    
    //collision with enemy
    for(int i = 0; i<team.size(); i++){
        for(int j = 0; j<entities.size(); j++){
            if(team[i]->distance(entities[j])<0.3&&entities[j]->isEnemy&&!team[i]->isDead){
                if(i==0){
                    Mix_PlayChannel(-1, gameover_sound, 0);
                    state = STATE_GAME_OVER;
                }else{
                    for(int x = i; x<team.size();x++){
                        team[x]->isDead = true;
                        team.erase(team.begin()+x);
                    }                   // delete team[i];
                    Mix_PlayChannel(-1, gameover_sound, 0);
                    break;
                }
            }
        }
    }
    //erase dead entities
    for(int i = 0; i<entities.size(); i++){
        if(entities[i]->isDead){
            delete entities[i];
            entities.erase(entities.begin()+i);
        }
    }
    for(int i = 0; i<team.size(); i++){
        for(int j = 0; j<enemyTeam.size(); j++){
            if(team[i]->distance(enemyTeam[j])<0.3&&!team[i]->isDead){
                if(i==0){
                    Mix_PlayChannel(-1, gameover_sound, 0);
                    state = STATE_GAME_OVER;
                }else{
                    for(int x = i; x<team.size();x++){
                        team[x]->isDead = true;
                        team.erase(team.begin()+x);
                    }                    // delete team[i];
                    Mix_PlayChannel(-1, gameover_sound, 0);
                    break;
                }
            }
        }
    }
    //erase dead entities
    for(int i = 0; i<entities.size(); i++){
        if(entities[i]->isDead){
            delete entities[i];
            entities.erase(entities.begin()+i);
        }
    }
    for(int i = 0; i<team.size(); i++){
        for(int j = 0; j<enemyTeam1.size(); j++){
            if(team[i]->distance(enemyTeam1[j])<0.3&&!team[i]->isDead){
                if(i==0){
                    Mix_PlayChannel(-1, gameover_sound, 0);
                    state = STATE_GAME_OVER;
                }else{
                    for(int x = i; x<team.size();x++){
                        team[x]->isDead = true;
                        team.erase(team.begin()+x);
                    }
                    Mix_PlayChannel(-1, gameover_sound, 0);
                    break;
                }
            }
        }
    }
    //erase dead entities
    for(int i = 0; i<entities.size(); i++){
        if(entities[i]->isDead){
            delete entities[i];
            entities.erase(entities.begin()+i);
        }
    }
    //collision with head
    for(int i = 1; i<team.size(); i++){
        if(team[0]->distance(team[i])<0.2&&!team[i]->isDead){
            for(int x = i; x<team.size();x++){
                team[x]->isDead = true;
                team.erase(team.begin()+x);
            }
            // delete team[i];
            Mix_PlayChannel(-1, gameover_sound, 0);
            break;
        }
    }
    //erase dead entities
    for(int i = 0; i<entities.size(); i++){
        if(entities[i]->isDead){
            delete entities[i];
            entities.erase(entities.begin()+i);
        }
    }
    //collision with itself
    for(int i = 1; i<team.size(); i++){
        for(int j = 1; j<team.size(); j++){
            if(i!=j){
                if(team[i]->distance(team[j])<0.2&&!team[i]->isDead){
                    int temp = 0;
                    if(i>j){
                        temp =j;
                    }else{
                        temp = i;
                    }
                    for(int x = temp; x<team.size();x++){
                        team[x]->isDead = true;
                        team.erase(team.begin()+x);
                    }
                    // delete team[i];
                    Mix_PlayChannel(-1, gameover_sound, 0);
                    break;
                }
            }
        }
    }
    
    //lost teammates
    for(int i = 1; i<team.size(); i++){
        if(team[i]->distance(team[i-1])>0.5){
            for(int x = i; x<team.size();x++){
                team[x]->isDead = true;
                    team.erase(team.begin()+x);
            }
            // delete team[i];
            Mix_PlayChannel(-1, gameover_sound, 0);
            break;
        }
    }
    
  
    
    //generate entities randomly
    generateEnemy();
    // generateAlly();
    
    //team member movement
    for (size_t i = 0; i < team.size(); i++) {
        // update y values
        team[i]->y += team[i]->velocity_y * FIXED_TIMESTEP;
        // update x values
        team[i]->x += team[i]->velocity_x * FIXED_TIMESTEP;
    }
    
    //generate group enemy.
    if(!enemyGroupGenerated){
        generateGroupEnemy();
        enemyGroupGenerated = true;
    }
 
    //enemy team position update.
    for (size_t i = 0; i < enemyTeam.size(); i++) {
        // update y values
        enemyTeam[i]->y += enemyTeam[i]->velocity_y * FIXED_TIMESTEP;
        // update x values
        enemyTeam[i]->x += enemyTeam[i]->velocity_x * FIXED_TIMESTEP;
    }
    for (size_t i = 0; i < enemyTeam1.size(); i++) {
        // update y values
        enemyTeam1[i]->y += enemyTeam1[i]->velocity_y * FIXED_TIMESTEP;
        // update x values
        enemyTeam1[i]->x += enemyTeam1[i]->velocity_x * FIXED_TIMESTEP;
    }

    
    //enemy team movement
    for (size_t i = 0; i < enemyTeam.size(); i++) {
        if(enemyTeam[i]->distancePoint(-1.2f, -1.2f)<=0.1f){
            enemyTeam[i]->velocity_x=0;
            enemyTeam[i]->velocity_y=-0.8;
        }else if(enemyTeam[i]->distancePoint(-1.2f, -2.2f)<=0.1f){
            enemyTeam[i]->velocity_x=0.8;
            enemyTeam[i]->velocity_y=0;
        }else if(enemyTeam[i]->distancePoint(1.0f, -2.2f)<=0.1f){
            enemyTeam[i]->velocity_x=0;
            enemyTeam[i]->velocity_y=0.8;
        }else if(enemyTeam[i]->distancePoint(1.0f, -1.2f)<=0.1f){
            enemyTeam[i]->velocity_x=-0.8;
            enemyTeam[i]->velocity_y=0;
        }
    }
    for (size_t i = 0; i < enemyTeam1.size(); i++) {
        if(enemyTeam1[i]->distancePoint(1.0f, -2.5f)<=0.1f){
            enemyTeam1[i]->velocity_x=0;
            enemyTeam1[i]->velocity_y=-0.8;
        }else if(enemyTeam1[i]->distancePoint(1.0f, -3.5f)<=0.1f){
            enemyTeam1[i]->velocity_x=-0.8;
            enemyTeam1[i]->velocity_y=0;
        }else if(enemyTeam1[i]->distancePoint(-1.2f, -3.5f)<=0.1f){
            enemyTeam1[i]->velocity_x=0;
            enemyTeam1[i]->velocity_y=0.8;
        }else if(enemyTeam1[i]->distancePoint(-1.2f, -2.5f)<=0.1f){
            enemyTeam1[i]->velocity_x=0.8;
            enemyTeam1[i]->velocity_y=0;
        }
    }


    //join team
    for(size_t j = 1; j < entities.size(); j++) {
        //collide with free agent,
        if(entities[j]->collidesWith(entities[0])&&entities[j]->follow==false&&entities[j]->isEnemy==false&&entities[j]->isTreasure==false){
            team.push_back(entities[j]);
            Mix_PlayChannel(-1, pickUp, 0);
            
            cout<<"team push back entity "<<j<<endl;
            entities[j]->follow = true;
            
            //initiate position for new member
            if(team[team.size()-2]->direction==1){
                entities[j]->x=team[team.size()-2]->x+0.3;
                entities[j]->y=team[team.size()-2]->y;
                entities[j]->walkLeft();
                entities[j]->direction = 1;
            }else if(team[team.size()-2]->direction==2){
                entities[j]->x=team[team.size()-2]->x-0.3;
                entities[j]->y=team[team.size()-2]->y;
                entities[j]->walkRight();
                entities[j]->direction = 2;
            }else if(team[team.size()-2]->direction==3){
                entities[j]->x=team[team.size()-2]->x;
                entities[j]->y=team[team.size()-2]->y-0.4;
                entities[j]->walkUp();
                entities[j]->direction = 3;
            }else if(team[team.size()-2]->direction==4){
                entities[j]->x=team[team.size()-2]->x;
                entities[j]->y=team[team.size()-2]->y+0.4;
                entities[j]->walkDown();
                entities[j]->direction = 4;
            }
            
            //initiate old_turning points for new member
            if(team[team.size()-2]->old_x.size()!=0&&team.size()>=2){
                for(int p = 0; p<team[team.size()-2]->old_x.size(); p++){
                    entities[j]->old_x.push_back(team[team.size()-2]->old_x[p]);
                    entities[j]->old_y.push_back(team[team.size()-2]->old_y[p]);
                    entities[j]->old_dir.push_back(team[team.size()-2]->old_dir[p]);
                    
                }
            }
        }
    }
    
    //turing point data
    for(size_t m = 1; m<team.size(); m++){
        //when agent is on the turing point
        if(team[m]->old_x.size()!=0){
            //cout<<team[m]->x<<" "<<team[m]->y<<" "<<team[m]->old_x[0]<<" "<<team[m]->old_y[0]<<endl;
            //if((team[m]->x-team[m]->old_x[0]<=0.000001f)&&(team[m]->y-team[m]->old_y[0]<=0.000001f)){
            if(AlmostEqual2sComplement(team[m]->x, team[m]->old_x[0], 500)&&AlmostEqual2sComplement(team[m]->y, team[m]->old_y[0], 500)){
                cout<<"turning point!"<<endl;
                cout<<team[m]->old_dir.size()<<endl;
                //assign entity dir to point turing dir
                team[m]->direction = team[m]->old_dir[0];
                //based on dir to make move
                if(team[m]->direction==1){
                    team[m]->walkLeft();
                }else if(team[m]->direction==2){
                    team[m]->walkRight();
                }else if(team[m]->direction==3){
                    team[m]->walkUp();
                }else if(team[m]->direction==4){
                    team[m]->walkDown();
                }
                //erase used turning point
                team[m]->old_dir.erase(team[m]->old_dir.begin());
                team[m]->old_x.erase(team[m]->old_x.begin());
                team[m]->old_y.erase(team[m]->old_y.begin());
                cout<<team[m]->old_dir.size()<<endl;
            }
        }
    }
    
    
    //auto shooting enemy detection
    time_t currentTime;
    time(&currentTime);
    for(size_t i=0; i<team.size();i++){
        //single enemy
        for(size_t j=0; j<entities.size(); j++){
            if(entities[j]->isEnemy&&(int)difftime(currentTime,timer)%1==0&&lastSecond3!=currentTime){
                if(team[i]->distance(entities[j])<=level1Detection) {
                    Mix_PlayChannel(-1, shoot, 0);
                    team[i]->enemyDetection(entities[j],(int)i);

                }
            }
        }
        //group enemy
        for(size_t j=0; j<enemyTeam.size(); j++){
            if(enemyTeam[j]->isEnemy&&(int)difftime(currentTime,timer)%1==0&&lastSecond3!=currentTime){
                if(team[i]->distance(enemyTeam[j])<=level1Detection) {
                    Mix_PlayChannel(-1, shoot, 0);
                    team[i]->enemyDetection(enemyTeam[j], (int)i);

                }

            }
        }
        for(size_t j=0; j<enemyTeam1.size(); j++){
            if(enemyTeam1[j]->isEnemy&&(int)difftime(currentTime,timer)%1==0&&lastSecond3!=currentTime){
                if(team[i]->distance(enemyTeam1[j])<=level1Detection) {
                    Mix_PlayChannel(-1, shoot, 0);
                    team[i]->enemyDetection(enemyTeam1[j],(int)i);

                }
            }
        }
    }
    lastSecond3= currentTime;
    
    //auto shooting player detection
    if(state==STATE_GAME_LEVEL2){
        time_t currentTime2;
        time(&currentTime2);
        for(size_t i=0; i<entities.size();i++){
            for(size_t j=0; j<team.size(); j++){
                if(entities[i]->isEnemy&&(int)difftime(currentTime2,timer)%3==0&&lastSecond4!=currentTime2){
                    //=====
                    if(entities[i]->distance(team[j])<=2) {
                     //   Mix_PlayChannel(-1, shoot, 0);
                        entities[i]->enemyDetection(team[j],(int)i);
                        break;
                    }
                }
            }
//            //group enemy
//            for(size_t j=0; j<enemyTeam.size(); j++){
//                if(enemyTeam[j]->isEnemy&&(int)difftime(currentTime,timer)%1==0&&lastSecond4!=currentTime){
//                    if(team[i]->distance(enemyTeam[j])<=level1Detection) {
//                        Mix_PlayChannel(-1, shoot, 0);
//                        team[i]->enemyDetection(enemyTeam[j], (int)i);
//                    
//                    }
//                
//                }
//            }
//            for(size_t j=0; j<enemyTeam1.size(); j++){
//                if(enemyTeam1[j]->isEnemy&&(int)difftime(currentTime,timer)%1==0&&lastSecond4!=currentTime){
//                    if(team[i]->distance(enemyTeam1[j])<=level1Detection) {
//                        Mix_PlayChannel(-1, shoot, 0);
//                        team[i]->enemyDetection(enemyTeam1[j],(int)i);
//                        
//                    }
//                }
//            }
        }
        lastSecond4= currentTime;
    }
    
    
    //bullet collision to single enemy
    for (int j = 0; j < 30; j++){
        for(int i = 0; i<team.size(); i++){
            for(int n = 0; n<entities.size(); n++){
                if (team[i]->bullets[j].visiable &&( entities[n]->distanceBullet(team[i]->bullets[j])<=0.3f)&&entities[n]->isEnemy) {
                    team[i]->bullets[j].visiable = false;
                    generateBonusAlly(entities[n]->x, entities[n]->y);
                    enemyKilled++;
                    if(state==STATE_GAME_LEVEL2){
                        enemyKilled2++;
                    }
                    delete entities[n];
                    entities.erase(entities.begin() + n);
                    break;
                }
            }
        }
    }
    
    // bullet collision to group enemy
    for (int j = 0; j < 30; j++){
        for(int i = 0; i<team.size(); i++){
            for(int n = 0; n<enemyTeam.size(); n++){
                if (team[i]->bullets[j].visiable &&( enemyTeam[n]->distanceBullet(team[i]->bullets[j])<=0.3f)) {
                    team[i]->bullets[j].visiable = false;
                    //generateBonusAlly(entities[n]->x, entities[n]->y);
                    enemyKilled++;
                    if(state==STATE_GAME_LEVEL2){
                        enemyKilled2++;
                    }
                    delete enemyTeam[n];
                    enemyTeam.erase(enemyTeam.begin() + n);
                    break;
                }
            }
            for(int n = 0; n<enemyTeam1.size(); n++){
                if (team[i]->bullets[j].visiable &&( enemyTeam1[n]->distanceBullet(team[i]->bullets[j])<=0.3f)) {
                    team[i]->bullets[j].visiable = false;
                    //generateBonusAlly(entities[n]->x, entities[n]->y);
                    enemyKilled++;
                    if(state==STATE_GAME_LEVEL2){
                        enemyKilled2++;
                    }
                    delete enemyTeam1[n];
                    enemyTeam1.erase(enemyTeam1.begin() + n);
                    break;
                }
            }
        }
    }
    
    //bullet collision with player
    for (int j = 0; j < 30; j++){
        for(int i = 0; i<entities.size(); i++){
            for(int n = 0; n<team.size(); n++){
                if (entities[i]->bullets[j].visiable &&( team[n]->distanceBullet(entities[i]->bullets[j])<=0.3f)&&entities[i]->isEnemy) {
                    if(n==0){
                        Mix_PlayChannel(-1, gameover_sound, 0);
                        state= STATE_GAME_OVER;
                    }else{
                        Mix_PlayChannel(-1, gameover_sound, 0);
                        entities[i]->bullets[j].visiable = false;
                        team[n]->isDead = true;
                        team.erase(team.begin() + n);
                        break;
                    }
                }
            }
        }
    }
    
    if(enemyTeam.size()==0||enemyTeam1.size()==0){
        enemyGroupGenerated = false;
    }
    
    if(enemyKilled>50&&state!= STATE_TRANSITION&&state!=STATE_GAME_LEVEL2&&state!=STATE_GAME_OVER){
        state = STATE_TRANSITION;
    }
    if(enemyKilled2>20&&state!= STATE_TRANSITION&&state==STATE_GAME_LEVEL2&&state!=STATE_GAME_OVER){
        state = STATE_GAME_OVER;
    }
    
    //head collide with treasure box
    for(int i =0; i<entities.size(); i++){
        if(entities[i]->isTreasure&&team[0]->distance(entities[i])<0.4){
            entities.erase(entities.begin()+i);
            generateDiamonds();
        }
    }
    
    //pick up diamonds
    for(int i =0; i<diamonds.size(); i++){
        for(int j=0; j<team.size(); j++){
            if(team[j]->distance(diamonds[i])<0.3){
                delete diamonds[i];
                diamondsPicked++;
                diamonds.erase(diamonds.begin()+i);
                Mix_PlayChannel(-1, shoot12, 0);
            }
        }
    }
    
    //diamond time out
    time_t current;
    time(&current);
    if(difftime(current, dimaondTimer)>4){
        for(int i =0; i<diamonds.size(); i++){
            delete diamonds[i];
            diamonds.erase(diamonds.begin()+i);
        }
    }
}

void SideScroller::Update(float elapsed) {
	switch (state) {
	case STATE_MAIN_MENU:
		updateMainMenu(elapsed);
		break;
	case STATE_GAME_LEVEL:
		updateGameLevel(elapsed);
		break;
    case STATE_TRANSITION:
        updateTransition(elapsed);
        break;
    case STATE_GAME_LEVEL2:
        updateGameLevel2(elapsed);
        break;
    case STATE_GAME_OVER:
        updateGameOver(elapsed);
        break;
    }
}
void SideScroller::updateMainMenu(float elapsed) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				state = STATE_GAME_LEVEL;
				break;
			}
		}
	}

}
void SideScroller::updateGameLevel(float elapsed) {
	// keyboard controls
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
	}

	const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    if(state == STATE_GAME_LEVEL&&musicStart==false){
        Mix_PlayMusic(music, -1);
        musicStart = true;
    }

    animationElapsed += elapsed;
    if(animationElapsed > 1.0/framesPerSecond) {
        currentIndex++;
        animationElapsed = 0.0;
        if(currentIndex > numFrames-1) {
            currentIndex = 0;
        }
    }

    for(int i=0; i<team.size(); i++){
        int index_old = team[i]->sprite.index;
        int index=calculateIndex(index_old);
        const int runAnimationRight2[] = {index+23,index+24,index+25};
        const int runAnimationLeft2[] = {index+11, index+12,index+13};
        const int runAnimationUp2[] = {index+35, index+36,index+37};
        const int runAnimationDown2[] = {index-1,index,index+1};
        
        if( team[i]->direction == 2){
            SpriteSheet playerSprite = SpriteSheet(team[i]->sprite.textureID, 12, 8, runAnimationRight2[currentIndex]);
            team[i]->sprite = playerSprite;
        }else if(team[i]->direction == 3){

            SpriteSheet playerSprite = SpriteSheet(team[i]->sprite.textureID, 12, 8, runAnimationUp2[currentIndex]);
            team[i]->sprite = playerSprite;
            
        }else if(team[i]->direction == 4){

            SpriteSheet playerSprite = SpriteSheet(team[i]->sprite.textureID, 12, 8, runAnimationDown2[currentIndex]);
            team[i]->sprite = playerSprite;
            
        }else if(team[i]->direction == 1){

            SpriteSheet playerSprite = SpriteSheet(team[i]->sprite.textureID, 12, 8, runAnimationLeft2[currentIndex]);
            team[i]->sprite = playerSprite;
            
        }

    }
//
	if (keys[SDL_SCANCODE_RIGHT]) {
        entities[0]->direction = 2;
        if (!entities[0]->collidedRight){
            entities[0]->walkRight();
            if(team.size()>1){
                for(int m = 1; m< team.size(); m++){
                    team[m]->saveTurningPoint(entities[0]->x, entities[0]->y, entities[0]->direction);
                }
            }
        }
    }else if (keys[SDL_SCANCODE_LEFT]) {
        entities[0]->direction = 1;
		if (!entities[0]->collidedLeft){
            entities[0]->walkLeft();
            if(team.size()>1){
                for(int m = 1; m< team.size(); m++){
                    team[m]->saveTurningPoint(entities[0]->x, entities[0]->y, entities[0]->direction);
                }
            }
		}
	}else if (keys[SDL_SCANCODE_UP]) {
        entities[0]->direction = 3;
        if (!entities[0]->collidedLeft){
            if(team.size()>1){
                for(int m = 1; m< team.size(); m++){
                    team[m]->saveTurningPoint(entities[0]->x, entities[0]->y, entities[0]->direction);
                }
            }
            entities[0]->walkUp();
        }
    }else if (keys[SDL_SCANCODE_DOWN]) {
        entities[0]->direction = 4;
        if (!entities[0]->collidedLeft){
            if(team.size()>1){
                for(int m = 1; m< team.size(); m++){
                    team[m]->saveTurningPoint(entities[0]->x, entities[0]->y, entities[0]->direction);
                }
            }
            entities[0]->walkDown();
        }
    }else if (keys[SDL_SCANCODE_T]) {
        state = STATE_TRANSITION;
    }else if (keys[SDL_SCANCODE_N]) {
        state = STATE_GAME_LEVEL2;
    }

    
    for(int i=0; i<30; i++){
        for(int j = 0; j<team.size(); j++){
            team[j]->bullets[i].Update(elapsed);
        }
    }
}
void SideScroller::updateGameLevel2(float elapsed) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    animationElapsed += elapsed;
    if(animationElapsed > 1.0/framesPerSecond) {
        currentIndex++;
        animationElapsed = 0.0;
        if(currentIndex > numFrames-1) {
            currentIndex = 0;
        }
    }
    
    for(int i=0; i<team.size(); i++){
        int index_old = team[i]->sprite.index;
        int index=calculateIndex(index_old);
        const int runAnimationRight2[] = {index+23,index+24,index+25};
        const int runAnimationLeft2[] = {index+11, index+12,index+13};
        const int runAnimationUp2[] = {index+35, index+36,index+37};
        const int runAnimationDown2[] = {index-1,index,index+1};
        
        if( team[i]->direction == 2){
            SpriteSheet playerSprite = SpriteSheet(team[i]->sprite.textureID, 12, 8, runAnimationRight2[currentIndex]);
            team[i]->sprite = playerSprite;
        }else if(team[i]->direction == 3){
            
            SpriteSheet playerSprite = SpriteSheet(team[i]->sprite.textureID, 12, 8, runAnimationUp2[currentIndex]);
            team[i]->sprite = playerSprite;
            
        }else if(team[i]->direction == 4){
            
            SpriteSheet playerSprite = SpriteSheet(team[i]->sprite.textureID, 12, 8, runAnimationDown2[currentIndex]);
            team[i]->sprite = playerSprite;
            
        }else if(team[i]->direction == 1){
            
            SpriteSheet playerSprite = SpriteSheet(team[i]->sprite.textureID, 12, 8, runAnimationLeft2[currentIndex]);
            team[i]->sprite = playerSprite;
            
        }
        
    }
    // keyboard controls
    if (keys[SDL_SCANCODE_RIGHT]) {
        entities[0]->direction = 2;
        if (!entities[0]->collidedRight){
            entities[0]->walkRight();
            if(team.size()>1){
                for(int m = 1; m< team.size(); m++){
                    team[m]->saveTurningPoint(entities[0]->x, entities[0]->y, entities[0]->direction);
                }
            }
        }
    }else if (keys[SDL_SCANCODE_LEFT]) {
        entities[0]->direction = 1;
        if (!entities[0]->collidedLeft){
            entities[0]->walkLeft();
            if(team.size()>1){
                for(int m = 1; m< team.size(); m++){
                    team[m]->saveTurningPoint(entities[0]->x, entities[0]->y, entities[0]->direction);
                }
            }
        }
    }else if (keys[SDL_SCANCODE_UP]) {
        entities[0]->direction = 3;
        if (!entities[0]->collidedLeft){
            if(team.size()>1){
                for(int m = 1; m< team.size(); m++){
                    team[m]->saveTurningPoint(entities[0]->x, entities[0]->y, entities[0]->direction);
                }
            }
            entities[0]->walkUp();
        }
    }else if (keys[SDL_SCANCODE_DOWN]) {
        entities[0]->direction = 4;
        if (!entities[0]->collidedLeft){
            if(team.size()>1){
                for(int m = 1; m< team.size(); m++){
                    team[m]->saveTurningPoint(entities[0]->x, entities[0]->y, entities[0]->direction);
                }
            }
            entities[0]->walkDown();
        }
    }else if (keys[SDL_SCANCODE_T]) {
        state = STATE_TRANSITION;
    }else if (keys[SDL_SCANCODE_N]) {
        state = STATE_GAME_LEVEL2;
    }
    
    
    for(int i=0; i<30; i++){
        for(int j = 0; j<team.size(); j++){
            team[j]->bullets[i].Update(elapsed);
        }
    }
    
    for(int i=0; i<30; i++){
        for(int j=0; j<entities.size(); j++){
            entities[j]->bullets[i].Update(elapsed);
        }
    }
    
}
void SideScroller::updateGameOver(float elapsed){
    animationElapsed += elapsed;
    if(animationElapsed > 1.0/(framesPerSecond/3)) {
        currentIndex++;
        animationElapsed = 0.0;
        if(currentIndex > numFrames-1) {
            currentIndex = 0;
        }
    }
    
    for(int i=0; i<EOGteam.size(); i++){
        int index_old = EOGteam[i]->sprite.index;
        int index=calculateIndex(index_old);
        const int runAnimationRight2[] = {index+23,index+24,index+25};
        const int runAnimationLeft2[] = {index+11, index+12,index+13};
        const int runAnimationUp2[] = {index+35, index+36,index+37};
        const int runAnimationDown2[] = {index-1,index,index+1};
        EOGteam[i]->direction = 4;
        if( EOGteam[i]->direction == 2){
            SpriteSheet playerSprite = SpriteSheet(EOGteam[i]->sprite.textureID, 12, 8, runAnimationRight2[currentIndex]);
            EOGteam[i]->sprite = playerSprite;
        }else if(EOGteam[i]->direction == 3){
            
            SpriteSheet playerSprite = SpriteSheet(EOGteam[i]->sprite.textureID, 12, 8, runAnimationUp2[currentIndex]);
            EOGteam[i]->sprite = playerSprite;
            
        }else if(EOGteam[i]->direction == 4){
            
            SpriteSheet playerSprite = SpriteSheet(EOGteam[i]->sprite.textureID, 12, 8, runAnimationDown2[currentIndex]);
            EOGteam[i]->sprite = playerSprite;
            
        }else if(EOGteam[i]->direction == 1){
            
            SpriteSheet playerSprite = SpriteSheet(EOGteam[i]->sprite.textureID, 12, 8, runAnimationLeft2[currentIndex]);
            EOGteam[i]->sprite = playerSprite;
            
        }
        
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
    }
}
void SideScroller::updateTransition(float elapsed){
    animationElapsed += elapsed;
    if(animationElapsed > 1.0/(framesPerSecond/3)) {
        currentIndex++;
        animationElapsed = 0.0;
        if(currentIndex > numFrames-1) {
            currentIndex = 0;
        }
    }
    
    for(int i=0; i<EOGteam.size(); i++){
        int index_old = EOGteam[i]->sprite.index;
        int index=calculateIndex(index_old);
        const int runAnimationRight2[] = {index+23,index+24,index+25};
        const int runAnimationLeft2[] = {index+11, index+12,index+13};
        const int runAnimationUp2[] = {index+35, index+36,index+37};
        const int runAnimationDown2[] = {index-1,index,index+1};
        EOGteam[i]->direction = 4;
        if( EOGteam[i]->direction == 2){
            SpriteSheet playerSprite = SpriteSheet(EOGteam[i]->sprite.textureID, 12, 8, runAnimationRight2[currentIndex]);
            EOGteam[i]->sprite = playerSprite;
        }else if(EOGteam[i]->direction == 3){
            
            SpriteSheet playerSprite = SpriteSheet(EOGteam[i]->sprite.textureID, 12, 8, runAnimationUp2[currentIndex]);
            EOGteam[i]->sprite = playerSprite;
            
        }else if(EOGteam[i]->direction == 4){
            
            SpriteSheet playerSprite = SpriteSheet(EOGteam[i]->sprite.textureID, 12, 8, runAnimationDown2[currentIndex]);
            EOGteam[i]->sprite = playerSprite;
            
        }else if(EOGteam[i]->direction == 1){
            
            SpriteSheet playerSprite = SpriteSheet(EOGteam[i]->sprite.textureID, 12, 8, runAnimationLeft2[currentIndex]);
            EOGteam[i]->sprite = playerSprite;
            
        }
        
    }
    
   	SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                state = STATE_GAME_LEVEL2;
                break;
            }
        }
    }

}

void SideScroller::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
   // background->Render2();
	switch (state) {
	case STATE_MAIN_MENU:
            renderMainMenu();
            break;
	case STATE_GAME_LEVEL:
            renderGameLevel();
            break;
    case STATE_GAME_LEVEL2:
            renderGameLevel2();
            break;
    case STATE_GAME_OVER:
            renderGameOver();
            break;
    case STATE_TRANSITION:
            renderTransition();
            break;
	}
	SDL_GL_SwapWindow(displayWindow);
}
void SideScroller::renderMainMenu() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.8f, 0.7f, 0.0f);
	DrawText(fontSheetTexture, "Snake", 0.1, 0.0, 1.0, 1.0, 0.0, 1.0);
	glLoadIdentity();
	glTranslatef(-0.8f, 0.2f, 0.0f);
	DrawText(fontSheetTexture, "Press Arrow Keys to Move", 0.05, 0.0, 1.0, 1.0, 1.0, 1.0);
	glLoadIdentity();
	glTranslatef(-0.8f, 0.0f, 0.0f);
	DrawText(fontSheetTexture, "", 0.05, 0.0, 1.0, 1.0, 1.0, 1.0);
	glLoadIdentity();
	glTranslatef(-0.8f, -0.7f, 0.0f);
	DrawText(fontSheetTexture, "Press SPACE to start the game", 0.05, 0.0, 1.0, 1.0, 0.0, 1.0);
    
    
}
void SideScroller::renderGameLevel() {
	loadLevel();

//    glClearColor(0.5f, 0.5f, 0.0f, 0.5f);
//	glClear(GL_COLOR_BUFFER_BIT);
    
    background->Render2();

	// setting limits on view
	float xloc = -entities[0]->x;
	float yloc = -entities[0]->y;

  
	if (yloc > 2.8){
		yloc = 2.80;
	}
    if (yloc < 1.8){
        yloc = 1.8;
    }
    
	if (xloc > 2.34){
		xloc = 2.34;
	}
	if (xloc < -.70){
		xloc = -.70;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xloc, yloc, 0.0f);
 

	// render level
	glBindTexture(GL_TEXTURE_2D, layoutSpriteSheetTexture);
	glEnable(GL_TEXTURE_2D);

	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(-TILE_SIZE* mapWidth / 2, TILE_SIZE* mapHeight / 2.0f, 0.0f);

	glDrawArrays(GL_QUADS, 0, vertexData.size() / 2.0f);

	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glDrawArrays(GL_QUADS, 0, vertexData.size() / 2.0f);

    glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();

    for(int j=0; j< team.size(); j++){
        for (int i= 0; i < 30; i++){
            if(team[j]->bullets[i].cd>=0.25f){
               // team[j]->shootBullet();
                team[j]->bullets[i].Draw();
            }else{
                team[j]->bullets[i].cd += elapsed1;
            }
        }
    }
    

	for (size_t i = 0; i < entities.size(); i++) {
        if(!entities[i]->isDead){
            entities[i]->Render();
        }
    }
    
    for (size_t i = 0; i < enemyTeam.size(); i++) {
        enemyTeam[i]->Render();
    }
    for (size_t i = 0; i < enemyTeam1.size(); i++) {
        enemyTeam1[i]->Render();
    }
    
    time_t current;
    time(&current);
    if(difftime(current, dimaondTimer)<=4){
        for(size_t i =0; i<diamonds.size(); i++){
            diamonds[i]->Render();
        }
    }
    
    glPushMatrix();
    glTranslated(-xloc-2.2f, -yloc+1.7f, 0);
    DrawText(fontSheetTexture, "coins :"+to_string(diamondsPicked), 0.1, 0.0, 1.0, 1.0, 0.0, 1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-xloc-2.2f, -yloc+1.5f, 0);
    DrawText(fontSheetTexture, "enemy left :"+to_string(50-enemyKilled), 0.1, 0.0, 1.0, 1.0, 0.0, 1.0);
    glPopMatrix();
}
void SideScroller::renderGameLevel2() {
    loadLevel();
    
    //    glClearColor(0.5f, 0.5f, 0.0f, 0.5f);
    //	glClear(GL_COLOR_BUFFER_BIT);
    
    background2->Render2();
    
    // setting limits on view
    float xloc = -entities[0]->x;
    float yloc = -entities[0]->y;
    
    
    if (yloc > 2.8){
        yloc = 2.80;
    }
    if (yloc < 1.8){
        yloc = 1.8;
    }
    
    if (xloc > 2.34){
        xloc = 2.34;
    }
    if (xloc < -.70){
        xloc = -.70;
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(xloc, yloc, 0.0f);
    
    
    // render level
    glBindTexture(GL_TEXTURE_2D, layoutSpriteSheetTexture);
    glEnable(GL_TEXTURE_2D);
    
    glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    glTranslatef(-TILE_SIZE* mapWidth / 2, TILE_SIZE* mapHeight / 2.0f, 0.0f);
    
    glDrawArrays(GL_QUADS, 0, vertexData.size() / 2.0f);
    
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glDrawArrays(GL_QUADS, 0, vertexData.size() / 2.0f);
    
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glPopMatrix();
    
    //render bullets
    for(int j=0; j< team.size(); j++){
        for (int i= 0; i < 30; i++){
            if(team[j]->bullets[i].cd>=0.25f){
                // team[j]->shootBullet();
                team[j]->bullets[i].Draw();
            }else{
                team[j]->bullets[i].cd += elapsed1;
            }
        }
    }
    for(int j=0; j< entities.size(); j++){
        for (int i= 0; i < 30; i++){
            if(entities[j]->bullets[i].cd>=0.25f&&entities[j]->isEnemy&&!entities[j]->isDead){
                entities[j]->bullets[i].Draw();
            }else{
                entities[j]->bullets[i].cd += elapsed1;
            }
        }
    }
    
    //render entities
    for (size_t i = 0; i < entities.size(); i++) {
        if(!entities[i]->isDead){
            entities[i]->Render();
        }
    }
    
    //render enemyTeam
    for (size_t i = 0; i < enemyTeam.size(); i++) {
        enemyTeam[i]->Render();
    }
    for (size_t i = 0; i < enemyTeam1.size(); i++) {
        enemyTeam1[i]->Render();
    }
    
    //render diamonds
    time_t current;
    time(&current);
    if(difftime(current, dimaondTimer)<=4){
        for(size_t i =0; i<diamonds.size(); i++){
            diamonds[i]->Render();
        }
    }
    
    //render score
    glPushMatrix();
    glTranslated(-xloc-2.2f, -yloc+1.7f, 0);
    DrawText(fontSheetTexture, "coins :"+to_string(diamondsPicked), 0.1, 0.0, 1.0, 1.0, 0.0, 1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-xloc-2.2f, -yloc+1.5f, 0);
    DrawText(fontSheetTexture, "enemy left :"+to_string(20-enemyKilled2), 0.1, 0.0, 1.0, 1.0, 0.0, 1.0);
    glPopMatrix();
}
void SideScroller::renderGameOver(){
    
    
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    
    for(int i=0; i<EOGteam.size(); i++){
        EOGteam[i]->Render();
    }
    
    if(enemyKilled2>=20){
       
//        glLoadIdentity();
        glTranslatef(-1.7f, 0.2f, 0.0f);
        DrawText(fontSheetTexture, "You Win!", 0.5, 0.0, -1.0, 1.0, 1.0, 1.0);

     
    }else{
    glLoadIdentity();
    glTranslatef(-1.2f, 0.7f, 0.0f);
    DrawText(fontSheetTexture, "dead dead dead dead dead dead dead", 0.06, 0.0, -1.0, 1.0, 0.0, 1.0);
    glLoadIdentity();
    glTranslatef(-2.0f, 0.2f, 0.0f);
    DrawText(fontSheetTexture, "Game Over", 0.5, 0.0, -1.0, 1.0, 1.0, 1.0);
    }
}
void SideScroller::renderTransition(){
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    for(int i=0; i<EOGteam.size(); i++){
        EOGteam[i]->Render();
    }
    
    if(enemyKilled>=50){
        
        //        glLoadIdentity();
        glTranslatef(-1.7f, 0.2f, 0.0f);
        DrawText(fontSheetTexture, "Congrats!", 0.2, 0.0, -1.0, 1.0, 1.0, 1.0);
        glLoadIdentity();
        glTranslatef(-1.2f, 0.7f, 0.0f);
        DrawText(fontSheetTexture, "press space to next level ", 0.1, 0.0, -1.0, 1.0, 0.0, 1.0);
        
    }else{
        glLoadIdentity();
        glTranslatef(-1.2f, 0.7f, 0.0f);
        DrawText(fontSheetTexture, "press space to next level ", 0.1, 0.0, -1.0, 1.0, 0.0, 1.0);
        glLoadIdentity();
        glTranslatef(-2.0f, 0.2f, 0.0f);
        DrawText(fontSheetTexture, "should never see this page tho", 0.1, 0.0, -1.0, 1.0, 1.0, 1.0);
    }
}



void SideScroller::loadLevel() {
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			float blacklines = 0.003f;
			if (levelData[y][x] != 0){
				float u = (float)(((int)levelData[y][x]) % SPRITE_COUNT_X) / (float)SPRITE_COUNT_X;
				float v = (float)(((int)levelData[y][x]) / SPRITE_COUNT_X) / (float)SPRITE_COUNT_Y;
				float spriteWidth = 1.0f / (float)SPRITE_COUNT_X;
				float spriteHeight = 1.0f / (float)SPRITE_COUNT_Y;
				vertexData.insert(vertexData.end(), {
					TILE_SIZE * x, -TILE_SIZE * y,
					TILE_SIZE * x, (-TILE_SIZE * y) - TILE_SIZE,
					(TILE_SIZE * x) + TILE_SIZE, (-TILE_SIZE * y) - TILE_SIZE,
					(TILE_SIZE * x) + TILE_SIZE, -TILE_SIZE * y
				});
				texCoordData.insert(texCoordData.end(), { u + blacklines, v + blacklines,
					u + blacklines, v + spriteHeight - blacklines,
					u + spriteWidth - blacklines, v + spriteHeight - blacklines,
					u + spriteWidth - blacklines, v + blacklines
				});
			}
		}
	}

}

bool SideScroller::isSolid(unsigned char tile) {
	// says whether or not its solid based on level data
	switch (tile) {
	// 37 is floor
	case 83:
		return true;
		break;
     
	// rest are trees
	default:
		return false;
		break;
	}
}
void SideScroller::collisionX(Entity *entity) {
   // cout<<entity->x;
    if(entity->x <=-4.5){
        entity->collidedLeft = true;
        Mix_PlayChannel(-1, gameover_sound, 0);
        entity->velocity_x=0;
        entity->x = -4.4f;
        state= STATE_GAME_OVER;
    }
    if(entity->x >=2.9){
        entity->collidedRight = true;
        Mix_PlayChannel(-1, gameover_sound, 0);
        entity->velocity_x=0;
        entity->x = -4.4f;

        state= STATE_GAME_OVER;

    }
}
void SideScroller::collisionY(Entity *entity) {
    if(entity->y <=-4.2){
		entity->collidedBottom = true;
        state= STATE_GAME_OVER;
    }
    if(entity->y >=-0.4){
        entity->collidedTop = true;
        state= STATE_GAME_OVER;
    }
}
