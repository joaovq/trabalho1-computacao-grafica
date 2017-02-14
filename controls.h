#ifndef CONTROLE_H_INCLUDED
#define CONTROLE_H_INCLUDED

bool testeLuz = false;

bool isAiming = true;
bool isShooting = false;

float   alphaCannon = 0;
float   thetaCannon  = 0;

GLfloat xAim = 0.0;
GLfloat yAim = 0.0;

GLfloat speedDisc = 0.001;
GLfloat xCurrentDisc = 0, yCurrentDisc = 0.0, zCurrentDisc = 0;
GLfloat xCurrentBullet = 0, yCurrentBullet = 0.0, zCurrentBullet = 22;

bool drawDisc = true;
double bulletGap = 0.0;

GLfloat xObservator = 0.0;
GLfloat yObservator = 5.0;
GLfloat zObservator = 47.0;

GLfloat xObservatorEye = 0.0;
GLfloat yObservatorEye = 0.0;
GLfloat zObservatorEye = 0.0;

// Observador
GLfloat observAng = 0.0;     // ângulo de rotação do observador em torno de Y

GLfloat zObservatorPosition = 45.0;

//variaveis para escrever na tela
int lauchedDiscs = 1;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void reload()
{
    isShooting = false;
    isAiming = true;
    bulletGap = 0;

}

void shoot()
{
    if(isAiming && !isShooting)
    {
        alphaCannon = camAng;
        thetaCannon = camTurning;
        isShooting = true;

        //isAiming = false;
        GLfloat deltax = xAim - xCurrentDisc;
        GLfloat deltay = yAim - yCurrentDisc;

        if(deltax >  -2.7 && deltax < 2.2 && deltay > -3.0 && deltay < 0)
            speedDisc = 0;
    }
}

void controle (unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
        case 27 :        
            exit(EXIT_SUCCESS);  // tecla ESC para sair
        case 32 :
            shoot();
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
            reload();
            break;
        case 't':
            if(drawDisc == false){
                lauchedDiscs++;
            }
            drawDisc = true;
            break;
    }

}
#endif // CONTROLE_H_INCLUDED
