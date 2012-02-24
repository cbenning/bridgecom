#include <irrlicht.h>
#include <iostream>
#include "rtscamera.h"
#include "ship.h"
#include "body.h"
#include "def.h"
#include "system.h"
#include "event.h"
#include "Box2D.h"

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
	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, dimension2d<u32>(1280, 800), 32,false, false, false, eventReceiver);

    if (!device)
            return 1;

    device->setWindowCaption((wchar_t*)APP_WINDOW_CAPTION);

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();
    
    guienv->addStaticText(L"Current Input",rect<s32>(10,10,260,22), true);
            
    System* solSys = new System(smgr,driver,"sol.xml");
    solSys->buildSystem();

    RTSCamera* camera = new RTSCamera(device,smgr->getRootSceneNode(),smgr,1,200.0f, 100.0f,2.0f);
    camera->setPosition(vector3df(250,250,0)); 
    camera->setRotation(vector3df(0,0,0)); 

    //smgr->setAmbientLight(video::SColorf(0.3,0.3,0.3,1));
    Ship* myShip = new Ship(smgr,driver,0);

    u32 then = device->getTimer()->getTime();
    while(device->run())
    {
        
        if(eventReceiver->handleInput(then,device,myShip) !=0)
            return -1;

        if (device->isWindowActive())
        {
            driver->beginScene(true, true, SColor(255,100,101,140));
            smgr->drawAll();
            guienv->drawAll();
            driver->endScene();
        }
        else
        {
            device->yield();
        }

    }
    
    device->drop();

    return 0;
}
