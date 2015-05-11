

#include "Entity.h"

Entity::Entity() {}
Entity::~Entity() {}

// draw the entity
void Entity::Render() {
	sprite.Draw(width, height, x, y, rotation);
}
void Entity::Render2() {
    sprite.Draw3( x,  y,  scale, 0.0f);
}


// check collision with another entity
bool Entity::collidesWith(Entity* entity) {
    if(follow){
        return true;
    }
	float entity1_top = y + height / 2;
	float entity1_bottom = y - height / 2;
	float entity1_right = x + width / 2;
	float entity1_left = x - width / 2;

	float entity2_top = entity->y + entity->height / 2;
	float entity2_bottom = entity->y - entity->height / 2;
	float entity2_right = entity->x + entity->width / 2;
	float entity2_left = entity->x - entity->width / 2;

	if (entity1_bottom > entity2_top)
		return false;
	if (entity1_top < entity2_bottom)
		return false;
	if (entity1_left > entity2_right)
		return false;
	if (entity1_right < entity2_left)
		return false;
		
	return true;
}

void Entity::shootBullet(int position){
//    int iSecret;
//    srand (time(NULL));
    /* generate secret number between 1 and 10: */
  //  iSecret = rand() % 11 + 1;
   // SpriteSheet bulletsSprite = SpriteSheet(bullet, 674.0/1024.0f, 262.0/1024.0f,  22.0/1024.0f,  21.0/1024.0f);
    SpriteSheet bulletsSprite;
    if(isEnemy){
         bulletsSprite = SpriteSheet(bullet, 11, 7, 9);
    }else{
         bulletsSprite = SpriteSheet(bullet, 11, 7, position);
    }
    bullets[bulletIndex].sprite = bulletsSprite;
    bullets[bulletIndex].visiable = true;
 //   bullets[bulletIndex].visiable = false;
    bullets[bulletIndex].x = x;
    bullets[bulletIndex].y = y;
    bullets[bulletIndex].scale = 3.0;
    bullets[bulletIndex].speed = 2.0f;
    bullets[bulletIndex].vy = detectedEnemyY*0.8;
    bullets[bulletIndex].vx = detectedEnemyX*0.8;
    bullets[bulletIndex].cd = 0.0f;
    bulletIndex++;
    if(bulletIndex > MAX_BULLETS-1) {
        bulletIndex = 0;
    }
    
    bulletCD = 0;
    
}
void Entity::shootBullet2(float e){
    SpriteSheet bulletsSprite = SpriteSheet(bullet, 674.0/1024.0f, 262.0/1024.0f,  22.0/1024.0f,  21.0/1024.0f);
    bullets[bulletIndex].sprite = bulletsSprite;
    bullets[bulletIndex].visiable = false;
    bullets[bulletIndex].x = x;
    bullets[bulletIndex].y = y;
    bullets[bulletIndex].scale = 5.0;
    bullets[bulletIndex].speed = 2.0f;
//    bullets[bulletIndex].vy = detectedEnemyY;
//    bullets[bulletIndex].vx = detectedEnemyX;

    bulletIndex++;
    if(bulletIndex > MAX_BULLETS-1) {
        bulletIndex = 0;
    }
}
float Entity::distance(Entity *entity){
    return sqrt((entity->x - x)*(entity->x - x) + (entity->y - y)*(entity->y - y));
}

float Entity::distancePoint(float x1, float y1){
    return sqrt((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y));
}

//distance between bullet and enemy entity
float Entity::distanceBullet(Bullet &bullet){
    return sqrt((bullet.x - x)*(bullet.x - x) + (bullet.y- y)*(bullet.y - y));
}

void Entity::enemyDetection(Entity *entity, int i){
    if (distance(entity)<=2){
        detectedEnemyX = entity->x - x;
        detectedEnemyY = entity->y - y;
        shootBullet(i);
    }
}
// walk right
void Entity::walkRight() {
	faceLeft = false;
    velocity_y = 0;
    velocity_x = 1;
}
void Entity::walkUp() {
    faceLeft = false;
    velocity_x = 0;

    velocity_y = 1;
}
void Entity::walkDown() {
    faceLeft = false;
    velocity_x = 0;

    velocity_y = -1;
}
void Entity::walkLeft() {
	faceLeft = true;
    velocity_y = 0;
    velocity_x = -1;
}

//because everyone need to save head's turning points, so pass it in as parameter instead of their own x,y,dir.
void Entity::saveTurningPoint(float x1, float y1, int dir1){
    if(old_x.size()==0){
        cout<<"oh";
        old_x.push_back(x1);
        old_y.push_back(y1);
        old_dir.push_back(dir1);
    }else if(dir1!=old_dir[old_dir.size()-1]){
        cout<<"ah";
        old_x.push_back(x1);
        old_y.push_back(y1);
        old_dir.push_back(dir1);
    }
}
void Entity::deleteDuplicate(){
    
}


// idle
void Entity::idle() {
	velocity_x = 0.0f;
	acceleration_x = 0.0f;
    velocity_y =0.0f;
    acceleration_y = 0.0f;
}