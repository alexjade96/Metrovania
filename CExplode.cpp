//=============================================================================
#include "CExplode.h"
#include "CApp.h"
#include "CSamus.h"
#include "CEntity.h"
#include <vector>
//=============================================================================
CExplode::CExplode(){
	Flags = ENTITY_FLAG_NONE;
	Type = 	ENTITY_TYPE_EFFECT;///////////changed this
	cycle = 0;
	MaxSpeedX = 0;
	MaxSpeedY = 0;
	fm = 1;
	cyclelimit = 100;
}

//-----------------------------------------------------------------------------
bool CExplode::OnLoad(char* File, int Width, int Height, int MaxFrames){
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
   	     return false;
	}
	
	return true;
}
//-----------------------------------------------------------------------------
void CExplode::OnLoop() {

	CEntity::OnLoop();
}


//-----------------------------------------------------------------------------
void CExplode::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
}

//------------------------------------------------------------------------------
void CExplode::OnCleanup() {
	CEntity::OnCleanup();
}

//------------------------------------------------------------------------------
void CExplode::OnAnimate() {
	CEntity::OnAnimate();
	Anim_Control.MaxFrames = 7;
	CurrentFrameRow = 0;
	CurrentFrameCol = 0;
	cycle++; //increment the cycle variable
	if (cycle >= cyclelimit) //n frames have been iterated over this time
	{
		Dead = true;
		OnCleanup(); //should erase the explosion
	}
}

//------------------------------------------------------------------------------
bool CExplode::OnCollision(CEntity* Entity) {
	return true;
}

//===============================================================
