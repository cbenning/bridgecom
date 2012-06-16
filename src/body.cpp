
#include "body.h"
#include "def.h"

Body::Body(ISceneManager* smgr,IVideoDriver* driver, core::vector3df position, const int radius, std::string name, std::string desc, std::string type, int orbitRadius, f32 orbitSpeed, Body* parentBody, std::string texture, int brightness) : TargetableObject(name,desc,type)
{

    this->radius=radius;
    this->orbitRadius=orbitRadius;
    this->orbitSpeed=orbitSpeed;
    this->parentBody=parentBody;
    this->numChildren=0;
    this->smgr=smgr;
    this->driver=driver;
    this->defaultPosition=position;
    this->texture=texture;
    this->brightness=brightness;
    this->node=NULL;

    cout << "Created " << this->getTName() << " with " << this->texture << "\n";

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
    if (this->node)
    {
        this->node->setMaterialTexture(0, this->driver->getTexture((IMG_DIR+this->texture).c_str()));
        
        vector3df tmp = this->getPosition();
        tmp.Y-=(this->radius+BODY_PLANE_BUFFER);
        this->node->setPosition(tmp);

        cout << "Type: " << this->getTType() << "\n";
        if(this->getTType()=="star"){
            this->smgr->addLightSceneNode(0,this->getPosition(),video::SColorf(this->brightness,this->brightness,this->brightness),this->radius,1); 
            this->node->setMaterialFlag(EMF_LIGHTING, false); // enable dynamic lighting
            //Offset the location to underneath the plane
        }
        else{
            this->node->setMaterialFlag(EMF_LIGHTING, true); // enable dynamic lighting
        }

        if(this->parentBody)
        {
            cout << this->getTName() << ", Orbit speed: " << this->orbitSpeed << "Parent: " << this->parentBody->getName() << "\n";
            vector3df tmp2 = this->parentBody->getPosition();
            tmp2.Y = tmp.Y;
            ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(tmp2, this->orbitRadius, this->orbitSpeed);
            if (anim)
            {
                this->node->addAnimator(anim);
                anim->drop();
            }
        }
    }
    else{
        cout<<"Failed to setup the body";
        return;
    }

    int i;
    for(i = 0; i< this->numChildren; i++){
        this->children[i]->buildBody();
    }
}

core::vector3df Body::getPosition(){
    if(this->node==NULL){
        return this->defaultPosition;
    }
    else{
        return this->node->getPosition();
    }
}

std::string Body::getName(){
    return this->getTName();
}


int Body::getRadius(){
    return this->radius;
}
