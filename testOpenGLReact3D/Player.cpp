#include "stdafx.h"
#include "Player.h"
#include <GL\freeglut.h>

Player::Player(rp3d::DynamicsWorld *world, rp3d::Vector3 initPosition, rp3d::Quaternion initOrientation, rp3d::Vector3 shapeData)
{
	//rp3d::Vector3 initPosition(0.0, -1.0, 0.0);
	//initOrientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(initPosition, initOrientation);
	body = world->createRigidBody(transform);

	//const rp3d::Vector3 shapeData(x, y, z);
	shape = new rp3d::BoxShape(shapeData, 0.1);

	rp3d::Transform transform2 = rp3d::Transform::identity();
	rp3d::decimal mass = rp3d::decimal(4.0);
	proxyShape = body->addCollisionShape(shape, transform2, mass);
}


Player::~Player()
{
}

//void Player::move(Direction dir)
//{
//	float dz = 0;
//	float dx = 0;
//
//	float speed = 0.1;
//	switch (dir)
//	{
//	case UP:
//		y += speed;
//		break;
//	case DOWN:
//		y -= speed;
//		break;
//	case RIGHT:
//		dx = speed;
//		break;
//	case LEFT:
//		dx = -speed;
//		break;
//	case FORWARD:
//		dz = speed;
//		break;
//	case BACK:
//		dz = -speed;
//		break;
//	}
//
//	float proportion = 1 / sqrt(pow(lx, 2) + pow(lz, 2));
//
//	//przod i tyl
//	z += lz*dz*proportion;
//	x += lx*dz*proportion;
//
//	//lewo i prawo
//	float beta = atan2(lz, lx);
//	z += cos(-beta) * dx;
//	x += sin(-beta) * dx;
//}
//
//void Player::rotate(Direction dir, int angle)
//{
//	angle = abs(angle);
//	switch (dir)
//	{
//	case UP:
//		if (ly < 0.999)
//			angle_v = 0.01 * angle;
//		else
//			angle_v = 0;
//		break;
//	case DOWN:
//		if (ly > -0.999)
//			angle_v = -0.01 * angle;
//		else
//			angle_v = 0;
//		break;
//	case RIGHT:
//		angle_h = 0.01 * angle;
//		break;
//	case LEFT:
//		angle_h = -0.01 * angle;
//		break;
//	case FORWARD:
//		break;
//	case BACK:
//		break;
//	}
//
//	float dl = sqrt(pow(lx, 2) + pow(lz, 2));
//	float alfa = atan2(ly, dl);
//	ly = sin(alfa + angle_v);
//	dl = cos(alfa + angle_v);
//
//
//	//lz = cos(alfa + angle_v);
//
//	float beta = atan2(lz, lx);
//	lx = cos(beta + angle_h)*dl;
//	lz = sin(beta + angle_h)*dl;
//	angle_h = 0;
//	angle_v = 0;
//}
//
//void Player::set()
//{
//	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0, 1, 0);
//}