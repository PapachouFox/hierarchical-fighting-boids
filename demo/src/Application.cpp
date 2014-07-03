#include "Application.h"

Application::Application(){
    device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(1920, 1080), 32, true, false);
    if (device){
        device->setWindowCaption(L"Boids Demo - 0.1");

        //irrlicht managers
        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        guienv = device->getGUIEnvironment();
        smgr->setAmbientLight(video::SColorf(0.1f,0.1f,0.1f,1.f));
        smgr->setShadowColor(video::SColor(150,0,0,0));
		font = device->getGUIEnvironment()->getFont("../resources/fonts/myfont.bmp");
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
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 30.0f, 0.4f);
    camera->setTarget(core::vector3df(0., 0., 0.));
    camera->setPosition(core::vector3df(0., 0., -70.));
    camera->setFarValue(5000.f);
    video::ITexture* text = driver->getTexture("../resources/textures/skybox_bottom.bmp");
    scene::ISceneNode* skybox = smgr->addSkyBoxSceneNode(text,text,text,text,text,text);
}


void Application::ProjectileCallback(Projectile& proj){

}

bool Application::run(){
    if(!device){
        return false;
    }

    Simulation sim;
    sim.Init();

    std::vector<Boid*> boids;
    this->CreateBoids(3, 10, 10, boids, sim, NULL,0,0,0);

    //this->SetCameraTarget(boids[0]);
	/*this->CreateBoids(150, &boids, &sim, Vector3(0.f, 0.f, 0.f));	
	this->CreateBoids(50, &boids, &sim, Vector3(40.f, 0.f, 0.f));*/

    ITimer* irrTimer = device->getTimer();
    u32 TimeStamp = irrTimer->getTime();
	irr::u32 DeltaTime = 0;
    while(device->run()){
        DeltaTime = irrTimer->getTime() - TimeStamp;
        TimeStamp = irrTimer->getTime();

        sim.Update((float)DeltaTime);
        vector<Unit*> list = sim.GetAllUnits();
        for(unsigned int i = 0; i < list.size(); i++){
            Vector3 pos = list[i]->m_position;
            ((Boid*)list[i]->GetData())->setOrientation(core::vector3df(pos.X, pos.Y, pos.Z));
            ((Boid*)list[i]->GetData())->setPosition(core::vector3df(pos.X, pos.Y, pos.Z));            
        }

        driver->beginScene();
        smgr->drawAll();

		irr::video::SMaterial m;
        m.Lighting=false;
        driver->setMaterial(m);
        driver->setTransform(video::ETS_WORLD, core::matrix4());
		
		for(unsigned int i = 0; i < list.size(); i++){
			if(list[i]->m_lead == NULL && list[i]->m_target != NULL) {
				Vector3 pos = list[i]->m_position;
				Vector3 posTarget = list[i]->m_target->m_position;				
				driver->draw3DLine(irr::core::vector3df(pos.X,pos.Y,pos.Z),irr::core::vector3df(posTarget.X,posTarget.Y,posTarget.Z), ((Boid*)list[i]->GetData())->getColor());
			}

            auto projectiles = list[i]->GetProjectileList();
            for(unsigned int j = 0; j < projectiles.size(); j++){
                Vector3 pos = projectiles[j].m_position;
                Vector3 posTarget = projectiles[j].m_position + (projectiles[j].m_velocity * projectiles[j].m_speed * 20.f);				
				driver->draw3DLine(irr::core::vector3df(pos.X,pos.Y,pos.Z),irr::core::vector3df(posTarget.X,posTarget.Y,posTarget.Z), ((Boid*)list[i]->GetData())->getColor());
            }
		}

		if(font) {
			std::vector<Unit*> rootUnits = sim.GetRootUnits();

			for(unsigned int i = 0; i < rootUnits.size(); i++) {
				wchar_t str[1000];
				swprintf(str,  L"LEADER %d", i + 1);
				video::SColor color = ((Boid*)rootUnits.at(i)->GetData())->getColor();

				font->draw(str,
						core::rect<s32>(20, (20 + 40)*i + 20,200,50),
						color);

				swprintf(str,  L"Units: %d", rootUnits.at(i)->m_units.size() + 1);
				font->draw(str,
						core::rect<s32>(45, (20 + 40)*i + 40,200,50),
						color);
			}
		}

        driver->endScene();
    }

    for(unsigned int i = 0; i < boids.size(); i++){
        delete boids[i];
    }
    sim.Clear();
    return true;
}

void Application::SetCameraTarget(Boid* boid){
    this->smgr->getActiveCamera()->setParent(boid->getSceneNode());
    this->smgr->getActiveCamera()->setPosition(irr::core::vector3df(0, 0, 2));
    //this->smgr->getActiveCamera()->updateAbsolutePosition();
    this->smgr->getActiveCamera()->setTarget(boid->getSceneNode()->getPosition());
}

void Application::CreateBoids(int number, int numberSubUnit, float size, std::vector<Boid*> &boids, Simulation &sim, Unit* parent, int pr, int pg, int pb) {
	for(int i = 0; i < number; i++){
        int r,g,b = 0;

        if(parent == NULL){
            r = rand()%255;
            g = rand()%255;
            b = rand()%255;
        }else{
            r = pr;
            g = pg;
            b = pb;
        }

        Boid* monBoid = new Boid(smgr, size); 
        monBoid->setColor(r,g,b);
        boids.push_back(monBoid);

        float t1 = (rand()%10 > 5) ? -1.f : 1.f;
        float t2 = (rand()%10 > 5) ? -1.f : 1.f;
        float t3 = (rand()%10 > 5) ? -1.f : 1.f;

        float x = rand() %25 * t1;
        float y = rand() %25 * t2;
        float z = rand() %25 * t3;
        
        Unit * unit = sim.CreateUnit(Vector3(x, y, z), Vector3(), monBoid);
        unit->SetCallbackFunction(this);
        if(parent == NULL){
            sim.AddUnit(unit);
        }else{
            parent->AddUnit(unit);
        }

        if(numberSubUnit > 0){
            this->CreateBoids(numberSubUnit, 0, size/2, boids, sim, unit, r, g, b);
        }
    }
}