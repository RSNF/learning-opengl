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
