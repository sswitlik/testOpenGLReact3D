#pragma once
#include <vector>
#include <reactphysics3d.h>
#include "OPlayer.h"
#include "OBodyObj.h"
#include <GL/freeglut.h>

class Game
{
public:
	Game();
	~Game();

	void setCamera();

private:
	std::vector<BodyObj> Scenery;
	std::vector<BodyObj> Alive;
	Player *player;
	rp3d::DynamicsWorld *world;
};

