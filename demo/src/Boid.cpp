#include "Boid.h"
#include <iostream>

Boid::Boid(irr::scene::ISceneManager* pSmgr){
    this->mSmgr = pSmgr;
    this->mCube = this->mSmgr->addCubeSceneNode(1.f);
}

Boid::~Boid(){

}

void Boid::setPosition(const irr::core::vector3df &pNewpos){
    this->mCube->setPosition(pNewpos);
}

void Boid::setOrientation(const irr::core::vector2df &pNeworientation){
    //this->mCube->setRotation(pNeworientation);
}
