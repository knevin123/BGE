#include "hingeController.h"
#include <btBulletDynamicsCommon.h>
#include "Utils.h"
using namespace BGE;

hingeController::hingeController(btHingeConstraint * j1, btHingeConstraint * j2, btHingeConstraint * j3, btHingeConstraint * j4, bool bool1) {
	FrontRHinge = j1;
	FrontLHinge = j2;
	BackRHinge = j3;
	BackLHinge = j4;
	
}

hingeController::~hingeController() {

}

void hingeController::Update(float timeDelta) {

	MoveLegs();
	GameComponent::Update(timeDelta);
}

void hingeController::MoveLegs(){
	/*
	if (FrontLAngle < 135)
	{
		LkneeHingeAngle = LkneeHingeAngle - 20;
		RkneeHingeAngle = RkneeHingeAngle + 20;
		RkneeHinge->enableAngularMotor(true, 135, -10);
		RhipHinge->enableAngularMotor(true, 40, -5);
		LkneeHinge->enableAngularMotor(true, 135, 20);
		LhipHinge->enableAngularMotor(true, 40, 5);
	}
	else
	{
		RkneeHingeAngle = RkneeHingeAngle - 20;
		LkneeHingeAngle = LkneeHingeAngle + 20;
		RkneeHinge->enableAngularMotor(true, 135, -10);
		RhipHinge->enableAngularMotor(true, 40, -5);
		LkneeHinge->enableAngularMotor(true, 135, 20);
		LhipHinge->enableAngularMotor(true, 40, 5);
	}
	*/
}