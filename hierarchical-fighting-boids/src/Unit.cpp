#include "Unit.h"

Unit::Unit(void)
{
	this->position = Vector3(0, 0, 0);
	this->speed = 0;
}

Unit::Unit(Vector3 position) 
{
	this->position = position;
	this->speed = 0;
}

Unit::Unit(Vector3 position, vector<Unit>& _units) {
	this->position = position;
	this->speed = 0;
	this->units = _units;
}

Unit::~Unit(void)
{
}

void Unit::Update() {

}

Vector3 Unit::GetPosition() {
	return this->position;
}

void Unit::SetTarget(Unit * target) {
	this->target = target;
}

void Unit::AddUnit(Unit unit) {
	this->units.push_back(unit);
}

void Unit::RemoveUnit(Unit unit) {
	this->units.pop_back();
}