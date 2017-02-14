    #ifndef OBJECTS_H_INCLUDED
    #define OBJECTS_H_INCLUDED

    GLfloat xBullet = 0, yBullet = 1.7, zBullet = 40;
    GLfloat xCan = 0, yCan = 0.15, zCan = 40;
    int  discTurning = 0;
    GLfloat wheelTurning = 0.0;

    float camAng = 0, camTurning = 0;

    GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
        {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
        {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}
    };

    GLfloat red   [3] = {1.0,0.0,0.0 };
    GLfloat blue   [3] = {0.0, 1.0, 0.0};

    void drawTriangle()
    {
        glBegin(GL_POLYGON);
            glVertex2f(0.0, 1.0  );
            glVertex2f(-1.0,-0.27 );
            glVertex2f(1.0,-0.27 );
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

    void drawWall()
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

    void drawFloor()
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

    void ball(){
        glutSolidSphere(2.0, 100, 10);
    }

    void partialBall()
    {
        glEnable(GL_CLIP_PLANE0);
        GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};
        glClipPlane(GL_CLIP_PLANE0, eqn);
        glutSolidSphere(2.0, 100, 10);
        glDisable(GL_CLIP_PLANE0);
    }


    void cylinder()
    {
        float raio = 1.0;
        float alt = 1.0;
        static GLUquadric* quad;
        quad = gluNewQuadric();
        gluCylinder(quad, raio, raio, alt, 20, 10);
    }

    //desenha bala do canh�o
    void bullet()
    {
        glTranslatef(xBullet,yBullet,zBullet);
        GLfloat xBullet = 0, yBullet = -5.0, zBullet = 22;

        glRotatef(180,0.0,1.0,0.0);
        glScalef(0.3,0.3,0.3);

        glPushMatrix();
            glTranslatef(0.0,0.0,2.0);
            glScalef(0.5,0.5,1.0);
            ball();
        glPopMatrix();

        glPushMatrix();
            glScalef(1.0,1.0,2.0);
            cylinder();
        glPopMatrix();
    }

    //desenha disco que ser� lan�ado
    void disc()
    {
        glTranslatef(-15, 3, 0);

        glPushMatrix();
            glScalef(1.3, 0.3, 1.3);
            glColor3f(0.169,0.169,0.169);
            ball();
        glPopMatrix();
    }

    void wheelModel()
    {
        glPushMatrix();
        glTranslatef(0.0,0.1,0.0);
        glPushMatrix();
            glTranslatef(0.0,0.0,0.15);
            glColor3f(0.85,0.0,0.0);

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
        glPopMatrix();

        glPushMatrix();
            glColor3f(0.1,0.1,0.1);
            glTranslatef(0.0,1.0,0.0);
            glScalef(1.02,1.02,0.3);
            cylinder();
        glPopMatrix();

        glPopMatrix();
    }

    //desenha suporte do canh�o
    void cannonSupport()
    {
        //cor
        glColor3f(0.1,0.1,0.1);

        //eixo
        glPushMatrix();
          glTranslatef(xCan-1.0,0.1,0.0);
          glRotatef(camAng,1.0,0.0,0.0);
          glRotatef(90,0.0,1.0,0.0);
          glScalef(0.2,0.2,2.3);
          cylinder();
        glPopMatrix();
    }

    void cannonWheels()
    {
        glPushMatrix();

        glPushMatrix();
            glTranslatef(xCan +1.0,0.0,zCan);
            glTranslatef(0.0,1.0,0.0);
            glRotatef(wheelTurning,1.0,0.0,0.0);
            glRotatef(-camTurning,1.0,0.0,0.0);
            glTranslatef(0.0,-1.0,0.0);
            glRotatef(90,0.0,1.0,0.0);
            wheelModel();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(xCan -1.0,0.0,zCan);
            glTranslatef(0.0,1.0,0.0);
            glRotatef(camTurning,1.0,0.0,0.0);
            glRotatef(wheelTurning,1.0,0.0,0.0);
            glTranslatef(0.0,-1.0,0.0);
            glRotatef(90,0.0,1.0,0.0);
            wheelModel();
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
            //tubo
            glPushMatrix();
                glTranslatef(xCan,1.5,zCan);
                glRotatef(camAng,1.0,0.0,0.0);

                glPushMatrix();
                   glColor3f(0.1,0.1,0.1);
                    glRotatef(180,0.0,1.0,0.0);
                    glTranslatef(0.0,0.0,-1.2);
                    glScalef(0.4,0.4,3.5);
                    cylinder();
                glPopMatrix();

                glPushMatrix();
                  glColor3f(0.1,0.1,0.1);
                  glTranslatef(0.0,0.0,1.2);
                  glRotatef(90,0.0,1.0,0.0);
                  glRotatef(90,0.0,0.0,1.0);
                  glScalef(0.2,0.2,0.2);
                  partialBall();
                glPopMatrix();
              glPopMatrix();

          glPushMatrix();
            glTranslatef(-0.125,1.0,zCan);
            cannonSupport();
          glPopMatrix();
        glPopMatrix();

        //roda e eixo
        glPushMatrix();
            glTranslatef(-0.13,0.0,-0.0);
            cannonWheels();
        glPopMatrix();

    }
    #endif // OBJECTS_H_INCLUDED
