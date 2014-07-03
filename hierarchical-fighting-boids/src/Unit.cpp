#include "Unit.h"

Unit::Unit(void){
    this->m_lead = NULL;
    this->m_target = NULL;
}

Unit::Unit(Vector3 position, Vector3 velocity, void *data){
    this->m_position = position;
    this->m_velocity = velocity;
    this->m_data = data;
    this->m_speed = 0.0005f;
    this->m_lead = NULL;
    this->m_target = NULL;
	this->m_callbackFunc = NULL;
}

Unit::~Unit(void){
    for(unsigned int i=0; i<this->m_units.size(); i++) {
        delete this->m_units[i];
        this->m_units.erase(this->m_units.begin() + i);
	}
}

void Unit::Update(float deltaTime, vector<Unit*> p_flock) {
    if(this->m_lead != NULL){
        Vector3 steer = (this->m_lead != NULL)?this->m_lead->m_position - this->m_position:Vector3();

        Vector3 prevVelocity = this->m_velocity;
		if(this->m_target != NULL){
			//move thowards target
			this->m_velocity += (this->m_target->m_position - this->m_position).Normalize();
		}
        this->m_velocity += (this->Center(p_flock)+this->Avoid(p_flock)+steer*10.f).Normalize();
        if((this->m_velocity.X + this->m_velocity.Y + this->m_velocity.Z) > 20.f)
            this->m_velocity = prevVelocity;

		//find a new target
		if(this->m_lead->m_target != NULL){
			auto units = this->m_lead->m_target->GetRootUnits();
			unsigned int closestIndex = 0;
			float minDistance = 100.f;
			for(unsigned int i = 0; i < units.size(); i++){
				if(units[i]->m_position.Distance(this->m_position) < minDistance) closestIndex = i;
				minDistance = units[i]->m_position.Distance(this->m_position);
			}
			this->m_target = units[closestIndex];
		}

		this->m_position += this->m_velocity * this->m_speed * deltaTime;

    }else{ //squad leader movement
        //go to the current target
        //if target is too close, flee

        Vector3 prevVelocity = this->m_velocity;

        if(this->m_position.Distance(this->m_target->m_position) < 200){
            this->m_velocity += ((this->m_position - this->m_target->m_position)).Normalize();
        }else{
            this->m_velocity += ((this->m_target->m_position - this->m_position)).Normalize();
        }

        if((this->m_velocity.X + this->m_velocity.Y + this->m_velocity.Z) > 10.f)
            this->m_velocity = prevVelocity;

        this->m_position += this->m_velocity * this->m_speed * deltaTime;
    }

    for(unsigned int i = 0; i < this->m_units.size(); i++){
        this->m_units[i]->Update(deltaTime, this->m_units);
    }
}

Vector3 Unit::Center(vector<Unit*>& p_flock){
    if(p_flock.size() == 0) return Vector3();

    Vector3 center;
    for(unsigned int i = 0; i < p_flock.size(); i++){
        if(p_flock[i] != this){
            center += p_flock[i]->m_position;
        }
    }
    center /= p_flock.size()-1;

    return (center - this->m_position);
}

Vector3 Unit::Avoid(vector<Unit*>& p_flock){
    if(p_flock.size() == 0) return Vector3();
    float maxDistance = 10.f;

    Vector3 move;
    for(unsigned int i = 0; i < p_flock.size(); i++){
         if(p_flock[i] != this){
             if(p_flock[i]->m_position.Distance(this->m_position) < maxDistance){
                move += this->m_position - p_flock[i]->m_position;
             }
         }
    }

    return move;
}

Vector3 Unit::Speed(vector<Unit*>& p_flock){
    if(p_flock.size() == 0) return Vector3();

    Vector3 velocity;
    for(unsigned int i = 0; i < p_flock.size(); i++){
         if(p_flock[i] != this){
            velocity += p_flock[i]->m_velocity;
         }
    }
    velocity /= p_flock.size()-1;

    return (velocity - this->m_velocity)/10.f;
}

void Unit::SetLeader(Unit* p_lead){
    this->m_lead = p_lead;
}

void* Unit::GetData() {
    return this->m_data;
}

void Unit::AddUnit(Unit *unit) {
    unit->SetLeader(this);
    this->m_units.push_back(unit);
}

vector<Unit*> Unit::GetRootUnits() {
    return this->m_units;
}

void Unit::SetTarget(Unit* p_target){
    this->m_target = p_target;
}

void Unit::SetCallbackFunction(callbackFunction p_callback) {
	this->m_callbackFunc = p_callback;
}

void Unit::CreateProjectile() {
	this->m_callbackFunc();
}