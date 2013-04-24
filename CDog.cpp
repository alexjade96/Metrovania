#include "CDog.h"
#include "CSamus.h"
#include "CSimon.h"
#include "CApp.h"
#include "CSoundBank.h"
#include <iostream>
CDog::CDog() {

	Type = ENTITY_TYPE_DOG;

	Flags = ENTITY_FLAG_GRAVITY;

	MoveRight = false;
	faceRight = false;
	MoveLeft = true;
	faceLeft = true;
	collisionTimer = 0;
	
	MaxSpeedX = 12;
	MaxSpeedY = 6;
	SpeedX = 12;
	health = 0;
	Dead = false;
	moving = true;


}

//==================================================================
bool CDog::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
		return false;
	}
	if((dogGrowlSound = CSoundBank::SoundControl.OnLoad("./sounds/dogGrowl.wav")) == -1) {
		return false;
	}
	return true;
}

//===================================================================
void CDog::OnLoop() {
	CEntity::OnLoop();

	if (X-playerPos > 50) {
		faceLeft = true;
		faceRight = false;
	} else if (X-playerPos < -50) {
		faceRight = true;
		faceLeft = false;
	}
	if (Y-yPlayerPos > 100 || Y-yPlayerPos < -100) {
		moving = false;
		MoveRight = false;
		MoveLeft = false;
	} else if (X-playerPos > 320 || X-playerPos < -320) {
		moving = false;
		MoveRight = false;
		MoveLeft = false;
	}
	else {
		moving = true;
		if(faceRight) {
			MoveRight = true;
			MoveLeft = false;
		} else {
			MoveLeft = true;
			MoveRight = false;
		}
	}

	if(X-playerPos <=50 && X-playerPos >= -50 && CanJump && moving) {
		Jump();
		if(soundTimer > 500){
			CSoundBank::SoundControl.Play(-1, dogGrowlSound, 0);
			soundTimer = 0;
		}
	}	

	if(soundTimer <= 500) soundTimer++;

	if(collisionTimer <= 100) collisionTimer++;
}

//===================================================================
void CDog::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
}

//===================================================================
void CDog::OnCleanup() {
	CEntity::OnCleanup();
}

//===================================================================
void CDog::OnAnimate() {
	if(MoveLeft) {
		CurrentFrameCol = 1;
	} else {
		CurrentFrameCol = 0;
	}
	
	if (!moving) {
		Anim_Control.MaxFrames = 0;
		CurrentFrameRow = 0;
	} else {
		Anim_Control.MaxFrames = 5;
		CurrentFrameRow = 0;
	}		
	CEntity::OnAnimate();
}

//===================================================================
bool CDog::OnCollision(CEntity* Entity) {
	if (Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >=100) {
		Entity->health++;
		Entity->healthTimer = 0;
	}
	if(Entity->Type == ENTITY_TYPE_BULLET){
		health++;
	}
	if(Entity->Type == ENTITY_TYPE_BOMB){
		health+=20;
	}
	if(Entity->Type == ENTITY_TYPE_WHIP) Dead = true;
	if (health >= 50) Dead = true;
}

