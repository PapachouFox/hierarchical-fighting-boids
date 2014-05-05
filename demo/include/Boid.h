#pragma once
#include <irrlicht/irrlicht.h>

class Boid{
public:
    Boid(irr::scene::ISceneManager* pSmgr);
    ~Boid();
private:
    irr::scene::ISceneManager* mSmgr;
};
