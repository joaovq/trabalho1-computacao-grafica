//#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <stdio.h>

#include "objects.h"
#include "scenario.h"

#include "controls.h"


#include "BMPLoader.h"
#include "BMPLoader.cpp"
	


/*
                    Como jogar 

./executavel valor1 valor2 valor3

space    -> atira
w a s d  -> posiciona o canhão
r        -> recarrega
esq      -> fecha jogo
t        -> lança novo disco após colisão 

onde:

valor1   = valor do intervalo do angulo de lançamento do disco
valor2   = central da velocidade de lançamento do disco  ( dica : 0.1)
valor3   = faixa de variação da velocidade de lançamento do disco  ( dica : 0.05)

*/

#define PI 3.14159265359

#define NFRAGMENTOS 250

using namespace std;

float angDisk = 45.0;
double gap = 0.5;

int IoAng = 0;
double IoCentralSpeed = 0.0, IoRangeSpeed = 0.0;

GLfloat discGravity = 0;

GLfloat fragmentsGravity = 0;
GLfloat yDiscPosition = 0;

GLfloat bulletSpeed = 1.0;

double randAngles[NFRAGMENTOS][20];

GLfloat objectColor [3] = {0.76,0.76,0.26 };
GLfloat collisionCoordenates [3] = {0.0,0.0,0.0 };

//retorna posição y dos "cacos"
GLfloat yObjeto()
{
    GLfloat mvMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mvMatrix);
    return mvMatrix[13];

}

//retorna posição x dos "cacos"
GLfloat xObjeto()
{
    GLfloat mvMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mvMatrix);
    return mvMatrix[12];

}

//retorna posição z dos "cacos"
GLfloat zObjeto()
{
    GLfloat mvMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mvMatrix);
    return mvMatrix[1];

}

//desenha mira
void drawAim(float x, float y)
{
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
        glPushMatrix();
            glTranslatef(x, y, 2.5);
            glScalef(0.4, 0.4, 0.2);
            cylinder();
        glPopMatrix();

        glPushMatrix();
	        glTranslatef(x, y, 2.5);
	        glScalef(0.1, 0.4, 0.1);
	        	cube();
        glPopMatrix();

        glPushMatrix();
        	glTranslatef(x, y, 2.5);
        	glScalef(0.4, 0.1, 0.1);
        	cube();
        glPopMatrix();
    glPopMatrix();
}

//posciona mira
void aim()
{
    if(isAiming)
    {
        float desloc = cos((camTurning*PI)/180.0)*zCan/cos((camAng*PI)/180.0);

        float y = sin((camAng*PI)/180.0)*desloc;
        float x = -sin((camTurning*PI)/180.0)*desloc;

        glPushMatrix();
            drawAim(x,y);
        glPopMatrix();

        xAim = x;
        yAim = y;

    }
}

//sorteia ângulo de lançamento do disco
int sortAng(){ return rand() % IoAng; }

//sorteia velocidade do disco
double sortDiscSpeed()
{
    double min, max;

    max = IoCentralSpeed + (IoRangeSpeed/2.0);
    min = IoCentralSpeed - (IoRangeSpeed/2.0);

    double aux = (rand() / (static_cast<double>(RAND_MAX) + 1.0))* (max - min) + min;;

    return abs(aux)+((double)lauchedDiscs/300.0);
}

//posciona disco no início
void placeDiscAtBeginning()
{	
    angDisk = 45 + sortAng();
    gap = 0.1;
    speedDisc = sortDiscSpeed();
    discGravity = 0;
}

//move o disco 
void moveDisc()
{
	//caso disco tenha atingido o chão
    if( yCurrentDisc < 0)
    {
        placeDiscAtBeginning();
	    lauchedDiscs++;
    }

    float x = cos((angDisk*PI)/180.0)*gap;
    float y = sin((angDisk*PI)/180.0)*gap + discGravity;

    xCurrentDisc = x -15;
    yCurrentDisc = y+3;
    zCurrentDisc = 0;

    glTranslatef(x, y, 0);

    gap = gap + speedDisc;

   	discGravity = discGravity - (sin((angDisk*PI)/180.0)*gap*speedDisc/36) ;

    disc();

    angDisk = angDisk - 0.01;

}

