
#include "body.h"
#include "def.h"

Body::Body(ISceneManager* smgr,IVideoDriver* driver, core::vector3df position, const int radius, std::string name, std::string type, int orbitRadius, int orbitSpeed, Body* parentBody, std::string texture, int brightness)
{

    this->radius=radius;
    this->name=name;
    this->type=type;
    this->orbitRadius=orbitRadius;
    this->orbitSpeed=orbitSpeed;
    this->parentBody=parentBody;
    this->numChildren=0;
    this->smgr=smgr;
    this->driver=driver;
    this->position=position;
    this->texture=texture;
    this->brightness=brightness;

}

void Body::addChild(Body* child)
{
    this->children.resize(this->numChildren+1);
    this->children[this->numChildren]=child;
    this->numChildren++;
}

void Body::buildBody()
{

	this->node = this->smgr->addSphereSceneNode(this->radius, PLANET_POLY_COUNT);
    if (node)
    {
        this->node->setPosition(this->position);
        std::string tmpTexture = IMG_DIR+this->texture;
        this->node->setMaterialTexture(0, this->driver->getTexture(tmpTexture.c_str()));
        this->node->setMaterialFlag(EMF_LIGHTING, false); // enable dynamic lighting
    }
    else{
        cout<<"Failed to setup the body";
    }
    //TODO Also build chrildren

}
