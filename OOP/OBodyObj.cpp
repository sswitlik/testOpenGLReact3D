#include "stdafx.h"
#include "OBodyObj.h"


BodyObj::BodyObj(rp3d::DynamicsWorld *world, rp3d::Vector3 initPosition, rp3d::Quaternion initOrientation, 
				rp3d::CollisionShape *initshape, Shape type)
{
	rp3d::Transform transform(initPosition, initOrientation);
	body = world->createRigidBody(transform);

	shape = initshape;

	rp3d::Transform transform2 = rp3d::Transform::identity();
	rp3d::decimal mass = rp3d::decimal(4.0);
	proxyShape = body->addCollisionShape(shape, transform2, mass);
}


BodyObj::~BodyObj()
{
}
