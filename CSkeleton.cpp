//=============================================================================
#include "CSkeleton.h"
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
	AttackTimer = 0;
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


	if (X-playerPos > 30) {
		faceLeft = true;
		faceRight = false;
	} else if (X-playerPos < -30) {
		faceRight = true;
		faceLeft = false;
	}

	if (X-playerPos <=50 && X-playerPos >= -50) {
		swordOut = true;
	} else {
		swordOut = false;		
	}	
	
	if (swordOut && AttackTimer <= 90) { 
		AttackTimer++;
	}
	else if (swordOut && AttackTimer > 90) {
		AttackTimer = 0;
		swordOut = false;
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
		Anim_Control.MaxFrames = 0;
		if(AttackTimer < 30) CurrentFrameRow = 0;
		else if (AttackTimer < 60) CurrentFrameRow = 1;
		else CurrentFrameRow = 2;	
		if (faceRight) {
			CurrentFrameCol = 2;
		} else if (faceLeft) {
			CurrentFrameCol = 3;
		}		
	} else {
		CurrentFrameRow = 0;
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
	if(Entity->Type == ENTITY_TYPE_WHIP) Dead = true;
}
