#pragma once
#include "Unit.h"
#include <vector>

using namespace std;

class Simulation
{
	public:
		Simulation(void);
		~Simulation(void);
		void Init();
		void Update(unsigned int deltaTime);
		void Clear();

		Unit * CreateUnit(Vector3 position,  Vector3 velocity, int team);
		void AddUnit(Unit *unit);
		
		vector<Unit*> * GetUnits();

	private:
		vector<Unit*> units;

};

