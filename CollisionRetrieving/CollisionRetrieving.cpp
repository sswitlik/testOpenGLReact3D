// CollisionRetrieving.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GL/freeglut.h"
#include "reactphysics3d.h"

enum Category {
	CATEGORY1 = 0x0001,
	CATEGORY2 = 0x0002,
	CATEGORY3 = 0x0004
};

//MOUSE
int mx, my;
//Keyboard
bool keystate[256];

//TIME
unsigned int previousFrameTime;
unsigned int accumulator;

//PHYSICS
rp3d::DynamicsWorld *world;

//floor
rp3d::RigidBody *fbody;
rp3d::ProxyShape *fproxy;
rp3d::BoxShape *fshape;
rp3d::Vector3 *f_colors;

//obj1
rp3d::RigidBody *body1;
rp3d::ProxyShape *proxy1;
rp3d::CollisionShape *shape1;
rp3d::Vector3 *obj1_colors;

class MyEventListener : public rp3d::EventListener
{
	void beginContact(const rp3d::ContactPointInfo &contact)
	{
		rp3d::ProxyShape *ps = fproxy;
		rp3d::Vector3 *fc = (rp3d::Vector3 *)ps->getUserData();
		fc->y = 1;
		fc->x = 0;
	}
};

void Display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	gluLookAt(0, 1, 3, 0, 0, 0, 0, 1, 0);

	float matrix[16];

	glPushMatrix();
		rp3d::Transform t = fbody->getTransform();
		t.getOpenGLMatrix(matrix);
		glMultMatrixf(matrix);
		glScalef(5, 1, 5);
		//getcolor
			rp3d::Vector3 *fc = (rp3d::Vector3 *) fproxy->getUserData();
			glColor3f(fc->x, fc->y, fc->z);
		glutSolidCube(1);
		glColor3f(0, 0, 0);
		glutWireCube(1);
	glPopMatrix();

//------OBJ1------------------
	glPushMatrix();
		t = body1->getTransform();
		t.getOpenGLMatrix(matrix);
		glMultMatrixf(matrix);
		glColor3f(obj1_colors->x, obj1_colors->y, obj1_colors->z);
		glutSolidSphere(0.5, 21, 21);
		glColor3f(0, 0, 0);
		//glutWireCube(1);
	glPopMatrix();



	glFlush();			// skierowanie poleceñ do wykonania
	glutSwapBuffers();	// zamiana buforów koloru
}

void Reshape(int width, int height)
{
	// obszar renderingu - ca³e okno
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// obliczenie aspektu obrazu z uwzglêdnieniem
	// przypadku, gdy wysokoœæ obrazu wynosi 0
	GLdouble aspect = 1;
	if (height > 0)
		aspect = width / (GLdouble)height;

	// rzutowanie perspektywiczne
	gluPerspective(90, aspect, 0.1, 30.0);

	Display();
}

void OnTimer(int id)
{
	glutTimerFunc(17, OnTimer, 0);

	//if (keystate['w'])
	//	cam.move(FORWARD);
}

void OnKeyDown(unsigned char key, int x, int y)
{
	if (key == 27)
	{ // ESC - wyjœcie
		glutLeaveMainLoop();
	}
	
}

void OnKeyPress(unsigned char key, int x, int y) {
	//printf("KeyPress: %c\n", key);
	if (!keystate[key]) {
		OnKeyDown(key, x, y); // Emulacja zdarzenia zwi¹zanego z pojedynczym wciœniêciem klawisza
	}

	keystate[key] = true;
}

// Obs³uga zdarzenia puszczenia klawisza.
void OnKeyUp(unsigned char key, int x, int y)
{
	if (key == 'w')
		;

	keystate[key] = false;
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);

		//case 'w':   cam.move(FORWARD);	break;
		//case 's':   cam.move(BACK);		break;
		//case 'd':   cam.move(RIGHT);	break;
		//case 'a':   cam.move(LEFT);	break;
		//case 'q':   cam.rotate(UP,1);	    break;
		//case 'e':   cam.rotate(DOWN,1);	break;
		//case 'z':	game.Update();		break;
		//case 'x':	game.plus();		break;
	}


	//Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
	Display();
}

