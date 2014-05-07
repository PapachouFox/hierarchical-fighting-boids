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
		void SetTarget(Unit *target);
		void AddUnit(Unit *unit);
		void RemoveUnit();
		void SetVelocity(Vector3 velocity);

		Vector3 * GetPosition();
		Vector3 * GetVelocity();
		void * GetData();
		vector<Unit*> GetUnits();

	public:
        static vector<Unit*> globalUnits;
		Vector3 position;
		Vector3 velocity;
		int team;
		Unit * target;
		vector<Unit*> units;
		void *data;
};

