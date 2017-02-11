#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

GLfloat xBala = 0, yBala = 1.7, zBala = 40;
GLfloat xCan = 0, yCan = 0.15, zCan = 40;
int  giraDisco = 0;
float giraSol = 0;
GLfloat giroRoda = 0.0;

float angCan = 0, giroCan = 0;


GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
    {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
    {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}
};

GLfloat ufoColorRing [3] = {0.8274,0.8274,0.8274 };
GLfloat ufoColor   [3] = {0.5274,0.5274,0.5274 };
GLfloat sunColor   [3] = {0.988,0.83,0.2509 };
GLfloat moonColor   [3] = {1.0,1.0,1.0};
GLfloat red   [3] = {1.0,0.0,0.0 };
GLfloat blue   [3] = {0.0, 1.0, 0.0};

void desenhaTriangulo()
{
    glBegin(GL_POLYGON);
        glVertex2f(0.0, 1.0  );
        glVertex2f(-1.0,-0.27 );
        glVertex2f(1.0,-0.27 );
    glEnd();
}

void desenhaPa()
{
    glBegin(GL_POLYGON);
    glVertex2f(0.0,1.0);
    glVertex2f(-1.0,-1.0);
    glVertex2f(-1.0,-2.0);
    glVertex2f(1.0,-2.0);
    glVertex2f(1.0,-1.0);
    glEnd();

}

void polygon(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
      glTexCoord2f(0.0, 0.0);
     	glVertex3fv(vertices[a]);
     	glTexCoord2f(1.0, 0.0);
     	glVertex3fv(vertices[b]);
     	glTexCoord2f(1.0, 1.0);
     	glVertex3fv(vertices[c]);
     	glTexCoord2f(0.0, 1.0);
     	glVertex3fv(vertices[d]);
     glEnd();
}

void cube()
{
    glNormal3f(0.0,0.0,-1.0);
    polygon(0,3,2,1);

    glNormal3f(0.0,1.0,0.0);
    polygon(2,3,7,6);

    glNormal3f(-1.0,0.0,0.0);
    polygon(0,4,7,3);

    glNormal3f(1.0,0.0,0.0);
    polygon(1,2,6,5);

    glNormal3f(0.0,0.0,1.0);
    polygon(4,5,6,7);

    glNormal3f(0.0,-1.0,0.0);
    polygon(0,1,5,4);
}

void desenhaParede()
{
    glScalef(200.0,0.1, 200.0 );
    glBegin(GL_POLYGON);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(  1.0, 0.0, -1.0 );

    glTexCoord2f(100, 0.0);
    glVertex3f(  1.0, 0.0,  1.0 );

    glTexCoord2f(100, 100);
    glVertex3f( -1.0, 0.0,  1.0 );

    glTexCoord2f(0.0, 100);
    glVertex3f( -1.0, 0.0, -1.0 );

    glEnd();
}

void desenhaChao()
{
    glScalef(1.0, 0.1, 1.0 );
    glBegin(GL_POLYGON);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(  1.0, 0.0, -1.0 );

        glTexCoord2f(1.0, 0.0);
        glVertex3f(  1.0, 0.0,  1.0 );

        glTexCoord2f(1.0, 1.0);
        glVertex3f( -1.0, 0.0,  1.0 );

        glTexCoord2f(0.0, 1.0);
        glVertex3f( -1.0, 0.0, -1.0 );
    glEnd();

}

void esfera()
{
    //glColor3f(objectColor[0],objectColor[1], objectColor[2] );
    glutSolidSphere(2.0, 100, 10);

}

void meiaEsfera()
{
    glEnable(GL_CLIP_PLANE0);
    GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glutSolidSphere(2.0, 100, 10);
    glDisable(GL_CLIP_PLANE0);
}

// modelo de cilindro com eixo em Z e thetaCannonbase em Z=0
void cilindro()
{
    float raio = 1.0;
    float alt = 1.0;
    static GLUquadric* quad;
    quad = gluNewQuadric();
    gluCylinder(quad, raio, raio, alt, 20, 10);
}/**<  */


