
#include "followcamera.h" 

FollowCamera::FollowCamera(IrrlichtDevice* devicepointer,ISceneNode* parent,ISceneManager* smgr,s32 id, 
    f32 rs,f32 zs,f32 ts) 
   : ICameraSceneNode(parent,smgr,id,vector3df(1.0f,1.0f,1.0f),vector3df(0.0f,0.0f,0.0f), 
               vector3df(1.0f,1.0f,1.0f)),InputReceiverEnabled(true) 
{ 
   device = devicepointer; 
   BBox.reset(0,0,0); 

   UpVector.set(0.0f, 1.0f, 0.0f); 

   // set default projection 
   Fovy = core::PI / 2.0f;   // Field of view, in radians. 
   Aspect = 4.0f / 3.0f;   // Aspect ratio. 
   ZNear = 1.0f;      // value of the near view-plane. 
   ZFar = 100000.0f;      // Z-value of the far view-plane. 

   IVideoDriver* d = smgr->getVideoDriver(); 
   if (d) 
      Aspect = (f32)d->getCurrentRenderTargetSize().Width / (f32)d->getCurrentRenderTargetSize().Height; 

   zooming = false; 
   rotating = false; 
   moving = false; 
   translating = false; 
   zoomSpeed = zs; 
   rotateSpeed = rs; 
   translateSpeed = ts; 
   targetMinDistance = 1.0f; 
   targetMaxDistance = 200.0f; 
   Target.set(0.0f,0.0f,0.0f); 
   rotX = 0; 
   rotY = 0; 
   oldTarget = Target; 

   atMinDistance = false; 
   atMaxDistance = false; 

   allKeysUp(); 
   allMouseButtonsUp(); 

   recalculateProjectionMatrix(); 
   recalculateViewArea(); 

   smgr->setActiveCamera(this); 
} 

FollowCamera::~FollowCamera() 
{ 
} 

bool FollowCamera::OnEvent(const SEvent& event) 
{ 
   if (!InputReceiverEnabled) 
      return false; 

   dimension2d<u32> ssize = SceneManager->getVideoDriver()->getScreenSize(); 
   if(event.EventType == EET_MOUSE_INPUT_EVENT) 
   { 
      //printf("a\n"); 
      switch(event.MouseInput.Event) 
      { 
         case EMIE_LMOUSE_PRESSED_DOWN: 
            /*
            selectednode = SceneManager->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(device->getCursorControl()->getPosition()); 
            if(selectednode && selectednode->getType() == ESNT_BILLBOARD) 
            { 
               pointCameraAtNode(selectednode); 
            } 
            else 
            { 
               selectednode = NULL; 
               MouseKeys[0] = true; 
            } */
            break; 
         case EMIE_RMOUSE_PRESSED_DOWN: 
            MouseKeys[2] = true; 
            break; 
         case EMIE_MMOUSE_PRESSED_DOWN: 
            MouseKeys[1] = true; 
            break; 
         case EMIE_LMOUSE_LEFT_UP: 
            MouseKeys[0] = false; 
            break; 
         case EMIE_RMOUSE_LEFT_UP: 
            MouseKeys[2] = false; 
            break; 
         case EMIE_MMOUSE_LEFT_UP: 
            MouseKeys[1] = false; 
            break; 
         case EMIE_MOUSE_MOVED: 
            { 
               IVideoDriver* driver = SceneManager->getVideoDriver(); 
               if (driver) 
               { 
                  MousePos.X = event.MouseInput.X / (f32)ssize.Width; 
                  MousePos.Y = event.MouseInput.Y / (f32)ssize.Height; 
               } 
            }
            break; 
         case EMIE_MOUSE_WHEEL: 
            currentZoom -= event.MouseInput.Wheel * zoomSpeed; 
            break; 
         default: 
            break; 
      } 

      return true; 
   } 

   if(event.EventType == EET_KEY_INPUT_EVENT) 
   { 
      Keys[event.KeyInput.Key] = event.KeyInput.PressedDown; 
      return true; 
   } 

   return false; 
} 

void FollowCamera::OnRegisterSceneNode() 
{ 
    
   vector3df pos = getAbsolutePosition(); 
   vector3df tgtv = Target - pos; 
   tgtv.normalize(); 

   vector3df up = UpVector; 
   up.normalize(); 

   f32 dp = tgtv.dotProduct(up); 

   if(core::equals((f32)fabs(dp),1.0f)) 
   { 
      up.X += 0.5f; 
   } 

   //ViewArea.Matrices [ ETS_VIEW ].buildCameraLookAtMatrixLH(pos, Target, up); 
   ViewArea.getTransform(ETS_VIEW).buildCameraLookAtMatrixLH(pos, Target, up); 
   //ViewArea.setTransformState ( ETS_VIEW ); 
   recalculateViewArea(); 

   if( SceneManager->getActiveCamera () == this ) 
      SceneManager->registerNodeForRendering(this, ESNRP_CAMERA); 

   if(IsVisible) 
      ISceneNode::OnRegisterSceneNode(); 
    
} 

