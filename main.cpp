#include <stdlib.h>
#include <GL/glut.h>

// Funcaoo para desenhar um quadrado
void DesenhaQuadrado(float tx, float ty){
	
	glPushMatrix();
	glTranslatef(tx,ty,0);
	glRotatef(45, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(-0.2, -0.2, 0);
	glVertex3f(-0.2, 0.2, 0);
	glVertex3f(0.2, 0.2, 0);
	glVertex3f(0.2, -0.2, 0);
	glEnd();
	glPopMatrix();
}

// Desenho 1 - Quatro losangos
void DesenhaLosangos(){
	glColor3f(0, 0, 1);
	DesenhaQuadrado(-0.4, 0);
	
	glColor3f(1, 0, 1);
	DesenhaQuadrado(0.4, 0);
	
	glColor3f(0, 1, 0);
	DesenhaQuadrado(0, 0.4);
	
	glColor3f(1, 0, 0);
	DesenhaQuadrado(0, -0.4);
}

// Desenho 2 - Um quadrado e uma cruz
void DesenhaQuadradoCruz(){
//	glPushMatrix();
//	glTranslatef(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, -0.3);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.3, 0.0);
	glVertex2f(0.3, -0.3);
	glEnd();
//	glPopMatrix();
}

// Funcao para desenhar uma linha
void Linha(float px, float py, float px2, float py2)
{
    glPushMatrix();
    glLineWidth(10.0);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(px, py);
    glVertex2f(px2, py2);
    glEnd();
    glPopMatrix();
}

// Desenho 2 - Um quadrado e uma cruz
void DesenhaQuadradoCruz()
{
    // Quadrado central maior
    // glPushMatrix();
    // glLineWidth(10.0);
    // glBegin(GL_LINE_LOOP);
    // glColor3f(1, 0, 0);
    // glVertex2f(0.5, 0.5);
    // glVertex2f(-0.5, 0.5);
    // glVertex2f(-0.5, -0.5);
    // glVertex2f(0.5, -0.5);
    // glEnd();
    // glPopMatrix();

    // Simulação do quadrado central maior com linhas
    // Linha horizontal superior
    Linha(0.5, 0.5, -0.5, 0.5);
    // Linha vertical esquerda
    Linha(-0.476, 0.5, -0.476, -0.5);
    // Linha horizontal inferior
    Linha(-0.5, -0.5, 0.5, -0.5);
    // Linha vertical direita
    Linha(0.476, -0.5, 0.476, 0.5);

    // Linha horizontal
    Linha(0, 1, 0, -1);
    // Linha vertical
    Linha(1, 0, -1, 0);

    // Quadrado central menor
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    glVertex2f(-0.06, 0.06);
    glVertex2f(-0.06, -0.06);
    glVertex2f(0.06, -0.06);
    glVertex2f(0.06, 0.06);
    glEnd();
    glPopMatrix();
}

void Vertente(char cor, float px, float py, float px2, float py2)
{
    if (cor == 'r'){
        glColor3f(1, 0, 0);
    }else if (cor == 'g'){
        glColor3f(0, 1, 0);
    }else if (cor == 'b'){
        glColor3f(0, 0, 1);
    }
    
    glVertex2f(px, py);
    glVertex2f(px2, py2);
}

void Trivertentes()
{
    glLineWidth(5.0);
    glBegin(GL_LINE_LOOP);
    Vertente('g', 0.2, 0, 0, 0.5);
    Vertente('r', -0.2, 0, -0.6, -0.5);
    Vertente('b', 0, -0.3, 0.6, -0.5);
    glEnd();
}

// Funcao callback de redesenho da janela de visualizacao
void Desenha(void)
{
	// Limpa a janela de visualizacaoo com a cor amarela
	glClearColor(1, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenho 1 - Quatro losangos
	DesenhaLosangos();

    // Desenho 2 - Um quadrado e uma cruz
    // DesenhaQuadradoCruz();

    // Desenho 3 - Tri-vertentes coloridos
    Trivertentes();

	glFlush(); // Executa os comandos OpenGL
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
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);						 // Programa Principal
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Define do modo de operacao da GLUT
	glutInitWindowSize(400, 400);				 // tamanho em pixels da janela

	glutCreateWindow("Pratica Computacao Grafica"); // Cria a janela

	glutDisplayFunc(Desenha);  // Registra funcao de redesenho
	glutKeyboardFunc(Teclado); // Registra funcao de teclado
	Inicializa();			   // Chama a funcao de inicializacoes

	glutMainLoop();			   // Inicia o processamento e aguarda interacoes do usuario

	return 0;
}
