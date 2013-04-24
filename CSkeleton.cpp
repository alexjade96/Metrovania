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
	
	upSword.Dead = true;
	outSword.Dead = true;
	
	upSword.Type = ENTITY_TYPE_SWORD1;
	outSword.Type = ENTITY_TYPE_SWORD2;
}

//=============================================================================

bool CSkeleton::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false){
	return false;
	}
	
	upSword.OnLoad("./images/sword1.png", 17, 16, 2);
	outSword.OnLoad("./images/sword2.png", 25, 8, 2);

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
	
	if (swordOut && AttackTimer > 30 && AttackTimer <=60) {
		upSword.Dead = false;
		outSword.Dead = true;
		if (faceRight) {
			upSword.X = X + 7;
			upSword.Y = Y - 16;
			upSword.CurrentFrameCol = 1;
		}	
		else if (faceLeft) {
			upSword.X = X + 7;
			upSword.Y = Y - 16;
			upSword.CurrentFrameCol = 0;
		}	
	} 
	else if (swordOut && AttackTimer > 60 && AttackTimer <= 90) {
		upSword.Dead = true;
		outSword.Dead = false;
		if (faceRight) {
			outSword.X = X + 30;
			outSword.Y = Y + 15;
			outSword.CurrentFrameCol = 0;
		}
		else if (faceLeft) {
			outSword.X = X - 20;
			outSword.Y = Y + 15;
			outSword.CurrentFrameCol = 1;
		}		
	}

	if(!swordOut || AttackTimer < 30){
		upSword.Dead = true;
		outSword.Dead = true;
	}

	
	outSword.OnLoop();
	upSword.OnLoop();
	outSword.PosValid(outSword.X,outSword.Y);
	upSword.PosValid(upSword.X,upSword.Y);
}

//=============================================================================
void CSkeleton::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
	if (!upSword.Dead) upSword.OnRender(Surf_Display);
	if (!outSword.Dead) outSword.OnRender(Surf_Display);
}

//=============================================================================
void CSkeleton::OnCleanup() {
	CEntity::OnCleanup();
	upSword.OnCleanup();
	outSword.OnCleanup();
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
	
	upSword.OnAnimate();
	outSword.OnAnimate();
		
}
//=============================================================================
bool CSkeleton::OnCollision(CEntity* Entity) {

	if(Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >= 100){
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
