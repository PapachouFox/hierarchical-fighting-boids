#include "Application.h"

Application::Application(){
    device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 32, false, true);
    if (device){
        device->setWindowCaption(L"Boids Demo - 0.1");

        //irrlicht managers
        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        guienv = device->getGUIEnvironment();
        smgr->setAmbientLight(video::SColorf(0.1f,0.1f,0.1f,1.f));
        smgr->setShadowColor(video::SColor(150,0,0,0));

        device->getCursorControl()->setVisible(false);
        init();

        state = DEMO_INIT;
    }
}

Application::~Application(){
    if(device){
        device->drop();
    }
}

void Application::init(){
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 20.0f, 0.01f);
    camera->setTarget(core::vector3df(0., 0., 0.));
    camera->setPosition(core::vector3df(0., 0., -20.));
    camera->setFarValue(100.f);
    video::ITexture* text = driver->getTexture("../textures/ESO_-_Milky_Way_Bottom.bmp");
    scene::ISceneNode* skybox = smgr->addSkyBoxSceneNode(text,text,text,text,text,text);
    Boid* myBoid = new Boid(smgr);
}

bool Application::run(){
    if(!device){
        return false;
    }

    /*
    Boid monBoid;
    Boid monBoid2;

    Simulation sim;
    sim.init({params});

    Unit* unit = sim.createUnit(&monBoid);
    sim.addUnit(unit);
    unit.addUnit(sim.createUnit(&monBoid2));
    */

    ITimer* irrTimer = device->getTimer();
    u32 TimeStamp = irrTimer->getTime(), DeltaTime = 0;
    while(device->run()){
        DeltaTime = irrTimer->getTime() - TimeStamp;
        TimeStamp = irrTimer->getTime();

        /*
        sim.update(DeltaTime);

        vector<Unit> unitList = sim.getSimulationData();
        Boid* b = ((Boid*)(unitList[0].data));
        b->setPosition(unitList[0].position);
        if(b->getPosition().x > 100){
            b->drop();
        }*/

        driver->beginScene();
        smgr->drawAll();
        driver->endScene();
    }

    //sim.drop();

    return true;
}
