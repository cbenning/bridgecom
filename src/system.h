
#include "pugixml/pugixml.hpp"

class System
{
private:
    std::string fileName;
    std::string name;
    std::string backdrop;
    Body* rootBody;
    ISceneManager* smgr;
    IVideoDriver* driver;

public:
    System(ISceneManager* smgr, IVideoDriver* driver, std::string fileName);
    void buildSystem();
    Body* processRoot(pugi::xml_node sysNode);
    Body* processChild(pugi::xml_node tmpRoot, Body* parent);
};
