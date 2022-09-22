#include <stdlib.h>
#include <GL/glut.h>

struct Point
{
    GLfloat x;
    GLfloat y;
};

struct Object
{
    GLfloat cor[3];
    GLfloat width;
    GLfloat height;
    GLfloat x, y;
};

struct Foguete
{
    Object bico;
    Object corpo;
    Object asaEsq;
    Object asaDir;
};

// Variaveis globais
int hp, qntObstaculos;
Point moveFoguete;
Foguete foguete, fogueteVidas;
Object obstaculos[10];

// Prototipos das funcoes
void Bico(Object obj);
void Corpo(Object obj);
void AsaEsquerda(Object obj);
void AsaDireita(Object obj);
void DesenhaFoguete(Foguete foguete);
void DesenhaQuadro();
void DesenhaObstaculo(Object obj);
void Desenha();
void VerificaColisao(Object obs);
void Teclado(unsigned char key, int x, int y);
void Movimentacao(int key, int x, int y);
Object InicializaObjeto(
    GLfloat x, GLfloat y, GLfloat h, GLfloat w,
    GLfloat r = 1, GLfloat g = 1, GLfloat b = 0);
void Inicializa(void);

// Desenha o bico do foguete
void Bico(Object obj)
{
    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);
    glVertex2f(obj.x, obj.y);
    glVertex2f(obj.x + obj.width, obj.y);
    glVertex2f(obj.x + obj.width / 2, obj.y + obj.height);
    glEnd();
}

// Desenha o corpo do foguete
void Corpo(Object obj)
{
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex2f(obj.x, obj.y);
    glVertex2f(obj.x + obj.width, obj.y);
    glVertex2f(obj.x + obj.width, obj.y + obj.height);
    glVertex2f(obj.x, obj.y + obj.height);
    glEnd();
}

// Desenha a asa esquerda do foguete
void AsaEsquerda(Object obj)
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(obj.x, obj.y);
    glVertex2f(obj.x + obj.width, obj.y);
    glVertex2f(obj.x + obj.width, obj.y + obj.height);
    glEnd();
}

// Desenha a asa direita do foguete
void AsaDireita(Object obj)
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(obj.x, obj.y);
    glVertex2f(obj.x + obj.width, obj.y);
    glVertex2f(obj.x, obj.y + obj.height);
    glEnd();
}

// Funcao para desenhar um foguete
void DesenhaFoguete(Foguete foguete)
{
    Bico(foguete.bico);
    Corpo(foguete.corpo);
    AsaEsquerda(foguete.asaEsq);
    AsaDireita(foguete.asaDir);
}

// Desenha o quadro correspondente a area onde o foguete pode se movimentar
void DesenhaQuadro()
{
    glLineWidth(7.0);
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 1, 1);
    glVertex2f(-95, -95);
    glVertex2f(95, -95);
    glVertex2f(95, 78);
    glVertex2f(-95, 78);
    glEnd();
}

// Desenha um obstaculo (quadrado) na tela
void DesenhaObstaculo(Object obj)
{
    // Desenha o obstaculo
    glBegin(GL_QUADS);
    glColor3f(obj.cor[0], obj.cor[1], obj.cor[2]);
    glVertex2f(obj.x, obj.y);
    glVertex2f(obj.x + obj.width, obj.y);
    glVertex2f(obj.x + obj.width, obj.y + obj.height);
    glVertex2f(obj.x, obj.y + obj.height);
    glEnd();

    // Desenha a linha da borda do obstaculo
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0, 0);
    glVertex2f(obj.x, obj.y);
    glVertex2f(obj.x + obj.width, obj.y);
    glVertex2f(obj.x + obj.width, obj.y + obj.height);
    glVertex2f(obj.x, obj.y + obj.height);
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
    glPushMatrix();
    glTranslatef(moveFoguete.x, moveFoguete.y, 0);
    DesenhaFoguete(foguete);
    glPopMatrix();

    // Desenha os foguetes das vidas
    glPushMatrix();
    for (int i = 0; i < hp; i++)
    {
        glTranslatef(-13, 0, 0);
        DesenhaFoguete(fogueteVidas);
    }
    glPopMatrix();

    // Desenha os obstaculos
    for (int i = 0; i < qntObstaculos; i++)
        DesenhaObstaculo(obstaculos[i]);

    glFlush();
}

