//=============================================================================
#include "CSkeleton.h"
#include "CSamus.h"

//=============================================================================

CSkeleton::CSkeleton() {

	Type = 	ENTITY_TYPE_SKELETON;
	Flags = ENTITY_FLAG_GRAVITY;

	MoveRight = false;
	faceRight = false;
	MoveLeft = true;
	faceLeft = true;

	collisionTimer = 0;
	MaxSpeedX = 4;
	SpeedX = 4;
}

//=============================================================================

bool CSkeleton::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false){
	return false;
	}

	return true;
}

//=============================================================================
void CSkeleton::OnLoop(){
	CEntity::OnLoop();

	if(faceRight) {
		MoveRight = true;
		MoveLeft = false;
	}
	else if (faceLeft){
		MoveLeft = true;
		MoveRight = false;
	}

	if(SpeedX == 0 && faceRight) faceLeft = true;
	if(SpeedX == 0 && faceLeft) faceRight = true;

	if(collisionTimer < 100) collisionTimer++;
	else Flags = ENTITY_FLAG_NONE;
	
}

//=============================================================================
void CSkeleton::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
}

//=============================================================================
void CSkeleton::OnCleanup() {
	CEntity::OnCleanup();
}

//=============================================================================
void CSkeleton::OnAnimate() {
	CurrentFrameRow = 0;
	if (faceRight) {
		CurrentFrameCol = 0;
	} else {
		CurrentFrameCol = 1;
	}	
		
}
//=============================================================================
bool CSkeleton::OnCollision(CEntity* Entity) {

	if(Entity->Type != ENTITY_TYPE_BULLET){
		Flags = ENTITY_FLAG_MAPONLY;
		collisionTimer = 0;
	}

	if(Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >= 100){
		Entity->health++;
		Entity->healthTimer = 0;
	}
}
