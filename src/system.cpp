
#include <irrlicht.h> 
#include <string>
#include <iostream>
#include "body.h"
#include "def.h"
#include "pugixml/pugixml.hpp"
#include "system.h"

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 
using namespace std;
using namespace pugi;


System::System(ISceneManager* smgr,IVideoDriver* driver, std::string fileName)
{

    this->fileName = fileName;
    this->rootBody = rootBody;
    this->smgr = smgr;
    this->driver = driver;

    xml_document doc;
    doc.load_file((DATA_SYSTEM_DIR+fileName).c_str());
    //xml_parse_result result = doc.load_file((DATA_SYSTEM_DIR+fileName).c_str());
    xml_node sysNode = doc.child("system");
    rootBody = processRoot(sysNode);

}

void System::buildSystem()
{
    //TODO get rid of magic nums
    std::string tmp = IMG_DIR+this->backdrop;
    this->smgr->addSkyDomeSceneNode(this->driver->getTexture(tmp.c_str()),32,32,0.9f,2.0f);
    this->rootBody->buildBody();
}


Body* System::processRoot(pugi::xml_node sysNode)
{
    xml_node rootNode,tmpNode;
    this->name = sysNode.child_value("name");
    cout << "System Name: " << this->name << "\n";
    this->backdrop = sysNode.child_value("backdrop");
    cout << "System Backdrop: " << backdrop << "\n";
    
    //Deal with the root node
    rootNode = sysNode.child("body");
    std::string tmpName = rootNode.child_value("name");
    std::string tmpType = rootNode.child_value("type");
    int tmpRadius = atoi(rootNode.child_value("radius"));
    std::string tmpTexture = rootNode.child_value("texture");
    int tmpOrbitRadius = 0;
    f32 tmpOrbitSpeed = 0.0;
    int tmpBrightness = atoi(rootNode.child_value("bright"));

    core::vector3df tmpDefaultPos = core::vector3df(0.0f,0.0f,0.0f);

    rootBody = new Body(this->smgr,this->driver,tmpDefaultPos,tmpRadius,tmpName,tmpType,tmpOrbitRadius,tmpOrbitSpeed,NULL,tmpTexture,tmpBrightness);

    tmpNode = rootNode.child("children").first_child();
    bool morePlanets = true;
    //Body* tmpBody, *tmpRoot;

    while(tmpNode && morePlanets){
        rootBody->addChild(processChild(tmpNode,rootBody));
        if(tmpNode.next_sibling()){
            tmpNode = tmpNode.next_sibling();
            continue;
        }
        else{
            morePlanets=false;
        }
    }
    
    return rootBody;
    
}


Body* System::processChild(pugi::xml_node tmpRoot, Body* parent)
{
    //Deal with the root node
    xml_node tmpNode;
    std::string tmpName = tmpRoot.child_value("name");
    std::string tmpType = tmpRoot.child_value("type");
    int tmpRadius = atoi(tmpRoot.child_value("radius"));
    std::string tmpTexture = tmpRoot.child_value("texture");
    int tmpOrbitRadius = atoi(tmpRoot.child_value("orbit_radius"));
    f32 tmpOrbitSpeed = atof(tmpRoot.child_value("orbit_speed"));
    int tmpBrightness = atoi(tmpRoot.child_value("bright"));

    
    core::vector3df tmpDefaultPos = parent->getPosition();
    tmpDefaultPos.X += tmpOrbitRadius;
    
    //core::vector3df(tmpOrbitRadius,0.0f,0.0f);

    Body* rootBody = new Body(this->smgr,this->driver,tmpDefaultPos,tmpRadius,tmpName,tmpName,tmpOrbitRadius,tmpOrbitSpeed,parent,tmpTexture,tmpBrightness);
    tmpNode = tmpRoot.child("children").first_child();
    bool morePlanets = true;

    while(tmpNode && morePlanets){
        rootBody->addChild(processChild(tmpNode,rootBody));
        if(tmpNode.next_sibling()){
            tmpNode = tmpNode.next_sibling();
            continue;
        }
        else{
            morePlanets=false;
        }
    }

    return rootBody;
}



