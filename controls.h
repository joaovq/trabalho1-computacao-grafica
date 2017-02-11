#ifndef CONTROLE_H_INCLUDED
#define CONTROLE_H_INCLUDED

bool testeLuz = false;

bool aim = true;
bool shoot = false;

float   alphaCannon = 0;
float   thetaCannon  = 0;

GLfloat xAim = 0.0;
GLfloat yAim = 0.0;

GLfloat speedSpaceShip = 0.001;
GLfloat xCurrentShip = 0, yCurrentShip = 0.0, zCurrentShip = 0;
GLfloat xCurrentBullet = 0, yCurrentBullet = 0.0, zCurrentBullet = 22;


bool drawShipBool = true;
double bulletGap = 0.0;

GLfloat xObservator = 0.0;
GLfloat yObservator = 5.0;
GLfloat zObservator = 50.0;

GLfloat xObservatorEye = 0.0;
GLfloat yObservatorEye = 0.0;
GLfloat zObservatorEye = 0.0;

// Observador
GLfloat observAng = 0.0;     // ângulo de rotação do observador em torno de Y

GLfloat zObservatorPosition = 45.0;

//variaveis para escrever na tela
int lauchedShips = 1;
int shipsHit = 0;


double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


//ao recarregar bala volta pro canhao e movimento de tiro para
void recarrega()
{
    shoot = false;
    aim = true;
    bulletGap = 0;

}

void atira()
{
    if(aim && !shoot)
    {
        alphaCannon = camAng;
        thetaCannon = camTurning;
        shoot = true;

        //aim = false;
        GLfloat deltax = xAim - xCurrentShip;
        GLfloat deltay = yAim - yCurrentShip;

        if(deltax >  -2.7 && deltax < 2.2 && deltay > -3.0 && deltay < 0)
                speedSpaceShip = 0;
    }
}


void mouseWheel(int button, int state,   int x, int y)
{
    switch(button)
    {
    case 3:
        if(zObservatorPosition < 94){
        zObservatorPosition = zObservatorPosition + 0.2;
        }
        break;
    case 4:
        zObservatorPosition = zObservatorPosition - 0.2;
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
            zBullet = zBullet - 0.1;
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
            zBullet = zBullet + 0.1;

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
            xBullet = xBullet - 0.1;
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
            xBullet = xBullet + 0.1;
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
            if(drawShipBool == false){
                ufoColor[0] = fRand(0, 1);
                ufoColor[1] = fRand(0, 1);
                ufoColor[2] = fRand(0, 1);
                ufoColorRing[0] = ufoColor[0];
                ufoColorRing[1] = ufoColor[1];
                ufoColorRing[2] = ufoColor[2];
                lauchedShips++;
            }
            drawShipBool = true;
            break;
        case 'o':
            break;
        case 'v': //Tesste meu teclado nao funciona down arrow
            handleSpecialKeypress(GLUT_KEY_DOWN, 0 , 0);

            break;
        case 'p': observAng -= 1.0; break;
        case 'P': observAng += 1.0; break;
    }

}
#endif // CONTROLE_H_INCLUDED
