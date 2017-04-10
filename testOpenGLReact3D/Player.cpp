#include "stdafx.h"
#include "Player.h"
#include <GL\freeglut.h>

#define RAD  0.01745329
#define PI_2 9.86960440108935


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

	//body->enableGravity(false);

	rp3d::Material& material = body->getMaterial();
	material.setBounciness(rp3d::decimal(0));
	material.setFrictionCoefficient(rp3d::decimal(1));

	cam.sync(initPosition, initOrientation);
	rot_angle = 0;
}


Player::~Player()
{
}

void QuaternionO2IToEulerAngles(float *Yaw, float *Pitch, float *Roll, const rp3d::Quaternion &q)
{
	float sp = -2.0f * (q.y*q.z - q.w*q.x);

	if (sp == 1.0f)
	{
		*Pitch = PI_2 * sp;
		*Yaw = atan2f(-q.x*q.z + q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		*Roll = 0.0f;
	}
	else
	{
		*Pitch = asinf(sp);
		*Yaw = atan2f(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		*Roll = atan2f(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
	}
}

void Player::unrotate()
{
	rp3d::Vector3 angv(0, 0, 0);
	body->setAngularVelocity(angv);
	
	rp3d::Transform trans = body->getTransform();
	rp3d::Quaternion orient = trans.getOrientation();

	float Yaw, Pitch, Roll;

	QuaternionO2IToEulerAngles(&Yaw, &Pitch, &Roll, orient);
	
	if (Pitch > 0.1 || Roll > 0.1)
	{
		rp3d::Quaternion o(Yaw, 0, 0);
		trans.setOrientation(o);
		body->setTransform(trans);
	}
}

void Player::move(Direction dir)
{
	rp3d::Transform trans = body->getTransform();
	rp3d::Quaternion orient = trans.getOrientation();
	rp3d::Vector3 pos = trans.getPosition();

	float lx = orient.x;
	float lz = orient.z;
	float x = 0;
	float y = 0;
	float z = 0;

	float dz = 0;
	float dx = 0;

	float speed = 0.1;
	switch (dir)
	{
	case UP:
		//y += speed;
		break;
	case DOWN:
		//y -= speed;
		break;
	case RIGHT:
		dx = speed;
		break;
	case LEFT:
		dx = -speed;
		break;
	case FORWARD:
		dz = speed;
		break;
	case BACK:
		dz = -speed;
		break;
	}

	float proportion = 1 / sqrt(pow(lx, 2) + pow(lz, 2));

	//przod i tyl
	z += lz*dz*proportion;
	x += lx*dz*proportion;

	//lewo i prawo
	float beta = atan2(lz, lx);
	z += cos(-beta) * dx;
	x += sin(-beta) * dx;

	pos.setAllValues(x, y, z);
	//trans.setPosition(pos);
	//body->applyForceToCenterOfMass(pos);
}

void Player::move2(Direction dir)
{
	//rp3d::Transform trans = body->getTransform();
	rp3d::Vector3 pos = body->getLinearVelocity();

	float x = 0;
	float y = 0;
	float z = 0;

	switch (dir)
	{
	case UP:
		//y += speed;
		break;
	case DOWN:
		//y -= speed;
		break;
	case RIGHT:
		z += 4;
		break;
	case LEFT:
		z -= 4;
		break;
	case FORWARD:
		x += 4;
		break;
	case BACK:
		x -= 4;
		break;
	}

	//trans.setPosition(pos);

	pos.setAllValues(x, pos.y, z);
	//trans.setPosition(pos);

	//body->setTransform(trans);
	body->setLinearVelocity(pos);
	//pos.setAllValues(x, y, z);
	//rp3d::Quaternion o = rp3d::Quaternion::identity();
	//rp3d::Transform t(pos, o);
	//body->applyForceToCenterOfMass(pos);
	////body->setLinearVelocity(pos);
}

void Player::rotate2(Direction dir, float angle)
{
	rp3d::Transform trans = body->getTransform();
	rp3d::Quaternion orient = trans.getOrientation();

	float Yaw, Pitch, Roll;

	QuaternionO2IToEulerAngles(&Yaw, &Pitch, &Roll, orient);
			
	rot_angle = Yaw;
	switch (dir)
	{
	case UP:
		break;
	case DOWN:
		break;
	case RIGHT:
		rot_angle += angle;
		break;
	case LEFT:
		rot_angle -= angle;
		break;
	case FORWARD:
		break;
	case BACK:
		break;
	}

	

	rp3d::Matrix3x3 m = orient.getMatrix();

	m[0][0] = cos(rot_angle);
	m[0][2] = sin(rot_angle);
	m[2][0] = -sin(rot_angle);
	m[2][2] = cos(rot_angle);

	rp3d::Quaternion neworient(m);

	trans.setOrientation(neworient);

	body->setTransform(trans);

}

//void Player::set()
//{
//	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0, 1, 0);
//}

void Player::Draw(float m[16])
{
	rp3d::Transform transform = body->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	for (int i = 0; i < 16; i++)
		m[i] = matrix[i];
}