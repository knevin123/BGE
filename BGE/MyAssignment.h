#pragma once
#include "Game.h"
#include "GameComponent.h"
#include "FountainEffect.h"

using namespace std;

namespace BGE
{
	class MyAssignment :
		public Game
	{
	public:
		MyAssignment(void);
		~MyAssignment(void);

		shared_ptr<PhysicsController> CreateAnimal(glm::vec3);
		shared_ptr<PhysicsController> CreateAnimal1(glm::vec3);
		shared_ptr<PhysicsController> CreateAnimal2(glm::vec3);
		shared_ptr<PhysicsController> CreateAnimal3(glm::vec3);

		float turnRate;
		float toRotate;
		float elapsed;
		bool Initialise();
		void Update(float timeDelta);
		bool slerping;
		glm::quat fromQuaternion;
		glm::quat toQuaternion;
		float scale;
		glm::vec3 pos;
		float t;
	};
}