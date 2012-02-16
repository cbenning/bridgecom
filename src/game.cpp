#include <irrlicht.h>
#include "rtscamera.h"
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif



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

	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, dimension2d<u32>(800, 600), 16,false, false, false, &eventReceiver);

        if (!device)
                return 1;

        device->setWindowCaption(L"Hello World!");
 
    	IVideoDriver* driver = device->getVideoDriver();
        ISceneManager* smgr = device->getSceneManager();
        IGUIEnvironment* guienv = device->getGUIEnvironment();
        
        guienv->addStaticText(L"Current Input",rect<s32>(10,10,260,22), true);
                
        smgr->addSkyDomeSceneNode(driver->getTexture("../media/img/starfield.png"),32,	32, 1.0f, 2.0f);

        IAnimatedMesh* mesh = smgr->getMesh("../media/model/ship1.b3d");
        if (!mesh)
        {
                device->drop();
                return 1;
        }
        IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
        
        if (node)
        {
                node->setMaterialFlag(EMF_LIGHTING, false);
                node->setMaterialFlag(EMF_WIREFRAME, true);
                //node->setMD2Animation(scene::EMAT_STAND);
                //node->setMaterialTexture( 0, driver->getTexture("media/sydney.bmp") );
        }

        node->setPosition(vector3df(0,0,0));
        node->setRotation(vector3df(0,-90,0));

        RTSCamera* camera = new RTSCamera(device,smgr->getRootSceneNode(),smgr,1,200.0f, 2.0f,2.0f);
        camera->setPosition(vector3df(30,30,0)); 
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
            if(eventReceiver.isKeyDown(irr::KEY_KEY_Q))
            {
                    device -> drop();
                    return 50;
            }

            driver->beginScene(true, true, SColor(255,100,101,140));
            smgr->drawAll();
            guienv->drawAll();
            driver->endScene();
        }
        
        device->drop();

        return 0;
}
