#include <stdlib.h>
#include <GL/glut.h>

struct Ponto
{
    GLfloat x;
    GLfloat y;
};

struct Objeto
{
    GLfloat cor[3];
    GLfloat largura;
    GLfloat altura;
    Ponto posicao;
};

struct Foguete
{
    Objeto bico;
    Objeto corpo;
    Objeto asaEsq;
    Objeto asaDir;
};

// Variaveis globais
int vidas, qntObstaculos;
bool houveColisao, venceu;
Ponto moveFoguete;
Foguete foguete, fogueteVidas;
Objeto obstaculos[10];

// Prototipos das funcoes
void Bico(Objeto obj);
void Corpo(Objeto obj);
void AsaEsquerda(Objeto obj);
void AsaDireita(Objeto obj);
void DesenhaFoguete(Foguete foguete);
void DesenhaQuadro();
void DesenhaObstaculo(Objeto obj);
void Desenha();
void VerificaColisao(Objeto obs);
void Teclado(unsigned char key, int x, int y);
void Movimentacao(int key, int x, int y);
Objeto InicializaObjeto(
    GLfloat x, GLfloat y, GLfloat h, GLfloat w,
    GLfloat r = 1, GLfloat g = 1, GLfloat b = 0);
void Inicializa(void);

// Desenha o bico do foguete
void Bico(Objeto obj)
{
    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);
    glVertex2f(obj.posicao.x, obj.posicao.y);
    glVertex2f(obj.posicao.x + obj.largura, obj.posicao.y);
    glVertex2f(obj.posicao.x + obj.largura / 2, obj.posicao.y + obj.altura);
    glEnd();
}

// Desenha o corpo do foguete
void Corpo(Objeto obj)
{
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex2f(obj.posicao.x, obj.posicao.y);
    glVertex2f(obj.posicao.x + obj.largura, obj.posicao.y);
    glVertex2f(obj.posicao.x + obj.largura, obj.posicao.y + obj.altura);
    glVertex2f(obj.posicao.x, obj.posicao.y + obj.altura);
    glEnd();
}

// Desenha a asa esquerda do foguete
void AsaEsquerda(Objeto obj)
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(obj.posicao.x, obj.posicao.y);
    glVertex2f(obj.posicao.x + obj.largura, obj.posicao.y);
    glVertex2f(obj.posicao.x + obj.largura, obj.posicao.y + obj.altura);
    glEnd();
}

// Desenha a asa direita do foguete
void AsaDireita(Objeto obj)
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(obj.posicao.x, obj.posicao.y);
    glVertex2f(obj.posicao.x + obj.largura, obj.posicao.y);
    glVertex2f(obj.posicao.x, obj.posicao.y + obj.altura);
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
void DesenhaObstaculo(Objeto obj)
{
    // Desenha o obstaculo
    glBegin(GL_QUADS);
    glColor3f(obj.cor[0], obj.cor[1], obj.cor[2]);
    glVertex2f(obj.posicao.x, obj.posicao.y);
    glVertex2f(obj.posicao.x + obj.largura, obj.posicao.y);
    glVertex2f(obj.posicao.x + obj.largura, obj.posicao.y + obj.altura);
    glVertex2f(obj.posicao.x, obj.posicao.y + obj.altura);
    glEnd();

    // Desenha a linha da borda do obstaculo
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0, 0);
    glVertex2f(obj.posicao.x, obj.posicao.y);
    glVertex2f(obj.posicao.x + obj.largura, obj.posicao.y);
    glVertex2f(obj.posicao.x + obj.largura, obj.posicao.y + obj.altura);
    glVertex2f(obj.posicao.x, obj.posicao.y + obj.altura);
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
    for (int i = 0; i < vidas; i++)
    {
        glTranslatef(-13, 0, 0);
        DesenhaFoguete(fogueteVidas);
    }
    glPopMatrix();

    // Desenha os obstaculos
    if (!venceu)
        for (int i = 0; i < qntObstaculos; i++)
            DesenhaObstaculo(obstaculos[i]);

    glFlush();
}

