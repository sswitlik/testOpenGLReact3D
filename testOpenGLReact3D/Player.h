#pragma once
#include "reactphysics3d.h"
#include "Camera.h"



class Player
{
public:
	Player(rp3d::DynamicsWorld *world, rp3d::Vector3 initPosition, rp3d::Quaternion initOrientation, rp3d::Vector3 shapeData);
	~Player();

	void move(Direction dir);
	void move2(Direction dir);
	void rotate2(Direction dir, float angle);
	void Draw(float m[16]);
	//void set();
	Camera cam;

	void unrotate();
	void stop();
	void update();
//private:
	float Yaw;		//y rotation
	float Pitch;	// rotation
	float Roll;		// rotation

	rp3d::Vector3 Position;
	//rp3d::Vector3 Orientation;
	
	rp3d::RigidBody *body;
	rp3d::ProxyShape *proxyShape;
	rp3d::BoxShape *shape;
};


