//=============================================================================
#include "CSkeleton.h"
#include "CSamus.h"
#include <iostream>
//=============================================================================

CSkeleton::CSkeleton() {

	Type = 	ENTITY_TYPE_SKELETON;
	Flags = ENTITY_FLAG_GRAVITY;

	MoveRight = true;
	faceRight = true;
	MoveLeft = false;
	faceLeft = false;

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


	if(collisionTimer <= 200) collisionTimer++;
	
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
	Anim_Control.MaxFrames = 3;
	CurrentFrameRow = 0;
	if (faceRight) {
		CurrentFrameCol = 0;
	} else {
		CurrentFrameCol = 1;
	}
	CEntity::OnAnimate();
		
}
//=============================================================================
bool CSkeleton::OnCollision(CEntity* Entity) {

	if(Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >= 100){
		Entity->health++;
		Entity->healthTimer = 0;
	}
}
