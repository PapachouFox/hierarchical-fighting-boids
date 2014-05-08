#pragma once
#include <irrlicht/irrlicht.h>
#include "Boid.h"
#include "Simulation.h"

using namespace irr;

enum GAME_STATE{
    DEMO_INIT,
    DEMO_RUN,
    DEMO_QUIT
};

class Application{
public:
  Application();
  ~Application();
  bool run();
  void CreateBoids(int number, std::vector<Boid*> *boids, Simulation *sim, Vector3 position);

private:
  GAME_STATE state;
  void init();
  IrrlichtDevice *device;
  scene::ISceneManager *smgr;
  video::IVideoDriver* driver;
  gui::IGUIEnvironment* guienv;
};
