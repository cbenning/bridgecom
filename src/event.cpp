
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
 
int GameEventReceiver::handleInput(u32 then, u32 now, IrrlichtDevice *device, Ship* shipNode)
{
    // Work Out A Frame Delta Time. This Allows For A Smooth Frame Rate On All Machines
    frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
    then = now;
    nodePosition = shipNode->getPosition();
    
    if(this->isKeyDown(irr::KEY_KEY_S)){
        shipNode->applyReverseThrust();
    }
    else{
        shipNode->cancelReverseThrust();
    }
    if(this->isKeyDown(irr::KEY_KEY_W)){
        shipNode->applyForwardThrust();
    }
    else{
        shipNode->cancelForwardThrust();
    }

    if(this->isKeyDown(irr::KEY_KEY_A)){
        shipNode->applyLeftThrust();
    }
    else{
        shipNode->cancelLeftThrust();
    }

    if(this->isKeyDown(irr::KEY_KEY_D)){
        shipNode->applyRightThrust();
    }
    else{
        shipNode->cancelRightThrust();
    }

    if(this->isKeyDown(irr::KEY_KEY_Q)){
        shipNode->applyLeftStrafeThrust();
    }
    else{
        shipNode->cancelLeftStrafeThrust();
    }

    if(this->isKeyDown(irr::KEY_KEY_E)){
        shipNode->applyRightStrafeThrust();
    }
    else{
        shipNode->cancelRightStrafeThrust();
    }
    
    //
    // Targetting
    //
    if(this->isKeyDown(irr::KEY_KEY_T)){
        shipNode->beginCycleTarget();
    }
    else{
        shipNode->commitCycleTarget();
    }

    if(this->isKeyDown(irr::KEY_UP)){
        shipNode->decreaseCameraZoom(false);
    }
    else{
        shipNode->decreaseCameraZoom(true);
    }

    if(this->isKeyDown(irr::KEY_DOWN)){
        shipNode->increaseCameraZoom(false);
    }
    else{
        shipNode->increaseCameraZoom(true);
    }

    if(this->isKeyDown(irr::KEY_ESCAPE))
    {
        device->drop();
        return 50;
    }
    return 0;
}
