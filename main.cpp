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
	


/*
///////////////////////////////////////////////////////////////////
//////////////////// COMO USAR  //////////////////////////////////

./executavel ValorInteriro1 ValorDouble1 ValorDouble2

space    -> atira
w a s d  -> posiciona canhao
r        -> recarrega canhao
esq      -> sai do jogo
l        -> iniciar lançamento do novo disco apos colisão
o 		 -> muda observador

onde:

ValorInteriro1 = int que representa o valor da mergem de sorteio para o angulo de lançamento do disco
ValorDouble1   = double que indica a central da velocidade de lançamento do disco  ( dica : 0.1)
ValorDouble2   = double que indica faixa de variação da velocidade de lançamento do disco  ( dica : 0.05)

//////////////////////////////////////////////////////////////////
*/

#define PI 3.14159265359

/***Numero de fragmentos a ser gerado*/
#define NFRAGMENTOS 256

using namespace std;

float angDisk = 45.0;
double gap = 0.5;

GLfloat xBuraco = 0;
GLfloat yBuraco = 0;

int IoAng = 0;
double IoSpeedCentral = 0.0, IoSpeedFaixa = 0.0;


GLfloat gravidadeDisco = 0;


GLfloat gravidadeFragmentos = 0;
GLfloat posicaoYDisco = 0;

GLfloat speedBala = 1.0;


/**Esta variavel guarda o angulo do vetor de colisao, as direções deste vetor, a escala dos objetos**/
double randAngles[NFRAGMENTOS][20];

double startColision = 0.01;


GLfloat objectColor [3] = {0.76,0.76,0.26 };
GLfloat coordenadascolisao [3] = {0.0,0.0,0.0 };

GLfloat yObjeto()
{
    GLfloat mvMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mvMatrix);
    return mvMatrix[13];

}

GLfloat xObjeto()
{
    GLfloat mvMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mvMatrix);
    return mvMatrix[12];

}

GLfloat zObjeto()
{
    GLfloat mvMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mvMatrix);
    return mvMatrix[1];

}

