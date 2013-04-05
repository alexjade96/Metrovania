//=============================================================================
#include "CShot.h"
#include "CApp.h"
#include "CSamus.h"
#include "CEntity.h"
//=============================================================================
CShot::CShot(){
	Flags = ENTITY_FLAG_NONE;
	Type = ENTITY_TYPE_GENERIC;
}

//-----------------------------------------------------------------------------
bool CShot::OnLoad(char* File, int Width, int Height, int MaxFrames){
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
   	     return false;
	}
	
	return true;
}
//-----------------------------------------------------------------------------
void CShot::OnLoop() {
	CEntity::OnLoop();
}


//-----------------------------------------------------------------------------
void CShot::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
}

//------------------------------------------------------------------------------
void CShot::OnCleanup() {
	CEntity::OnCleanup();
}

//------------------------------------------------------------------------------
void CShot::OnAnimate() {
	CEntity::OnAnimate();
	Anim_Control.MaxFrames = 0;
	CurrentFrameRow = 55;
	CurrentFrameCol = 3;
}

//------------------------------------------------------------------------------
bool CShot::OnCollision(CEntity* Entity) {
	OnCleanup();
	return true;
}

//===============================================================
