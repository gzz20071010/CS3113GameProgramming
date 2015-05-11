

#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <math.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Entity.h"
#include <time.h>

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define BULLET_COOLDOWN	0.25f

#define SPRITE_COUNT_X 14
#define SPRITE_COUNT_Y 8
#define TILE_SIZE 0.2f
using namespace std;

class SideScroller{
public:
	SideScroller();
	~SideScroller();

	// setup
	void Init();

	// all updates
	void Update(float elapsed);
	void updateMainMenu(float elapsed);
	void updateGameLevel(float elapsed);
    void updateTransition(float elapsed);
    void updateGameLevel2(float elapsed);
    void updateGameOver(float elapsed);
	void FixedUpdate();

	// all renders
	void Render();
	void renderMainMenu();
	void renderGameLevel();
    void renderTransition();
    void renderGameLevel2();
    void renderGameOver();

	// update and render (elapsed)
	bool UpdateAndRender();

	//level building
	void buildLevel();
	bool readHeader(ifstream& stream);
	bool readLayerData(ifstream& stream);
	void loadLevel();

	// tile collision
	bool isSolid(unsigned char tile);
	void worldToTileCoordinates(float worldX, float worldY, int* gridX, int* gridY);
	void collisionX(Entity* entity);
	void collisionY(Entity* entity);
    
    
    void generateEnemy();
    void generateGroupEnemy();
    void generateAlly();
    void generateBonusAlly(float x, float y);
    void generateDiamonds();
    void shootBullet();
    bool bulletCollision(Entity& entity, Bullet& bullet);
    
    //useful func
    float genRandomNum(float, float);
    int calculateIndex(int);


	// lerp and drawing text
	void DrawText(GLuint fontTexture, string text, float size, float spacing, float r, float g, float b, float a);
	float lerp(float v0, float v1, float t);

private:
	// general privates
	bool done;
    int enemyKilled;
    int enemyKilled2;
    bool entitiesCleaned = false;
    bool gameover;
    bool enemyGroupGenerated = false;
    bool musicStart = false;
    
	float lastFrameTicks;
	float timeLeftOver;
    time_t timer;
    float elapsed1;
    
    long lastSecond;
    long lastSecond2;
    long lastSecond3;
    long lastSecond4;
	SDL_Window* displayWindow;

	// textures
	GLuint characterSpriteSheetTexture;
    GLuint characterSpriteSheetTexture2;
    GLuint characterSpriteSheetTexture3;
    GLuint enemySheetTexture1;
    GLuint equipment;
	GLuint layoutSpriteSheetTexture;
	GLuint fontSheetTexture;
    GLuint background_images;
    GLuint background_images2;


	// gravity
	float gravity_x;
	float gravity_y;

	// game states
	enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL, STATE_TRANSITION, STATE_GAME_LEVEL2,STATE_GAME_OVER };
	int state;

	// vectors
	vector<Entity*> entities;
    vector<Entity*> entities2;
    vector<Entity*> team;
    vector<Entity*> enemyTeam;
    vector<Entity*> enemyTeam1;
    vector<Entity*> enemyTeam2;
    vector<Entity*> enemyTeam3;
    vector<Entity*> EOGteam;
    vector<Entity*> diamonds;
    
    Entity* background;
    Entity* background2;


	vector<float> vertexData;
	vector<float> texCoordData;

	// map stats
	unsigned int mapWidth;
	unsigned int mapHeight;
	unsigned char** levelData;
    
    Mix_Chunk* shoot;
    Mix_Chunk* shoot1;
    Mix_Chunk* shoot2;
    Mix_Chunk* shoot3;
    Mix_Chunk* shoot4;
    Mix_Chunk* shoot5;
    Mix_Chunk* shoot6;
    Mix_Chunk* shoot7;
    Mix_Chunk* shoot8;
    Mix_Chunk* shoot9;
    Mix_Chunk* shoot10;
    Mix_Chunk* shoot11;
    Mix_Chunk* shoot12;
    Mix_Chunk* pickUp;
    Mix_Music* music;
    Mix_Chunk* gameover_sound;
    Mix_Chunk* GroupEnemySound;
    vector<Mix_Chunk*> shoots;
    
    //animation
    const int numFrames = 3;
    float animationElapsed = 0.0f;
    float framesPerSecond = 20.0f;
    int currentIndex =0;

    //level 1
    int level1Detection = 1;
    //level 1 enemy
    int switchs = 0;
    
    time_t dimaondTimer;
    int diamondsPicked=0;
};