//inicia vetores de colisão
void setCollisionsVectors()
{
    for(int i = 0; i< NFRAGMENTOS; i++)
    {
        randAngles[i][0] = fRand(0.0,360.0) + 90;

        randAngles[i][1] = fRand(-1.0,1.0);
        randAngles[i][2] = fRand(-1.0,1.0);
        randAngles[i][3] = fRand(-1.0,1.0);

        randAngles[i][4] = fRand(0.0,1.0);
        randAngles[i][5] = fRand(0.0,1.0);
        randAngles[i][6] = fRand(0.0,1.0);

        randAngles[i][7] = 0.0;
        randAngles[i][8] = fRand(0.0,5.0);

        randAngles[i][9] = 0.0;

        randAngles[i][10] = 0.1;
        randAngles[i][11] = 0.1;
    }
}

//detecta quando há uma colisão
void collision()
{
    GLfloat deltax = xCurrentDisc - xCurrentBullet;
    GLfloat deltay = yCurrentDisc - yCurrentBullet;
    GLfloat deltaz = zCurrentDisc - zCurrentBullet;

    if(deltax >  -2.5 && deltax < 2.5)
    {
        if(deltay > -2.0 && deltay < 1.0 )
        {
            if(deltaz > -1.5 && deltaz < 1.5)
            {
                drawDisc = false;
                placeDiscAtBeginning();
                reload();
                setCollisionsVectors();
                collisionCoordenates[0] = xCurrentDisc;
                collisionCoordenates[1] = yCurrentDisc;
                collisionCoordenates[2] = zCurrentDisc;
            }
        }
    }
}

//move bala do canhão
void moveBullet()
{
    if(isShooting)
    {
        float z = -cos((alphaCannon*PI)/180.0)*bulletGap /  cos((thetaCannon*PI)/180.0);
        float y = sin((alphaCannon*PI)/180.0)*bulletGap;
        float x = -sin((thetaCannon*PI)/180.0)*bulletGap;

        yCurrentBullet = yBullet + y;
        xCurrentBullet = xBullet + x;
        zCurrentBullet = zBullet + z;

        glPushMatrix();
			glTranslatef(x,y, z);
        	if(bulletGap >= 50)
            	reload();
            bulletGap = bulletGap + bulletSpeed;
            glTranslatef( xBullet, yBullet, zBullet );
            glRotatef(thetaCannon, 0.0, 1.0,0.0 );
            glRotatef(alphaCannon, 1.0, 0.0,0.0 );
            glTranslatef( -xBullet,- yBullet, -zBullet );
            bullet();
        glPopMatrix();
        collision();
    }
}

//reproduz efeitos após a colisão
void afterCrashAnimations()
{
    glTranslatef(collisionCoordenates[0], collisionCoordenates[1], collisionCoordenates[2]);
    reload();

    for(int i = 0; i< NFRAGMENTOS; i++)
    {
        glPushMatrix();
            glTranslatef(0, -randAngles[i][10], 0);
            glRotatef(randAngles[i][0], randAngles[i][1], randAngles[i][2],randAngles[i][3] );
            glTranslatef(randAngles[i][9], randAngles[i][9], randAngles[i][9]);
            glScalef(randAngles[i][4], randAngles[i][5], randAngles[i][6]);

            glPushMatrix();
	            glRotatef(randAngles[i][7],0.0, 0.0, 1.0 );

	            GLfloat y = yObjeto();
	        	GLfloat x = xObjeto();
	        	GLfloat z = zObjeto();

	            glColor3f(0.169,0.169,0.169);
	            drawTriangle();
        	glPopMatrix();

        glPopMatrix();

	   bool collision = false;

    	if( y > 0 && y < 4 && x < -15 && x > -19 && z < -1 && z > -3)
    	 	collision = true;

        if(y  > 0 && !collision )
        {
            randAngles[i][7] = randAngles[i][7] + randAngles[i][8];
    	    randAngles[i][9] = randAngles[i][9] + 0.1 ;

	    if(randAngles[i][9] < 3)
            	randAngles[i][10] = randAngles[i][10] + 0.05;
	    else if(randAngles[i][9] < 5)
	    	    randAngles[i][10] = randAngles[i][10] + 0.1;
		else if(randAngles[i][9] < 8 ){
 			randAngles[i][9] = randAngles[i][9] + 0.05 ;
	    	    	randAngles[i][10] = randAngles[i][10] + 0.4;
		  } 
		else{
			randAngles[i][9] = randAngles[i][9] + 0.1 ;
			randAngles[i][10] = randAngles[i][10] + 0.8;
		  }
        }
    }
}

