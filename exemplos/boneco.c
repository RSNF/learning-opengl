/*
 *  boneco.c
 *  Este programa demonstra o uso de distintas transforma��es
 *  para composicao de uma cena complexa
 *
 *  author: Ting (19/08/06)
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define v .577350269

static GLfloat vdata[8][3] = {
    {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}};

static GLfloat ndata[8][3] = {
    {-v, -v, -v}, {v, -v, -v}, {v, v, -v}, {-v, v, -v}, {-v, -v, v}, {v, -v, v}, {v, v, v}, {-v, v, v}};

static GLuint vindices[6][4] = {
    {0, 3, 2, 1}, {2, 3, 7, 6}, {0, 4, 7, 3}, {1, 2, 6, 5}, {4, 5, 6, 7}, {0, 1, 5, 4}};

static GLfloat m[4][4] = {
    {1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0}};

GLfloat spin_x = 0.0, spin_y = 0.0, spin_z = 0.0;

GLfloat ant = 0.0, bra = 0.0, cab = 0.0;

GLuint braco, busto, cabeca, perna;

/* Desenhar um cubo */

static void cube()
{
   int i;

   /* desenhar o cubo */
   for (i = 0; i < 6; i++)
   {
      glBegin(GL_POLYGON);
      glColor3f(1.0, 0.0, 0.0);
      glNormal3fv(&ndata[vindices[i][0]][0]);
      glVertex3fv(&vdata[vindices[i][0]][0]);
      glColor3f(0.0, 1.0, 0.0);
      glNormal3fv(&ndata[vindices[i][1]][0]);
      glVertex3fv(&vdata[vindices[i][1]][0]);
      glColor3f(0.0, 0.0, 1.0);
      glNormal3fv(&ndata[vindices[i][2]][0]);
      glVertex3fv(&vdata[vindices[i][2]][0]);
      glColor3f(0.0, 1.0, 1.0);
      glNormal3fv(&ndata[vindices[i][3]][0]);
      glVertex3fv(&vdata[vindices[i][3]][0]);
      glEnd();
   }
}

static void boneco()
{
   /* criar braco */
   /* gerar um indice de uma lista */
   braco = glGenLists(1);
   /* inicializar o conteudo da lista "braco". Ha dois modos:
      GL_COMPLIE: somente armazena; GL_COMPILE_AND_EXECUTE: armazena e executa
      */
   glNewList(braco, GL_COMPILE);
   glScalef(0.09, 0.28, 0.09);
   cube();
   /* finalizar a lista inicializada */
   glEndList();

   /* criar busto */
   busto = glGenLists(1);
   glNewList(busto, GL_COMPILE);
   glScalef(0.35, 0.525, 0.2);
   cube();
   glEndList();

   /* criar cabeca */
   cabeca = glGenLists(1);
   glNewList(cabeca, GL_COMPILE);
   glScalef(0.2, 0.2, 0.2);
   cube();
   glEndList();

   /* criar perna */
   perna = glGenLists(1);
   glNewList(perna, GL_COMPILE);
   glScalef(0.09, 0.57, 0.09);
   cube();
   glEndList();
}

void init(void)
{
   /* definir dados do boneco */
   boneco();
   /* definir a cor em preto (0,0,0) como cor de "CLEAR" */
   glClearColor(0.0, 0.0, 0.0, 0.0);
   /* setar o tipo de tonalizacao. Ha duas alternativas
      GL_FLAT (constante) e GL_SMOOTH (interpolacao linear
      entre os vertices) */
   glShadeModel(GL_SMOOTH);
   /* setar o tamanho do ponto em pixels */
   glPointSize(5.0);
   /* setar a largura da linha em pixels */
   glLineWidth(3.0);
   /* setar o modo de renderizacao das faces. Ha tres alternativas:
      GL_POINT (somente vertices), GL_LINE (somente linhas) e GL_FILL
      (faces preenchidas) */
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   /* setar a convencao de orientacao. Ha duas alternativas: GL_CCW (anti-horario)      e GL_CW (horario) */
   glFrontFace(GL_CCW);
   /* Habilitar face culling */
   glEnable(GL_CULL_FACE);
   /* definir as faces a serem discardadas. Ha tres alternativas: GL_FRONT,
      GL_BACK e GL_FRONT_AND_BACK */
   glCullFace(GL_BACK);
}

