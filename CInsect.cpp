//=============================================================================
#include "CInsect.h"
#include "CSamus.h"

//=============================================================================

CInsect::CInsect() {

	Type = 	ENTITY_TYPE_INSECT;

	Flags = ENTITY_FLAG_GRAVITY;

	MoveRight = false;
	faceRight = false;
	MoveLeft = true;
	faceLeft = true;
	jumpTimer = 0;

	SpeedX = 10;
}

//=============================================================================

bool CInsect::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false){
	return false;
	}

	return true;
}

//=============================================================================
void CInsect::OnLoop(){
	CEntity::OnLoop();

	if(faceRight && SpeedY != 0) {
		MoveRight = true;
		MoveLeft = false;
	}
	else if (faceLeft && SpeedY != 0){
		MoveLeft = true;
		MoveRight = false;
	}
	
	if (SpeedY == 0) {
		MoveLeft = false;
		MoveRight = false;
	}	
	
	if(CanJump && jumpTimer >= 100) {
		jumpTimer = 0;
		Jump();
	}	
	
}

//=============================================================================
void CInsect::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
}

//=============================================================================
void CInsect::OnCleanup() {
	CEntity::OnCleanup();
}

//=============================================================================
void CInsect::OnAnimate() {
	CurrentFrameCol = 0;
	if (CanJump && jumpTimer < 100) {
		CurrentFrameRow = 2;
		Anim_Control.MaxFrames = 0;
		jumpTimer++;
	} else {
		CurrentFrameRow = 0;
		Anim_Control.MaxFrames = 2;
	}	
		
}
//=============================================================================
bool CInsect::OnCollision(CEntity* Entity) {
	if(Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >= 100){
		Entity->health--;
		Entity->healthTimer = 0;
	}
}