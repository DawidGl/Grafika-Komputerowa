#include "stdafx.h"
#include <cmath>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Pocztkowy rozmiar i pozycja prostokta

GLfloat x_1 = 100.0f;
GLfloat y_1 = 100.0f;
GLsizei rsize = 50;

// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = -3.0f;
GLfloat ystep = 3.0f;

// Dane zmieniajcych się rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;

///////////////////////////////////////////////////////////
// Wywoływana w celu przerysowania sceny

void RenderScene(void) {

	// Wyczyszczenie okna aktualnym kolorem czyszczącym
	glClear(GL_COLOR_BUFFER_BIT);

	// Aktualny kolor rysujący - czerwony
	// R G B
	glColor3f(1.0f, 0.0f, 0.0f);
	// Narysowanie prostokąta wypełnionego aktualnym kolorem

	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(x_1, y_1);
	int dlBoku = 6;
	for (int i = 0; i <= 11; i++)
	{
		glVertex2f((x_1 + (dlBoku * cos(i * 2 * 3.14f / 11)) * 11), (y_1 + (dlBoku * sin(i * 2 * 3.14f / 11)) * 11));
	}
	glEnd();
	glFlush();

	// Wysłanie poleceń do wykonania - !!! dla animacji to jest inne polecenie

	glutSwapBuffers();

}

///////////////////////////////////////////////////////////

// Wywoływana przez bibliotek GLUT w czasie, gdy okno nie

// jest przesuwane ani nie jest zmieniana jego wielkość

void TimerFunction(int value) {

	// Odwrócenie kierunku, jeżeli osiągnięto lewą lub prawą krawędź
	if (x_1 > windowWidth - rsize || x_1 + (10.0 * cos(3 * 2 * 3.14f / 5)) * 5 < 0)
		xstep = -xstep;

	// Odwrócenie kierunku, jeżeli osiągnięto dolną lub górną krawędź

	if (y_1 > windowHeight - rsize || y_1 - rsize < 0)
		ystep = -ystep;

	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno
	// zmniejszyło swoj wielkość w czasie, gdy kwadrat odbijał się od
	// krawędzi, co mogłoby spowodować, że znalazł by się poza
	// przestrzenią ograniczajcą.

	if (x_1 > windowWidth - rsize)
		x_1 = windowWidth - rsize - 1;

	if (y_1 > windowHeight - rsize)
		y_1 = windowHeight - rsize - 1;

	// Wykonanie przesunięcia kwadratu

	x_1 += xstep;
	y_1 += ystep;
	// Ponowne rysowanie sceny z nowymi współrzędnymi

	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

///////////////////////////////////////////////////////////

// Konfigurowanie stanu renderowania

void SetupRC(void) {
	// Ustalenie niebieskiego koloru czyszczącego
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

///////////////////////////////////////////////////////////

// Wywoływana przez bibliotek GLUT przy każdej zmianie wielkości okna

void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero

	if (h == 0)
		h = 1;
	// Ustalenie wielkości widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie układu współrzędnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Keep the square square, this time, save calculated
	// width and height for later use

	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}
	// Ustanowienie przestrzeni ograniczającej (lewo, prawo, dół, góra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

///////////////////////////////////////////////////////////

// Główny punkt wejścia programu

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Bounce");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();

}