//Lança o disco voador
void throwDisc(){
    //Disco Voador
    glPushMatrix();
    	moveDisc();
    glPopMatrix();
}

//Cria cena com o terreno, disco e a mira
void scene()
{
    glColor3f(objectColor[0],objectColor[1], objectColor[2] );
    
    //Canhao com a bala
    glPushMatrix();
        glTranslatef(xCan,yCan,zCan);
        glRotatef(camTurning,0.0,1.0,0.0);
        glTranslatef(-xCan,-yCan,-zCan);
        cannon();
    glPopMatrix();

    glPushMatrix();
        moveBullet();
    glPopMatrix();

    glPushMatrix();
        drawScenario();
        aim();
    glPopMatrix();

    //spin();
}

//posição do observador
void observator()
{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, 1.0, 1.0, 1000.0);

		gluLookAt(xObservator, yObservator, zObservator, xObservatorEye, yObservatorEye, 0.0, 0.0, 1.0, 0.0);

        glMatrixMode(GL_MODELVIEW);
}

void show()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glRotatef(observAng,0.0,1.0,0.0);
        scene();
        if(drawDisc == true)
            throwDisc();
        if(drawDisc == false)
            afterCrashAnimations();
    glPopMatrix();

    observator();

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

void window(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void setUpLights()
{
    GLfloat light_ambient[]={0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]={0.6, 0.6, 0.6, 1.0};
    GLfloat light_specular[]={0.6, 0.6, 0.6, 1.0};

    GLfloat light_position[]={10.0,3.8,10.0,1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat mat_ambient[]={1.0, 1.0, 0.0, 1.0};
    GLfloat mat_diffuse[]={0.6, 0.6, 0.0, 1.0};
    GLfloat mat_specular[]={0.4, 0.4, 0.0, 1.0};
    GLfloat mat_shininess={50.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity ();
    glEnable(GL_COLOR_MATERIAL);

    terreno = new Terreno();
}

BMPClass setTextures(string path, int id){
	BMPClass bmp;
	BMPLoad(path,bmp);


	glBindTexture(GL_TEXTURE_2D, id);  // numero 13 escolhido para identificar a textura
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.bytes);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  //GL_LINEAR ou GL_NEAREST

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);  //GL_MODULATE ou GL_REPLACE

	return bmp;
}

int main(int argc, char** argv)
{
    srand (time(NULL));

    if(argc != 4)
    {
        cout << endl <<"Wrong entry format." << endl
         << "Please check out how to run this program" << endl << endl;
        return 0;
    }

    IoAng          = atoi(argv[1]);
    IoCentralSpeed = atof(argv[2]);
    IoRangeSpeed   = atof(argv[3]);
    IoAng +=1;
    speedDisc = sortDiscSpeed(); 
    if(IoAng > 45)
        IoAng = 45;
    else if(IoAng < -45)
        IoAng = -45;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lançamento de discos");
    glutReshapeFunc(window);
    glutDisplayFunc(show);
    glutKeyboardFunc(controle);

    BMPClass bmp1 = setTextures("texturas/grama3.bmp",1);
    BMPClass bmp2 = setTextures("texturas/ground2.bmp",2);
    BMPClass bmp3 = setTextures("texturas/gray.bmp",3);
    
    setUpLights();
    glutMainLoop();
}
