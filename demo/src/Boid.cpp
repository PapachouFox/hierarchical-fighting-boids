#include "Boid.h"
#include <iostream>

Boid::Boid(irr::scene::ISceneManager* pSmgr, float size){
    this->mSmgr = pSmgr;
    irr::scene::IAnimatedMesh* mesh = pSmgr->getMesh("../resources/models/spaceship.coyhot.3ds");
    this->mCube = pSmgr->addMeshSceneNode(mesh);
    if(size >= 10){
        this->mCube->setScale(irr::core::vector3df(size, size, size));
    }
}

Boid::~Boid(){

}

void Boid::setColor(int r, int g, int b){
	this->mColor = irr::video::SColor(255,r,g,b);
    this->mCube->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    this->mCube->getMaterial(0).DiffuseColor.set(0,0,0,0);
    this->mCube->getMaterial(0).AmbientColor.set(0,0,0,0);
    this->mCube->getMaterial(0).SpecularColor.set(0,0,0,0);
    this->mCube->getMaterial(0).EmissiveColor.set(255,r,g,b);
}

void Boid::setPosition(const irr::core::vector3df &pNewpos){
    this->mCube->setPosition(pNewpos);
}

void Boid::setOrientation(const irr::core::vector3df &pDirection){
    if ( !this->mCube ) return;
    irr::core::vector3df rot, dif = this->mCube->getPosition() - pDirection;
    rot.Y = atan2( dif.X, dif.Z ) * 180.f / irr::core::PI;
    rot.X = -atan2( dif.Y, sqrt( dif.X * dif.X + dif.Z * dif.Z ) ) * 180.f / irr::core::PI;
    this->mCube->setRotation( rot );
}

irr::scene::ISceneNode* Boid::getSceneNode(){
    return this->mCube;
}

irr::video::SColor Boid::getColor() {
	return this->mColor;
}
