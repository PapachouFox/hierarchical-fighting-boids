#pragma once
#include "Vector3.h"
#include <vector>

using namespace std;

class Unit
{
	public:
		Unit(void);
		Unit(Vector3 position);
		Unit(Vector3 position, vector<Unit> &units);
		~Unit(void);
		void Update();

		void SetTarget(Unit * unit);
		void AddUnit(Unit unit);
		void RemoveUnit(Unit unit);
		
		Vector3 GetPosition();

	public:
		Vector3 position;
		Unit * target;
		float speed;
		vector<Unit> units;
};

