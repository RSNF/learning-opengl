//*****************************************************
//
// Casa.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e desenha uma casa.
//
// Marcelo Cohen e Isabel H. Manssour
// Este codigo acompanha o livro 
// "OpenGL - Uma Abordagem Pratica e Objetiva"
// 
//*****************************************************

#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>

// Funcao callback de redesenho da janela de visualizacao
void Desenha(void)
{
	// Limpa a janela de visualizacao com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha uma casinha composta de um quadrado e um triangulo

	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);     
	// Desenha a casa
	glBegin(GL_QUADS);
		glVertex2f(-15.0f,-15.0f);
		glVertex2f(-15.0f,  5.0f);       
		glVertex2f( 15.0f,  5.0f);       
		glVertex2f( 15.0f,-15.0f);
	glEnd();

	// Altera a cor do desenho para branco
	glColor3f(1.0f, 1.0f, 1.0f);  
	// Desenha a porta e a janela  
	glBegin(GL_QUADS);
		glVertex2f(-4.0f,-14.5f);
		glVertex2f(-4.0f,  0.0f);       
		glVertex2f( 4.0f,  0.0f);       
		glVertex2f( 4.0f,-14.5f);       
		glVertex2f( 7.0f,-5.0f);
		glVertex2f( 7.0f,-1.0f);       
		glVertex2f(13.0f,-1.0f);       
		glVertex2f(13.0f,-5.0f);             
	glEnd();

	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);     
	// Desenha as "linhas" da janela  
	glBegin(GL_LINES);      
		glVertex2f( 7.0f,-3.0f);      
		glVertex2f(13.0f,-3.0f);       
		glVertex2f(10.0f,-1.0f);    
		glVertex2f(10.0f,-5.0f);             
	glEnd();    

	// Altera a cor do desenho para vermelho
	glColor3f(1.0f, 0.0f, 0.0f); 
	// Desenha o telhado
	glBegin(GL_TRIANGLES);
		glVertex2f(-15.0f, 5.0f);   
		glVertex2f(  0.0f,17.0f);    
		glVertex2f( 15.0f, 5.0f);       
	glEnd();
 
	// Executa os comandos OpenGL 
	glFlush();
}

// Funcao callback chamada quando o tamanho da janela eh alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variaveis
	largura = w;
	altura = h;

	// Especifica as dimensoes da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de selecao (esquerda, direita, inferior, 
	// superior) mantendo a proporcao com a janela de visualizacao
	if (largura <= altura) 
		gluOrtho2D (-40.0f, 40.0f, -40.0f*altura/largura, 40.0f*altura/largura);
	else 
		gluOrtho2D (-40.0f*largura/altura, 40.0f*largura/altura, -40.0f, 40.0f);
}

// Funcao callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Funcao responsavel por inicializar parametros e variaveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualizacao como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Programa Principal 
int main(int argc, char *argv[])
{

	glutInit( & argc, argv ); // Adicionado.

	// Define do modo de operacao da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posicao inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("Desenho de uma casa");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(Desenha);

	// Registra a funcao callback de redimensionamento da janela de visualizacao
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a funcao callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);
    
	// Chama a funcao responsavel por fazer as inicializacoes 
	Inicializa();

	// Inicia o processamento e aguarda interacoes do usuario
	glutMainLoop();

	return 0;
}
