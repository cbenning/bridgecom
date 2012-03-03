
#include <irrlicht.h> 
#include "util.h"

b2Vec2 Util::rad2vec(float r, float m ) {
   return (m*b2Vec2(cos(r),sin(r)));
}

b2Vec2 Util::deg2vec(float r, float m ) {
   float rad = r*(irr::core::PI/180);
   return rad2vec(rad,m);
}

float Util::vec2rad(b2Vec2 v) {
   return atan2(v.y,v.x);
}

float Util::vec2deg(b2Vec2 v) {
   return vec2rad(v)*57.295779513082320876798154814105f;
}

