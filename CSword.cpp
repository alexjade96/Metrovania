#include "CSword.h"

CSword::CSword() {
	Flags = ENTITY_FLAG_NONE;
	MaxSpeedX = 0;
	MaxSpeedY = 0;
}	


bool CSword::OnLoad(char* File, int Width, int Height, int MaxFrames){
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
   	     return false;
	}
	
	return true;
}
//-----------------------------------------------------------------------------
void CSword::OnLoop() {
	CEntity::OnLoop();
}


//-----------------------------------------------------------------------------
void CSword::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
}

//------------------------------------------------------------------------------
void CSword::OnCleanup() {
	CEntity::OnCleanup();
}

//------------------------------------------------------------------------------
void CSword::OnAnimate() {
	Anim_Control.MaxFrames = 0;
	CurrentFrameRow = 0;
	CEntity::OnAnimate();
	OnCleanup();
}

//------------------------------------------------------------------------------
bool CSword::OnCollision(CEntity* Entity) {
	if (Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >=100) {
		Entity->health++;
		Entity->healthTimer = 0;
	}	
	
	return true;
}
