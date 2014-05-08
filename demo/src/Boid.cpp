#include "Boid.h"
#include <iostream>

Boid::Boid(irr::scene::ISceneManager* pSmgr, float size){
    this->mSmgr = pSmgr;
    this->mCube = this->mSmgr->addCubeSceneNode(size);
}

Boid::~Boid(){

}

void Boid::setPosition(const irr::core::vector3df &pNewpos){
    this->mCube->setPosition(pNewpos);
}

void Boid::setOrientation(const irr::core::vector2df &pNeworientation){
    //this->mCube->setRotation(pNeworientation);
}
