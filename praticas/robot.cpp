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
GLfloat hc, hb, hp, hwc;
GLfloat wc, wb, wp;
GLfloat aux_hbr, aux_hbl;
GLboolean toggleColors1, toggleColors2;

// Desenha um quadrado de acordo com uma posicao inicial e suas dimensoes
void DesenhaQuadrado(GLfloat x, GLfloat y, GLfloat width, GLfloat heigth)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + heigth);
    glVertex2f(x, y + heigth);
    glEnd();
}

// Funcao de desenho da janela de visualizacao
void DesenhaRobo()
{
    // Define a cor de background (preta)
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha a cabeca do robot
    toggleColors1 ? glColor3f(0, 0, 1) : glColor3f(1, 1, 1);
    DesenhaQuadrado(xi + (wc - hwc) / 2, yi + hc + 1, hwc, hwc);

    // Desenha o tronco do robot
    toggleColors1 ? glColor3f(1, 1, 1) : glColor3f(0, 0, 1);
    DesenhaQuadrado(xi, yi, wc, hc);

    // Desenha os bracos do robot
    toggleColors2 ? glColor3f(1, 1, 0) : glColor3f(1, 0, 0);
    DesenhaQuadrado(xi + wc - 2, yi + hc - aux_hbl, wb, hb);
    DesenhaQuadrado(xi - wb + 2, yi + hc - aux_hbr, wb, hb);

    // Desenha as pernas do robot
    toggleColors2 ? glColor3f(1, 0, 0) : glColor3f(1, 1, 0);
    DesenhaQuadrado(xi, yi - hp - 1, wp, hp);
    DesenhaQuadrado(xi + wc - wp, yi - hp - 1, wp, hp);

    glFlush();
}

// Funcao callback chamada para movimentar o robo
void Movimentacao(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'm': // Move o robo pra sua direita
        if (xi > -90)
            xi -= 5;
        break;

    case 'M': // Move o robo pra sua esquerda
        if (xi < 60)
            xi += 5;
        break;

    case 'i': // Levanta o braco direito
        aux_hbr = 2;
        break;

    case 'I': // Abaixa o braco direito
        aux_hbr = hb;
        break;

    case 'p': // Levanta o braco esquerdo
        aux_hbl = 2;
        break;

    case 'P': // Abaixa o braco esquerdo
        aux_hbl = hb;
        break;
    }

    glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos do mouse
void AlterarCores(int button, int state, int x, int y)
{
    // Altera as cores dos braços e pernas
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
            toggleColors1 = !toggleColors1;

    // Altera as cores da cabeca e tronco
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN)
            toggleColors2 = !toggleColors2;

    glutPostRedisplay();
}

// Inicializa os parametros de renderizacao e variaveis globais
void Inicializa()
{
    // Ponto de referencia inicial (base do tronco)
    xi = -15;
    yi = -30;

    // Dimensoes das partes do corpo
    hc = 60;  // Altura do tronco
    wc = 30;  // Largura do tronco
    hwc = 20; // Altura e largura da cabeca
    hb = 50;  // Altura dos bracos
    wb = 11;  // Largura dos bracos
    hp = 55;  // Altura das pernas
    wp = 12;  // Largura das pernas

    // Variaveis auxiliares para movimentacao dos bracos
    aux_hbr = hb; // Braco direito
    aux_hbl = hb; // Braco esquerdo

    // Variaveis auxiliares para trocar as cores dos membros
    toggleColors1 = false;
    toggleColors2 = false;

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
    glutKeyboardFunc(Movimentacao);
    glutMouseFunc(AlterarCores);

    Inicializa();
    glutMainLoop();
}
