#ifndef CONTROLE_H_INCLUDED
#define CONTROLE_H_INCLUDED

bool testeLuz = false;

bool mirar = true;
bool atirar = false;
bool finnestShot= false;
bool observadorTorreBool = false;

float  alphaCannon = 0;
float thetaCannon  = 0;

GLfloat xMira = 0.0;
GLfloat yMira = 0.0;

GLfloat speedDiscoVoador = 0.001;
GLfloat xDiscoAtual = 0, yDiscoAtual = 0.0, zDiscoAtual = 0;
GLfloat xBalaAtual = 0, yBalaAtual = 0.0, zBalaAtual = 22;


bool desenhaDiscoBool = true;
double balaGap = 0.0;

GLfloat xObservador = 0.0;
GLfloat yObservador = 5.0;
GLfloat zObservador = 50.0;

GLfloat xObservadorEye = 0.0;
GLfloat yObservadorEye = 0.0;
GLfloat zObservadorEye = 0.0;

// Observador
GLfloat angObserv = 0.0;     // ângulo de rotação do observador em torno de Y

GLfloat zObservadorPosicao = 45.0;

//variaveis para escrever na tela
int discosLancados = 1;
int acertosDisco = 0;
int bestScore;


double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


//ao recarregar bala volta pro canhao e movimento de tiro para
void recarrega()
{
    atirar = false;
    mirar = true;
    balaGap = 0;

}

void atira()
{
    if(mirar && !atirar)
    {
        alphaCannon = camAng;
        thetaCannon = camTurning;
        atirar = true;

        //mirar = false;
        GLfloat deltax = xMira - xDiscoAtual;
        GLfloat deltay = yMira - yDiscoAtual;

        if(deltax >  -2.7 && deltax < 2.2 && deltay > -3.0 && deltay < 0)
        {
                finnestShot =true;
                speedDiscoVoador = 0;

        }
        else
        {
                finnestShot = false;
        }
    }
}


void mouseWheel(int button, int state,   int x, int y)
{
    switch(button)
    {
    case 3:
        if(zObservadorPosicao < 94){
        zObservadorPosicao = zObservadorPosicao + 0.2;
        }
        break;
    case 4:
        zObservadorPosicao = zObservadorPosicao - 0.2;
        break;
    }


}


void handleSpecialKeypress(int key, int x, int y)
{

    switch(key)
    {

    case GLUT_KEY_UP:
    {
        if(camTurning > 1.0)
        {
            camTurning = camTurning - 1.0;

        }
        else if(camTurning < 1.0)
        {
            camTurning = camTurning + 1.0;
        }
        else
        {
            zCan = zCan - 0.1;
            zBala = zBala - 0.1;
            wheelTurning = wheelTurning - 4.0;

        }


    }
    break;

    case GLUT_KEY_DOWN:
    {
        if(camTurning > 1.0)
        {
            camTurning = camTurning - 1.0;

        }
        else if(camTurning < 0)
        {
            camTurning = camTurning + 1.0;
        }
        else
        {

            wheelTurning = wheelTurning + 4.0;
            zCan = zCan + 0.1;
            zBala = zBala + 0.1;

        }
    }
    break;

    case GLUT_KEY_LEFT:
    {
        if(camTurning > 91.0)
        {
            camTurning = camTurning - 1.0;

        }
        else if(camTurning < 90)
        {
            camTurning = camTurning + 1.0;
        }
        else
        {

            xCan = xCan - 0.1;
            xBala = xBala - 0.1;
            wheelTurning = wheelTurning - 4.0;

        }
    }
    break;

    case GLUT_KEY_RIGHT:
    {

        if(camTurning > -90 )
        {
            camTurning = camTurning - 1.0;

        }
        else if(camTurning > -89.1 )
        {
            camTurning = camTurning + 1.0;
        }
        else
        {
            xCan = xCan + 0.1;
            xBala = xBala + 0.1;
            wheelTurning = wheelTurning - 4.0;

        }
    }
    break;


    }
}



void controle (unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
        case 27 :        
            exit(EXIT_SUCCESS);  // tecla ESC para sair
        case 32 :
            atira();
            break; /*Espaco para atirar*/
        case 'w':
            if (camAng < 30.0) camAng += 1.0;
            break;
        case 's':
            if (camAng > 0.0) camAng -= 1.0;
            break;
        case 'a':
            if (camTurning < 35.0) camTurning += 1.0;
            break;
        case 'd':
            if (camTurning > -45.0) camTurning -= 1.0;
            break;
        case 'r':
            recarrega();
            break;
        case 'l':
            if(desenhaDiscoBool == false){
                ufoColor[0] = fRand(0, 1);
                ufoColor[1] = fRand(0, 1);
                ufoColor[2] = fRand(0, 1);
                ufoColorRing[0] = ufoColor[0];
                ufoColorRing[1] = ufoColor[1];
                ufoColorRing[2] = ufoColor[2];
                discosLancados++;
            }
            desenhaDiscoBool = true;
            break;
        case 'o':
            if(observadorTorreBool == false)observadorTorreBool=true;
            else observadorTorreBool = false;
            break;
        case 'v': //Tesste meu teclado nao funciona down arrow
            handleSpecialKeypress(GLUT_KEY_DOWN, 0 , 0);

            break;
        case 'p': angObserv -= 1.0; break;
        case 'P': angObserv += 1.0; break;
    }

}
#endif // CONTROLE_H_INCLUDED
