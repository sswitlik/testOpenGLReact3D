#pragma once
#include "reactphysics3d.h"

class BodyObj
{
public:
	BodyObj();
	BodyObj(rp3d::DynamicsWorld *world, rp3d::Vector3 initPosition, rp3d::Quaternion initOrientation, rp3d::Vector3 shapeData, rp3d::decimal mass);
	~BodyObj();
	void Draw(float m[16]);	//return translate matrix
	void Draw();			//OpenGL drawing
	void setType(int type);
	void setMaterial(float , float);

	//test 0.2
	void testset();
	void rd();
	float angle;
//protected:
	rp3d::RigidBody *body;
	rp3d::ProxyShape *proxyShape;
	rp3d::CollisionShape *shape;
	//rp3d::Material& material;
};