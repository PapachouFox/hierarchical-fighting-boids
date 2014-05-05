#include "Simulation.h"

Simulation::Simulation(void)
{

}

Simulation::~Simulation(void)
{
	for(unsigned int i=0; i<this->units.size(); i++) {
		delete this->units[i];
	}
}

void Simulation::Init() {

}

void Simulation::Clear() {

}

void Simulation::Update(unsigned int deltaTime) {
	for(unsigned int i=0; i<this->units.size(); i++) {
		this->units[i]->Update(deltaTime);
	}
}

Unit * Simulation::CreateUnit(Vector3 position, Vector3 velocity, int team) {
	return new Unit(position, velocity, team);
}

void Simulation::AddUnit(Unit *unit) {
	this->units.push_back(unit);
}

vector<Unit*> * Simulation::GetUnits() {
	return &this->units;
}