//desenha bala
void bala()
{
    glTranslatef(xBala,yBala,zBala);
    GLfloat xBala = 0, yBala = -5.0, zBala = 22;

    glRotatef(180,0.0,1.0,0.0);
    glScalef(0.3,0.3,0.3);

    glPushMatrix();
    glTranslatef(0.0,0.0,2.0);
    glScalef(0.5,0.5,1.0);
    esfera();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0,1.0,2.0);
    cilindro();
    glPopMatrix();
}

void luzDiscoVoador()
{
    glPushMatrix();
        glColor3f(red[0], red[1], red[2]);
        glPushMatrix();
        
            glTranslatef(-2.0, 0.4, 0.0);
            GLfloat light_ambient[]= {red[0], red[1], red[2], 1.0};
            GLfloat light_diffuse[]= {red[0], red[1], red[2], 1.0};
            GLfloat light_specular[]= {red[0], red[1], red[2], 1.0};
            GLfloat light_position[]= {0.0, 0.0, 0.0, 1.0};

            glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
            glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
            glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT3, GL_POSITION, light_position);
            glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 8.0);


            GLfloat mat_ambient[]= {1.0, 1.0, 1.0, 1.0};
            GLfloat mat_diffuse[]= {1.0, 1.0, 1.0, 1.0};
            GLfloat mat_specular[]= {1.0,1.0,1.0, 1.0};
            GLfloat mat_shininess= {1000.0};

            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
            glColorMaterial(GL_FRONT_AND_BACK, 8.0);
            glScalef(0.1, 0.1, 0.1);
            cube();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(2.0, 0.4, 0.0);
            GLfloat light_ambient2[]= {red[0], red[1], red[2], 1.0};
            GLfloat light_diffuse2[]= {red[0], red[1], red[2], 1.0};
            GLfloat light_specular2[]= {red[0], red[1], red[2], 1.0};
            GLfloat light_position2[]= {0.0, 0.0, 0.0, 1.0};

            glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient2);
            glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse2);
            glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular2);
            glLightfv(GL_LIGHT4, GL_POSITION, light_position2);
            glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 8.0);

            
            GLfloat mat_ambient2[]= {1.0, 1.0, 1.0, 1.0};
            GLfloat mat_diffuse2[]= {1.0, 1.0, 1.0, 1.0};
            GLfloat mat_specular2[]= {1.0,1.0,1.0, 1.0};
            GLfloat mat_shininess2= {1000.0};

            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
            glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess2);
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glScalef(0.1, 0.1, 0.1);
            cube();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glColor3f(blue[0], blue[1], blue[2]);
        glPushMatrix();
            glTranslatef(0.0, 0.4, -2.0);
            GLfloat light_ambient3[]= {blue[0], blue[1], blue[2], 1.0};
            GLfloat light_diffuse3[]= {blue[0], blue[1], blue[2], 1.0};
            GLfloat light_specular3[]= {blue[0], blue[1], blue[2], 1.0};
            GLfloat light_position3[]= {0.0, 0.0, 0.0, 1.0};

            glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient3);
            glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse3);
            glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular3);
            glLightfv(GL_LIGHT5, GL_POSITION, light_position3);
            glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 8.0);
            
            GLfloat mat_ambient3[]= {1.0, 1.0, 1.0, 1.0};
            GLfloat mat_diffuse3[]= {1.0, 1.0, 1.0, 1.0};
            GLfloat mat_specular3[]= {1.0,1.0,1.0, 1.0};
            GLfloat mat_shininess3= {1000.0};

            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
            glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess3);
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glScalef(0.1, 0.1, 0.1);
            cube();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0, 0.4, 2.0);
            GLfloat light_ambient4[]= {blue[0], blue[1], blue[2], 1.0};
            GLfloat light_diffuse4[]= {blue[0], blue[1], blue[2], 1.0};
            GLfloat light_specular4[]= {blue[0], blue[1], blue[2], 1.0};
            GLfloat light_position4[]= {0.0, 0.0, 0.0, 1.0};

            glLightfv(GL_LIGHT6, GL_AMBIENT, light_ambient4);
            glLightfv(GL_LIGHT6, GL_DIFFUSE, light_diffuse4);
            glLightfv(GL_LIGHT6, GL_SPECULAR, light_specular4);
            glLightfv(GL_LIGHT6, GL_POSITION, light_position4);
            glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 8.0);

            
            GLfloat mat_ambient4[]= {1.0, 1.0, 1.0, 1.0};
            GLfloat mat_diffuse4[]= {1.0, 1.0, 1.0, 1.0};
            GLfloat mat_specular4[]= {1.0,1.0,1.0, 1.0};
            GLfloat mat_shininess4= {1000.0};

            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
            glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess4);
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glScalef(0.1, 0.1, 0.1);
            cube();
        glPopMatrix();
    glPopMatrix();
}

