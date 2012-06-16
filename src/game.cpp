#include <irrlicht.h>
#include <iostream>
#include "followcamera.h"
#include "ship.h"
//#include "targets.h"
#include "body.h"
#include "def.h"
#include "system.h"
#include "event.h"
#include "Box2D/Box2D.h"
#include <vector>
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
    //core::dimension2d<u32> resolution = core::dimension2d<u32>(1280, 800);
    //Fullscreen
    IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);
    core::dimension2d<u32> resolution = nulldevice->getVideoModeList()->getDesktopResolution();
	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, resolution, 16, false, true, true, eventReceiver);

    //
    // Box2D Stuff
    //
    b2Vec2 gravity = b2Vec2(0.0f,0.0f);
    b2World* gameWorld = new b2World(gravity);
    float32 timeStep = 1.0f / 30.f;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
    gameWorld->Step(timeStep, velocityIterations, positionIterations);
    if (!device)
            return 1;

    device->setWindowCaption((wchar_t*)APP_WINDOW_CAPTION);

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();
    
    //
    // Targeting text
    //
    guienv->addStaticText(L"Current Input",rect<s32>(10,10,260,22), true);
            
    System* solSys = new System(smgr,driver,"sol.xml");
    solSys->buildSystem();
    


    //smgr->setAmbientLight(video::SColorf(0.3,0.3,0.3,1));
    Ship* myShip = new Ship(smgr,driver,gameWorld,0);

    ICameraSceneNode* camera = smgr->addCameraSceneNode(0);
    camera->setFarValue(50000.0f); 
    camera->bindTargetAndRotation(true);
    camera->setPosition(myShip->getCamFollowPosition()); 
    camera->setTarget(myShip->getPosition()); 

    //Plane Grid - Needs work
    //CGridSceneNode* grid = new CGridSceneNode(smgr->getRootSceneNode(), smgr, -1, 100, 16384, SColor(16,8,42,8),20,SColor(16,8,42,8));

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
