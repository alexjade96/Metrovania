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
	fm = 7; //general framerate
	cyclelimit = 100;
	health = 0; //health will act as a bomb timer
	isbomb = 0; //not a bomb
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
	if (!isbomb) //if this effect is not a bomb
	{
		Anim_Control.MaxFrames = fm;
		CurrentFrameRow = 0;
		CurrentFrameCol = 0;
		cycle++; //increment the cycle variable
	}else{ //if isbomb is true
		if (health <260) health++; //increment the health
		
	}
	if ((health >= 260)&&(isbomb))
	{
		Anim_Control.MaxFrames = altframemax; //changes to the explosion frames
		CurrentFrameRow = 0;
		CurrentFrameCol = 1; //for the explosion animation
		Type = 	ENTITY_TYPE_BOMB; //make this bomb collidable with other objects
		cycle++; //increment cycle
	}
	if (cycle >= cyclelimit) //n frames have been iterated over this time
	{
		Dead = true;
		OnCleanup(); //should erase the explosion
	}
}

//------------------------------------------------------------------------------
bool CExplode::OnCollision(CEntity* Entity) {

	//I want to make her jump but I cannot as of now. I am confused.
	if(!(Entity->Type==ENTITY_TYPE_PLAYER) && (isbomb)) //if an enemy
	{
		Entity->health += 5; //big damage from the bomb
	}
	return true;
}

//===============================================================
