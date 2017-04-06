// testOpenGLReact3D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL\freeglut.h>
#include "Game.h"
#include "Camera.h"

Game game;
Camera cam;

double eyex = 0, eyey = 0, eyez = 5;
int rotator = 0; bool bckfor = true; int LPP = GLUT_UP;

void Display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	//gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);
	cam.set();
	float matrix[16];
	
	

	glPushMatrix();
		matrix[16];
		game.Draw_floor(matrix);
		glMultMatrixf(matrix);
		glScalef(20, 1, 20);
		glColor3f(0.5, 0, 0);
		glutSolidCube(1);
		glColor3f(0, 0, 0);
		glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
		matrix[16];
		game.Draw_1(matrix);
		glMultMatrixf(matrix);
		//glScalef(20, 1, 20);
		glColor3f(0, 0, 0.5);
		glutSolidCube(1);
		glColor3f(0, 0, 0);
		glutWireCube(1);
	glPopMatrix();

	for (int i = 0; i < game.quantity; i++)
	{
		glPushMatrix();
			matrix[16];
			game.objs[i].Draw(matrix);
			glMultMatrixf(matrix);
			glColor3f(1 - 0.02*i, 0, 0.02*i);
			glutSolidCube(1);
			glColor3f(0, 0, 0);
			glutWireCube(1);
		glPopMatrix();
	}




	glFlush();			// skierowanie poleceñ do wykonania
	glutSwapBuffers();	// zamiana buforów koloru

	//game.Update();
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

	case 'w':   cam.move(FORWARD);	break;
	case 's':   cam.move(BACK);		break;
	case 'd':   cam.rotate(RIGHT);	break;
	case 'a':   cam.rotate(LEFT);	break;
	case 'q':   cam.rotate(UP);	    break;
	case 'e':   cam.rotate(DOWN);	break;
	case 'z':	game.Update();		break;
	case 'x':	game.plus();		break;
	}


	//Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
	Display();
}


void Idle()
{
	game.Update();
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
	int j = x;
	glutPostRedisplay();
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(5, 5);
	glutCreateWindow("Kwadrat 1");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(Idle);

	glutMainLoop();
    return 0;
}