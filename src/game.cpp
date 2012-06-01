#include <irrlicht.h>
#include <iostream>
#include "followcamera.h"
#include "ship.h"
#include "body.h"
#include "def.h"
#include "system.h"
#include "event.h"
#include "Box2D/Box2D.h"
//#include "grid/CGridSceneNode.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

/*#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif*/

int main()
{

    GameEventReceiver* eventReceiver = new GameEventReceiver();

    //Windowed
	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, dimension2d<u32>(1280, 800), 32,false, false, true, eventReceiver);

    //
    // Box2D Stuff
    //
    b2Vec2 gravity = b2Vec2(0.0f,0.0f);
    b2World* gameWorld = new b2World(gravity);
    float32 timeStep = 1.0f / 10.f;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
    gameWorld->Step(timeStep, velocityIterations, positionIterations);




    /* Fullscreen
    IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);
    core::dimension2d<u32> deskres = nulldevice->getVideoModeList()->getDesktopResolution();
    nulldevice -> drop();
	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, deskres, 32, true, false, false, eventReceiver);
    */
    if (!device)
            return 1;

    device->setWindowCaption((wchar_t*)APP_WINDOW_CAPTION);

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();
    
    smgr->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0));
    guienv->addStaticText(L"Current Input",rect<s32>(10,10,260,22), true);
            
    System* solSys = new System(smgr,driver,"sol.xml");
    solSys->buildSystem();

    //RTSCamera* camera = new RTSCamera(device,smgr->getRootSceneNode(),smgr,1,200.0f, 100.0f,2.0f);
    //camera->setPosition(vector3df(250,250,0)); 
    //camera->setRotation(vector3df(0,0,0)); 

    //smgr->setAmbientLight(video::SColorf(0.3,0.3,0.3,1));
    Ship* myShip = new Ship(smgr,driver,gameWorld,0);
    ICameraSceneNode* camera = smgr->addCameraSceneNode(0);
    camera->bindTargetAndRotation(true);
    //camera->setParent(myShip->getSceneNode());
    camera->setPosition(myShip->getCamFollowPosition()); 
    camera->setTarget(myShip->getPosition()); 

    //Plane Grid
    //CGridSceneNode* grid = new CGridSceneNode(smgr->getRootSceneNode(), smgr, -1, 400, 16384, SColor(16,8,42,8),20,SColor(16,8,42,8));


    u32 then = device->getTimer()->getTime();
    u32 now;

    while(device->run())
    {
        
        now = device->getTimer()->getTime();

        if(eventReceiver->handleInput(then,now,device,myShip) !=0)
            return -1;

        //if (device->isWindowActive())
        //{
            //camera->setPosition(myShip->getCamFollowPosition()); 
            //vector3df tmp1 = myShip->getCamFollowPosition();
            //vector3df tmp2 = myShip->getPosition();
            //cout << "CP: "<<tmp1.X<<","<<tmp1.Y<<","<<tmp1.Z<<"  CT: " <<tmp2.X<<","<<tmp2.Y<<","<<tmp2.Z<<"\n";
            driver->beginScene(true, true, SColor(255,100,101,140));

            // Instruct the world to perform a single step of simulation.
            // It is generally best to keep the time step and iterations fixed.

            gameWorld->Step(timeStep, velocityIterations, positionIterations);
            myShip->update(camera);

            /* For when more than one physics body exists
            for(int i=0; i < bodies.size(); i++)
            {
                bodies[i]->update();
            }*/

            smgr->drawAll();
            guienv->drawAll();
            driver->endScene();
        //}
        //else
        //{
        //    device->yield();
        //}

    }
    
    device->drop();

    return 0;
}
