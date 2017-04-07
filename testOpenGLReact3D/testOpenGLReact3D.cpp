// testOpenGLReact3D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL\freeglut.h>
#include "Game.h"
#include "Camera.h"

Game game;
Camera cam;

//MOUSE test 0.5
float mx, my; int mi;
//double eyex = 0, eyey = 0, eyez = 5;
//int rotator = 0; bool bckfor = true; int LPP = GLUT_UP;

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
			glColor3f(1 - 0.05*i, 0, 0.05*i);
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
	gluPerspective(90, aspect, 0.1, 30.0);

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
	case 'd':   cam.rotate(RIGHT,1);	break;
	case 'a':   cam.rotate(LEFT,1);	break;
	case 'q':   cam.rotate(UP,1);	    break;
	case 'e':   cam.rotate(DOWN,1);	break;
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
	Display();
}

// obs³uga ruchu kursora myszki

void MouseMotion(int x, int y)
{
	
	glutPostRedisplay();
}

void MousePassiveMotion(int x, int y)
{
	if (x > 600 || x < 200 || y > 450 || y < 150)
	{
		SetCursorPos(400, 300);
		mx = 400;
		my = 300;
		return;
	}

	if (mx - x < 0)
		cam.rotate(RIGHT, mx - x);
	if (mx - x > 0)
		cam.rotate(LEFT, mx -x);
	if (my - y > 0)
		cam.rotate(UP, my -y);
	if (my - y < 0)
		cam.rotate(DOWN, my -y);
	mx = x; my = y;


	Display();
}

void EntryFunc(int state)
{
	;
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
	glutEntryFunc(EntryFunc);

	glutPassiveMotionFunc(MousePassiveMotion);
	glutIdleFunc(Idle);

	glutMainLoop();
    return 0;
}