#include <stdlib.h>
#include <GL/glut.h>

void Desenha(void) // Função callback de redesenho da janela de visualização
{
// Limpa a janela de visualização com a cor branca
glClearColor(1,1,1,0); glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1,0,0); // Define a cor de desenho: vermelho
// Desenha um triângulo no centro da janela

glBegin(GL_TRIANGLES);
glVertex3f(-0.5,-0.5,0);
glVertex3f( 0.0, 0.5,0);
glVertex3f( 0.5,-0.5,0);
glEnd();
               
glFlush(); //Executa os comandos OpenGL
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y) {
if (key == 27)
exit(0);
}
// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void) {
// Define a janela de visualização 2D
glMatrixMode(GL_PROJECTION);
gluOrtho2D(-1.0,1.0,-1.0,1.0);
glMatrixMode(GL_MODELVIEW);
}

int main (int argc, char **argv){
	
	glutInit(&argc, argv);// Programa Principal
// Define do modo de operação da GLUT
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(400,400); // tamanho em pixels da janela
// Cria a janela passando como argumento o título da mesma
glutCreateWindow("Primeiro Programa");
glutDisplayFunc(Desenha); // Registra função de redesenho
glutKeyboardFunc (Teclado); // Registra função de teclado
Inicializa(); // Chama a função de inicializações
// Inicia o processamento e aguarda interações do usuário
glutMainLoop();
return 0;
}