#pragma once
#include <irrlicht/irrlicht.h>
#include "Boid.h"
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

private:
  GAME_STATE state;
  void init();
  IrrlichtDevice *device;
  scene::ISceneManager *smgr;
  video::IVideoDriver* driver;
  gui::IGUIEnvironment* guienv;
};
