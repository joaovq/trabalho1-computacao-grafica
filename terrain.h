//#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <float.h>
#include <cmath>
using namespace std;
#include <vector>

// definir algumas operacoes como macros, para melhorar desempenho
#define cross_product(n, a, b)\
       ((n).x = (a).y * (b).z - (a).z * (b).y,\
        (n).y = (a).z * (b).x - (a).x * (b).z,\
        (n).z = (a).x * (b).y - (a).y * (b).x)

#define dot_product(a, b)\
       ((a).x * (b).x + (a).y * (b).y + (a).z * (b).z)

#define length(a) sqrt(dot_product(a, a))

//#define PI 3.141593;


typedef struct{
    float x,y,z;
}vetor;

bool normalizaVetor (vetor &v)
{
  float tam;
  tam = length(v);
  if (tam == 0){
     cout << "vetor nulo" << endl;
     return false;
  }
  v.x /= tam;
  v.y /= tam;
  v.z /= tam;
  return true;
}

struct Ponto {
   double x,y,z;
   Ponto(){};
   Ponto(double x, double y, double z) {
      this->x = x;
      this->y = y;
      this->z = z;
   }
};

struct Triangulo {
   int v1,v2,v3;   // índices dos vértices no vetor de pontos
   Triangulo(int v1, int v2, int v3) {
      this->v1 = v1;
      this->v2 = v2;
      this->v3 = v3;
   }
};

class Terreno {
    // representacao de um terreno por uma estrutura de triangulacao
   private:
     vector<Ponto> pontos;
     vector<vetor> normaisVert;
     vector<Triangulo> triangulos;
     vector<vetor> normaisTri;
     double minX, maxX, minY, maxY;
     double distancia(double x1, double y1, double x2, double y2);
     int pontoMaisProximo(double x, double y);
     void calculaNormais();
     int estiloDesenho;  // desenhar apenas linhas ou desenhar polígonos cheios
   public:
     Terreno();
     void exibir();
     void setEstiloDesenho(int est);
};

Terreno::Terreno() {
    ifstream arq_entrada;
    arq_entrada.open("terreno.tri");
    double x,y,z;
    int nPontos;
    arq_entrada >> nPontos;
    minX = DBL_MAX;  maxX = DBL_MIN;
    minY = DBL_MAX;  maxY = DBL_MIN;
    for (int i=0; i<nPontos; i++) {
        arq_entrada >> x >> y >> z;
        Ponto P(x, y, z);
        pontos.push_back(P);
        if (x<minX)  minX=x;
        else if (x>maxX)  maxX=x;
        if (y<minY)  minY=y;
        else if (y>maxY)  maxY=y;
    }
    int v1,v2,v3;
    int nTriangs;
    arq_entrada >> nTriangs;
    for (int i=0; i<nTriangs; i++) {
        arq_entrada >> v1 >> v2 >> v3;
        Triangulo T(v1,v2,v3);
        triangulos.push_back(T);
    }
    arq_entrada.close();
    calculaNormais();

    estiloDesenho = GL_POLYGON;
}

double Terreno::distancia(double x1, double y1, double x2, double y2) {
    double dx = x2-x1;
    double dy = y2-y1;
    return sqrt(dx*dx + dy*dy);
}

int Terreno::pontoMaisProximo(double x, double y) {
    int k;
    double d;
    double menorDist = DBL_MAX;
    int t = pontos.size();
    for (int i=0; i<t; i++) {
        d = distancia(x,y,pontos[i].x, pontos[i].y);
        if (d<menorDist) {
            menorDist = d;
            k = i;
        }
    }
    return k;
}