void FollowCamera::render() 
{ 
   IVideoDriver* driver = SceneManager->getVideoDriver(); 
   if ( driver) 
   { 
      //driver->setTransform(ETS_PROJECTION, ViewArea.Matrices [ ETS_PROJECTION ] ); 
      driver->setTransform(ETS_PROJECTION, ViewArea.getTransform(ETS_PROJECTION) ); 
      //driver->setTransform(ETS_VIEW, ViewArea.Matrices [ ETS_VIEW ] ); 
      driver->setTransform(ETS_VIEW, ViewArea.getTransform(ETS_VIEW) ); 
   } 
} 

void FollowCamera::OnAnimate(u32 timeMs) 
{ 
   animate(); 

   ISceneNode::setPosition(Pos); 
   updateAbsolutePosition(); 
} 

void FollowCamera::setInputReceiverEnabled(bool enabled) 
{ 
   InputReceiverEnabled = enabled; 
} 

bool FollowCamera::isInputReceiverEnabled() const 
{ 
   _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX; 
   return InputReceiverEnabled; 
} 

const aabbox3d<f32>& FollowCamera::getBoundingBox() const 
{ 
   return ViewArea.getBoundingBox(); 
} 

const matrix4& FollowCamera::getProjectionMatrix() const 
{ 
   //return ViewArea.Matrices [ ETS_PROJECTION ]; 
   return ViewArea.getTransform(ETS_PROJECTION); 
} 

const SViewFrustum* FollowCamera::getViewFrustum() const 
{ 
   return &ViewArea; 
} 

const core::vector3df& FollowCamera::getTarget() const 
{ 
   return Target; 
} 

const matrix4& FollowCamera::getViewMatrix() const 
{ 
   //return ViewArea.Matrices [ video::ETS_VIEW ]; 
   return ViewArea.getTransform(ETS_VIEW); 
} 

const core::vector3df& FollowCamera::getUpVector() const 
{ 
   return UpVector; 
} 

f32 FollowCamera::getNearValue() const 
{ 
   return ZNear; 
} 

f32 FollowCamera::getFarValue() const 
{ 
   return ZFar; 
} 

f32 FollowCamera::getAspectRatio() const 
{ 
   return Aspect; 
} 

f32 FollowCamera::getFOV() const 
{ 
   return Fovy; 
} 

void FollowCamera::setNearValue(f32 f) 
{ 
   ZNear = f; 
   recalculateProjectionMatrix(); 
} 

void FollowCamera::setFarValue(f32 f) 
{ 
   ZFar = f; 
   recalculateProjectionMatrix(); 
} 

void FollowCamera::setAspectRatio(f32 f) 
{ 
   Aspect = f; 
   recalculateProjectionMatrix(); 
} 

void FollowCamera::setFOV(f32 f) 
{ 
   Fovy = f; 
   recalculateProjectionMatrix(); 
} 

void FollowCamera::setUpVector(const vector3df& pos) 
{ 
   UpVector = pos; 
} 

void FollowCamera::setProjectionMatrix(const matrix4& projection) 
{ 
   //ViewArea.Matrices [ ETS_PROJECTION ] = projection; 
   ViewArea.getTransform(ETS_PROJECTION) = projection; 
   //ViewArea.setTransformState ( ETS_PROJECTION ); 
} 

void FollowCamera::setPosition(const core::vector3df& pos) 
{ 
   Pos = pos; 
   updateAnimationState(); 

   ISceneNode::setPosition(pos); 
} 

void FollowCamera::setTarget(const core::vector3df& pos) 
{ 
   Target = oldTarget = pos; 
   updateAnimationState(); 
} 

void FollowCamera::setZoomSpeed(f32 value) 
{ 
   zoomSpeed = value; 
} 

void FollowCamera::setTranslateSpeed(f32 value) 
{ 
   translateSpeed = value; 
} 

void FollowCamera::setRotationSpeed(f32 value) 
{ 
   rotateSpeed = value; 
} 

void FollowCamera::pointCameraAtNode(ISceneNode* selectednode) 
{ 
   vector3df totarget = getPosition() - getTarget(); 
   setPosition(selectednode->getPosition() + (totarget.normalize() * 100)); 
   setTarget(selectednode->getPosition()); 
   updateAnimationState(); 
} 

void FollowCamera::setMinZoom(f32 amount) 
{ 
   targetMinDistance = amount; 
} 

void FollowCamera::setMaxZoom(f32 amount) 
{ 
   targetMaxDistance = amount; 
} 

