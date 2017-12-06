#include "MyAssignment.h"
#include "Content.h"
#include "VectorDrawer.h"
#include "LazerBeam.h"
#include "FountainEffect.h"
#include "Utils.h"
#include <btBulletDynamicsCommon.h>
#include "PhysicsFactory.h"
#include "PhysicsController.h"
#include "Sphere.h"
#include "PhysicsCamera.h"
#include "Box.h"
#include "Cylinder.h"
#include "GravityController.h"

using namespace BGE;

/*Author: Keith Nevin C14447012
The aim of this assignment was to create a dog in BGE using multiple shapes and hinges
I have decided to create an evolution of the dog as you can see issue that each implementation has
and how each one built onto the next
I explain how hinge joints are created in the CreateAnimal
I explain fixed contraints and cone joints work in CreateAnimal1
I explain ball and socket joints in CreateAnimal2
*/


MyAssignment::MyAssignment(void)
{
	elapsed = 10000;
	turnRate = glm::half_pi<float>(); // Turn half_pi radians per second
}


MyAssignment::~MyAssignment(void)
{
}

shared_ptr<PhysicsController> cy2;

bool MyAssignment::Initialise()
{
	//setting up positions for the animals
	scale = 0.50f;
	pos = glm::vec3(0, 5, 0);
	glm::vec3 pos1 = glm::vec3(20, 5, 20);
	glm::vec3 pos2 = glm::vec3(40, 5, 40);
	glm::vec3 pos3 = glm::vec3(60, 5, 60);

	physicsFactory->CreateGroundPhysics();

	physicsFactory->CreateCameraPhysics();
	//this makes the ground solid
	std::shared_ptr<GameComponent> ground = make_shared<Ground>();
	Attach(ground);
	//this adds gravity to the game
	Game::dynamicsWorld->setGravity(btVector3(0, -10, 0));
	//lets define our animals shape
	shared_ptr<PhysicsController> animal = CreateAnimal(pos);
	shared_ptr<PhysicsController> animal1 = CreateAnimal1(pos1);
	shared_ptr<PhysicsController> animal2 = CreateAnimal2(pos2);
	shared_ptr<PhysicsController> animal3 = CreateAnimal3(pos3);

	//animal->Attach(make_shared<GravityController>());
	Game::Initialise();

	//sets the camera position
	camera->transform->position = glm::vec3(30, 50, -20);
	return true;
}

