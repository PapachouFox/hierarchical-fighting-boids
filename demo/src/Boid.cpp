#include "Boid.h"
#include <iostream>

Boid::Boid(irr::scene::ISceneManager* pSmgr, float size){
    this->mSmgr = pSmgr;
    this->mCube = this->mSmgr->addCubeSceneNode(size);
}

Boid::~Boid(){

}

void Boid::setColor(int r, int g, int b){
    this->mCube->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    this->mCube->getMaterial(0).DiffuseColor.set(0,0,0,0);
    this->mCube->getMaterial(0).AmbientColor.set(0,0,0,0);
    this->mCube->getMaterial(0).SpecularColor.set(0,0,0,0);
    this->mCube->getMaterial(0).EmissiveColor.set(255,r,g,b);
}

void Boid::setPosition(const irr::core::vector3df &pNewpos){
    this->mCube->setPosition(pNewpos);
}

void Boid::setOrientation(const irr::core::vector2df &pNeworientation){
    //this->mCube->setRotation(pNeworientation);
}
