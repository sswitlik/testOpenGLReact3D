#include "stdafx.h"
#include "BodyObj.h"

BodyObj::BodyObj(rp3d::DynamicsWorld *world, rp3d::Vector3 initPosition, rp3d::Quaternion initOrientation, rp3d::Vector3 shapeData)
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
	case 1:	body->setType(rp3d::STATIC); break;
	case 2:	body->setType(rp3d::DYNAMIC); break;
	case 3: body->setType(rp3d::KINEMATIC); break;
	}
}

void BodyObj::setMaterial(float bounce)
{
	rp3d::Material& material = body->getMaterial();
	material.setBounciness(rp3d::decimal(bounce));
	material.setFrictionCoefficient(rp3d::decimal(0.8));
	body->setLinearDamping(0.8);
}

//void BodyObj::roznedziwne()	//test 0.1
//{	
//	rp3d::Transform trans =  body->getTransform();
//	rp3d::Quaternion orient = trans.getOrientation();
//	double x = orient.y;
//
//	rp3d::Vector3 force(2.0, x, 0.0);
//
//	// Apply a force to the center of the body 
//	//body->applyForceToCenterOfMass(force);
//	//body->applyTorque(force);
//	body->setAngularVelocity(force);
//}
//
//void BodyObj::obrot()	//test 0.2
//{
//	rp3d::Vector3 force(0.0, 5.0, 0.0);
//	body->setAngularVelocity(force);
//}

void BodyObj::testset()	//test 0.2
{
	body->enableGravity(false);

	body->setAngularDamping(0.99);
}
