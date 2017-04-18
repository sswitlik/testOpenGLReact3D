#pragma once
#include "reactphysics3d.h"

enum Shape
{
	BOX,
	SPHERE
};

class BodyObj
{
public:
	BodyObj(rp3d::DynamicsWorld *world, rp3d::Vector3 initPosition, rp3d::Quaternion initOrientation, rp3d::CollisionShape *initshape, Shape type);
	~BodyObj();

private:
	rp3d::RigidBody *body;
	rp3d::ProxyShape *proxyShape;
	rp3d::CollisionShape *shape;
};

