// testOpenGLReact3D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL\freeglut.h>
#include "Game.h"

Game game;


double eyex = 0, eyey = 0, eyez = 5;
int rotator = 0; bool bckfor = true; int LPP = GLUT_UP;

void Display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);

	float matrix[16];
	glPushMatrix();
		matrix[16];
		game.Draw_floor(matrix);
		glMultMatrixf(matrix);
		glScalef(20, 1, 20);
		glColor3f(0.5, 0, 0);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		matrix[16];
		game.Draw_floor(matrix);
		glMultMatrixf(matrix);
		//glScalef(20, 1, 20);
		glColor3f(0, 0, 0.5);
		glutSolidCube(1);
	glPopMatrix();

	glFlush();			// skierowanie poleceñ do wykonania
	glutSwapBuffers();	// zamiana buforów koloru
}

void Reshape(int width, int height)
{
	// obszar renderingu - ca³e okno
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// obliczenie aspektu obrazu z uwzglêdnieniem
	// przypadku, gdy wysokoœæ obrazu wynosi 0
	GLdouble aspect = 1;
	if (height > 0)
		aspect = width / (GLdouble)height;

	// rzutowanie perspektywiczne
	gluPerspective(90, aspect, 0.5, 30.0);

	Display();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);

	case 'w':   eyez -= 0.1;    break;
	case 's':   eyez += 0.1;    break;
	case 'd':   eyex += 0.1;    break;
	case 'a':   eyex -= 0.1;    break;
	case 'q':   eyey += 0.1;    break;
	case 'e':   eyey -= 0.1;    break;
	case 'z':	game.Update();
	}


	//Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
	Display();
}

static void Timer(int value) {
	
	glutPostRedisplay();
	// 100 milliseconds
	glutTimerFunc(100, Timer, 0);
}

void Idle()
{
	
	glutPostRedisplay();
}

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (LPP == GLUT_UP)
			LPP = GLUT_DOWN;
		else
			LPP = GLUT_UP;
	}

	Display();
}

// obs³uga ruchu kursora myszki

void MouseMotion(int x, int y)
{
	if (LPP == GLUT_DOWN)
	{
		
	}
	glutPostRedisplay();
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(5, 5);
	glutCreateWindow("Kwadrat 1");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	//glutIdleFunc(Idle);

	glutMainLoop();
    return 0;
}