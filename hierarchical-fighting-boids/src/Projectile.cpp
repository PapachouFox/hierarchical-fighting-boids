#include "Projectile.h"

Projectile::Projectile(void)
{
}

Projectile::Projectile(Vector3 position, Vector3 velocity){
	this->m_position = position;
    this->m_velocity = velocity;
    this->m_speed = 0.0005f;
    this->ttl = 3000;
}

Projectile::~Projectile(void)
{
}

void Projectile::Update(float deltaTime) {
	this->m_position += this->m_velocity * this->m_speed * deltaTime;
}