//
//  SpriteSheet.cpp
//  HW1
//
//  Created by shengxiang guo on 2/22/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "SpriteSheet.h"

SpriteSheet::SpriteSheet() {}
SpriteSheet::SpriteSheet(unsigned int textureID, float u, float v, float width, float height) : textureID(textureID), u(u), v(v), width(width), height(height) {}

void SpriteSheet::Draw(float x, float y, float scale, float rotation) {
//    if(x==0.2f&&y== -0.2f){
//        cout<<"hey i got x==0.2f && y == -0.2f"<<endl;
//    }
//    if(x==0.2f){
//        cout<<"when x == 0.2f, y value is: "<<y<<endl;
//    }
//    if(x==1.0f){
//        cout<<"when x == 1.0f, y value is: "<<y<<endl;
//    }
//    if(y==0.2f){
//        cout<<"when y == 0.2f, x value is: "<<x<<endl;
//    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    GLfloat quad[] = {-width * scale , height * scale, -width * scale, -height * scale,
        width * scale, -height * scale, width * scale, height * scale};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    GLfloat quadUVs[] = {u, v, u, v+height, u+width, v+height, u+width, v};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDrawArrays(GL_QUADS, 0, 4);
    //glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);

}
