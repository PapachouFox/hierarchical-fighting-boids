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
	this->maxSpeed = 5;
	this->maxSteeringForce = 0.05f;
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
	this->Flock(deltaTime);
	//this->ApplyForce(this->Seek(Vector3(0.f, 0.f, 0.f)));
	this->Move(deltaTime);
	//this->Border();
}

void Unit::Flock(float deltaTime) {
	Vector3 separation = this->Separation();
	Vector3 alignment = this->Alignment();
	Vector3 cohesion = this->Cohesion();

	separation *= 5.0f;
	alignment *= 0.8f;
	cohesion *= 1.0f;

	this->ApplyForce(separation);
	this->ApplyForce(alignment);
	this->ApplyForce(cohesion);
}

void Unit::ApplyForce(Vector3 force) {
	this->acceleration += force;
}

void Unit::Move(float deltaTime) {
	this->velocity += this->acceleration ;
	this->velocity.Limit(this->maxSpeed);
	this->position += this->velocity * deltaTime / 500;
	this->acceleration *= 0;
}

Vector3 Unit::Separation() {
	float desiredSeparation = 2.0f;
	Vector3 steer;
	int count = 0;

	for(unsigned int i=0; i<globalUnits.size(); i++) {
		float d = this->position.Distance(globalUnits[i]->GetPosition());
		if((d > 0) && (d < desiredSeparation)) {
			Vector3 diff = this->position - globalUnits[i]->GetPosition();
			diff.Normalize();
			diff /= d;
			steer += diff;
			count++;
		}
	}

	if(count > 0) {
		steer /= (float)count;
	}

	if(steer.Length() > 0) {
		steer.Normalize();
		steer *= this->maxSpeed;
		steer -= this->velocity;
		steer.Limit(this->maxSteeringForce);
	}

	return steer;
}

Vector3 Unit::Alignment() {
	float neighborDistance = 8.f;
	Vector3 alignment;
	int count = 0;

	for(unsigned int i=0; i<globalUnits.size(); i++) {
		float d = this->position.Distance(globalUnits[i]->GetPosition());
		if((d > 0) && (d < neighborDistance)) {
			alignment += globalUnits[i]->GetVelocity();
			count++;
		}
	}

	if(count > 0) {
		alignment /= (float)count;
		alignment.Normalize();
		alignment *= this->maxSpeed;
		Vector3 steer = alignment - this->velocity;
		steer.Limit(this->maxSteeringForce);
		return steer;
	} else {
		Vector3 v;
		return v;
	}

	return alignment;
}

Vector3 Unit::Cohesion() {
	float neighborDistance = 20.f;
	Vector3 cohesion;
	int count = 0;

	for(unsigned int i=0; i<globalUnits.size(); i++) {
		float d = this->position.Distance(globalUnits[i]->GetPosition());
		if((d > 0) && (d < neighborDistance)) {
			cohesion += globalUnits[i]->GetPosition();
			count++;
		}
	}

	if(count > 0) {
		cohesion /= (float)count;
		return this->Seek(cohesion);
	} else {
		Vector3 v;
		return v;
	}
}

Vector3 Unit::Seek(Vector3 target) {
	Vector3 desired = target - this->position;
	desired.Normalize();
	desired *= this->maxSpeed;

	Vector3 steer = desired - this->velocity;
	steer.Limit(this->maxSteeringForce);
	return steer;
}

void Unit::Border() {
	if(this->position.X < -50) this->position.X = 50;
	if(this->position.Y < -50) this->position.Y = 50;
	if(this->position.Z < -50) this->position.Z = 50;
	if(this->position.X > 50) this->position.X = -50;
	if(this->position.Y > 50) this->position.Y = -50;
	if(this->position.Z > 50) this->position.Z = -50;
}

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

