
#include "ship.h"
#include "def.h"


Ship::Ship(ISceneManager* smgr, IVideoDriver* driver, const int model)
{

    //TODO: Make this better. suck it from a file?
    shipModel[0] = "ship2.b3d";

    cout<<(MODEL_DIR+shipModel[model]).c_str();
    mesh = smgr->getMesh((MODEL_DIR+shipModel[model]).c_str());
    node = smgr->addAnimatedMeshSceneNode(mesh);
    
    if (node)
    {       
        //node->setMaterialTexture(0, driver->getTexture("../media/img/ship2.png"));
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMaterialFlag(EMF_WIREFRAME, true);
    } 
    node->setPosition(vector3df(0,0,0));
    node->setRotation(vector3df(0,-90,0));

}