void objetoMira(float x, float y)
{


    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(x, y, 2.5);
    glScalef(0.4, 0.4, 0.2);
    cilindro();
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

void mira()
{
    if(mirar)
    {
        float desloc = cos((giroCan*PI)/180.0)*zCan/cos((angCan*PI)/180.0);

        float y = sin((angCan*PI)/180.0)*desloc;
        float x = -sin((giroCan*PI)/180.0)*desloc;


        x = xBala + x;
        y = yBala + y;

        glPushMatrix();
            objetoMira(x,y);
        glPopMatrix();

        xMira = x;
        yMira = y;

    }
}

//gira circulo externo do disco
void gira()
{

    giraDisco += 4;
    giraSol += 0.42;
    if( giraDisco > 360.0 )
        giraDisco -= 360.0;
    if(giraSol > 360.0)
    	giraSol -= 360.0;

}

//retorna angulo sorteado dado angulo informado na entrada
int sorteiaAng()
{
    return rand() % IoAng;
}

//sorteia velocidade do disco voador.
double sorteiaSpeedDisco()
{
    double min, max;

    max = IoSpeedCentral + (IoSpeedFaixa/2.0);
    min = IoSpeedCentral - (IoSpeedFaixa/2.0);

    double aux = (rand() / (static_cast<double>(RAND_MAX) + 1.0))* (max - min) + min;;

    //quanto mais discos são lançados a velocidade aumenta
    return abs(aux)+((double)discosLancados/300.0);
}

//volta disco pra horigem, seta nova velocidade e angulo de lancamento
void voltaDiscoPraOrigem()
{	
    angDisk = 45 + sorteiaAng();
    gap = 0.1;
    speedDiscoVoador = sorteiaSpeedDisco();
    cout << speedDiscoVoador << endl;
    gravidadeDisco = 0;

    if(acertosDisco > bestScore){
            ofstream myfile ("melhorScore.txt");

            if (myfile.is_open()){
                myfile << acertosDisco;
                myfile.close();
            }
            else cout << "Erro ao abrir arquivo" << endl;
    }
}

void moveDiscoVoador()
{
    if( yDiscoAtual < 0 )
    {
        voltaDiscoPraOrigem();
        ufoColor[0] = fRand(0, 1);
	    ufoColor[1] = fRand(0, 1);
	    ufoColor[2] = fRand(0, 1);
	    ufoColorRing[0] = ufoColor[0];
	    ufoColorRing[1] = ufoColor[1];
	    ufoColorRing[2] = ufoColor[2];
	    discosLancados++;
    }

    float x = cos((angDisk*PI)/180.0)*gap;
    float y = sin((angDisk*PI)/180.0)*gap + gravidadeDisco;

    //valores somados e subtraidos aqui tem a ver com a translação inicial do disco
    xDiscoAtual = x -15;
    yDiscoAtual = y+3;
    zDiscoAtual = 0;

    glTranslatef(x, y, 0);

    gap = gap + speedDiscoVoador;

    gravidadeDisco = gravidadeDisco - (sin((angDisk*PI)/180.0)*gap*speedDiscoVoador/36) ;

    discoVoador();

    angDisk = angDisk - 0.01;

}
void inicializaVetorDeColisao()
{
    startColision = 0.0;

    for(int i = 0; i< NFRAGMENTOS; i++)
    {
        /**BMPLoadDireção pos colisao*/
        randAngles[i][0] = fRand(0.0,360.0) + 90;

        /**Eixos de colisao*/
        randAngles[i][1] = fRand(-1.0,1.0);
        randAngles[i][2] = fRand(-1.0,1.0);
        randAngles[i][3] = fRand(-1.0,1.0);

        /**Escala dos fragmentos*/
        randAngles[i][4] = fRand(0.0,1.0);
        randAngles[i][5] = fRand(0.0,1.0);
        randAngles[i][6] = fRand(0.0,1.0);

        /**Rotacao em torno de seu propio eixo*/
        randAngles[i][7] = 0.0;//Acumulador da rotacao
        randAngles[i][8] = fRand(0.0,5.0); //Velocidade de rotacao

        /**Acumula translacao*/
        randAngles[i][9] = 0.0;


        /**Gravidade dos fragmentos*/
        randAngles[i][10] = 0.1;
         randAngles[i][11] = 0.1;
    }
}


void colisao()
{
    GLfloat deltax = xDiscoAtual - xBalaAtual;
    GLfloat deltay = yDiscoAtual - yBalaAtual;
    GLfloat deltaz = zDiscoAtual - zBalaAtual;

    if(deltax >  -2.5 && deltax < 2.5)
    {
        if(deltay > -2.0 && deltay < 1.0 )
        {
            if(deltaz > -1.5 && deltaz < 1.5)
            {

                //se acertar volta disco pra origem volta bala pro canhao e para de desenhar disco
                //com desenha disco bool = false efeitos da colisao vão ser desenhados
                desenhaDiscoBool = false;
                voltaDiscoPraOrigem();
                recarrega();
                inicializaVetorDeColisao();
                acertosDisco++;
                coordenadascolisao[0] =xDiscoAtual;
                coordenadascolisao[1] =yDiscoAtual;
                coordenadascolisao[2] =zDiscoAtual;
            }
        }
    }
}

void movimentoBala()
{
    if(atirar)
    {
        float z = -cos((alphaCannon*PI)/180.0)*balaGap /  cos((thetaCannon*PI)/180.0);
        float y = sin((alphaCannon*PI)/180.0)*balaGap;
        float x = -sin((thetaCannon*PI)/180.0)*balaGap;

        xBalaAtual = xBala + x;
        yBalaAtual = yBala + y;
        zBalaAtual = zBala + z;

        glPushMatrix();

        glTranslatef(x,y, z);

        // Apos a bala "sumir" da tela, o canhão faz o reload automatico
        if(balaGap >= 50 )
        {
            recarrega();
        }

        balaGap = balaGap + speedBala;
        glTranslatef( xBala, yBala, zBala );
        glRotatef(thetaCannon, 0.0, 1.0,0.0 );
        glRotatef(alphaCannon, 1.0, 0.0,0.0 );
        glTranslatef( -xBala,- yBala, -zBala );
        bala();
        glPopMatrix();
        colisao();
    }
}

//fazer tudo que acontece depois da colisao AQUI --- desenhaDiscoBool é falso chama essa funcao
void efeitosPosColisao()
{
    glTranslatef(coordenadascolisao[0], coordenadascolisao[1], coordenadascolisao[2]);
    recarrega();

    for(int i = 0; i< NFRAGMENTOS; i++)
    {
        glPushMatrix();

        /*Rotaciona e translada um Objeto*/
        glTranslatef(0, -randAngles[i][10], 0);
        glRotatef(randAngles[i][0], randAngles[i][1], randAngles[i][2],randAngles[i][3] );
        glTranslatef(randAngles[i][9], randAngles[i][9], randAngles[i][9]);

        /* apos a rotação aplicar a gravidade no fragmento*/

        /*dimensiona o fragmento*/
        glScalef(randAngles[i][4], randAngles[i][5], randAngles[i][6]);
        glPushMatrix();

        /* Rotaciona um fragmento */
        glRotatef(randAngles[i][7],0.0, 0.0, 1.0 );

        GLfloat y = yObjeto();
    	GLfloat x = xObjeto();
    	GLfloat z = zObjeto();

        glColor3f(ufoColor[0], ufoColor[1], ufoColor[2]);
        desenhaTriangulo();
        glPopMatrix();

        glPopMatrix();

	   bool colisao = false;

    	if( y > 0 && y < 4 && x < -15 && x > -19 && z < -1 && z > -3)
    	 	colisao = true;

        /***Caso fragmento caia no chao deve -se parar o fragmento*/
        if(y  > 0 && !colisao )
        {
            randAngles[i][7] = randAngles[i][7] + randAngles[i][8];
	    randAngles[i][9] = randAngles[i][9] + 0.1 ;

	    if(randAngles[i][9] < 3)
            	randAngles[i][10] = randAngles[i][10] + 0.05;
	    else
		if(randAngles[i][9] < 5)
	    	    randAngles[i][10] = randAngles[i][10] + 0.1;
		else
		   if(randAngles[i][9] < 8 )
		   {
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

//disco em sendo desenhado enquanto desenhaDiscoBool é true
void lancarDisco()
{
    //Disco Voador
    glPushMatrix();
    moveDiscoVoador();
    glPopMatrix();
}

void cena()
{
    glColor3f(objectColor[0],objectColor[1], objectColor[2] );
    
    //Base
    glPushMatrix();
        baseDeLancamento();
    glPopMatrix();

    //Canhao com a bala
    glPushMatrix();
        glTranslatef(xCan,yCan,zCan);
        glRotatef(giroCan,0.0,1.0,0.0);
        glTranslatef(-xCan,-yCan,-zCan);
        cannon();
    glPopMatrix();

    glPushMatrix();
        movimentoBala();
    glPopMatrix();

    glPushMatrix();
        drawScenario();
    mira();
    glPopMatrix();

    gira();
}

void observador()
{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, 1.0, 1.0, 1000.0);

		gluLookAt(xObservador, yObservador, zObservador, xObservadorEye, yObservadorEye, 0.0, 0.0, 1.0, 0.0);

        glMatrixMode(GL_MODELVIEW);
}

void exibe()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glRotatef(angObserv,0.0,1.0,0.0);
        cena();
        if(desenhaDiscoBool == true)
            lancarDisco();
        if(desenhaDiscoBool == false)
            efeitosPosColisao();
    glPopMatrix();

    observador();

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();

    /**On linux comment*/
    //Sleep(10);
}

void window(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void setUp()
{
    // estabelece parametros de iluminacao
    GLfloat light_ambient[]={0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]={0.6, 0.6, 0.6, 1.0};
    GLfloat light_specular[]={0.6, 0.6, 0.6, 1.0};

    GLfloat light_position[]={10.0,3.8,10.0,1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // caracteristicas de reflexao do material para
    // fins de iluminacao (material amarelo)
    GLfloat mat_ambient[]={1.0, 1.0, 0.0, 1.0};
    GLfloat mat_diffuse[]={0.6, 0.6, 0.0, 1.0};
    GLfloat mat_specular[]={0.4, 0.4, 0.0, 1.0};
    GLfloat mat_shininess={50.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    // habilita algumas caracteristicas de OpenGL
    glEnable(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity ();
    glEnable(GL_COLOR_MATERIAL);

    terreno = new Terreno();
}

int main(int argc, char** argv)
{
    srand (time(NULL));

    IoAng          = 45;
    IoSpeedCentral = 0.1;
    IoSpeedFaixa   = 0.5;
    IoAng +=1;
    speedDiscoVoador = sorteiaSpeedDisco(); //sorteio da primeira velocidade de lancamento deve ser feita aqui

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("TP Disco Voadores");
    glutReshapeFunc(window);
    glutDisplayFunc(exibe);
    glutKeyboardFunc(controle);
    glutSpecialFunc(handleSpecialKeypress);
    glutMouseFunc(mouseWheel);


    setUp();
    glutMainLoop();
}
