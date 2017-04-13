﻿// testOpenGLReact3D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL\freeglut.h>
#include "Game.h"
#include "Camera.h"
#include "Player.h"

Game game;
Camera cam;
Player *player;

//MOUSE
int mx, my;
//Keyboard
bool keystate[256];

void Display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	//cam.set();
	player->cam.set();
	float matrix[16];
	
	
	//FLOOR
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

	//OBJ
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

	////PLAYER
	glPushMatrix();
		player->Draw(matrix);
		glMultMatrixf(matrix);
		glScalef(0.5, 1, 0.5);
		glColor3f(0, 0, 0.5);
		//glutSolidCube(1);
		glColor3f(1, 1, 1);
		glutWireCube(1);
	glPopMatrix();

	for (int i = 0; i < game.quantity; i++)
	{
		glPushMatrix();
			matrix[16];
			game.objs[i].Draw(matrix);
			glMultMatrixf(matrix);
			glColor3f(0, 0.05*i, 0.05*i);
			glutSolidCube(1);
			glColor3f(0, 0, 0);
			glutWireCube(1);
		glPopMatrix();
	}




	glFlush();			// skierowanie poleceń do wykonania
	glutSwapBuffers();	// zamiana buforów koloru

	//game.Update();
}

void Reshape(int width, int height)
{
	// obszar renderingu - całe okno
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// obliczenie aspektu obrazu z uwzględnieniem
	// przypadku, gdy wysokość obrazu wynosi 0
	GLdouble aspect = 1;
	if (height > 0)
		aspect = width / (GLdouble)height;

	// rzutowanie perspektywiczne
	gluPerspective(90, aspect, 0.1, 30.0);

	Display();
}

void OnTimer(int id)
{
	glutTimerFunc(17, OnTimer, 0);

	if (keystate['w'])
		cam.move(FORWARD);
	if (keystate['s'])
		cam.move(BACK);
	if (keystate['d'])
		cam.move(RIGHT);
	if (keystate['a'])
		cam.move(LEFT);

	if (keystate['u'])
		player->cam.rotate(UP, 2.5);
		//player->rotate2(LEFT, 0.04);
	if (keystate['o'])
		player->cam.rotate(DOWN, 2.5);
		//player->rotate2(RIGHT, 0.04);
	if (keystate['i'])
		player->set_control(0);
		//player->move(FORWARD);
	if (keystate['k'])
		player->set_control(1);
		//player->move(BACK);
	if (keystate['j'])
		player->set_control(2);
		//player->move(LEFT);
	if (keystate['l'])
		player->set_control(3);
		//player->move(RIGHT);

	if (keystate[' '])
		player->set_control(4);
		//player->jump();
}

void OnKeyDown(unsigned char key, int x, int y)
{
	if (key == 27) 
	{ // ESC - wyjście
		glutLeaveMainLoop();
	}
	if (key == 'x')
		game.plus();
}

void OnKeyPress(unsigned char key, int x, int y) {
	printf("KeyPress: %c\n", key);
	if (!keystate[key]) {
		OnKeyDown(key, x, y); // Emulacja zdarzenia związanego z pojedynczym wciśnięciem klawisza
	}
	keystate[key] = true;
}


// Obsługa zdarzenia puszczenia klawisza.
void OnKeyUp(unsigned char key, int x, int y) 
{
	if (key == 'i')
		player->unset_control(0);
		//player->stop();
	if (key == 'k')
		player->unset_control(1);
		//player->stop();
	if (key == 'j')
		player->unset_control(2);
		//player->stop();
	if (key == 'l')
		player->unset_control(3);
		//player->stop();
	if (key == ' ')
		player->unset_control(4);
		//player->stop();

	keystate[key] = false;
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);

	//case 'w':   cam.move(FORWARD);	break;
	//case 's':   cam.move(BACK);		break;
	//case 'd':   cam.move(RIGHT);	break;
	//case 'a':   cam.move(LEFT);	break;
	//case 'q':   cam.rotate(UP,1);	    break;
	//case 'e':   cam.rotate(DOWN,1);	break;
	//case 'z':	game.Update();		break;
	//case 'x':	game.plus();		break;
	}


	//Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
	Display();
}


void Idle()
{
	game.Update();
	player->update();
	glutPostRedisplay();
}

void MouseButton(int button, int state, int x, int y)
{
	Display();
}

// obsługa ruchu kursora myszki
void MousePassiveMotion(int x, int y)
{
	if (x > 600 || x < 200 || y > 450 || y < 150)
	{
		glutWarpPointer(400, 300);
		mx = 400;
		my = 300;
		return;
	}

	if (mx - x < 0)
		player->rotate2(RIGHT, (float)(mx - x)/-100);
	if (mx - x > 0)
		player->rotate2(LEFT, (float)(mx - x) / 100);
	if (my - y > 0)
		player->cam.rotate(UP, my - y);
		//player->rotate2(UP, (float)(mx - x) / 100);
	if (my - y < 0)
		player->cam.rotate(DOWN, my - y);
	//player->rotate2(DOWN, (float)(mx - x) / 100);
	mx = x; my = y;

	//Display();
}

void MouseMotion(int x, int y)
{
	MousePassiveMotion(x, y);
	glutPostRedisplay();
}

void EntryFunc(int state)
{
	;
}

int main(int argc, char * argv[])
{
	//PLAYER
	rp3d::Vector3 initPosition(1.0, 2.0, 2.0);
	rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
	rp3d::Vector3 shapeData(0.25, 0.5, 0.25);

	player = new Player(game.World, initPosition, initOrientation, shapeData);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(5, 5);
	glutCreateWindow("LOL");
	glutSetCursor(GLUT_CURSOR_NONE);

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
//KEYBOARD
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
//MOUSE
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutEntryFunc(EntryFunc);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
//TIMER
	glutTimerFunc(17, OnTimer, 0);

	glutIdleFunc(Idle);

	glutMainLoop();
    return 0;
}