// Funcao para verificar a colisao entre uma parte do foguete e um obstaculo
void VerificaColisao(Objeto fog, Objeto obs)
{
    // Define as coordenadas da parte do foguete
    float coordFoguete[] = {
        fog.posicao.x + moveFoguete.x,
        fog.posicao.x + moveFoguete.x + fog.largura,
        fog.posicao.y + moveFoguete.y,
        fog.posicao.y + moveFoguete.y + fog.altura
    };

    // Define as coordenadas do obstaculo
    float coordObstaculo[] = {
        obs.posicao.x,
        obs.posicao.x + obs.largura,
        obs.posicao.y,
        obs.posicao.y + obs.altura
    };

    // Verifica se alguma das extremidades das partes do foguete colidem com o obstaculo
    if (((coordFoguete[0] >= coordObstaculo[0] && coordFoguete[0] <= coordObstaculo[1]) ||
         (coordFoguete[1] >= coordObstaculo[0] && coordFoguete[1] <= coordObstaculo[1])) &&
        ((coordFoguete[2] >= coordObstaculo[2] && coordFoguete[2] <= coordObstaculo[3]) ||
         (coordFoguete[3] >= coordObstaculo[2] && coordFoguete[3] <= coordObstaculo[3])))
    {
        // Volta o foguete para o ponto inicial
        moveFoguete.x = 0;
        moveFoguete.y = 0;

        // O jogador perde uma vida
        if (vidas > 0)
            vidas--;

        // Seta o verificador de colisao como true
        houveColisao = true;
    }
}

// Funcao callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    // Tecla 'ESC' para encerrar o programa
    case 27:
        exit(0);
        break;

    // Tecla 'R' para reiniciar o jogo
    case 'r':
    case 'R':
        // Restaura as vidas e o estado de venceu
        vidas = 3;
        venceu = false;

        // Volta para a posicao inicial
        moveFoguete.x = 0;
        moveFoguete.y = 0;

        // Faz o redesenho da tela
        glutPostRedisplay();
        break;
    }
}

// Funcao callback chamada para movimentar o foguete
void Movimentacao(int key, int x, int y)
{
    if (key == GLUT_KEY_UP && moveFoguete.y < 150 && vidas > 0)
        moveFoguete.y += 5;

    if (key == GLUT_KEY_DOWN && moveFoguete.y > 0 && vidas > 0)
        moveFoguete.y -= 5;

    if (key == GLUT_KEY_LEFT && moveFoguete.x > -90 && vidas > 0)
        moveFoguete.x -= 5;

    if (key == GLUT_KEY_RIGHT && moveFoguete.x < 85 && vidas > 0)
        moveFoguete.x += 5;

    // Verifica se o foguete chegou na linha de chegada
    if (moveFoguete.y == 150)
        venceu = true;

    // Verifica a colisao do foguete com todos os obstaculos
    else if (venceu == false)
    {
        for (int i = 0; i < qntObstaculos; i++)
        {
            houveColisao = false;
            VerificaColisao(foguete.bico, obstaculos[i]);
            VerificaColisao(foguete.corpo, obstaculos[i]);
            VerificaColisao(foguete.asaEsq, obstaculos[i]);
            VerificaColisao(foguete.asaDir, obstaculos[i]);
            if (houveColisao)
                break;
        }
    }

    // Faz o redesenho da tela
    glutPostRedisplay();
}

// Funcao responsavel por definir os objetos
Objeto InicializaObjeto(
    GLfloat x, GLfloat y, GLfloat h, GLfloat w,
    GLfloat r, GLfloat g, GLfloat b)
{
    Objeto obj;

    // Posicao de referencia
    obj.posicao.x = x;
    obj.posicao.y = y;

    // Dimensoes
    obj.altura = h;
    obj.largura = w;

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
    vidas = 3;
    venceu = false;

    // Valor da translacao e rotacao iniciais do foguete
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

    // Posicao e dimensoes dos obstaculos
    obstaculos[0] = InicializaObjeto(-60, -40, 10, 40);
    obstaculos[1] = InicializaObjeto(-20, -40, 40, 10);
    obstaculos[2] = InicializaObjeto(20, -40, 10, 40);
    obstaculos[3] = InicializaObjeto(60, -40, 10, 32);

    obstaculos[4] = InicializaObjeto(-80, 0, 10, 40);
    obstaculos[5] = InicializaObjeto(-20, 0, 10, 40);
    obstaculos[6] = InicializaObjeto(20, 0, 40, 10);
    obstaculos[7] = InicializaObjeto(60, 0, 10, 32);

    obstaculos[8] = InicializaObjeto(-80, 40, 10, 40);
    obstaculos[9] = InicializaObjeto(-40, 40, 10, 40);
    obstaculos[10] = InicializaObjeto(20, 40, 10, 20);
    obstaculos[11] = InicializaObjeto(60, 40, 10, 32);

    obstaculos[12] = InicializaObjeto(-92, 40, 10, 20);

    qntObstaculos = 13;

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