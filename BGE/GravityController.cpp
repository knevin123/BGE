#include "GravityController.h"
#include "Utils.h"


BGE::GravityController::GravityController()
{
	gravity = glm::vec3(0.0f, -9.8f, 0.0f);
}


BGE::GravityController::~GravityController()
{
}

void BGE::GravityController::Update(float timeDelta)
{
	transform->velocity += gravity * timeDelta;
	transform->position += transform->velocity * timeDelta;

	if (transform->position.y - transform->scale.x < 0)
	{
		transform->velocity = -transform->velocity;
		transform->position.y = transform->scale.y;
	}
}