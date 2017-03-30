#pragma once
#include "reactphysics3d.h"

class BodyObj
{
public:
	BodyObj(rp3d::DynamicsWorld *world, rp3d::Vector3 initPosition, rp3d::Quaternion initOrientation, rp3d::Vector3 shapeData);
	~BodyObj();
	void Draw(float m[16]);
	void setType(int type);
private:
	rp3d::RigidBody *body;
	rp3d::ProxyShape *proxyShape;
	rp3d::BoxShape *shape;
};