void display(void)
{
   int i;

   /* "CLEAR" o display */
   glClear(GL_COLOR_BUFFER_BIT);
   /* setar a cor de desenho em branco (1,1,1) */
   glColor3f(1.0, 1.0, 1.0);
   /* carregar a matriz de identidade na pilha de matriz de transformacao */
   glLoadIdentity();

   /* concatenar a matriz de translacao com a do topo da pilha */
   glTranslatef(0.0, 0.0, -2.0);

   /* concatenar a matriz de rotacao com a do topo da pilha */
   glRotatef(spin_x, 1.0, 0.0, 0.0);

   /* concatenar a matriz de rotacao com a do topo da pilha */
   glRotatef(spin_y, 0.0, 1.0, 0.0);

   /* concatenar a matriz de rotacao com a do topo da pilha */
   glRotatef(spin_z, 0.0, 0.0, 1.0);

   /* definir matriz de cisalhamento */
   m[0][0] = 1.0;
   m[1][0] = 0.0;
   m[2][0] = 0.0;
   m[3][0] = 0.0;
   m[0][1] = 0.0;
   m[1][1] = 1.0;
   m[2][1] = 0.0;
   m[3][1] = 0.0;
   m[0][2] = 0.0;
   m[1][2] = 0.0;
   m[2][2] = 1.0;
   m[3][2] = 0.0;
   m[0][3] = 0.0;
   m[1][3] = 0.0;
   m[2][3] = 0.0;
   m[3][3] = 1.0;
   /* concatenar a matriz com a do topo da pilha */
   glMultMatrixf(&m[0][0]);

   /* concatenar a matriz de mudanca de escala com a do topo da pilha */
   glScalef(1., 1., 1.);

   /* desenhar a figura */
   /* desenhar o busto */
   glPushMatrix();
   glCallList(busto);
   glPopMatrix();

   /* desenhar as pernas */
   glPushMatrix();
   glTranslatef(0.2, -1.12, 0.0);
   glCallList(perna);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-0.2, -1.12, 0.0);
   glCallList(perna);
   glPopMatrix();

   /* desenhar a cabeca */
   glPushMatrix();
   glTranslatef(0.0, 0.73, 0.0);
   // rotacionar a cabeca no sentido anti-horario em torno de y */
   glRotatef(cab, 0.0, 1.0, 0.0);
   glCallList(cabeca);
   glPopMatrix();

   /* desenhar os bracos */
   glPushMatrix();
   glTranslatef(-0.45, 0.26, 0.0);
   glPushMatrix();
   glCallList(braco);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.0, -0.59, 0.0);
   glCallList(braco);
   glPopMatrix();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.45, 0.26, 0.0);
   /* rotationar o braco no sentido anti-horario em trono do x */
   glTranslatef(.0, .28, .0);
   glRotatef(bra, 1.0, 0.0, 0.0);
   glTranslatef(.0, -.28, .0);
   glPushMatrix();
   glCallList(braco);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0., -0.59, 0.0);
   /* rotationar o anti-braco no sentido anti-horario em trono do x */
   glTranslatef(.0, .28, .0);
   glRotatef(ant, 1.0, 0.0, 0.0);
   glTranslatef(.0, -0.28, .0);
   glCallList(braco);
   glPopMatrix();
   glPopMatrix();

   /* forcar a execucao dos comandos enviados a OpenGL */
   glFlush();
}

void reshape(int w, int h)
{
   /* definir o tamanha de janela no display, em pixels */
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   /* chavear para a pilha de transformacao de projecao */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-2.0, 2.0, -2.0, 2.0, 0.0, 5.0);
   /* chavear para a pilha de transformacao de modelo */
   glMatrixMode(GL_MODELVIEW);
}

/* ARGSUSED1 */
void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 'a':
      /* increment -10.0 no �ngulo de rota��o em torno do eixo x */
      ant -= 10.0;
      if (ant < -160.0)
         ant = 0.0;
      break;
   case 'b':
      /* increment -10.0 no �ngulo de rota��o em torno do eixo x */
      bra -= 10.0;
      if (bra < -160.0)
         bra = 0.0;
      break;
   case 'c':
      /* increment -10.0 no �ngulo de rota��o em torno do eixo x */
      cab += 10.0;
      break;
   case 'x':
      /* increment +10.0 no �ngulo de rota��o em torno do eixo x */
      spin_x += 10.0;
      break;
   case 'y':
      /* incrementa +10.0 no �ngulo de rota��o em torno do eixo y */
      spin_y += 10.0;
      break;
   case 'z':
      /* increment +10.0 no �ngulo de rota��o em torno do eixo z */
      spin_z += 10.0;
      break;
   case 'r':
      /* reset */
      spin_x = spin_y = spin_z = 0.0;
      break;
   case 27:
      exit(0);
      return;
   }
   /* for�ar um evento para ativar o redesenho */
   glutPostRedisplay();
}

int main(int argc, char **argv)
{
   /* estabelecimento de comunicacao com o sistema de janela */
   glutInit(&argc, argv);
   /* setar o " visual" do display */
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   /* definir a janela */
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   /* inicializar openGL */
   init();
   /* registrar os tratadores de eventos */
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   /* entre no modo de espera */
   glutMainLoop();
   return 0;
}
