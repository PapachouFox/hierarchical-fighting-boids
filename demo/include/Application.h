#pragma once
#include <irrlicht/irrlicht.h>
#include <time.h>
#include "Boid.h"
#include "IProjectileCallback.h"
#include "Simulation.h"

using namespace irr;

enum GAME_STATE{
    DEMO_INIT,
    DEMO_RUN,
    DEMO_QUIT
};

class Application: public IProjectileCallback{
public:
    Application();
    ~Application();
    bool run();
    void CreateBoids(int number, int numberSubUnit, float size, std::vector<Boid*> &boids, Simulation &sim, Unit* parent, int pr, int pg, int pb);
    void SetCameraTarget(Boid* boid);
    void ProjectileCallback();
private:
    GAME_STATE state;
    void init();
    IrrlichtDevice *device;
    scene::ISceneManager *smgr;
    video::IVideoDriver* driver;
    gui::IGUIEnvironment* guienv;
};