void MyAssignment::Update(float timeDelta)
{
	// Movement of ship2
	if (keyState[SDL_SCANCODE_UP])
	{
		
	}
	if (keyState[SDL_SCANCODE_DOWN])
	{
		
	}
	if (keyState[SDL_SCANCODE_LEFT])
	{
		
	}
	if (keyState[SDL_SCANCODE_RIGHT])
	{
		
	}

	if (keyState[SDL_SCANCODE_O])
	{
		
	}

	if (keyState[SDL_SCANCODE_L])
	{
		
	}
	

	Game::Update(timeDelta);

}
shared_ptr<PhysicsController> MyAssignment::CreateAnimal(glm::vec3 position)
{
	
	//prototype 1
	shared_ptr<PhysicsController> chest = physicsFactory->CreateBox(3, 2, 8, glm::vec3(position), glm::quat());

	//this set up the dogs 4 legs -1 and 2 are the front legs with 3 and 4 being the back
	shared_ptr<PhysicsController> leg1 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x + 3, position.y, position.z + 4), glm::quat());
	
	//how to create a hinge constraint
	////btHingeConstraint * hinge = new btHingeConstraint(rigidBody1, rigidBody2, vec3 position of hinge for rigidbody 1, vec3 position of hinge for rigidbody 2,rigidbody1 hinge axis, rigisbody 2 axis, true);
	//vec3 positions of rigid bodies are local to the bodies
	//the axis are done by putting a 1 in the axis you want the hinge to sit on. eg,(0,1,0) is the y axis
	//creates hinge constraint for chest and leg1
	btHingeConstraint * leg1hinge = new btHingeConstraint(*chest->rigidBody, *leg1->rigidBody, btVector3(1.5, -1, 4), btVector3(-1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);


	shared_ptr<PhysicsController> leg2 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x - 3, position.y, position.z + 4), glm::quat());
	//creates hinge constraint for chest and leg2
	btHingeConstraint * leg2hinge = new btHingeConstraint(*chest->rigidBody, *leg2->rigidBody, btVector3(-1.5, -1, 4), btVector3(1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);

	shared_ptr<PhysicsController> leg3 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x + 3, position.y, position.z - 4), glm::quat());
	//creates hinge constraint for chest and leg3
	btHingeConstraint * leg3hinge = new btHingeConstraint(*chest->rigidBody, *leg3->rigidBody, btVector3(1.5, -1, -4), btVector3(-1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);


	shared_ptr<PhysicsController> leg4 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x - 3, position.y, position.z - 4), glm::quat());
	//creates hinge constraint for chest and leg4
	btHingeConstraint * leg4hinge = new btHingeConstraint(*chest->rigidBody, *leg4->rigidBody, btVector3(-1.5, -1, -4), btVector3(1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);

	//this sets the upper and lower limit angles for the hinges in radians
	leg1hinge->setLimit(0, 6);
	leg2hinge->setLimit(0, 6);
	leg3hinge->setLimit(0, 6);
	leg4hinge->setLimit(0, 6);

	//this sets the target speed for the angle movement and the force applied to achieve this
	leg1hinge->enableAngularMotor(true, 2, 100);
	leg2hinge->enableAngularMotor(true, 2, 100);
	leg3hinge->enableAngularMotor(true, 2, 100);
	leg4hinge->enableAngularMotor(true, 2, 100);

	dynamicsWorld->addConstraint(leg1hinge);
	dynamicsWorld->addConstraint(leg2hinge);
	dynamicsWorld->addConstraint(leg3hinge);
	dynamicsWorld->addConstraint(leg4hinge);
	

	return chest;
}

