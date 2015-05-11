
#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "SpriteSheet.h"
#include "Bullet.h"
#include <time.h>
#include <vector>
#include <cmath>
#include <iostream>
#define MAX_BULLETS		30
#define BULLET_COOLDOWN	0.25f

using namespace std;
class Entity {
public:
	Entity();
	~Entity();
	
	// rendering the entity
	virtual void Render();
    void Render2();

	// checking collision
	bool collidesWith(Entity* entity);

	// movement of entities
	void jump();
	void walkRight();
	void walkLeft();
    
    void walkUp();
    void walkDown();
    void walkTowards(Entity* entity);
	void idle();
    void saveTurningPoint(float x1, float y1, int dir1);
    void deleteDuplicate();
    void shootBullet(int position);
    void shootBullet2(float e);

    float distance(Entity* entity);
    float distancePoint(float x, float y);
    float distanceBullet(Bullet &bullet);
    void enemyDetection(Entity* entity, int i);

	SpriteSheet sprite;

	// location
	float x = 0.0f;
	float y = 0.0f;
	float scale = 0.0f;
	float rotation = 0.0f;
    float detectedEnemyX = 1.0f;
    float detectedEnemyY = 1.0f;

	float width = 0.2f;
	float height = 0.2f;
	
	// movement
	float velocity_x = 0.0f;
	float velocity_y = 0.0f;
	float acceleration_x = 0.0f;
	float acceleration_y = 0.0f;
	float friction_x = 0.0f;
	float friction_y = 0.0f;
	float mass  = 0.0f;
    int direction=0; //left:1 right:2 top:3 down:4
    float speed = 3.0;
    std::vector<float> old_x;
    std::vector<float> old_y;
    std::vector<int> old_dir;
    bool turingFlag;
    

	// collision
	bool isStatic = false;
	bool collidedTop = false;
	bool collidedBottom = false;
	bool collidedLeft = false;
	bool collidedRight = false;

	// types
	bool isPlayer = false;
	bool isEnemy = false;
    bool isTreasure = false;
    bool follow = false;
    bool isVisiable = true;
    bool isDiamond = false;

	// status
	bool isDead = false;
	bool isJumping = false;
	bool faceLeft = false;
    
    Bullet bullets[30];
    int bulletIndex = 0;
    float bulletCD = 0.0f;
   // GLuint bullet = LoadTexture("sheet.png");
    GLuint bullet = LoadTexture("bullets1.png");

    
};