#pragma once
#include "reactphysics3d.h"
#include "Camera.h"

class Player
{
public:
	Player(rp3d::DynamicsWorld *world, rp3d::Vector3 initPosition, rp3d::Quaternion initOrientation, rp3d::Vector3 shapeData);
	~Player();

	/*void move(Direction dir);
	void rotate(Direction dir, int angle);
	void set();*/
private:
	Camera cam;
	
	rp3d::RigidBody *body;
	rp3d::ProxyShape *proxyShape;
	rp3d::BoxShape *shape;
};