void antenaDiscoVoador(){

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glScalef(0.1, 0.1, 2.0);
	glTranslatef(0, 0.0, -1.8);
	cilindro();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.15, 0.15, 0.15);
	glTranslatef(0, 25, 0);
	glColor3f(red[0], red[1], red[2]);
	esfera();
	glPopMatrix();
}


//desenha disco voador
void discoVoador()
{
    //se mudar aqui DEVE mudar na funçao moveDiscoVoador
    glTranslatef(-15, 3, 0);

    //disco esterno
    glPushMatrix();
    glRotatef(giraDisco, 0.0, 1.0, 0);
    luzDiscoVoador();
    glScalef(1.3, 0.3, 1.3);
    glColor3f(ufoColor[0], ufoColor[1], ufoColor[2]);
    esfera();
    glPopMatrix();

    //cabine, bola do meio
    glColor3f(ufoColorRing[0], ufoColorRing[1], ufoColorRing[2]);
    glPushMatrix();
    glScalef(0.6,1.2, 0.6);
    meiaEsfera();
    glPopMatrix();
    glPushMatrix();
    glRotatef(180, 0.0, 0.0, 1.0);
    glScalef(0.9,0.4, 0.9);
    meiaEsfera();
    glPopMatrix();

}

void modeloRoda()
{
    glPushMatrix();
    glTranslatef(0.0,0.1,0.0);
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTranslatef(0.0,0.0,0.15);
        glColor3f(1.0,1.0,1.0);
        glBindTexture(GL_TEXTURE_2D, 15);

        glPushMatrix();
            glTranslatef(0.0,1.0,0.0);
            glRotatef(-45.0,0.0,0.0,1.0);
            glScalef(0.08,1.0,0.1);
            cube();
        glPopMatrix();

    
        glPushMatrix();
        glTranslatef(0.0,1.0,0.0);
        glRotatef(45.0,0.0,0.0,1.0);
        glScalef(0.08,1.0,0.1);
        cube();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0,1.0,0.0);
        glRotatef(90.0,0.0,0.0,1.0);
        glScalef(0.08,1.0,0.1);
        cube();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0,1.0,0.0);
        glScalef(0.08,1.,0.1);
        cube();
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.1,0.1,0.1);
        glTranslatef(0.0,1.0,0.0);
        glScalef(1.02,1.02,0.3);
        cilindro();
    glPopMatrix();

    glPopMatrix();
}

void eixoCanhao()
{
    //Cor do eixo
    glColor3f(0.1,0.1,0.1);

    //Eixo
    glPushMatrix();
      glTranslatef(xCan-1.0,0.1,0.0);
      glRotatef(angCan,1.0,0.0,0.0);
      glRotatef(90,0.0,1.0,0.0);
      glScalef(0.2,0.2,2.3);
      cilindro();
    glPopMatrix();

    //Ponta daq esquerda
    glPushMatrix();

      glTranslatef(xCan-1.0,0.1,0.0);
      glRotatef(angCan,1.0,0.0,0.0);
      glRotatef(90,0.0,0.0,1.0);
      glScalef(0.1,0.1,0.1);
      meiaEsfera();
    glPopMatrix();

    //Ponta daq esquerda
    glPushMatrix();
      glTranslatef(xCan +1.25,0.1,0.0);
      glRotatef(angCan,1.0,0.0,0.0);
      glRotatef(-90,0.0,0.0,1.0);
      glScalef(0.1,0.1,0.1);
      meiaEsfera();
    glPopMatrix();
}

