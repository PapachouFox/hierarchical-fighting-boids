#pragma once
#include "Vector3.h"
#include <vector>

#ifndef NULL
#define NULL 0
#endif
using namespace std;

class Unit
{
	public:
		Unit(void);
        Unit(Vector3 position, Vector3 velocity, void *data);
		~Unit(void);

        void Update(float deltaTime, vector<Unit*> p_flock);

        vector<Unit*> GetRootUnits();
        void AddUnit(Unit *unit);
        void SetLeader(Unit* p_lead);
		void * GetData();

        Vector3 m_position;
        float m_speed;
	private:
        vector<Unit*> m_units;
        Vector3 m_velocity;
        void* m_data;
        Unit* m_lead;

        Vector3 Center(vector<Unit*>& p_flock);
        Vector3 Avoid(vector<Unit*>& p_flock);
        Vector3 Speed(vector<Unit*>& p_flock);
};