void Terreno::calculaNormais() {
    // calcular normal para cada triangulo;
    vetor a,b,n;
    int i,j, nTri = triangulos.size();
    for (i=0; i<nTri; i++)
    {
        a.x = pontos[triangulos[i].v2].x - pontos[triangulos[i].v1].x;
        a.y = pontos[triangulos[i].v2].y - pontos[triangulos[i].v1].y;
        a.z = pontos[triangulos[i].v2].z - pontos[triangulos[i].v1].z;

        b.x = pontos[triangulos[i].v3].x - pontos[triangulos[i].v2].x;
        b.y = pontos[triangulos[i].v3].y - pontos[triangulos[i].v2].y;
        b.z = pontos[triangulos[i].v3].z - pontos[triangulos[i].v2].z;

        cross_product(n,a,b);
        normalizaVetor(n);   // melhor guardar a normal normalizada
        normaisTri.push_back(n);
    }

    // calcular normal para cada vértice como média das normais
    // dos triângulos adjacentes a esse vértice
    int nVert = pontos.size();
    vetor normalVert;
    for (j=0; j<nVert; j++) {
        normalVert.x = 0.0;   normalVert.y = 0.0;   normalVert.z = 0.0;
        for (i=0; i<nTri; i++){
            if (triangulos[i].v1==j || triangulos[i].v2==j || triangulos[i].v3==j) {
                // triângulo adjacente ao vértice j
                normalVert.x += normaisTri[i].x;
                normalVert.y += normaisTri[i].y;
                normalVert.z += normaisTri[i].z;
            }
        }
        normalizaVetor(normalVert);   // melhor guardar a normal normalizada
        normaisVert.push_back(normalVert);
    }
}

void Terreno::exibir() {
    glTranslatef(-(maxX-minX)/2, -(maxY-minY)/2, 0.0);

    int nx=20,    // nx = numero de repetições da textura na direcao x
        ny=20;    // idem para y
    double dx = (maxX-minX)/ nx; //dx*dy = area coberta por uma textura
    double dy = (maxY-minY)/ ny;
    int t = triangulos.size();
    for (int i=0; i<t; i++) {
       int v1 = triangulos[i].v1;
       int v2 = triangulos[i].v2;
       int v3 = triangulos[i].v3;
       Ponto p1 = pontos[v1];
       Ponto p2 = pontos[v2];
       Ponto p3 = pontos[v3];

       glBegin(estiloDesenho);  
          glNormal3f(normaisVert[v1].x, normaisVert[v1].y, normaisVert[v1].z);
          glTexCoord2f(p1.x/dx, p1.y/dy);
          glVertex3d(p1.x, p1.y, p1.z);
          glNormal3f(normaisVert[v2].x, normaisVert[v2].y, normaisVert[v2].z);
          glTexCoord2f(p2.x/dx, p2.y/dy);
          glVertex3d(p2.x, p2.y, p2.z);
          glNormal3f(normaisVert[v3].x, normaisVert[v3].y, normaisVert[v3].z);
          glTexCoord2f(p3.x/dx, p3.y/dy);
          glVertex3d(p3.x, p3.y, p3.z);
       glEnd();
    }
}

//*******************************************************************

/* Definicao da posicao do observador por deslocamento sobre uma esfera.
   Esquema de visualização simplificado apresentado em aula */

GLfloat teta = 0.0;    /* ângulo de rotação do observador em torno de Y */
GLfloat fi = 45.0;     /* ângulo de rotação do observador em torno de um eixo normal
                          ao plano definido pelo eixo Y e a posicao do observador   */
GLfloat rho = 200.0;   /* distancia entre o observador e a origem */


Terreno* terreno;


void posicionaObservador() {
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -rho);
    glRotatef(fi, 1.0, 0.0, 0.0);
    glRotatef(-teta, 0.0, 1.0, 0.0);

    // girar o observador, porque o plano horizontal default eh ZX, mas o
    // modelo do terreno considera como horizontal o plano XY
    glRotatef(-90.0, 1.0, 0.0, 0.0);
}



GLfloat posicao_da_luz[]={300.0,300.0,600.0,1.0};


void createTerrain()
{
  glPushMatrix();
    terreno->exibir();
  glPopMatrix();
}