void Idle()
{
	if (previousFrameTime == 0)
		previousFrameTime = glutGet(GLUT_ELAPSED_TIME) - 1;
	const float timeStep = 0.016;
	const int timeStep2 = 16;
	unsigned int currentFrameTime = glutGet(GLUT_ELAPSED_TIME);

	unsigned int deltaTime = currentFrameTime - previousFrameTime;

	previousFrameTime = currentFrameTime;

	accumulator += deltaTime;

	int t1 = glutGet(GLUT_ELAPSED_TIME);
	while (accumulator >= timeStep2) {

		world->update(timeStep);

		accumulator -= timeStep2;
	}
	int t2 = glutGet(GLUT_ELAPSED_TIME);

//--------------------------------------------
	const rp3d::ContactManifoldListElement* listElem;
 
	listElem = body1->getContactManifoldsList();
	
	for (; listElem != NULL; listElem = listElem->next) 
	{
		rp3d::ContactManifold* manifold = listElem->contactManifold;

		rp3d::ProxyShape *ps = manifold->getShape1();
		rp3d::Vector3 *fc = (rp3d::Vector3 *)ps->getUserData();
		//fc->y = 1;
		//fc->x = 0;
	}

//--------------------------------------------
	glutPostRedisplay();
}

int main(int argc, char * argv[])
{
	//PHYSICS
	rp3d::Vector3 gravity(0.0, -9.81, 0.0);
	world = new rp3d::DynamicsWorld(gravity);
	world->setNbIterationsVelocitySolver(15);
	world->setNbIterationsPositionSolver(8);

	MyEventListener listener;
	world->setEventListener(&listener);
/*
	rp3d::EventListener l;
	l.beginContact()*/

//----------FLOOR----------------------------------
	rp3d::Vector3 initPosition(0.0, -1.0, 0.0);
	rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(initPosition, initOrientation);
	fbody = world->createRigidBody(transform);
	rp3d::Vector3 shapeData(5, 0.5, 5);
	fshape = new rp3d::BoxShape(shapeData, 0.1);
	rp3d::Transform transform2 = rp3d::Transform::identity();
	rp3d::decimal mass = rp3d::decimal(4.0);
	fproxy = fbody->addCollisionShape(fshape, transform2, mass);

	fbody->setType(rp3d::STATIC);
	//fbody->setIsAllowedToSleep(false);

	f_colors = new rp3d::Vector3(1, 0, 0);
	fproxy->setUserData(f_colors);

	//fproxy->setCollisionCategoryBits(CATEGORY1);
	//fproxy->setCollideWithMaskBits(CATEGORY1 | CATEGORY2);

	rp3d::Material& fmaterial = fbody->getMaterial();
	fmaterial.setBounciness(rp3d::decimal(0.3));

//----------OBJ1----------------------------------
	initPosition.setAllValues(0.0, 2.0, 0.0);
	rp3d::Quaternion initOrientation2(0,90,90);
	transform.setPosition(initPosition);
	transform.setOrientation(initOrientation2);
	body1 = world->createRigidBody(transform);
	shapeData.setAllValues(0.5, 0.5, 0.5);
	shape1 = new rp3d::SphereShape(0.5);
	//rp3d::Transform transform2 = rp3d::Transform::identity();
	//rp3d::decimal mass = rp3d::decimal(4.0);
	proxy1 = body1->addCollisionShape(shape1, transform2, mass);

	body1->setIsAllowedToSleep(false);
	
	obj1_colors = new rp3d::Vector3(0, 0.1, 0);
	proxy1->setUserData(obj1_colors);

	//proxy1->setCollisionCategoryBits(CATEGORY2);
	//proxy1->setCollideWithMaskBits(CATEGORY1 | CATEGORY2);

	rp3d::Material& material = body1->getMaterial();
	material.setBounciness(rp3d::decimal(0.4));
	material.setRollingResistance(rp3d::decimal(0.001));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(5, 5);
	glutCreateWindow("LOL");
	glutSetCursor(GLUT_CURSOR_NONE);

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	//KEYBOARD
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	//MOUSE
	//glutMouseFunc(MouseButton);
	//glutMotionFunc(MouseMotion);
	//glutEntryFunc(EntryFunc);
	//glutPassiveMotionFunc(MousePassiveMotion);
	//glutSetKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
	//TIMER
	glutTimerFunc(17, OnTimer, 0);

	glutIdleFunc(Idle);

	glutMainLoop();

	delete world;
	delete fshape;
	delete shape1;
	delete obj1_colors;
	return 0;
}


