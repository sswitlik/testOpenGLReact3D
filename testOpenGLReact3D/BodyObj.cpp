#include "stdafx.h"
#include "BodyObj.h"

BodyObj::BodyObj(rp3d::DynamicsWorld *world, float x, float y, float z)
{
	rp3d::Vector3 initPosition(0.0, -1.0, 0.0);
	rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(initPosition, initOrientation);
	body = world->createRigidBody(transform);

	const rp3d::Vector3 bshape(x, y, z);
	shape = new rp3d::BoxShape(bshape);

	rp3d::Transform transform2 = rp3d::Transform::identity();
	rp3d::decimal mass = rp3d::decimal(4.0);
	proxyShape = body->addCollisionShape(shape, transform2, mass);
}


BodyObj::~BodyObj()
{
	//delete
}

void BodyObj::Draw(float m[16])
{
	rp3d::Transform transform = body->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	for (int i = 0; i < 16; i++)
		m[i] = matrix[i];
}

void BodyObj::setType(int type)
{
	switch (type)
	{
	case 1:	body->setType(rp3d::KINEMATIC); break;
	case 2:	body->setType(rp3d::DYNAMIC); break;
	}
}