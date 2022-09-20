/*
 *--------------------------------------------------
 * exSimples.c
 * UFPE
 * Autor: Prof. Marcelo Walter
 * Data: Jan 15, 1999
 * Ultima modificacao: Nov 6, 2006
 *
 * Este programa introduz os principais
 * conceitos de programacao 2D com GLUT e
 * OpenGL. Este programa desenha um quadrado
 * aproximadamente centrado no meio da tela
 * A cor do quadrado muda aleatoriamente
 * ao pressionar-se o botao esquerdo do mouse
 *--------------------------------------------------
 */

/*
 *--------------------------------------------------
 * Includes
 *--------------------------------------------------
 */

#include <stdio.h>
#include <GL/glut.h>

/*
 *--------------------------------------------------
 * Prototipos para as funcoes globais
 *--------------------------------------------------
 */

void exibeCB(void);
void tecladoCB(unsigned char tecla, int x, int y);
void redesenhaCB(int w, int h);
void inic(void);
void mouseCB(int botao, int estado, int x, int y);

/*
 *--------------------------------------------------
 * Funcao principal
 *--------------------------------------------------
 */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    inic();
    glutMainLoop();
    return 1;
}

/*
 *--------------------------------------------------
 * Esta funcao inicializa a janela OpenGL, registra
 * as rotinas de callback e inicializa as matrizes
 * do OpenGL
 *--------------------------------------------------
 */

void inic(void)
{
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Exemplo Simples 1");

    /* Registra as rotinas de CallBack */
    glutDisplayFunc(exibeCB);
    glutKeyboardFunc(tecladoCB);
    glutReshapeFunc(redesenhaCB);
    glutMouseFunc(mouseCB);

    /* Cor default fundo preta */
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Limpa buffer de cor */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Cor default para objetos. Vermelho */
    glColor3f(1.0, 0.0, 0.0);
}

/*
 *----------------------------------------------------------
 * Rotina para tratamento de eventos relacionados ao mouse
 *
 * botao: Botao que foi pressionado. Um de 3 valores
 * GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON
 *
 * estado: Se o mouse foi clicado ou solto
 * GLUT_UP ou GLUT_DOWN
 *
 * x,y: posicao do mouse dentro da janela
 *----------------------------------------------------------
 */

void mouseCB(int botao, int estado, int x, int y)
{
    if (botao == GLUT_LEFT_BUTTON)
        glColor3ub((char)rand() % 256, (char)rand() % 256, (char)rand() % 256);
    glutPostRedisplay();
}

/*
 *----------------------------------------------------------
 * Rotina para tratamento de evento - Exibicao da janela
 *----------------------------------------------------------
 */

void exibeCB(void)
{
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_POLYGON);
    glVertex2i(200, 200);
    glVertex2i(200, 150);
    glVertex2i(150, 150);
    glVertex2i(150, 200);
    glEnd();
    glFlush();
}

/*
 *--------------------------------------------------
 * Rotina para tratamento de evento - Teclado
 *
 * tecla: Tecla pressionada pelo usuario
 * x - posicao x do mouse
 * y - posicao y do mouse
 *
 *--------------------------------------------------
 */

void tecladoCB(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'q': /* Encerra o programa */
    case 'Q':
        exit(0);

    default:
        printf("Opcao nao definida!\n");
    }
}

/*
 *--------------------------------------------------
 * Rotina para tratamento de evento
 * Alteracao de tamanho da janela
 * w - largura corrente da janela
 * h - altura corrente da janela
 *--------------------------------------------------
 */

void redesenhaCB(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (GLfloat)w, 0, (GLfloat)h, -1.0, 1.0);
}