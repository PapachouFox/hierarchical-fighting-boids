#pragma once
#include "Vector3.h"
#include <vector>

using namespace std;

class Unit
{
	public:
		Unit(void);
		Unit(Vector3 position, Vector3 velocity, Unit * leader, int team, void *data);
		~Unit(void);

		void Update(float deltaTime);
		void Flock(vector<Unit*> flock, float deltaTime);
		void Move(float deltaTime);
		void Border();		
		void ApplyForce(Vector3 force);

		Vector3 Separation(vector<Unit*> flock);
		Vector3 Alignment(vector<Unit*> flock);
		Vector3 Cohesion(vector<Unit*> flock);
		Vector3 Seek(Vector3& target);
		
		Vector3 * GetVelocity();
		vector<Unit*> GetUnits();
		void AddUnit(Unit *unit);
		void * GetData();

		Vector3 position;
		static vector<Unit*> globalUnits;
	private:
		vector<Unit*> units;
		Unit * leader;

		Vector3 velocity;
		Vector3 acceleration;

		float maxSteeringForce;
		float maxSpeed;

		int team;
		void *data;

		bool test;
		Vector3 target;
};

