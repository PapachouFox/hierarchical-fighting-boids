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
		void Update(unsigned int deltaTime);
		void SetTarget(Unit *target);
		void AddUnit(Unit *unit);
		void RemoveUnit();
		//void SetPosition(Vector3 position);
		void SetVelocity(Vector3 velocity);

		Vector3 Rule1();
		Vector3 Rule2();
		Vector3 Rule3();

		Vector3 * GetPosition();
		Vector3 * GetVelocity();
		void * GetData();
		vector<Unit*> GetUnits();

	public:
		Vector3 position;
		Vector3 velocity;
		int team;
		Unit * target;
		vector<Unit*> units;
		void *data;
};

static vector<Unit*> globalUnits;


