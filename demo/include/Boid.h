#pragma once
#include <irrlicht/irrlicht.h>

class Boid{
public:
    Boid(irr::scene::ISceneManager* pSmgr);
    ~Boid();
    void setPosition(const irr::core::vector3df &pNewpos);
    void setOrientation(const irr::core::vector2df &pNeworientation);
private:
    irr::scene::ISceneManager* mSmgr;
    irr::scene::IMeshSceneNode* mCube;
};
