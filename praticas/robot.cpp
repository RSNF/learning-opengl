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

// Desenha a cabeca do robo
void Cabeca()
{
    GLfloat x = xi + (wc - hwc) / 2;
    GLfloat y = yi + hc + 1;

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + hwc, y);
    glVertex2f(x + hwc, y + hwc);
    glVertex2f(x, y + hwc);
    glEnd();
}

// Desenha o braco esquerdo do robo
void BracoEsquerdo()
{
    GLfloat x = xi + wc - 2;
    GLfloat y = yi + hc - aux_hbl;

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + wb, y);
    glVertex2f(x + wb, y + hb);
    glVertex2f(x, y + hb);
    glEnd();
}

// Desenha o braco direito do robo
void BracoDireito()
{
    GLfloat x = xi - wb + 2;
    GLfloat y = yi + hc - aux_hbr;

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + wb, y);
    glVertex2f(x + wb, y + hb);
    glVertex2f(x, y + hb);
    glEnd();
}

// Desenha o tronco do robo
void Tronco()
{
    GLfloat x = xi;
    GLfloat y = yi;

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + wc, y);
    glVertex2f(x + wc, y + hc);
    glVertex2f(x, y + hc);
    glEnd();
}

// Desenha a perna esquerda do robo
void PernaEsquerda()
{
    GLfloat x = xi + wc - wp;
    GLfloat y = yi - hp - 1;

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + wp, y);
    glVertex2f(x + wp, y + hp);
    glVertex2f(x, y + hp);
    glEnd();
}

// Desenha a perna direita do robo
void PernaDireita()
{
    GLfloat x = xi;
    GLfloat y = yi - hp - 1;

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + wp, y);
    glVertex2f(x + wp, y + hp);
    glVertex2f(x, y + hp);
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
    Tronco();
    glColor3f(1, 0, 0);
    BracoEsquerdo();
    BracoDireito();
    glColor3f(1, 1, 0);
    PernaEsquerda();
    PernaDireita();

    glFlush();
}

// Funcao callback chamada para movimentar o robo
void Movimentacao(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'm': // Move o robo pra sua direita
        if (xi > -90)
        {
            xi -= 5;
        }
        break;

    case 'M': // Move o robo pra sua esquerda
        if (xi < 60)
        {
            xi += 5;
        }
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

    // Variavel auxiliar para movimentacao dos bracos
    aux_hbr = hb; // Braco direito
    aux_hbl = hb; // Braco esquerdo

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
    // glutMouseFunc(GerenciaMouse);

    Inicializa();
    glutMainLoop();
}
