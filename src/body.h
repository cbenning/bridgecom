
#include <irrlicht.h> 
#include <string>
#include <iostream>

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 
using namespace std;

#define MAX_PLANET_MODELS 1
#define PLANET_POLY_COUNT 32

class Body 
{
private:
    int radius;
    std::string name;
    std::string type;
    int orbitRadius;
    int orbitSpeed;
    Body* parentBody;
    ISceneNode* node;
public:
    Body(ISceneManager* smgr,IVideoDriver* driver, core::vector3df position, const int radius, std::string name, std::string type, int orbitRadius, int orbitSpeed, Body* parentBody, std::string texture, bool bright);
};
