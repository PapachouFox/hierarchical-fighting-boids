#pragma once
#include "Vector3.h"
#include <vector>

using namespace std;

class Unit
{
	public:
		Unit(void);
		Unit(Vector3 position, Vector3 velocity, int team, void *data);
		~Unit(void);

		void Update(float deltaTime);
		void Flock(float deltaTime);
		void Move(float deltaTime);
		void Border();		
		void ApplyForce(Vector3 force);

		Vector3 Separation();
		Vector3 Alignment();
		Vector3 Cohesion();
		Vector3 Seek(Vector3 target);

		
		vector<Unit*> GetUnits();
		Vector3 * GetPosition();
		Vector3 * GetVelocity();
		void * GetData();

	public:
        static vector<Unit*> globalUnits;		
		vector<Unit*> units;

		Vector3 position;
		Vector3 velocity;
		Vector3 acceleration;

		float maxSteeringForce;
		float maxSpeed;

		int team;
		void *data;
};

