#pragma once
#include "reactphysics3d.h"

class BodyObj
{
public:
	BodyObj(rp3d::DynamicsWorld *world, float x, float y, float z);
	~BodyObj();
	void Draw(float m[16]);
	void setType(int type);
private:
	rp3d::RigidBody *body;
	rp3d::ProxyShape *proxyShape;
	rp3d::BoxShape *shape;
};

