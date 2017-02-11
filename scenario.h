#ifndef CENARIO_H_INCLUDED
#define CENARIO_H_INCLUDED

#include "terrain.h"

void drawScenario()
{
	// glPushMatrix();
 //    	glRotatef(-giraSol, 0, 0.0, 1);
 //        desenhaSol();
 //        desenhaLua();
 //    glPopMatrix();

    //parede de fundo
    glPushMatrix();
        glTranslatef(0, 0.0, -50);
        glRotatef(90.0, 1.0, 0.0, 0);
        glColor3f(0,1,1);        
        desenhaParede();
    glPopMatrix();

    //chão
    glPushMatrix();
        glColor3f(0, 1, 0);
        desenhaParede();
    glPopMatrix();

    //Terreno
    glPushMatrix();
        glColor3f (0.5f, 0.35f, 0.05f);
        criaTerreno();
    glPopMatrix();
}

#endif // CENARIO_H_INCLUDED
