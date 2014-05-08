#include "Simulation.h"

Simulation::Simulation(void)
{

}

Simulation::~Simulation(void)
{
	for(unsigned int i=0; i<this->units.size(); i++) {
		delete this->units[i];
		this->units.erase(this->units.begin() + i);
	}
}

void Simulation::Init() {

}

void Simulation::Clear() {

}

void Simulation::Update(float deltaTime) {
	for(unsigned int i=0; i<this->units.size(); i++) {
		this->units[i]->Update(deltaTime);
	}
}

Unit * Simulation::CreateUnit(Vector3 position, Vector3 velocity, Unit * unit, int team, void *data) {
	return new Unit(position, velocity, unit, team, data);
}

void Simulation::AddUnit(Unit *unit) {
	this->units.push_back(unit);
}

vector<Unit*> * Simulation::GetAllUnits() {
    return &Unit::globalUnits;
}

vector<Unit*> * Simulation::GetUnits() {
	return &this->units;
}
