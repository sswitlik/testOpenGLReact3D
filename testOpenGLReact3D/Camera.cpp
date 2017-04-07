#include "stdafx.h"
#include "Camera.h"
#include <cmath>
#include <GL\freeglut.h>
#define PI180 0.01745329

Camera::Camera()
{
	x = 0;
	y = 0;
	z = 5.0;

	lx = 0;
	ly = 0;
	lz = -1;

	angle_h = 0;
	angle_v = 0;

	orient.setAllValues(lx, ly, lz, 1);
}


Camera::~Camera()
{
}

void Camera::move(Direction dir)
{
	float d = 0;
	switch (dir)
	{
	case UP:
		y += 0.2;
		break;
	case DOWN:
		y -= 0.2;
		break;
	case RIGHT:
		x += 0.2;
		break;
	case LEFT:
		x -= 0.2;
		break;
	case FORWARD:
		d = 0.2;
		break;
	case BACK:
		d = -0.2;
		break;
	}

	z += lz*d;
	x += lx*d;
}

void Camera::rotate(Direction dir, int angle)
{
	angle = abs(angle);
	switch (dir)
	{
	case UP:
		angle_v = 0.01 * angle;
		break;
	case DOWN:
		angle_v = -0.01 * angle;
		break;
	case RIGHT:
		angle_h = 0.01 * angle;
		break;
	case LEFT:
		angle_h = -0.01 * angle;
		break;
	case FORWARD:
		break;
	case BACK:
		break;
	}

	float dl = sqrt(pow(lx, 2) + pow(lz, 2));
	float alfa = atan2(ly, dl);
	ly = sin(alfa + angle_v);
	dl = cos(alfa + angle_v);


	//lz = cos(alfa + angle_v);

	float beta = atan2(lz, lx);
	lx = cos(beta + angle_h)*dl;
	lz = sin(beta + angle_h)*dl;
	angle_h = 0;
	angle_v = 0;
}

void Camera::set()
{
	gluLookAt(x, y, z, x+lx, y+ly, z+lz, 0, 1, 0);
}