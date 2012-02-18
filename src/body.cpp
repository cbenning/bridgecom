
#include "body.h"
#include "def.h"


Body::Body(ISceneManager* smgr,IVideoDriver* driver, core::vector3df position, const int radius, std::string name, std::string type, int orbitRadius, int orbitSpeed, Body* parentBody, std::string texture, bool bright)
{

    this->radius=radius;
    this->name=name;
    this->type=type;
    this->orbitRadius=orbitRadius;
    this->orbitSpeed=orbitSpeed;
    this->parentBody=parentBody;

	node = smgr->addSphereSceneNode(radius, PLANET_POLY_COUNT);
    if (node)
    {
        
        node->setPosition(position);
        node->setMaterialTexture(0, driver->getTexture(texture.c_str()));
        node->setMaterialFlag(EMF_LIGHTING, true); // enable dynamic lighting
        node->getMaterial(0).Shininess = 20.0f; // set size of specular highlights
        // add white light
        if(bright)
            smgr->addLightSceneNode(0, position, video::SColorf(1.0f, 1.0f, 1.0f));
        // set ambient light
        //smgr->setAmbientLight(video::SColor(0,60,60,60));
    }
    else{
        cout<<"Failed to setup the body";
    }
}
