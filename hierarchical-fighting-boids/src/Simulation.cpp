#include "Simulation.h"

Simulation::Simulation(void){

}

Simulation::~Simulation(void){
    for(unsigned int i=0; i<this->m_units.size(); i++) {
        delete this->m_units[i];
        this->m_units.erase(this->m_units.begin() + i);
	}
}

void Simulation::Init() {

}

void Simulation::Clear() {

}

void Simulation::Update(float deltaTime) {
    for(unsigned int i=0; i<this->m_units.size(); i++) {
        this->m_units[i]->Update(deltaTime, this->m_units);
	}
}

Unit * Simulation::CreateUnit(Vector3 position, Vector3 velocity, void *data) {
    return new Unit(position, velocity, data);
}

void Simulation::AddUnit(Unit *unit) {
    this->m_units.push_back(unit);
}

vector<Unit*> Simulation::GetAllUnits() {
    vector<Unit*> units = this->m_units;
    for(unsigned int i = 0; i < this->m_units.size(); i++){
        vector<Unit*> toInsert = this->m_units[i]->GetRootUnits();
        units.insert(units.end(), toInsert.begin(), toInsert.end());
    }
    return units;
}

vector<Unit*> Simulation::GetRootUnits() {
    return this->m_units;
}
