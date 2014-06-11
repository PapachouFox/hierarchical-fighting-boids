#pragma once
#include <irrlicht/irrlicht.h>

class Boid{
public:
    Boid(irr::scene::ISceneManager* pSmgr, float size);
    ~Boid();
    void setPosition(const irr::core::vector3df &pNewpos);
    void setOrientation(const irr::core::vector3df &pDirection);
    void setColor(int r, int g, int b);
    irr::scene::ISceneNode* getSceneNode();
private:
    irr::scene::ISceneManager* mSmgr;
    irr::scene::IMeshSceneNode* mCube;
};
