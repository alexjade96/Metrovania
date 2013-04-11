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
	swordOut = false;

	collisionTimer = 0;
	MaxSpeedX = 4;
	SpeedX = 4;
	health = 0;
	Dead = false;
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

	//check to see if player in range
	if (true) {
		swordOut = true;
	}	
	
	if (swordOut) {	
		if (faceRight) {
			MoveRight = false;	
		}	
		else if (faceLeft) {
			MoveLeft = false;
		}	
	}
	else if(faceRight) {
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
	
	CurrentFrameRow = 0;
	if (swordOut) {
		Anim_Control.MaxFrames = 4;
		if (faceRight) {
			CurrentFrameCol = 2;
		} else if (faceLeft) {
			CurrentFrameCol = 3;
		}		
	} else {
		Anim_Control.MaxFrames = 3;
		if (faceRight) {
			CurrentFrameCol = 0;
		} else {
			CurrentFrameCol = 1;
		}
	}
	CEntity::OnAnimate();
		
}
//=============================================================================
bool CSkeleton::OnCollision(CEntity* Entity) {

	if(Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >= 100){
		Entity->health++;
		Entity->healthTimer = 0;
	}
	if(Entity->Type == ENTITY_TYPE_BULLET){
		health++;
		if (health >= 50) Dead = true;
	}
}
