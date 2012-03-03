
#include <irrlicht.h> 
#include "Box2D/Box2D.h"
#include "def.h"


class Util
{

public:
    static b2Vec2 rad2vec(float r, float m = 1);
    static b2Vec2 deg2vec(float r, float m = 1);
    static float vec2rad(b2Vec2 v);
    static float vec2deg(b2Vec2 v);
};

