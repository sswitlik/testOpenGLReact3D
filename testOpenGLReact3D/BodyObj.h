#pragma once
#include "reactphysics3d.h"

class BodyObj
{
public:
	BodyObj(rp3d::DynamicsWorld *world, rp3d::Vector3 initPosition, rp3d::Quaternion initOrientation, rp3d::Vector3 shapeData);
	~BodyObj();
	void Draw(float m[16]);
	void setType(int type);
	void setMaterial(float bounce);

	//test 0.2
	void testset();


private:
	rp3d::RigidBody *body;
	rp3d::ProxyShape *proxyShape;
	rp3d::BoxShape *shape;
	//rp3d::Material& material;
};
