#include <irrlicht.h>
#include <iostream>
#include "rtscamera.h"
#include "ship.h"
#include "body.h"
#include "def.h"
#include "system.h"

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


class GameEventReceiver : public IEventReceiver
{
private:
    bool KeyDown[KEY_KEY_CODES_COUNT];
public:
    GameEventReceiver()
    {
            for(int i = 0; i < KEY_KEY_CODES_COUNT; i++)
            {
                    KeyDown[i] = false;
            }
    }
    
    virtual bool OnEvent(const SEvent& event)
    {
            switch(event.EventType)
            {
            case EET_KEY_INPUT_EVENT:
                    {
                        KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
                        break;
                    }
            default:
                    break;
            }
            return false;
    }
    
    virtual bool isKeyDown(EKEY_CODE keyCode) 
    {
            return KeyDown[keyCode];
    }

    virtual bool isKeyUp(EKEY_CODE keyCode) 
    {
            return !KeyDown[keyCode];
    }
 
};


int main()
{
    GameEventReceiver eventReceiver;

	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, dimension2d<u32>(1280, 800), 32,false, false, false, &eventReceiver);

    if (!device)
            return 1;

    device->setWindowCaption((wchar_t*)APP_WINDOW_CAPTION);

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();
    
    guienv->addStaticText(L"Current Input",rect<s32>(10,10,260,22), true);
            
    smgr->setAmbientLight(video::SColorf(0.3,0.3,0.3,1));
    Ship myship = Ship(smgr,driver,0);

    System* solSys = new System(smgr,driver,"sol.xml");
    solSys->buildSystem();

    RTSCamera* camera = new RTSCamera(device,smgr->getRootSceneNode(),smgr,1,200.0f, 100.0f,2.0f);
    camera->setPosition(vector3df(250,250,0)); 
    camera->setRotation(vector3df(0,0,0)); 

    int lastFPS = -1;
    // In order to do framerate independent movement, we have to know
    // how long it was since the last frame
    u32 then = device->getTimer()->getTime();

    // This is the movemen speed in units per second.
    const f32 MOVEMENT_SPEED = 1.0f;

     while(device->run())
    {
        
        // Work Out A Frame Delta Time. This Allows For A Smooth Frame Rate On All Machines
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;
        /*
        core::vector3df nodePosition = node->getPosition();
        if(eventReceiver.isKeyDown(irr::KEY_KEY_S))
        {
                cout<<"S\n";
                core::vector3df v = node -> getPosition();
                v.X += MOVEMENT_SPEED;
                node->setPosition(v);
        }
        if(eventReceiver.isKeyDown(irr::KEY_KEY_W))
        {
                cout<<"W\n";
                core::vector3df v = node -> getPosition();
                v.X -= MOVEMENT_SPEED;
                node->setPosition(v);
        }
        if(eventReceiver.isKeyDown(irr::KEY_KEY_A))
        {
                cout<<"A\n";
                core::vector3df v = node -> getRotation();
                v.Y -= 5.0f;
                node->setRotation(v);
        }
        if(eventReceiver.isKeyDown(irr::KEY_KEY_D))
        {
                cout<<"D\n";
                core::vector3df v = node -> getRotation();
                v.Y += 5.0f;
                node -> setRotation(v);
        }
        */
        if(eventReceiver.isKeyDown(irr::KEY_KEY_Q))
        {
                device -> drop();
                return 50;
        }
        
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
