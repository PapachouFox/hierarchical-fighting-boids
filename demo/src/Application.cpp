#include "Application.h"

Application::Application(){
    device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800, 600), 32, false, false);
    if (device){
        device->setWindowCaption(L"Boids Demo - 0.1");

        //irrlicht managers
        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        guienv = device->getGUIEnvironment();
        smgr->setAmbientLight(video::SColorf(0.1f,0.1f,0.1f,1.f));
        smgr->setShadowColor(video::SColor(150,0,0,0));
		font = device->getGUIEnvironment()->getFont("../resources/fonts/myfont.bmp");

		m_currentTime = 0;
		m_lastTime = 0;

		ps = smgr->addParticleSystemSceneNode(false);
		em = ps->createBoxEmitter(
		core::aabbox3d<f32>(-2,0,-2,2,1,2), // emitter size
		core::vector3df(0.0f,0.0f,0.0f),   // initial direction
		20,50,                             // emit rate
		video::SColor(0,255,255,255),       // darkest color
		video::SColor(0,255,255,255),       // brightest color
		600,800,90,                         // min and max age, angle
		core::dimension2df(5.f,5.f),         // min size
		core::dimension2df(10.f,10.f));        // max size

		ps->setEmitter(em); // this grabs the emitter
		em->drop(); // so we can drop it here without deleting it

		scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

		ps->addAffector(paf); // same goes for the affector
		paf->drop();

		ps->setPosition(irr::core::vector3df());
		ps->setScale(core::vector3df(2,2,2));
		ps->setMaterialFlag(video::EMF_LIGHTING, false);
		ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, driver->getTexture("../resources/textures/explosion.jpg"));
		ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);

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

    //std::vector<Boid*> boids;
	int nbLead = 3;
	int nbUnit = 20;
    this->CreateBoids(nbLead, nbUnit, 10, sim, NULL,0,0,0);

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
		
		m_currentTime += DeltaTime;

		if(m_currentTime >= m_lastTime) {
			m_lastTime = TimeStamp + 10000 / (nbUnit * nbLead);
			if(list.size() > nbLead) {			
				int r = rand()%list.size();
				ps->setPosition(irr::core::vector3df(list[r]->m_position.X, list[r]->m_position.Y, list[r]->m_position.Z));
			} else {
				ps->setEmitter(0);
			}
		}

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

    /*for(unsigned int i = 0; i < boids.size(); i++){
        delete boids[i];
    }*/
    sim.Clear();
    return true;
}

void Application::SetCameraTarget(Boid* boid){
    this->smgr->getActiveCamera()->setParent(boid->getSceneNode());
    this->smgr->getActiveCamera()->setPosition(irr::core::vector3df(0, 0, 2));
    //this->smgr->getActiveCamera()->updateAbsolutePosition();
    this->smgr->getActiveCamera()->setTarget(boid->getSceneNode()->getPosition());
}

void Application::CreateBoids(int number, int numberSubUnit, float size, Simulation &sim, Unit* parent, int pr, int pg, int pb) {
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
        //boids.push_back(monBoid);

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
            this->CreateBoids(numberSubUnit, 0, size/2, sim, unit, r, g, b);
        }
    }
}