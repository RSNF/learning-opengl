#include <stdlib.h>
#include <GL/glut.h>

// Funcaoo para desenhar um quadrado
void DesenhaQuadrado(float tx, float ty){
	
	glPushMatrix();
	glTranslatef(tx,ty,0);
	glRotatef(45, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(2, 2, 0);
	glVertex3f(-2, 2, 0);
	glVertex3f(-2, -2, 0);
	glVertex3f(2, -2, 0);
	glEnd();
	glPopMatrix();
}

// Desenho 1 - Quatro losangos
void DesenhaLosangos(){

	// Limpa a janela de visualizacaoo com a cor verde
	glClearColor(0, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 1, 0);
	DesenhaQuadrado(-4, 0);
	
	glColor3f(1, 0, 0);
	DesenhaQuadrado(4, 0);
	
	glColor3f(0, 0,	 1);
	DesenhaQuadrado(0, 4);
	
	glColor3f(0, 0, 0);
	DesenhaQuadrado(0, -4);
}

// Funcao para desenhar uma linha
void Linha(float x1, float y1, float x2, float y2)
{
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
}

// Desenho 2 - Um quadrado e uma cruz
void DesenhaQuadradoCruz()
{
    // Limpa a janela de visualizacaoo com a cor amarela
	glClearColor(1, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glLineWidth(10.0);
	glBegin(GL_LINES);

    // Quadrado central maior
    Linha(5, 5, -5, 5);
    Linha(-4.75, 5, -4.75, -5);
    Linha(-5, -5, 5, -5);
    Linha(4.75, -5, 4.75, 5);

    // Cruz
    Linha(0, 20, 0, -20);
    Linha(20, 0, -20, 0);
	glEnd();

    // Quadrado central menor
    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(-0.5, 0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.5, 0.5);
    glEnd();
}

void DesenhaTrivertentes()
{
    glLineWidth(5.0);
    glBegin(GL_LINE_LOOP);
	
	glColor3f(0, 1, 0);
    Linha(2, 0, 0, 6);

	glColor3f(1, 0, 0);
    Linha(-2, 0, -6, -5);

	glColor3f(0, 0, 1);
    Linha(0, -3.5, 6, -5);
    glEnd();
}

// Funcao callback de redesenho da janela de visualizacao
void Desenha(void)
{
	// Desenho 1 - Quatro losangos
	// DesenhaLosangos();

	// Desenho 2 - Um quadrado e uma cruz
	// DesenhaQuadradoCruz();

	// Desenho 3 - Tri-vertentes coloridos
    DesenhaTrivertentes();

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
	gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
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
