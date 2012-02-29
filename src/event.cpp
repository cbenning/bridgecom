
#include "ship.h"
#include "event.h"

GameEventReceiver::GameEventReceiver()
{
    for(int i = 0; i < KEY_KEY_CODES_COUNT; i++)
    {
        KeyDown[i] = false;
    }
}

bool GameEventReceiver::OnEvent(const SEvent& event)
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

bool GameEventReceiver::isKeyDown(EKEY_CODE keyCode) 
{
    return KeyDown[keyCode];
}

bool GameEventReceiver::isKeyUp(EKEY_CODE keyCode) 
{
    return !KeyDown[keyCode];
}
 
int GameEventReceiver::handleInput(u32 then, IrrlichtDevice *device, Ship* shipNode)
{
    // Work Out A Frame Delta Time. This Allows For A Smooth Frame Rate On All Machines
    now = device->getTimer()->getTime();
    frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
    then = now;
    nodePosition = shipNode->getPosition();
    
    if(this->isKeyDown(irr::KEY_KEY_S))
    {
        cout<<"S\n";
        //shipNode->setPosition(v);
    }
    if(this->isKeyDown(irr::KEY_KEY_W))
    {
        cout<<"W\n";
        //shipNode->setPosition(v);
    }
    if(this->isKeyDown(irr::KEY_KEY_A))
    {
        cout<<"A\n";
        //shipNode->applyLeftThrust();
    }
    if(this->isKeyDown(irr::KEY_KEY_D))
    {
        cout<<"D\n";
        //shipNode->applyRightThrust();
    }
    
    if(this->isKeyDown(irr::KEY_KEY_Q))
    {
        device -> drop();
        return 50;
    }
    return 0;
}
