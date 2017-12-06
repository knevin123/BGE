#include "PhysicsGame1.h"
#include "PhysicsController.h"
#include "Sphere.h"
#include "PhysicsCamera.h"
#include "Box.h"
#include "Cylinder.h"
#include "Steerable3DController.h"
#include "Ground.h"
#include "Content.h"
#include <btBulletDynamicsCommon.h>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/euler_angles.hpp>
#include <gtx/norm.hpp>
#include "VectorDrawer.h"
#include "Utils.h"

using namespace BGE;

PhysicsGame1::PhysicsGame1(void)
{
}

PhysicsGame1::~PhysicsGame1(void)
{
}

shared_ptr<PhysicsController> cyl;
std::shared_ptr<GameComponent> station;

bool PhysicsGame1::Initialise()
{
	Game::dynamicsWorld->setGravity(btVector3(0, -20, 0));
	physicsFactory->CreateGroundPhysics();
	physicsFactory->CreateCameraPhysics();

	//shared_ptr<PhysicsController> box1 = physicsFactory->CreateBox(1,1,9, glm::vec3(5, 5, 0), glm::quat()); 
	//shared_ptr<PhysicsController> box2 = physicsFactory->CreateBox(1,1,9, glm::vec3(5, 5, 10), glm::quat()); 

	// //A hinge
	////btHingeConstraint * hinge = new btHingeConstraint(rigidBody1, rigidBody2, vec3 hinge for rigidbody 1, vec3 hinge for rigidbody 2,rigidbody1 hinge axis, rigisbody 2 axis, true);
	//btHingeConstraint * hinge = new btHingeConstraint(*box1->rigidBody, *box2->rigidBody, btVector3(0,0,5),btVector3(0,0,-5), btVector3(1,0,0), btVector3(1,0,0), true);
	//dynamicsWorld->addConstraint(hinge);


	shared_ptr<PhysicsController> body = physicsFactory->CreateBox(1, 1, 10, glm::vec3(0, 10, 0), glm::quat());
	shared_ptr<PhysicsController> leg1 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(2, 7, 10), glm::quat());
	btHingeConstraint * hinge1 = new btHingeConstraint(*body->rigidBody, *leg1->rigidBody, btVector3(2, -1, 5), btVector3(0, 2, 0), btVector3(0, 0, 0), btVector3(1, 0, 0), true);


	shared_ptr<PhysicsController> leg2 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(-2, 7, 10), glm::quat());
	btHingeConstraint * hinge2 = new btHingeConstraint(*body->rigidBody, *leg2->rigidBody, btVector3(-2, -1, 5), btVector3(0, 2, 0), btVector3(0, 0, 0), btVector3(1, 0, 0), true);

	//shared_ptr<PhysicsController> leg2 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(-2, 7, 10), glm::quat());
	//btHingeConstraint * hinge2 = new btHingeConstraint(*body->rigidBody, *leg2->rigidBody, btVector3(-2, -1, -5), btVector3(0, 2, 0), btVector3(0, 0, 0), btVector3(1, 0, 0), true);


	hinge1->setLimit(0, 0.05235988);
	hinge2->setLimit(0, 0.05235988);


	hinge1->enableAngularMotor(true, 100, 100);
	hinge2->enableAngularMotor(true, 100, 100);

	dynamicsWorld->addConstraint(hinge1);
	dynamicsWorld->addConstraint(hinge2);

	//shared_ptr<PhysicsController> leg2 = physicsFactory->CreateBox(1, 3, 1, glm::vec3(-1, 7, 0), glm::quat());
	//shared_ptr<PhysicsController> leg1 = physicsFactory->CreateBox(1, 3, 1, glm::vec3(0, 8, 0), glm::quat());
	//shared_ptr<PhysicsController> leg1 = physicsFactory->CreateBox(1, 3, 1, glm::vec3(0, 8, 0), glm::quat());

	//shared_ptr<PhysicsController> body = physicsFactory->CreateBox(3, 1, 4, glm::vec3(0, 10, 0), glm::quat());
	//shared_ptr<PhysicsController> leg1 = physicsFactory->CreateBox(1, 1, 1, glm::vec3(1, 7, -2), glm::quat());
	//shared_ptr<PhysicsController> leg2 = physicsFactory->CreateBox(1, 1, 1, glm::vec3(1, 7, 2), glm::quat());

	//shared_ptr<PhysicsController> leg3 = physicsFactory->CreateBox(1, 1, 1, glm::vec3(1, 13, -2), glm::quat());
	//shared_ptr<PhysicsController> leg4 = physicsFactory->CreateBox(1, 1, 1, glm::vec3(1, 13, 2), glm::quat());

	//btHingeConstraint * hinge = new btHingeConstraint(*body->rigidBody, *leg1->rigidBody, btVector3(0, 0, 5), btVector3(0, 0, 5), btVector3(1, 0, 0), btVector3(1, 0, 0), true);
	//dynamicsWorld->addConstraint(hinge);
	//hinge = new btHingeConstraint(*body->rigidBody, *leg2->rigidBody, btVector3(0, 0, 2.5), btVector3(0, 0, -2.5), btVector3(1, 0, 0), btVector3(1, 0, 0), true);
	//dynamicsWorld->addConstraint(hinge);
	//hinge = new btHingeConstraint(*body->rigidBody, *leg3->rigidBody, btVector3(0, 0, 2.5), btVector3(0, 0, -2.5), btVector3(1, 0, 0), btVector3(1, 0, 0), true);
	//dynamicsWorld->addConstraint(hinge);
	//hinge = new btHingeConstraint(*body->rigidBody, *leg4->rigidBody, btVector3(0, 0, 2.5), btVector3(0, 0, -2.5), btVector3(1, 0, 0), btVector3(1, 0, 0), true);
	//dynamicsWorld->addConstraint(hinge);


	//// Another hinge
	//box1 = physicsFactory->CreateBox(6,1,2, glm::vec3(15, 5, 0), glm::quat());
	//cyl = physicsFactory->CreateCylinder(2, 1, glm::vec3(15, 5, -5), glm::angleAxis(90.0f, glm::vec3(1,0,0)));
	//hinge = new btHingeConstraint(*box1->rigidBody, *cyl->rigidBody, btVector3(0,0,-2),btVector3(0,2,0), btVector3(0,0,1), btVector3(0,1,0), true);
	//dynamicsWorld->addConstraint(hinge);

	//// A Ball and socket
	//box1 = physicsFactory->CreateBox(1,1,4, glm::vec3(20, 5, 0), glm::quat()); 
	//box2 = physicsFactory->CreateBox(1,1,4, glm::vec3(20, 5, 5), glm::quat()); 

	//btPoint2PointConstraint * ptpConstraint = new btPoint2PointConstraint(*box1->rigidBody, *box2->rigidBody, btVector3(0,0,2.5f),btVector3(0,0,-2.5f));
	//dynamicsWorld->addConstraint(ptpConstraint);

	//// A Slider
	//box1 = physicsFactory->CreateBox(1,1,4, glm::vec3(25, 5, 0), glm::quat()); 
	//box2 = physicsFactory->CreateBox(1,1,4, glm::vec3(25, 5, 5), glm::quat()); 
	//btTransform box1Transform;
	//btTransform box2Transform;
	//box1Transform.setIdentity();
	//box2Transform.setIdentity();
	//
	//// You have to make the x axis rotate to the axis you want to slide
	//box1Transform.setRotation(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0,1,0))));
	//box2Transform.setRotation(GLToBtQuat(glm::angleAxis(90.0f, glm::vec3(0,1,0))));
	//
	//btSliderConstraint * slider = new btSliderConstraint(*box1->rigidBody, *box2->rigidBody, box1Transform, box2Transform, true);
	//dynamicsWorld->addConstraint(slider);

	if (!Game::Initialise()) {
		return false;
	}

	camera->transform->position = glm::vec3(0, 20, 40);

	return true;
}

void BGE::PhysicsGame1::Update(float timeDelta)
{
	//	cyl->rigidBody->applyTorque(GLToBtVector(glm::vec3(0.0f,0.0f,1.0f)));

	Game::Update(timeDelta);
}

void BGE::PhysicsGame1::Cleanup()
{
	Game::Cleanup();
}
