#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include <GL/glut.h>

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Alteracao 1 - cor do fundo amarelo
	// Limpa a janela de visualização com a cor amarela
	glClearColor(1, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Alteracao 2 - gradiente de cor
	// Desenha um triângulo no centro da janela
	glColor3f(0, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.0, -0.5, 0);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5, 0.5, 0);
	glVertex3f(0.0, -0.5, 0);
	glEnd();

	// Alteracao 4 - desenhar um quadrado
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(0.0, -0.5, 0);
	glVertex3f(0.0, 0.5, 0);
	glVertex3f(1.0, 0.5, 0);
	glVertex3f(1.0, -0.5, 0);
	glEnd();

	glFlush(); // Executa os comandos OpenGL
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);						 // Programa Principal
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Define do modo de operação da GLUT
	glutInitWindowSize(400, 400);				 // tamanho em pixels da janela
	
	// Alteracao 3 - Titulo da Janela
	glutCreateWindow("Pratica Computacao Grafica"); // Cria a janela

	glutDisplayFunc(Desenha);  // Registra função de redesenho
	glutKeyboardFunc(Teclado); // Registra função de teclado
	Inicializa();			   // Chama a função de inicializações

	// Alteracao 5 - transformacoes geometricas
	glTranslatef(0, -0.5, 0);
	glScalef(0.5, 0.5, 0);

	glutMainLoop();			   // Inicia o processamento e aguarda interações do usuário

	return 0;
}