void FollowCamera::recalculateProjectionMatrix() 
{ 
   //ViewArea.Matrices [ ETS_PROJECTION ].buildProjectionMatrixPerspectiveFovLH(Fovy, Aspect, ZNear, ZFar); 
   ViewArea.getTransform(ETS_PROJECTION).buildProjectionMatrixPerspectiveFovLH(Fovy, Aspect, ZNear, ZFar); 
   //ViewArea.setTransformState ( ETS_PROJECTION ); 
} 


void FollowCamera::recalculateViewArea() 
{ 
   ViewArea.cameraPosition = getAbsolutePosition(); 
   //ViewArea.setFrom ( ViewArea.Matrices [ SViewFrustum::ETS_VIEW_PROJECTION_3 ] ); 
   ViewArea.setFrom ( ViewArea.getTransform(ETS_PROJECTION)*ViewArea.getTransform(ETS_VIEW) ); 
} 

void FollowCamera::allKeysUp() 
{ 
   for(int i = 0;i < KEY_KEY_CODES_COUNT;i++) 
      Keys[i] = false; 
} 

void FollowCamera::allMouseButtonsUp() 
{ 
   for (s32 i=0; i<3; ++i) 
      MouseKeys[i] = false; 
} 

bool FollowCamera::isKeyDown(s32 key) 
{ 
   return Keys[key]; 
} 

bool FollowCamera::isMouseButtonDown(s32 key) 
{ 
   return MouseKeys[key]; 
} 

