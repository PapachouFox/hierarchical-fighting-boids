#include "Unit.h"

vector<void*> globalBoids;
vector<Unit*> Unit::globalUnits;

Unit::Unit(void)
{
	globalUnits.push_back(this);
	this->team = 0;
}

Unit::Unit(Vector3 position, Vector3 velocity, Unit * leader, int team, void *data) 
{
	globalUnits.push_back(this);
	this->position = position;
	this->velocity = velocity;
	this->leader = leader;
	this->team = team;
	this->data = data;
	this->maxSpeed = 5;
	this->maxSteeringForce = 0.05f;
	this->test = true;
	if(leader == NULL)
		this->target = Vector3(40.f, 20.f, 0.f);
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
	if(this->leader == NULL) {		
		Vector3 v1 = Vector3(40.f, 20.f, 0.f);
		Vector3 v2 = Vector3(-40.f, -20.f, 0.f);
		if(this->test && this->position.Distance(&v1) < 2) {
			this->test = false;
			target = v2;
		} else if (!this->test && this->position.Distance(&v2) < 2) {
			this->test = true;
			target = v1;
		}
		this->ApplyForce(this->Seek(this->target));
	} else {
		this->Flock(this->leader->GetUnits(), deltaTime);
		this->ApplyForce(this->Seek(this->leader->GetPosition()) * 3.0f);
	}			
	this->Move(deltaTime);
	//this->Border();
}

void Unit::Flock(vector<Unit*> flock, float deltaTime) {
	Vector3 separation = this->Separation(flock);
	Vector3 alignment = this->Alignment(flock);
	Vector3 cohesion = this->Cohesion(flock);

	separation *= 5.0f;
	alignment *= 1.0f;
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

Vector3 Unit::Separation(vector<Unit*> flock) {
	float desiredSeparation = 3.0f;
	Vector3 steer;
	int count = 0;

	for(unsigned int i=0; i<flock.size(); i++) {
		float d = this->position.Distance(flock[i]->GetPosition());
		if((d > 0) && (d < desiredSeparation)) {
			Vector3 diff = this->position - flock[i]->GetPosition();
			diff.Normalize();
			diff /= d;
			steer += diff;
			count++;
		}
	}

	if(this->leader != NULL) {
		float d = this->position.Distance(this->leader->GetPosition());
		if((d > 0) && (d < desiredSeparation)) {
			Vector3 diff = this->position - this->leader->GetPosition();
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

Vector3 Unit::Alignment(vector<Unit*> flock) {
	float neighborDistance = 8.f;
	Vector3 alignment;
	int count = 0;

	for(unsigned int i=0; i<flock.size(); i++) {
		float d = this->position.Distance(flock[i]->GetPosition());
		if((d > 0) && (d < neighborDistance)) {
			alignment += flock[i]->GetVelocity();
			count++;
		}
	}

	if(this->leader != NULL) {
		float d = this->position.Distance(this->leader->GetPosition());
		if((d > 0) && (d < neighborDistance)) {
			alignment += this->leader->GetVelocity();
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

Vector3 Unit::Cohesion(vector<Unit*> flock) {
	float neighborDistance = 20.f;
	Vector3 cohesion;
	int count = 0;

	for(unsigned int i=0; i<flock.size(); i++) {
		float d = this->position.Distance(flock[i]->GetPosition());
		if((d > 0) && (d < neighborDistance)) {
			cohesion += flock[i]->GetPosition();
			count++;
		}
	}

	if(this->leader != NULL) {
		float d = this->position.Distance(this->leader->GetPosition());
		if((d > 0) && (d < neighborDistance)) {
			cohesion += this->leader->GetPosition();
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

void Unit::AddUnit(Unit *unit) {
	this->units.push_back(unit);
}

vector<Unit*> Unit::GetUnits() {
	return this->units;
}

