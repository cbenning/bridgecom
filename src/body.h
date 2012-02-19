
#include <irrlicht.h> 
#include <string>
#include <iostream>
#include <vector>

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 
using namespace std;

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
    std::vector<Body*> children;
    int numChildren;
    ISceneNode* node;
    ISceneManager* smgr;
    IVideoDriver* driver;
    core::vector3df position;
    std::string texture;
    int brightness;

public:
    Body(ISceneManager* smgr, IVideoDriver* driver, core::vector3df position, const int radius, std::string name, std::string type, int orbitRadius, int orbitSpeed, Body* parentBody, std::string texture, int brightness);
    void addChild(Body* child);
    void buildBody();
};
