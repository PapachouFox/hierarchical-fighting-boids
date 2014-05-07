#include "Unit.h"

vector<void*> globalBoids;
vector<Unit*> Unit::globalUnits;

Unit::Unit(void)
{
	globalUnits.push_back(this);
	this->team = 0;
}

Unit::Unit(Vector3 position, Vector3 velocity, int team, void *data) 
{
	globalUnits.push_back(this);
	this->position = position;
	this->team = team;
	this->velocity = velocity;
	this->data = data;
}

Unit::~Unit(void)
{
	for(unsigned int i=0; i<this->units.size(); i++) {
		delete this->units[i];
		this->units.erase(this->units.begin() + i);
	}

	for(unsigned int j=0; j<globalUnits.size(); j++) {
		if(this == globalUnits[j]) {			
			globalUnits.erase(globalUnits.begin() + j);
			break;
		}
	}
}

void Unit::Update(float deltaTime) {
	this->position = this->position + this->velocity * deltaTime / 500;
}

void Unit::SetTarget(Unit *target) {
	this->target = target;
}

void Unit::SetVelocity(Vector3 velocity) {
	this->velocity = velocity;
}

void Unit::AddUnit(Unit *unit) {
	this->units.push_back(unit);
}

void Unit::RemoveUnit() {
	//this->units.pop_back();
}

//void Unit::SetPosition(Vector3 position) {
//	this->position = position;
//}

Vector3 * Unit::GetPosition() {
	return &this->position;
}

Vector3 * Unit::GetVelocity() {
	return &this->velocity;
}

void * Unit::GetData() {
	return this->data;
}

vector<Unit*> Unit::GetUnits() {
	return this->units;
}

