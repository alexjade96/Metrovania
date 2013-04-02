//=============================================================================
#include "CTurtle.h"
#include "CSamus.h"

//=============================================================================

CTurtle::CTurtle() {

	Type = 	ENTITY_TYPE_GENERIC;

	Flags = ENTITY_FLAG_NONE;

	MoveRight = false;
	faceRight = false;
	MoveLeft = true;
	faceLeft = true;

	SpeedX = 10;
}

//=============================================================================

bool CTurtle::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false){
	return false;
	}

	return true;
}

//=============================================================================
void CTurtle::OnLoop(){
	CEntity::OnLoop();
	if(CurrentFrameCol == 0){
		faceRight = true;
		faceLeft = false;
	}
	else{
		faceRight = false;
		faceLeft = true;
	}
	if(faceRight) {
		MoveRight = true;
		MoveLeft = false;
	}
	else{
		MoveLeft = true;
		MoveRight = false;
	}

	if(SpeedX == 0){
		if(faceRight){
			faceRight = false;
			MoveRight = false;
			faceLeft = true;
			MoveLeft = true;
			}
		else{
			faceLeft = false;
			MoveLeft = false;
			faceRight = true;
			MoveRight = true;
		}
	}
	
}

//=============================================================================
void CTurtle::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
}

//=============================================================================
void CTurtle::OnCleanup() {
	CEntity::OnCleanup();
}

//=============================================================================
void CTurtle::OnAnimate() {
	Anim_Control.MaxFrames = 5;
	CurrentFrameRow = 0;
	if(MoveLeft) {
		CurrentFrameCol = 1;
	} else {
		CurrentFrameCol = 0;
	}
}
//=============================================================================
bool CTurtle::OnCollision(CEntity* Entity) {

	if(Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >= 100){
		Entity->health++;
		Entity->healthTimer = 0;
	}


}