shared_ptr<PhysicsController> MyAssignment::CreateAnimal1(glm::vec3 position)
{

	//prototype 2
	shared_ptr<PhysicsController> chest = physicsFactory->CreateBox(3, 2, 8, glm::vec3(position), glm::quat());

	//this set up the dogs 4 legs -1 and 2 are the front legs with 3 and 4 being the back
	shared_ptr<PhysicsController> leg1 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x + 3, position.y, position.z + 4), glm::quat());
	//creates hinge constraint for chest and leg1
	btHingeConstraint * leg1hinge = new btHingeConstraint(*chest->rigidBody, *leg1->rigidBody, btVector3(1.5, -1, 4), btVector3(-1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);


	shared_ptr<PhysicsController> leg2 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x - 3, position.y, position.z + 4), glm::quat());
	//creates hinge constraint for chest and leg2
	btHingeConstraint * leg2hinge = new btHingeConstraint(*chest->rigidBody, *leg2->rigidBody, btVector3(-1.5, -1, 4), btVector3(1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);

	shared_ptr<PhysicsController> leg3 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x + 3, position.y, position.z - 4), glm::quat());
	//creates hinge constraint for chest and leg3
	btHingeConstraint * leg3hinge = new btHingeConstraint(*chest->rigidBody, *leg3->rigidBody, btVector3(1.5, -1, -4), btVector3(-1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);


	shared_ptr<PhysicsController> leg4 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x - 3, position.y, position.z - 4), glm::quat());
	//creates hinge constraint for chest and leg4
	btHingeConstraint * leg4hinge = new btHingeConstraint(*chest->rigidBody, *leg4->rigidBody, btVector3(-1.5, -1, -4), btVector3(1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);

	//setup for fixed constraint
	//these use bttransforms for positons instead of btvectors
	//must set origin for the positions this is also local to the rigid bodies
	btTransform coord1;
	btTransform coord2;
	coord1.setIdentity();
	coord2.setIdentity();
	coord1.setOrigin(btVector3(0, 3, 4.0f));
	coord2.setOrigin(btVector3(0, 0, 0));
	//creates head shape
	shared_ptr<PhysicsController> head = physicsFactory->CreateBox(2, 2, 2, glm::vec3(position.x, position.y+5, position.z+4), glm::quat());
	//makes fixed constraint that put the head on the dog
	//the transforms and rigid body is all that is entered as there is no movement
	btFixedConstraint * headjoint = new btFixedConstraint(*chest->rigidBody, *head->rigidBody, coord1, coord2);
	

	//create ears
	shared_ptr<PhysicsController> ear1 = physicsFactory->CreateBox(0.2, 1.5, 1, glm::vec3(position.x - 2.5, position.y+5, position.z + 4), glm::quat());
	//creates hinge constraint for ear1 and head
	btHingeConstraint * ear1hinge = new btHingeConstraint(*head->rigidBody, *ear1->rigidBody, btVector3(-1, 0, 0), btVector3(1, 0, 0), btVector3(1, 2, 0), btVector3(0, 1, 0), true);

	shared_ptr<PhysicsController> ear2 = physicsFactory->CreateBox(0.2, 1.5, 1, glm::vec3(position.x + 2.5, position.y + 5, position.z + 4), glm::quat());
	//creates hinge constraint for ear2 and head
	btHingeConstraint * ear2hinge = new btHingeConstraint(*head->rigidBody, *ear2->rigidBody, btVector3(+1, 0, 0), btVector3(-1, 0, 0), btVector3(0, 2, 0), btVector3(1, 1, 0), true);

	//Create tail
	//tail trasform setup for cone twist constraint
	//these use bttransforms for positons instead of btvectors
	//must set origin for the positions this is also local to the rigid bodies
	btTransform coorda;
	btTransform coordb;
	coorda.setIdentity();
	coordb.setIdentity();
	coorda.setOrigin(btVector3(0, 0, -4.5f));
	coordb.setOrigin(btVector3(0, 0.5f, 0));
	shared_ptr<PhysicsController> tail = physicsFactory->CreateBox(0.5, 0.5, 1.5, glm::vec3(position.x + 2.5, position.y + 5, position.z + 4), glm::quat());
	//creates the cone twist this take in the rigid body and the transforms, no axis, cone automatically points towards the z axis, cannot change it.
	btConeTwistConstraint*tailjoint = new btConeTwistConstraint(*chest->rigidBody, *tail->rigidBody, coorda, coordb);

	//this sets the upper and lower limit angles for the hinges in radians
	leg1hinge->setLimit(0, 6);
	leg2hinge->setLimit(0, 6);
	leg3hinge->setLimit(0, 6);
	leg4hinge->setLimit(0, 6);
	ear1hinge->setLimit(0, 0.25);
	ear2hinge->setLimit(0, 0.25);


	//this sets the target speed for the angle movement and the force applied to achieve this
	leg1hinge->enableAngularMotor(true, 2, 100);
	leg2hinge->enableAngularMotor(true, 2, 100);
	leg3hinge->enableAngularMotor(true, 2, 100);
	leg4hinge->enableAngularMotor(true, 2, 100);
	ear1hinge->enableAngularMotor(true, 2, 100);
	ear2hinge->enableAngularMotor(true, 2, 100);

	dynamicsWorld->addConstraint(leg1hinge);
	dynamicsWorld->addConstraint(leg2hinge);
	dynamicsWorld->addConstraint(leg3hinge);
	dynamicsWorld->addConstraint(leg4hinge);
	dynamicsWorld->addConstraint(headjoint);
	dynamicsWorld->addConstraint(ear1hinge);
	dynamicsWorld->addConstraint(ear2hinge);
	dynamicsWorld->addConstraint(tailjoint);


	return chest;
}

