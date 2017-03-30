#pragma once
#include "reactphysics3d.h"
#include <vector>
#include "BodyObj.h"

class Game
{
public:
	Game();
	~Game();
	void Draw_floor(float m[16]);
	void Draw_1(float m[16]);

	void Update();
private:
	rp3d::DynamicsWorld *World;
	BodyObj *floor;
	BodyObj *obj1;
	void ExampleTestInit();

};
