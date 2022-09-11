#include <stdlib.h>
#include <GL/glut.h>

// Desenha o bico do foguete
void Bico()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);
    glVertex3f(3.0, 6.0, 0);
    glVertex3f(4.0, 8.0, 0);
    glVertex3f(5.0, 6.0, 0);
    glEnd();
}

// Desenha o corpo do foguete
void Corpo()
{
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex3f(3.0, 1.0, 0);
    glVertex3f(5.0, 1.0, 0);
    glVertex3f(5.0, 6.0, 0);
    glVertex3f(3.0, 6.0, 0);
    glEnd();
}

// Desenha a asa esquerda do foguete
void AsaEsquerda()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(1.5, 1.0, 0);
    glVertex3f(3.0, 1.0, 0);
    glVertex3f(3.0, 3.0, 0);
    glEnd();
}

// Desenha a asa direita do foguete
void AsaDireita()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(5.0, 1.0, 0);
    glVertex3f(6.5, 1.0, 0);
    glVertex3f(5.0, 3.0, 0);
    glEnd();
}

// Funcao callback de redesenho da janela de visualizacao
void DesenhaFoguete(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-4.0, -4.0, 0);
    glScalef(1.0, 1.0, 0);
    glRotatef(20, 0.0f, 0.0f, 1.0f);
    Bico();
    Corpo();
    AsaEsquerda();
    AsaDireita();
    glPopMatrix();
    glFlush();
}

// Funcao callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

// Funcao responsavel por inicializar parametros e variaveis
void Inicializa(void)
{
    // Define a janela de visualizacao 2D
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // 20x20
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                       // Programa Principal
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Define do modo de operacao da GLUT
    glutInitWindowSize(400, 400);                // tamanho em pixels da janela

    glutCreateWindow("Foguete"); // Cria a janela

    glutDisplayFunc(DesenhaFoguete); // Registra funcao de redesenho
    glutKeyboardFunc(Teclado);       // Registra funcao de teclado
    Inicializa();                    // Chama a funcao de inicializacoes

    glutMainLoop(); // Inicia o processamento e aguarda interacoes do usuario

    return 0;
}
