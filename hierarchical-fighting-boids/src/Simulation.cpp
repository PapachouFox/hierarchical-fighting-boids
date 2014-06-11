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
    //root unit IA
    for(unsigned int i=0; i<this->m_units.size(); i++) {
        //basic IA: chase closest high level enemy
        unsigned int chaseIndex = 0;
        unsigned int minDistance = 10000000;
        for(unsigned int j=0; j<this->m_units.size(); j++) {
            if(i!=j){
                float dist = this->m_units[i]->m_position.Distance(this->m_units[j]->m_position);
                if(dist < minDistance){
                    minDistance = dist;
                    chaseIndex = j;
                }
            }
        }
        if(i != chaseIndex)
            this->m_units[i]->SetTarget(this->m_units[chaseIndex]);
    }

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
