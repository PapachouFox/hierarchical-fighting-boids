#pragma once
#include "Unit.h"
#include <vector>

using namespace std;

class Simulation
{
	public:
		Simulation(void);
		~Simulation(void);
		void Update();
		void GetSimulationData(vector<Unit>& boidsList);

};