void rodaDoCanhao()
{

    glPushMatrix();

    glPushMatrix();
        glTranslatef(xCan +1.0,0.0,zCan);
        glTranslatef(0.0,1.0,0.0);
        glRotatef(giroRoda,1.0,0.0,0.0);
        glRotatef(-giroCan,1.0,0.0,0.0);
        glTranslatef(0.0,-1.0,0.0);
        glRotatef(90,0.0,1.0,0.0);
        modeloRoda();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(xCan -1.0,0.0,zCan);
        glTranslatef(0.0,1.0,0.0);
        glRotatef(giroCan,1.0,0.0,0.0);
        glRotatef(giroRoda,1.0,0.0,0.0);
        glTranslatef(0.0,-1.0,0.0);
        glRotatef(90,0.0,1.0,0.0);
        modeloRoda();
    glPopMatrix();


    glPopMatrix();
}

//desenha canhao
void cannon()
{
    GLfloat mat_ambient[]= {0.4, 0.3, 0.4, 0.3};
    GLfloat mat_diffuse[]= {0.8, 0.8, 0.8, 0.8};
    GLfloat mat_specular[]= {0.3,0.3,0.3, 1.0};
    GLfloat mat_shininess= {80.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glTranslatef(0.0,yCan,0.0);

    glPushMatrix();
    //Tubo do canhao
      glPushMatrix();
        glTranslatef(xCan,1.5,zCan);
        glRotatef(angCan,1.0,0.0,0.0);

        glPushMatrix();
          glColor3f(0.1,0.1,0.1);

          glRotatef(180,0.0,1.0,0.0);
          glTranslatef(0.0,0.0,-1.2);
          glScalef(0.4,0.4,3.5);
          cilindro();
        glPopMatrix();

        glPushMatrix();
          glColor3f(0.1,0.1,0.1);
          glTranslatef(0.0,0.0,1.2);
          glRotatef(90,0.0,1.0,0.0);
          glRotatef(90,0.0,0.0,1.0);
          glScalef(0.2,0.2,0.2);
          meiaEsfera();
        glPopMatrix();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-0.125,1.0,zCan);
      eixoCanhao();
      glPopMatrix();
    glPopMatrix();

    //Roda e eixo
    glPushMatrix();
    glTranslatef(-0.13,0.0,-0.0);
    rodaDoCanhao();
    glPopMatrix();

}

void desenhaTorreObservacao(){
    double alturaPilarBase = 12;
    glColor3f(1.0,1.0,1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 15);
    //PilaresBase da Torre
    glPushMatrix();

        glPushMatrix();
            glTranslatef(-3, 0, 0);
            glScalef(0.3, alturaPilarBase, 0.3);
            cube();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(3, 0, 0);
            glScalef(0.3, alturaPilarBase, 0.3);
            cube();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-3, 0, 6);
            glScalef(0.3, alturaPilarBase, 0.3);
            cube();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(3, 0, 6);
            glScalef(0.3, alturaPilarBase, 0.3);
            cube();
        glPopMatrix();
    glPopMatrix();

    //Escada
    glPushMatrix();

        glPushMatrix();
            glTranslatef(-1.5, 6, 6);
            glScalef(1.5, 0.3, 0.3);
            cube();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1.5, 4, 6);
            glScalef(1.5, 0.3, 0.3);
            cube();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1.5, 2, 6);
            glScalef(1.5, 0.3, 0.3);
            cube();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, 6);
            glScalef(0.3, alturaPilarBase, 0.3);
            cube();
        glPopMatrix();

    glPopMatrix();

    //Piso
    glPushMatrix();
        float xTorre = 2.75, yTorre = 0.3, zTorre = 3;

        glPushMatrix();
            glTranslatef(0, (yTorre/2)+alturaPilarBase-4, (zTorre));
            glScalef(xTorre+0.55, yTorre, zTorre+0.3);
            cube();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, alturaPilarBase-0.3, 0);
            glScalef(3, 0.3, 0.3);
            cube();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(1.5, alturaPilarBase-0.3, 6);
            glScalef(1.5, 0.3, 0.3);
            cube();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(3, alturaPilarBase-0.3, 3);
            glScalef(0.3, 0.3, 3);
            cube();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-3, alturaPilarBase-0.3, 3);
            glScalef(0.3, 0.3, 3);
            cube();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

