#ifndef CENARIO_H_INCLUDED
#define CENARIO_H_INCLUDED

#include "terrain.h"

void drawScenario()
{
    //parede de fundo
    glPushMatrix();
        glTranslatef(0, 0.0, -50);
        glRotatef(90.0, 1.0, 0.0, 0);
        glColor3f(0,1,1);        
        drawWall();
    glPopMatrix();

    //chão
    glPushMatrix();
        glColor3f(0, 1, 0);
        drawWall();
    glPopMatrix();

    //Montanha da direita
    glPushMatrix();
        glColor3f (0.5f, 0.35f, 0.05f);
        glTranslatef(25, 5.5, -25.0);
        glRotatef(180.0, 0.0, 1.0, 0.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(0.75, 0.1, 1.35);
        createTerrain();
    glPopMatrix();

    //Montanha da esquerda
    glPushMatrix();
        glColor3f (0.5f, 0.35f, 0.05f);
        glTranslatef(-30, 5.5, -2.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(0.25, 0.1, 0.5);
        createTerrain();
    glPopMatrix();
}

#endif // CENARIO_H_INCLUDED
