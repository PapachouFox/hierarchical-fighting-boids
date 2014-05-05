#include "Boid.h"

Boid::Boid(irr::scene::ISceneManager* pSmgr){
    this->mSmgr = pSmgr;
    this->mSmgr->addCubeSceneNode(1.f);
}

Boid::~Boid(){

}