//desenha base lancamento
void baseDeLancamento()
{
    GLfloat yBaseL = 2.0;
    glColor3f(1.0, 1.0, 1.0);
    GLfloat mat_ambient[]= {0.4, 0.3, 0.4, 0.3};
    GLfloat mat_diffuse[]= {0.5, 0.5, 0.5, 0.5};
    GLfloat mat_specular[]= {0.6,0.6,0.6, 1.0};
    GLfloat mat_shininess= {1000.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 16);
    //Frente da caixa
    glPushMatrix();
        glTranslatef(-11.0, yBaseL, 0.0);
        glScalef(0.3, yBaseL, 3.3);
        cube();
    glPopMatrix();

    //Parte de tras da caixa
    glPushMatrix();
        glTranslatef(-19.0, yBaseL, 0.0);
        glScalef(0.3, yBaseL, 3.3);
        cube();
    glPopMatrix();

    //Laterais
    glPushMatrix();
        glTranslatef(-15.0, yBaseL, -3.0);
        glScalef(4.0, yBaseL, 0.3);
        cube();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-15.0, yBaseL, 3.0);
        glScalef(4.0, yBaseL, 0.3);
        cube();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-15.0, 0.0, 0.0);
        glScalef(4.0, 0.3, 3.0);
        cube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void desenhaPoste(){
    
    glPushMatrix();

        GLfloat light_ambient[]= {1.0, 1.0, 1.0, 1.0};
        GLfloat light_diffuse[]= {1.0, 1.0, 1.0, 1.0};
        GLfloat light_specular[]= {1.0,1.0,1.0, 1.0};
        GLfloat light_position[]= {-3.2,11.0,0.0, 1.0};
        GLfloat spot_direction[]= {0.0, -8.0, 0.0};

        glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT2, GL_POSITION, light_position);
        //glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
        //glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.9);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.015);


        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60.0);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.5);
        
        GLfloat mat_ambient[]= {0.7, 0.5, 0.7, 1.0};
        GLfloat mat_diffuse[]= {1.0, 1.0, 1.0, 1.0};
        GLfloat mat_specular[]= {1.0,1.0,1.0, 1.0};
        GLfloat mat_shininess= {1000.0};

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
       

        glColor3f(1.0,1.0,1.0);
        glTranslatef(-2.0,10.0,0.0);
        glRotatef(135,0.0,0.0,1.0);
        glScalef(0.4,0.3,0.2);
        meiaEsfera();
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0.0,0.0,0.0);
        glTranslatef(-2.0,10.0,0.0);
        glRotatef(-45,0.0,0.0,1.0);
        glScalef(0.5,0.15,0.3);
        esfera();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.0,0.0);
        glTranslatef(0.0,8.5,0.0);
        glRotatef(50,0.0,0.0,1.0);
        glScalef(0.2,3.0,0.2);
        glRotatef(-90.0,1.0,0.0,0.0);
        cilindro();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.0,0.0);
        glScalef(0.3,9.0,0.3);
        glRotatef(-90.0,1.0,0.0,0.0);
        cilindro();
    glPopMatrix();
}



#endif // OBJECTS_H_INCLUDED