shared_ptr<PhysicsController> MyAssignment::CreateAnimal2(glm::vec3 position)
{

	//prototype 3
	shared_ptr<PhysicsController> chest = physicsFactory->CreateBox(3, 2, 8, glm::vec3(position), glm::quat());

	//this set up the dogs 4 legs -1 and 2 are the front legs with 3 and 4 being the back
	shared_ptr<PhysicsController> leg1 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x + 3, position.y, position.z + 4), glm::quat());
	//creates hinge constraint for chest and leg1
	btHingeConstraint * leg1hinge = new btHingeConstraint(*chest->rigidBody, *leg1->rigidBody, btVector3(1.5, -1, 4), btVector3(-1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);


	shared_ptr<PhysicsController> leg2 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x - 3, position.y, position.z + 4), glm::quat());
	//creates hinge constraint for chest and leg2
	btHingeConstraint * leg2hinge = new btHingeConstraint(*chest->rigidBody, *leg2->rigidBody, btVector3(-1.5, -1, 4), btVector3(1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);

	shared_ptr<PhysicsController> leg3 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x + 3, position.y, position.z - 4), glm::quat());
	//creates hinge constraint for chest and leg3
	btHingeConstraint * leg3hinge = new btHingeConstraint(*chest->rigidBody, *leg3->rigidBody, btVector3(1.5, -1, -4), btVector3(-1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);


	shared_ptr<PhysicsController> leg4 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x - 3, position.y, position.z - 4), glm::quat());
	//creates hinge constraint for chest and leg4
	btHingeConstraint * leg4hinge = new btHingeConstraint(*chest->rigidBody, *leg4->rigidBody, btVector3(-1.5, -1, -4), btVector3(1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);

	//// A Ball and socket
	shared_ptr<PhysicsController>head = physicsFactory->CreateBox(2, 2, 2, glm::vec3(position.x, position.y + 2, position.z + 5), glm::quat());
	//makes ball and joint head constraint
	//this uses the rigid bodies and their positions. No axis needed as it moves across several freely,
	btPoint2PointConstraint * headjoint = new btPoint2PointConstraint(*chest->rigidBody, *head->rigidBody, btVector3(0, 3, 5.0f), btVector3(0, 0, 0));

	//create ears
	shared_ptr<PhysicsController> ear1 = physicsFactory->CreateBox(0.2, 1.5, 1, glm::vec3(position.x - 2.5, position.y + 5, position.z + 4), glm::quat());
	//creates hinge constraint for ear1 and head
	btHingeConstraint * ear1hinge = new btHingeConstraint(*head->rigidBody, *ear1->rigidBody, btVector3(-1, 0, 0), btVector3(1, 0, 0), btVector3(1, 2, 0), btVector3(0, 1, 0), true);

	shared_ptr<PhysicsController> ear2 = physicsFactory->CreateBox(0.2, 1.5, 1, glm::vec3(position.x + 2.5, position.y + 5, position.z + 4), glm::quat());
	//creates hinge constraint for ear1 and head
	btHingeConstraint * ear2hinge = new btHingeConstraint(*head->rigidBody, *ear2->rigidBody, btVector3(+1, 0, 0), btVector3(-1, 0, 0), btVector3(0, 2, 0), btVector3(1, 1, 0), true);

	//this sets the upper and lower limit angles for the hinges in radians
	leg1hinge->setLimit(0, 6);
	leg2hinge->setLimit(0, 6);
	leg3hinge->setLimit(0, 6);
	leg4hinge->setLimit(0, 6);
	ear1hinge->setLimit(0, 0.25);
	ear2hinge->setLimit(0, 0.25);


	//this sets the target speed for the angle movement and the force applied to achieve this
	leg1hinge->enableAngularMotor(true, 2, 100);
	leg2hinge->enableAngularMotor(true, 2, 100);
	leg3hinge->enableAngularMotor(true, 2, 100);
	leg4hinge->enableAngularMotor(true, 2, 100);
	ear1hinge->enableAngularMotor(true, 2, 100);
	ear2hinge->enableAngularMotor(true, 2, 100);

	dynamicsWorld->addConstraint(leg1hinge);
	dynamicsWorld->addConstraint(leg2hinge);
	dynamicsWorld->addConstraint(leg3hinge);
	dynamicsWorld->addConstraint(leg4hinge);
	dynamicsWorld->addConstraint(headjoint);
	dynamicsWorld->addConstraint(ear1hinge);
	dynamicsWorld->addConstraint(ear2hinge);


	return chest;
}

