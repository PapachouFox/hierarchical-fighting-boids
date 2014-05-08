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
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 30.0f, 0.05f);
    camera->setTarget(core::vector3df(0., 0., 0.));
    camera->setPosition(core::vector3df(0., 0., -70.));
    camera->setFarValue(300.f);
    video::ITexture* text = driver->getTexture("../textures/ESO_-_Milky_Way_Bottom.bmp");
    scene::ISceneNode* skybox = smgr->addSkyBoxSceneNode(text,text,text,text,text,text);
}

#include <iostream>
#include <time.h>

bool Application::run(){
    if(!device){
        return false;
    }

    Simulation sim;
    sim.Init();

    std::vector<Boid*> boids;
	this->CreateBoids(1, 20, 3, NULL, &boids, &sim, Vector3(0.f, 0.f, 0.f));
	/*this->CreateBoids(150, &boids, &sim, Vector3(0.f, 0.f, 0.f));	
	this->CreateBoids(50, &boids, &sim, Vector3(40.f, 0.f, 0.f));*/

    ITimer* irrTimer = device->getTimer();
    u32 TimeStamp = irrTimer->getTime();
	float DeltaTime = 0;
    while(device->run()){
        DeltaTime = irrTimer->getTime() - TimeStamp;
        TimeStamp = irrTimer->getTime();

        sim.Update(DeltaTime);
        vector<Unit*>* list = sim.GetAllUnits();
        for(unsigned int i = 0; i < list->size(); i++){
            Vector3 pos = list->at(i)->GetPosition();
            ((Boid*)list->at(i)->GetData())->setPosition(core::vector3df(pos.X, pos.Y, pos.Z));
        }

        driver->beginScene();
        smgr->drawAll();
        driver->endScene();
    }

    for(unsigned int i = 0; i < boids.size(); i++){
        delete boids[i];
    }
    sim.Clear();
    return true;
}

void Application::CreateBoids(int number, int numberSubUnit, float size, Unit * leader, std::vector<Boid*> *boids, Simulation *sim, Vector3 position) {
	for(int i = 0; i < number; i++){
        Boid* monBoid = new Boid(smgr, size);
        boids->push_back(monBoid);
		float t1 = (rand()%10 > 5) ? -1.f : 1.f;
		float t2 = (rand()%10 > 5) ? -1.f : 1.f;
		float t3 = (rand()%10 > 5) ? -1.f : 1.f;

		float x = (float)((double)rand() / (RAND_MAX) + 2) * t1;
		float y = (float)((double)rand() / (RAND_MAX) + 2) * t2;
		float z = 0.f;

		Unit * unit = sim->CreateUnit(position, Vector3(x, y, z), leader, 0, monBoid);		
		sim->AddUnit(unit);
		if(leader != NULL)
			leader->AddUnit(unit);

		if(numberSubUnit > 0)
			this->CreateBoids(numberSubUnit, 0, 1, unit, boids, sim, Vector3(x, y, z));
    }
}
