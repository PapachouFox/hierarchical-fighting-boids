#pragma once
#include "Vector3.h"
#include "IProjectileCallback.h"
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
        void SetTarget(Unit* p_target);
		void * GetData();
		void CreateProjectile();
        void SetCallbackFunction(IProjectileCallback* p_ProjCallback);

        Vector3 m_position;
        float m_speed;
        Unit* m_target;

	private:
        IProjectileCallback* m_projCallback;
        vector<Unit*> m_units;
        Vector3 m_velocity;
        void* m_data;
        Unit* m_lead;

        Vector3 Center(vector<Unit*>& p_flock);
        Vector3 Avoid(vector<Unit*>& p_flock);
        Vector3 Speed(vector<Unit*>& p_flock);
};

