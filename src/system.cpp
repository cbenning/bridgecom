
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
    xml_parse_result result = doc.load_file((DATA_SYSTEM_DIR+fileName).c_str());
    
    rootBody = processRoot(doc);

}

void System::buildSystem()
{
    //TODO get rid of magic nums
    std::string tmp = IMG_DIR+this->backdrop;
    this->smgr->addSkyDomeSceneNode(this->driver->getTexture(tmp.c_str()),32,32,1.0f,2.0f);
    this->rootBody->buildBody();
}


Body* System::processRoot(xml_document doc)
{
    xml_node tmpNode;
    xml_node sysNode = doc.child("system");
    this->name = sysNode.child_value("name");
    cout << "System Name: " << this->name << "\n";
    this->backdrop = sysNode.child_value("backdrop");
    cout << "System Backdrop: " << backdrop << "\n";
    
    //Deal with the root node
    rootNode = sysNode.child("body");
    std::string tmpName = tmpNode.child_value("name");
    std::string tmpType = tmpNode.child_value("type");
    int tmpRadius = atoi(tmpNode.child_value("radius"));
    std::string tmpTexture = tmpNode.child_value("texture");
    core::vector3df tmpDefaultPos = core::vector3df(0.0f,0.0f,0.0f);
    int tmpOrbitRadius = 0;
    int tmpOrbitSpeed = 0;
    int tmpBrightness = atoi(tmpNode.child_value("bright"));

    rootBody = new Body(this->smgr,this->driver,tmpDefaultPos,tmpRadius,tmpName,tmpName,tmpOrbitRadius,tmpOrbitSpeed,NULL,tmpTexture,tmpBrightness);

    tmpNode = rootNode.child("children").first_child();
    bool morePlanets = true;
    Body* tmpBody,tmpRoot;

    while(morePlanets){
        rootBody.addChild(processChild(tmpNode,rootBody));
        
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


Body* System::processChild(xml_node tmpRoot, Body* parent)
{
    //Deal with the root node
    std::string tmpName = tmpRoot.child_value("name");
    std::string tmpType = tmpRoot.child_value("type");
    int tmpRadius = atoi(tmpRoot.child_value("radius"));
    std::string tmpTexture = tmpRoot.child_value("texture");
    core::vector3df tmpDefaultPos = core::vector3df(0.0f,0.0f,0.0f);
    int tmpOrbitRadius = atoi(tmpRoot.child_value("orbit_radius"));
    int tmpOrbitSpeed = atoi(tmpRoot.child_value("orbit_speed"));
    int tmpBrightness = atoi(tmpRoot.child_value("bright"));

    Body* rootBody = new Body(this->smgr,this->driver,tmpDefaultPos,tmpRadius,tmpName,tmpName,tmpOrbitRadius,tmpOrbitSpeed,parent,tmpTexture,tmpBrightness);
    tmpNode = tmpRoot.child("children").first_child();
    bool morePlanets = true;

    while(morePlanets){
        rootBody.addChild(processChild(tmpNode,rootBody));
        
        if(rootNode.next_sibling()){
            tmpNode = tmpNode.next_sibling();
            continue;
        }
        else{
            morePlanets=false;
        }
    }

    return rootBody;

}
