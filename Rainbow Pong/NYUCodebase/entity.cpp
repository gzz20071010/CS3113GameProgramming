//
//  entity.cpp
//  HW2
//
//  Created by shengxiang guo on 2/15/15.
//

#include <stdio.h>
#include "entity.h"


void Entity::DrawSprite() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glScalef(scale, scale, scale); //functions multiply the current matrix by a general scaling matrix.
    
    GLfloat quad[] = {
        (x - (width / 2.0f)), (y + (height / 2.0f)), (x - (width / 2.0f)), (y - (height / 2.0f)),
        (x + (width / 2.0f)), (y - (height / 2.0f)),  (x + (width / 2.0f)), (y + (height / 2.0f)),
    };
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}

void Entity::Draw(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glScalef(scale, scale, scale); //functions multiply the current matrix by a general scaling matrix.
    
    GLfloat quad[] = {
        (x - (width / 2.0f)), (y + (height / 2.0f)), (x - (width / 2.0f)), (y - (height / 2.0f)),
        (x + (width / 2.0f)), (y - (height / 2.0f)),  (x + (width / 2.0f)), (y + (height / 2.0f)),
    };
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    GLfloat triangleColors[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    glColorPointer(3, GL_FLOAT, 0, triangleColors);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_COLOR_ARRAY);
}