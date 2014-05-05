#include "Unit.h"

vector<void*> globalBoids;

Unit::Unit(void)
{
	globalUnits.push_back(this);
	this->globalPos = globalUnits.size();
	this->team = 0;
}

Unit::Unit(Vector3 position, Vector3 velocity, int team, void *data) 
{
	globalUnits.push_back(this);
	this->globalPos = globalUnits.size();
	this->position = position;
	this->team = team;
	this->velocity = velocity;
	this->data = data;
}

Unit::~Unit(void)
{
	for(unsigned int i=0; i<this->units.size(); i++) {
		delete this->units[i];
	}

	globalUnits.erase(globalUnits.begin() + this->globalPos);
}

void Unit::Update(unsigned int deltaTime) {

	//Go to target
	/*if(this->target) {
		if(this->position.Distance(this->target->GetPosition()) > 0) {
			this->position += (*this->target->GetPosition() - this->position).Normalize();
		}
	}*/

	//REYNOLDS
	/*v1 = rule1(b)
	v2 = rule2(b)
	v3 = rule3(b)

	b.velocity = b.velocity + v1 + v2 + v3
	b.position = b.position + b.velocity*/

	Vector3 v1 = Rule1();
	Vector3 v2 = Rule2();
	Vector3 v3 = Rule3();

	this->velocity = this->velocity + v1 + v2 + v3;
	this->position += this->velocity;

	/*for(unsigned int i=0; i<this->units.size(); i++) {
		this->units[i]->Update(deltaTime);
	}*/
}

//boids try to fly towards the centre of mass of neighbouring boids.
Vector3 Unit::Rule1() {
	//Having calculated the perceived centre, we need to work out how to move the boid towards it. 
	//To move it 1% of the way towards the centre (this is about the factor I use) this is given by (pcJ - bJ.position) / 100.
	/*PROCEDURE rule1(boid bJ)
		Vector pcJ
		FOR EACH BOID b
			IF b != bJ THEN
				pcJ = pcJ + b.position
			END IF
		END
		pcJ = pcJ / N-1
		RETURN (pcJ - bJ.position) / 100
	END PROCEDURE*/

	Vector3 pcenter;
	for(unsigned int i=0; i<globalUnits.size(); i++) {
		if(i != this->globalPos) {
			pcenter += *globalUnits[i]->GetPosition();
		}
	}

	pcenter /= (float)(globalUnits.size() - 1);
	return (pcenter - this->position) / (float)100;
}

//boids try to keep a small distance away from other objects (including other boids).
Vector3 Unit::Rule2() { 
	//The purpose of this rule is to for boids to make sure they don't collide into each other. 
	//I simply look at each boid, and if it's within a defined small distance (say 100 units) of another boid move it as far away again as it already is. 
	//This is done by subtracting from a vector c the displacement of each boid which is near by. 
	//We initialise c to zero as we want this rule to give us a vector which when added to the current position moves a boid away from those near it.
	/*PROCEDURE rule2(boid bJ)
		Vector c = 0;
		FOR EACH BOID b
			IF b != bJ THEN
				IF |b.position - bJ.position| < 100 THEN
					c = c - (b.position - bJ.position)
				END IF
			END IF
		END
		RETURN c
	END PROCEDURE*/
	Vector3 c;
	for(unsigned int i=0; i<globalUnits.size(); i++) {
		if(i != this->globalPos) {
			if(this->position.Distance(globalUnits[i]->GetPosition()) < 100) {
				c -= (*globalUnits[i]->GetPosition() - this->position);
			}
		}
	}
	return c;
}

//boids try to match velocity with near boids.
Vector3 Unit::Rule3() {
	//This is similar to Rule 1, however instead of averaging the positions of the other boids we average the velocities. 
	//We calculate a 'perceived velocity', pvJ, then add a small portion (about an eighth) to the boid's current velocity.
	/*PROCEDURE rule3(boid bJ)
		Vector pvJ
		FOR EACH BOID b
			IF b != bJ THEN
				pvJ = pvJ + b.velocity
			END IF
		END
		pvJ = pvJ / N-1
		RETURN (pvJ - bJ.velocity) / 8
	END PROCEDURE*/
	Vector3 pvelocity;
	for(unsigned int i=0; i<globalUnits.size(); i++) {
		if(i != this->globalPos) {
			pvelocity += *globalUnits[i]->GetVelocity();
		}
	}
	pvelocity /= (float)(globalUnits.size() - 1);
	return (pvelocity - this->velocity) / (float)8;
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

