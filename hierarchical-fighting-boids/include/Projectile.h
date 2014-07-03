#pragma once
#include "Vector3.h"

class Projectile
{
	public:
		Projectile(void);
		Projectile(Vector3 position, Vector3 velocity);
		~Projectile(void);
		
		void Update(float deltaTime);
		
		Vector3 m_position;
		float m_speed;
        Vector3 m_velocity;
        float ttl;
	private:
        
};

