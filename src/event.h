
#include <irrlicht.h>
//#include "ship.h"

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 


class GameEventReceiver : public IEventReceiver
{
private:
    u32 then;
    u32 now;
    f32 frameDeltaTime;
    core::vector3df nodePosition;
    bool KeyDown[KEY_KEY_CODES_COUNT];
    bool isKeyUp(EKEY_CODE keyCode);
    bool isKeyDown(EKEY_CODE keyCode);
    bool OnEvent(const SEvent& event);

public:
    GameEventReceiver();
    int handleInput(u32 then, IrrlichtDevice *device, Ship* shipNode);
};