// Funcao para verificar a colisao entre o foguete e um obstaculo
void VerificaColisao(Object obs)
{
    Object f;
    Point p;

    // Verifica colisao com o corpo do foguete
    f = foguete.corpo;
    p.x = f.x + moveFoguete.x;
    p.y = f.y + moveFoguete.y;

    if (((p.x <= obs.x + obs.width && p.x >= obs.x) ||
         (p.x + f.width <= obs.x + obs.width && p.x + f.width >= obs.x)) &&
        ((p.y <= obs.y + obs.height && p.y >= obs.y) ||
         (p.y + f.height <= obs.y + obs.height && p.y + f.height >= obs.y)))
    {
        // Volta para o ponto inicial
        moveFoguete.x = 0;
        moveFoguete.y = 0;

        // E perde uma vida
        if (hp > 0)
            hp--;

        glutPostRedisplay();
    }
}

// Funcao callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y)
{
    // Tecla 'ESC' para encerrar o programa
    if (key == 27)
        exit(0);
}

// Funcao callback chamada para movimentar o foguete
void Movimentacao(int key, int x, int y)
{
    if (key == GLUT_KEY_UP && moveFoguete.y < 150)
        moveFoguete.y += 5;

    if (key == GLUT_KEY_DOWN && moveFoguete.y > 0)
        moveFoguete.y -= 5;

    if (key == GLUT_KEY_LEFT && moveFoguete.x > -90)
        moveFoguete.x -= 5;

    if (key == GLUT_KEY_RIGHT && moveFoguete.x < 85)
        moveFoguete.x += 5;

    // Verifica a colisao do foguete com todos os obstaculos
    for (int i = 0; i < qntObstaculos; i++)
        VerificaColisao(obstaculos[i]);

    glutPostRedisplay();
}

// Funcao responsavel por definir os objetos
Object InicializaObjeto(
    GLfloat x, GLfloat y, GLfloat h, GLfloat w,
    GLfloat r, GLfloat g, GLfloat b)
{
    Object obj;

    // Posicao de referencia
    obj.x = x;
    obj.y = y;

    // Dimensoes
    obj.height = h;
    obj.width = w;

    // Cor
    obj.cor[0] = r;
    obj.cor[1] = g;
    obj.cor[2] = b;

    return obj;
}

// Funcao responsavel por inicializar parametros e variaveis
void Inicializa(void)
{
    // Quantidade de vidas/tentativas do jogador
    hp = 3;

    // Valor da translacao inicial do foguete
    moveFoguete.x = 0;
    moveFoguete.y = 0;

    // Dimensoes do foguete principal
    foguete.bico = InicializaObjeto(0, -80, 3.99, 3.99);
    foguete.corpo = InicializaObjeto(0, -90, 9.99, 3.99);
    foguete.asaEsq = InicializaObjeto(-3, -90, 3.99, 2.99);
    foguete.asaDir = InicializaObjeto(4, -90, 3.99, 2.99);

    // Dimensoes do foguete das vidas
    fogueteVidas.bico = InicializaObjeto(103, 93, 4, 4);
    fogueteVidas.corpo = InicializaObjeto(103, 83, 10, 4);
    fogueteVidas.asaEsq = InicializaObjeto(100, 83, 4, 3);
    fogueteVidas.asaDir = InicializaObjeto(107, 83, 4, 3);

    // Dimensoes dos obstaculos
    obstaculos[0] = InicializaObjeto(10, 10, 10, 10);
    obstaculos[1] = InicializaObjeto(30, 40, 10, 10);
    obstaculos[2] = InicializaObjeto(-50, -10, 10, 10);
    obstaculos[3] = InicializaObjeto(-20, 10, 10, 10);
    obstaculos[4] = InicializaObjeto(-10, -60, 10, 30);
    obstaculos[5] = InicializaObjeto(-40, -70, 40, 10);

    qntObstaculos = 6;

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
