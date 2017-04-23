#include "stdafx.h"
#include "Arrow.h"

Arrow::Arrow()
{

}

Arrow::Arrow(rp3d::DynamicsWorld *world, rp3d::Vector3 initPosition, rp3d::Quaternion initOrientation, rp3d::Vector3 shapeData, rp3d::decimal mass)
{
	BodyObj(world, initPosition, initOrientation, shapeData, mass);
}


Arrow::~Arrow()
{
}
