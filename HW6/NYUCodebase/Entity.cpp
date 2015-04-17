

#include "Entity.h"

Entity::Entity() {}
Entity::~Entity() {}

void Entity::Update(float elapsed) {
	if (x < -2.6f || x >2.6f)
		velocity_x *= -1;
	if (y < -2.0f || y > 2.0f)
		velocity_y *= -1.0f;

	if (isPlayer){
		if (x < -2.0f)
			x = -2.0f;
		else if (x > 2.0f)
			x = 2.0f;
		if (y < -2.0f)
			y = -2.0f;
		else if (y > 2.0f)
			y = 2.0f;
	}
}

void Entity::Render() {
	buildMatrix();
	glPushMatrix();
	glMultMatrixf(matrix.ml);
	sprite.Draw(scale_x, scale_y);
	glPopMatrix();
}

void Entity::buildMatrix() {

    Matrix translateMatrix;
	translateMatrix.identity();
	translateMatrix.m[3][0] = x;
	translateMatrix.m[3][1] = y;
	translateMatrix.m[3][2] = 1;

    Matrix rotateMatrix;
    rotateMatrix.identity();
	rotateMatrix.m[0][0] = cos(rotation); 	rotateMatrix.m[0][1] = sin(rotation);
	rotateMatrix.m[1][0] = -sin(rotation);	rotateMatrix.m[1][1] = cos(rotation);

    Matrix scaleMatrix;
	scaleMatrix.identity();
	scaleMatrix.m[0][0] = scale_x;
	scaleMatrix.m[1][1] = scale_y;
	scaleMatrix.m[2][2] = 1;

    matrix.identity();
	matrix = translateMatrix * rotateMatrix * scaleMatrix;


	TL = Vector(-sprite.width * scale_x, sprite.height * scale_y, 0.0);
    BL = Vector(-sprite.width * scale_x, -sprite.height * scale_y, 0.0);
	TR = Vector(sprite.width * scale_x, sprite.height * scale_y, 0.0);
	BR = Vector(sprite.width * scale_x, -sprite.height * scale_y, 0.0);
}