//=============================================================================
#include "CDog.h"
#include "CSamus.h"

//=============================================================================

CDog::CDog() {

	Type = 	ENTITY_TYPE_DOG;

	Flags = ENTITY_FLAG_GRAVITY;

	MoveRight = false;
	faceRight = false;
	MoveLeft = true;
	faceLeft = true;
	collisionTimer = 0;
	SpeedX = 10;
	health = 0;
	MaxSpeedY = 5;
	Dead = false;
}

//=============================================================================

bool CDog::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false){
	return false;
	}

	return true;
}

//=============================================================================
void CDog::OnLoop(){
	CEntity::OnLoop();

	if(faceRight) {
		MoveRight = true;
		MoveLeft = false;
	}
	else if (faceLeft){
		MoveLeft = true;
		MoveRight = false;
	}	
	
	if(CanJump && jumpTimer >= 100) {
		jumpTimer = 0;
		Jump();
	}	

	if(collisionTimer <= 100) collisionTimer++;
	
}

//=============================================================================
void CDog::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
}

//=============================================================================
void CDog::OnCleanup() {
	CEntity::OnCleanup();
}

//=============================================================================
void CDog::OnAnimate() {
	CurrentFrameCol = 0;
	if (CanJump && jumpTimer < 100) {
		CurrentFrameRow = 0;
		Anim_Control.MaxFrames = 4;
		jumpTimer++;
	} else {
		CurrentFrameRow = 4;
		Anim_Control.MaxFrames = 0;
	}
	CEntity::OnAnimate();
		
}
//=============================================================================
bool CDog::OnCollision(CEntity* Entity) {

	if(Entity->Type == ENTITY_TYPE_PLAYER) SpeedY = MaxSpeedY;

	if(Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >= 100) {
		Entity->health++;
		Entity->healthTimer = 0;
	}
	if(Entity->Type == ENTITY_TYPE_BULLET){
		health++;
		if (health >= 50) Dead = true;
	}
	if(Entity->Type == ENTITY_TYPE_WHIP) Dead = true;

}
