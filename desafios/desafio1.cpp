#include <stdlib.h>
#include <GL/glut.h>

GLint hp;
GLfloat xi, yi, xv, yv, xf, yf;

// Desenha o bico do foguete
void Bico(GLfloat x, GLfloat y)
{
    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);
    glVertex2f(x, y + 10);
    glVertex2f(x + 2, y + 14);
    glVertex2f(x + 4, y + 10);
    glEnd();
}

// Desenha o corpo do foguete
void Corpo(GLfloat x, GLfloat y)
{
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex2f(x, y);
    glVertex2f(x + 4, y);
    glVertex2f(x + 4, y + 10);
    glVertex2f(x, y + 10);
    glEnd();
}

// Desenha a asa esquerda do foguete
void AsaEsquerda(GLfloat x, GLfloat y)
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(x - 3, y);
    glVertex2f(x, y);
    glVertex2f(x, y + 4);
    glEnd();
}

// Desenha a asa direita do foguete
void AsaDireita(GLfloat x, GLfloat y)
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(x + 4, y);
    glVertex2f(x + 7, y);
    glVertex2f(x + 4, y + 4);
    glEnd();
}

// Funcao para desenhar um foguete
void DesenhaFoguete(GLfloat x, GLfloat y)
{
    glPushMatrix();
    // glTranslatef(-6.5, -8, 0);
    // glScalef(scale, scale, 0);
    Bico(x, y);
    Corpo(x, y);
    AsaEsquerda(x, y);
    AsaDireita(x, y);
    glPopMatrix();
    glFlush();
}

// Desenha o quadro onde o foguete pode se movimentar
void DesenhaQuadro(){
    glLineWidth(7.0);
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 1, 1);
    glVertex2f(-95, -95);
    glVertex2f(95, -95);
    glVertex2f(95, 78);
    glVertex2f(-95, 78);
    glEnd();
}

// Função callback de desenho principal
void Desenha()
{
    // Define a cor do fundo como preto
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o quadro onde o foguete pode se movimentar
    DesenhaQuadro();

    // Desenha o foguete do jogador
    DesenhaFoguete(xf, yf);

    // Desenha os foguetes das vidas
    DesenhaFoguete(xv, yv);
    DesenhaFoguete(xv - 13, yv);
    DesenhaFoguete(xv - 26, yv);
}

// Funcao callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

// Funcao callback chamada para movimentar o foguete
void Movimentacao(int key, int x, int y)
{
    if (key == GLUT_KEY_UP && yf < 60)
    {
        yf += 5;
    }
    if (key == GLUT_KEY_DOWN && yf > yi)
    {
        yf -= 5;
    }
    if (key == GLUT_KEY_LEFT && xf > -90)
    {
        xf -= 5;
    }
    if (key == GLUT_KEY_RIGHT && xf < 85)
    {
        xf += 5;
    }
    glutPostRedisplay();
}

// Funcao responsavel por inicializar parametros e variaveis
void Inicializa(void)
{
    // Quantidade de vidas/tentativas do jogador
    hp = 3;

    // Posicao inicial do foguete
    xi = 0;
    yi = -90;

    // Posicao atual do foguete
    xf = xi;
    yf = yi;

    // Posicao inicial do foguete das vidas
    xv = 90;
    yv = 83;

    // Define a janela de visualizacao 2D
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0); // 200x200
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                       // Programa Principal
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Define do modo de operacao da GLUT
    glutInitWindowSize(800, 600);                // tamanho em pixels da janela

    // Centraliza a janela do GLUT
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 800) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - 600) / 2);

    glutCreateWindow("Foguete"); // Cria a janela

    glutDisplayFunc(Desenha);      // Registra funcao de redesenho
    glutKeyboardFunc(Teclado);     // Registra funcao de teclado
    glutSpecialFunc(Movimentacao); // Registra funcao de movimento nas setas
    Inicializa();                  // Chama a funcao de inicializacoes

    glutMainLoop(); // Inicia o processamento e aguarda interacoes do usuario

    return 0;
}
