//*****************************************************
//
// Exemplo3DComTransformacoes.cpp
// Um programa OpenGL simples que abre uma janela GLUT,
// e usa as funcoes glPushMatrix() e glPopMatrix() para
// rotacionar, transladar e trocar a escala de tres
// "torus" para depois desenha-los.
//
// Marcelo Cohen e Isabel H. Manssour
// Este codigo acompanha o livro
// "OpenGL - Uma Abordagem Pratica e Objetiva"
//
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

GLfloat fAspect;

// Funcao callback de redesenho da janela de visualizacao
void Desenha(void)
{
	// Limpa a janela de visualizacao com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Guarda a matriz de transformacao corrente na pilha
	glPushMatrix();
	// Aplica uma translacao
	glTranslatef(-35.0f, 0.0f, 0.0f);
	// Aplica uma rotacao ao redor do eixo z
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	// Altera a cor do desenho para preto
	glColor3f(0.0f, 0.0f, 0.0f);
	// Funcao da GLUT para fazer o desenho de um "torus"
	glutWireTorus(7.0, 14.0, 20, 40);
	// Restaura a matriz de transformacao corrente da pilha
	glPopMatrix();

	// Guarda a matriz de transformacao corrente na pilha
	glPushMatrix();
	// Aplica uma rotacao ao redor do eixo x
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	// Aplica uma translacao
	glTranslatef(-35.0f, 0.0f, 0.0f);
	// Altera a cor do desenho para cinza escuro
	glColor3f(0.4f, 0.4f, 0.4f);
	// Funcao da GLUT para fazer o desenho de um "torus"
	glutWireTorus(7.0, 14.0, 20, 40);
	// Restaura a matriz de transformacao corrente da pilha
	glPopMatrix();

	// Guarda a matriz de transformacao corrente na pilha
	glPushMatrix();
	// Aplica uma translacao
	glTranslatef(35.0f, 0.0f, 0.0f);
	// Aplica uma rotacao ao redor do eixo x
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	// Altera a cor do desenho para cinza
	glColor3f(0.6f, 0.6f, 0.6f);
	// Funcao da GLUT para fazer o desenho de um "torus"
	glutWireTorus(7.0, 14.0, 20, 40);
	// Restaura a matriz de transformacao corrente da pilha
	glPopMatrix();

	// Executa os comandos OpenGL
	glFlush();
}

// Funcao usada para especificar o volume de visualizacao
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projecao
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projecao
	glLoadIdentity();

	// Especifica a projecao perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(45, fAspect, 0.5, 500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posicao do observador e do alvo
	gluLookAt(0, 60, 150, 0, 0, 0, 0, 1, 0);
}

// Funcao callback chamada quando o tamanho da janela eh alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisao por zero
	if (h == 0)
		h = 1;

	// Especifica as dimensoes da viewport
	glViewport(0, 0, w, h);

	// Calcula a correcao de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
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
	// Define a cor de fundo da janela de visualizacao como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Programa Principal
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	// Define do modo de operacao da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posicao inicial da janela GLUT
	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450, 450);

	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("Desenho de varios torus 3D");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(Desenha);

	// Registra a funcao callback de redimensionamento da janela de visualizacao
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a funcao callback para tratamento das teclas ASCII
	glutKeyboardFunc(Teclado);

	// Chama a funcao responsavel por fazer as inicializacoes
	Inicializa();

	// Inicia o processamento e aguarda interacoes do usuario
	glutMainLoop();

	return 0;
}