shared_ptr<PhysicsController> MyAssignment::CreateAnimal3(glm::vec3 position)
{

	//prototype 4
	shared_ptr<PhysicsController> chest = physicsFactory->CreateBox(3, 2, 8, glm::vec3(position), glm::quat());

	//this set up the dogs 4 legs -1 and 2 are the front legs with 3 and 4 being the back
	shared_ptr<PhysicsController> leg1 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x + 3, position.y, position.z + 4), glm::quat());
	//creates hinge constraint for chest and leg1
	btHingeConstraint * leg1hinge = new btHingeConstraint(*chest->rigidBody, *leg1->rigidBody, btVector3(1.5, -1, 4), btVector3(-1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);


	shared_ptr<PhysicsController> leg2 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x - 3, position.y, position.z + 4), glm::quat());
	//creates hinge constraint for chest and leg2
	btHingeConstraint * leg2hinge = new btHingeConstraint(*chest->rigidBody, *leg2->rigidBody, btVector3(-1.5, -1, 4), btVector3(1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);

	shared_ptr<PhysicsController> leg3 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x + 3, position.y, position.z - 4), glm::quat());
	//creates hinge constraint for chest and leg3
	btHingeConstraint * leg3hinge = new btHingeConstraint(*chest->rigidBody, *leg3->rigidBody, btVector3(1.5, -1, -4), btVector3(-1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);


	shared_ptr<PhysicsController> leg4 = physicsFactory->CreateBox(1, 4, 1, glm::vec3(position.x - 3, position.y, position.z - 4), glm::quat());
	//creates hinge constraint for chest and leg4
	btHingeConstraint * leg4hinge = new btHingeConstraint(*chest->rigidBody, *leg4->rigidBody, btVector3(-1.5, -1, -4), btVector3(1.5, 0, 0), btVector3(1, 0, 0), btVector3(0, 0, 0), true);

	//// A Ball and socket
	shared_ptr<PhysicsController>head = physicsFactory->CreateBox(2, 2, 2, glm::vec3(position.x, position.y+2, position.z+5), glm::quat());
	btPoint2PointConstraint * headjoint = new btPoint2PointConstraint(*chest->rigidBody, *head->rigidBody, btVector3(0,3,5.0f),btVector3(0,0,0));

	//this sets the upper and lower limit angles for the hinges in radians
	leg1hinge->setLimit(0, 6);
	leg2hinge->setLimit(0, 6);
	leg3hinge->setLimit(0, 6);
	leg4hinge->setLimit(0, 6);

	//this sets the target speed for the angle movement and the force applied to achieve this
	leg1hinge->enableAngularMotor(true, 2, 100);
	leg2hinge->enableAngularMotor(true, 2, 100);
	leg3hinge->enableAngularMotor(true, 2, 100);
	leg4hinge->enableAngularMotor(true, 2, 100);

	dynamicsWorld->addConstraint(leg1hinge);
	dynamicsWorld->addConstraint(leg2hinge);
	dynamicsWorld->addConstraint(leg3hinge);
	dynamicsWorld->addConstraint(leg4hinge);
	dynamicsWorld->addConstraint(headjoint);


	return chest;
}



													