void FollowCamera::animate() 
{ 
   f32 nRotX = rotX; 
   f32 nRotY = rotY; 
   f32 nZoom = currentZoom; 

   vector3df translate(oldTarget); 
   vector3df tvectX = Pos - Target; 
   tvectX = tvectX.crossProduct(UpVector); 
   tvectX.normalize(); 

   //Zoom 
   if (isMouseButtonDown(MOUSE_BUTTON_RIGHT) && isMouseButtonDown(MOUSE_BUTTON_LEFT)) 
   { 
      if (!zooming) 
      { 
         zoomStartX = MousePos.X; 
         zoomStartY = MousePos.Y; 
         zooming = true; 
         nZoom = currentZoom; 
      } 
      else 
      { 
         f32 old = nZoom; 
         nZoom += (zoomStartX - MousePos.X) * zoomSpeed * 100; 

//         f32 targetMinDistance = 0.1f; 
//         if (nZoom < targetMinDistance) 
//            nZoom = targetMinDistance; 

         if (nZoom < targetMinDistance) 
            nZoom = targetMinDistance; 
         else if (nZoom > targetMaxDistance) 
            nZoom = targetMaxDistance; 


         if (nZoom < 0) 
            nZoom = old; 
      } 
   } 
   else 
   { 
      if (zooming) 
      { 
         f32 old = currentZoom; 
         currentZoom = currentZoom + (zoomStartX - MousePos.X ) * zoomSpeed; 
         nZoom = currentZoom; 

         if (nZoom < 0) 
            nZoom = currentZoom = old; 
      } 
      zooming = false; 
   } 

   //Rotate 
   if(isMouseButtonDown(MOUSE_BUTTON_LEFT) && !zooming) 
   { 
      if (!rotating) 
      { 
         rotateStartX = MousePos.X; 
         rotateStartY = MousePos.Y; 
         rotating = true; 
         nRotX = rotX; 
         nRotY = rotY; 
      } 
      else 
      { 
         nRotX += (rotateStartX - MousePos.X) * rotateSpeed; 
         nRotY += (rotateStartY - MousePos.Y) * rotateSpeed; 
      } 
   } 
   else 
   { 
      if (rotating) 
      { 
         rotX = rotX + (rotateStartX - MousePos.X) * rotateSpeed; 
         rotY = rotY + (rotateStartY - MousePos.Y) * rotateSpeed; 
         nRotX = rotX; 
         nRotY = rotY; 
      } 

      rotating = false; 
   } 

   //Translate 
   if(isMouseButtonDown(MOUSE_BUTTON_RIGHT) && !zooming) 
   { 
      if (!translating) 
      { 
         translateStartX = MousePos.X; 
         translateStartY = MousePos.Y; 
         translating = true; 
      } 
      else 
      { 
         translate += tvectX * (translateStartX - MousePos.X) * translateSpeed; 
         translate.X += tvectX.Z * (translateStartY - MousePos.Y) * translateSpeed; 
         translate.Z -= tvectX.X * (translateStartY - MousePos.Y) * translateSpeed; 

         oldTarget = translate; 
      } 
   } 
   else if (isKeyDown(KEY_UP) && !zooming) 
   { 
      if (!translating) 
         translating = true; 
      else 
      { 
         vector3df movevector = getPosition() - getTarget(); 
         movevector.Y = 0; 
         movevector.normalize(); 

         setPosition(getPosition() - movevector * translateSpeed); 
         setTarget(getTarget() - movevector * translateSpeed); 
         updateAbsolutePosition(); 
      } 
   } 
   else if (isKeyDown(KEY_DOWN) && !zooming) 
   { 
      if (!translating) 
         translating = true; 
      else 
      { 
         vector3df movevector = getPosition() - getTarget(); 
         movevector.Y = 0; 
         movevector.normalize(); 

         setPosition(getPosition() + movevector * translateSpeed); 
         setTarget(getTarget() + movevector * translateSpeed); 
         updateAbsolutePosition(); 
      } 
   } 
   else if (isKeyDown(KEY_LEFT) && !zooming) 
   { 
      if (!translating) 
         translating = true; 
      else 
      { 
         vector3df totargetvector = getPosition() - getTarget(); 
         totargetvector.normalize(); 
         vector3df crossvector = totargetvector.crossProduct(getUpVector()); 
         vector3df strafevector = crossvector.normalize(); 

         setPosition(getPosition() - strafevector * translateSpeed); 
         setTarget(getTarget() - strafevector * translateSpeed); 
         updateAbsolutePosition(); 
      } 
   } 
   else if (isKeyDown(KEY_RIGHT) && !zooming) 
   { 
      if (!translating) 
         translating = true; 
      else 
      { 
         vector3df totargetvector = getPosition() - getTarget(); 
         totargetvector.normalize(); 
         vector3df crossvector = totargetvector.crossProduct(getUpVector()); 
         vector3df strafevector = crossvector.normalize(); 

         setPosition(getPosition() + strafevector * translateSpeed); 
         setTarget(getTarget() + strafevector * translateSpeed); 
         updateAbsolutePosition(); 
      } 
   } 
   else 
   { 
      translating = false; 

      //This code is for the mouse at edge of screen stuff
      /*
      if (!translating && !zooming && !rotating) 
      { 
         //Mouse Coordinates go from 0 to 1 on both axes 
         if (MousePos.X < 0.05)   //Up 
         { 
            vector3df totargetvector = getPosition() - getTarget(); 
            totargetvector.normalize(); 
            vector3df crossvector = totargetvector.crossProduct(getUpVector()); 
            vector3df strafevector = crossvector.normalize(); 

            setPosition(getPosition() - strafevector * translateSpeed); 
            setTarget(getTarget() - strafevector * translateSpeed); 
            updateAbsolutePosition(); 
         } 
         else if (MousePos.X > 0.95) //Down 
         { 
            vector3df totargetvector = getPosition() - getTarget(); 
            totargetvector.normalize(); 
            vector3df crossvector = totargetvector.crossProduct(getUpVector()); 
            vector3df strafevector = crossvector.normalize(); 

            setPosition(getPosition() + strafevector * translateSpeed); 
            setTarget(getTarget() + strafevector * translateSpeed); 
            updateAbsolutePosition(); 
         } 
         else if (MousePos.Y < 0.05)   //Up 
         { 
            vector3df movevector = getPosition() - getTarget(); 
            movevector.Y = 0; 
            movevector.normalize(); 

            setPosition(getPosition() - movevector * translateSpeed); 
            setTarget(getTarget() - movevector * translateSpeed); 
            updateAbsolutePosition(); 
         } 
         else if (MousePos.Y > 0.95) //Down 
         { 
            vector3df movevector = getPosition() - getTarget(); 
            movevector.Y = 0; 
            movevector.normalize(); 

            setPosition(getPosition() + movevector * translateSpeed); 
            setTarget(getTarget() + movevector * translateSpeed); 
            updateAbsolutePosition(); 
         } 
      } 
      */
   } 

   //Set Position 
   Target = translate; 

   Pos.X = nZoom + Target.X; 
   Pos.Y = Target.Y; 
   Pos.Z = Target.Z; 

   Pos.rotateXYBy(nRotY, Target); 
   Pos.rotateXZBy(-nRotX, Target); 

   //Correct Rotation Error 
   UpVector.set(0,1,0); 
   UpVector.rotateXYBy(-nRotY, core::vector3df(0,0,0)); 
   UpVector.rotateXZBy(-nRotX+180.f, core::vector3df(0,0,0)); 
} 

void FollowCamera::updateAnimationState() 
{ 
   vector3df pos(Pos - Target); 

   // X rotation 
   vector2df vec2d(pos.X, pos.Z); 
   rotX = (f32)vec2d.getAngle(); 

   // Y rotation 
   pos.rotateXZBy(rotX, vector3df()); 
   vec2d.set(pos.X, pos.Y); 
   rotY = -(f32)vec2d.getAngle(); 

   // Zoom 
   currentZoom = (f32)Pos.getDistanceFrom(Target); 
}


