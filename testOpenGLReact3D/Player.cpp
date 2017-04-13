#include "stdafx.h"
#include "Player.h"
#include <GL\freeglut.h>

#define RAD  0.01745329
#define PI_2 1.57079632679
#define PIx2 6.28318530717

Player::Player(rp3d::DynamicsWorld *world, rp3d::Vector3 initPosition, rp3d::Quaternion initOrientation, rp3d::Vector3 shapeData)
{
	rp3d::Transform transform(initPosition, initOrientation);
	body = world->createRigidBody(transform);
	shape = new rp3d::BoxShape(shapeData, 0.1);

	rp3d::Transform transform2 = rp3d::Transform::identity();
	rp3d::decimal mass = rp3d::decimal(4.0);
	proxyShape = body->addCollisionShape(shape, transform2, mass);

	//body->enableGravity(false);

	rp3d::Material& material = body->getMaterial();
	material.setBounciness(rp3d::decimal(0));
	material.setFrictionCoefficient(rp3d::decimal(1));

	Yaw = 0; Roll = 0; Pitch = 0;
	cam.sync(initPosition, Yaw, Roll, Pitch);
}


Player::~Player()
{
}

void Player::update()
{
	rp3d::Transform trans = body->getTransform();
	
	cam.sync(trans.getPosition(), Yaw, Roll, Pitch);
	//cam.set();
	unrotate();
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

	QuaternionO2IToEulerAngles(&Yaw, &Pitch, &Roll, orient);
	
	if (Pitch > 0.1 || Roll > 0.1 || Pitch < -0.1 || Roll < -0.1)
	{
		rp3d::Quaternion o(0, Yaw, 0);
		trans.setOrientation(o);
		body->setTransform(trans);
	}
}

void Player::stop()
{
	rp3d::Material& material = body->getMaterial();
	material.setFrictionCoefficient(rp3d::decimal(1));

	rp3d::Vector3 vel = body->getLinearVelocity();
	rp3d::Vector3 speed(0, vel.y, 0);
	body->setLinearVelocity(speed);
}

void Player::move(Direction dir)
{
	rp3d::Material& material = body->getMaterial();
	material.setFrictionCoefficient(rp3d::decimal(0));


	rp3d::Transform trans = body->getTransform();
	rp3d::Quaternion orient = trans.getOrientation();
	//float Yaw, Pitch, Roll;
	QuaternionO2IToEulerAngles(&Yaw, &Pitch, &Roll, orient);

	rp3d::Vector3 vel = body->getLinearVelocity();

	if (vel.y > 0.1 || vel.y < -0.1)		//can't move if fall
		return;

	float x = 0;
	float y = 0;
	float z = 0;

	float speed = 2.5;

	switch (dir)
	{
	case UP:
		//y += speed;
		break;
	case DOWN:
		//y -= speed;
		break;
	case RIGHT:
		x = -sin(Yaw + PI_2)*speed;
		z = -cos(Yaw + PI_2)*speed;
		break;
	case LEFT:
		x = sin(Yaw + PI_2)*speed;
		z = cos(Yaw + PI_2)*speed;
		break;
	case FORWARD:
		x = sin(Yaw)*speed;
		z = cos(Yaw)*speed;
		break;
	case BACK:
		x = -sin(Yaw)*speed;
		z = -cos(Yaw)*speed;
		break;
	}

	float new_x = x + vel.x;
	float new_z = z + vel.z;
	float new_y = y + vel.y;

	rp3d::Vector2 max_speed(new_x, new_z);
	if (max_speed.length() > 5)
	{
		max_speed.normalize();
		max_speed *= 5;
	
	}
	rp3d::Vector3 new_vel(max_speed.x, new_y, max_speed.y);
	body->setLinearVelocity(new_vel);
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

	switch (dir)
	{
	case UP:
		break;
	case DOWN:
		break;
	case RIGHT:
		Yaw -= angle;
		break;
	case LEFT:
		Yaw += angle;
		break;
	case FORWARD:
		break;
	case BACK:
		break;
	}

	rp3d::Matrix3x3 m = orient.getMatrix();
	m[0][0] = cos(Yaw);
	m[0][2] = sin(Yaw);
	m[2][0] = -sin(Yaw);
	m[2][2] = cos(Yaw);

	rp3d::Quaternion neworient(m);
	trans.setOrientation(neworient);
	body->setTransform(trans);
}

void Player::Draw(float m[16])
{
	rp3d::Transform transform = body->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	for (int i = 0; i < 16; i++)
		m[i] = matrix[i];
}

void Player::look_vertical(float angle)
{
	if (angle > 0)
		cam.ly += 0.5;
	//cam.rotate(UP, angle);
	else
		cam.ly -= 0.5;
		//cam.rotate(DOWN, angle);
}

void Player::jump()
{
	rp3d::Vector3 vel = body->getLinearVelocity();

	if (vel.y > 0.01 || vel.y < -0.01)		//can't move if fall
		return;

	rp3d::Vector3 force(0, 1000, 0);
	body->applyForceToCenterOfMass(force);
}