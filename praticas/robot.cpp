// ************************************************
//
// Universidade Estadual do Sudoeste da Bahia
// Disciplina: Computacao Grafica
// Docente: Elienai Bittencourt
// Aluno: William Jefferson Silva Sena
//
// robot.cpp
// Programa OpenGL que desenha um robo e simula o
// movimento dos bracos e do corpo, utilizando
// gerenciamento de eventos de mouse e teclado
//
// ************************************************

#include <GL/glut.h>

GLfloat xi, yi;
GLfloat h_c, h_b, h_p, h_w_c;
GLfloat w_c, w_b, w_p;

// Desenha a cabeca do robo
void Cabeca()
{
    GLfloat x = xi + (w_c - h_w_c) / 2;
    GLfloat y = yi + h_c + 1;

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + h_w_c, y);
    glVertex2f(x + h_w_c, y + h_w_c);
    glVertex2f(x, y + h_w_c);
    glEnd();
}

// Desenha o braco esquerdo do robo
void BracoEsquerdo()
{
    GLfloat x = xi + w_c - 2;
    // GLfloat y = yi + h_c - h_b; // braco abaixado
    GLfloat y = yi + h_c - 2; // braco levantado

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w_b, y);
    glVertex2f(x + w_b, y + h_b);
    glVertex2f(x, y + h_b);
    glEnd();
}

// Desenha o braco direito do robo
void BracoDireito()
{
    GLfloat x = xi - w_b + 2;
    GLfloat y = yi + h_c - h_b;

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w_b, y);
    glVertex2f(x + w_b, y + h_b);
    glVertex2f(x, y + h_b);
    glEnd();
}

// Desenha o corpo do robo
void Corpo()
{
    GLfloat x = xi;
    GLfloat y = yi;

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w_c, y);
    glVertex2f(x + w_c, y + h_c);
    glVertex2f(x, y + h_c);
    glEnd();
}

// Desenha a perna esquerda do robo
void PernaEsquerda()
{
    GLfloat x = xi + w_c - w_p;
    GLfloat y = yi - h_p - 1;

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w_p, y);
    glVertex2f(x + w_p, y + h_p);
    glVertex2f(x, y + h_p);
    glEnd();
}

// Desenha a perna direita do robo
void PernaDireita()
{
    GLfloat x = xi;
    GLfloat y = yi - h_p - 1;

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w_p, y);
    glVertex2f(x + w_p, y + h_p);
    glVertex2f(x, y + h_p);
    glEnd();
}

// Funcao de desenho da janela de visualizacao
void DesenhaRobo()
{
    // Define a cor de background (preta)
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha as partes do corpo do robo
    glColor3f(1, 1, 1);
    Cabeca();
    glColor3f(0, 0, 1);
    Corpo();
    glColor3f(1, 0, 0);
    BracoEsquerdo();
    BracoDireito();
    glColor3f(1, 1, 0);
    PernaEsquerda();
    PernaDireita();

    glFlush();
}

// Inicializa os parametros de renderizacao e variaveis globais
void Inicializa()
{
    // Ponto de referencia inicial (base do corpo)
    xi = -15;
    yi = -30;

    // Dimensoes das partes do corpo
    h_c = 60;   // Altura do corpo
    w_c = 30;   // Largura do corpo
    h_w_c = 20; // Altura e largura da cabeca
    h_b = 50;   // Altura dos bracos
    w_b = 11;   // Largura dos bracos
    h_p = 55;   // Altura das pernas
    w_p = 12;   // Largura das pernas

    // Define a janela de visualizacao 2D
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0); // 200x200
    glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Tamanho em pixels da janela
    glutInitWindowSize(700, 600);

    // Centraliza a janela do GLUT
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 700) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - 600) / 2);

    // Cria a janela
    glutCreateWindow("Robot");

    // Registra funcao de redesenho
    glutDisplayFunc(DesenhaRobo);

    // Registra funcoes de gerenciamento de teclado e mouse
    // glutKeyboardFunc(GerenciaTeclado);
    // glutMouseFunc(GerenciaMouse);
    // glutSpecialFunc(TeclasEspeciais);

    Inicializa();
    glutMainLoop();
}
