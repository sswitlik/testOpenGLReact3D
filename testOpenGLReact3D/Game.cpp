#include "stdafx.h"
#include "Game.h"
//#include "reactphysics3d.h"

Game::Game()
{
	ExampleTestInit();
}


Game::~Game()
{
	//World->destroyRigidBody(floor);
}


void Game::ExampleTestInit()
{
	//WORLD
	rp3d::Vector3 gravity(0.0, -9.81, 0.0);
	World = new rp3d::DynamicsWorld(gravity);
	
	World->setNbIterationsVelocitySolver(15);
	World->setNbIterationsPositionSolver(8);

	
	//TEMPORARY DATA FOR INITIALIZATION
	rp3d::Vector3 initPosition;
	rp3d::Quaternion initOrientation;
	rp3d::Vector3 shapeData;

	//FLOOR
	initPosition.setAllValues(0.0, -1.0, 0.0);
	initOrientation = rp3d::Quaternion::identity();
	shapeData.setAllValues(10, 0.5, 10);
	floor = new BodyObj(this->World, initPosition, initOrientation, shapeData);
	floor->setType(1);
	
	//OBJ
	initPosition.setAllValues(0.0, 2.0, 0.0);
	initOrientation = rp3d::Quaternion::identity();
	shapeData.setAllValues(0.5, 0.5, 0.5);
	obj1 = new BodyObj(this->World, initPosition, initOrientation, shapeData);
}

void Game::Draw_floor(float m[16])
{
	floor->Draw(m);
	/*rp3d::Transform transform = floor->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);
	
	for (int i = 0; i < 16; i++)
		m[i] = matrix[i];*/
}

void Game::Draw_1(float m[16])
{
	obj1->Draw(m);
}

void Game::Update()
{
	World->update(0.1);
}