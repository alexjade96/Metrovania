//=============================================================================
#include "CTurtle.h"

//=============================================================================

CTurtle::CTurtle() {
	MoveRight = true;
	MoveLeft = false;
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
	if(CurrentFrameRow == 0){
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
	CurrentFrameCol = 0;
	if(MoveLeft) {
		CurrentFrameRow = 0;
	} else {
		CurrentFrameRow = 1;
	}
}
//=============================================================================
bool CTurtle::OnCollision(CEntity* Entity) {
	if(faceRight){
		MoveLeft = true;
		MoveRight = false;
	}
	else{ 
		MoveRight = true;
		MoveLeft = false;
	}
	return true;
}
