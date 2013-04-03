//=============================================================================
#include "CSimon.h"
#include "CApp.h"
#include <iostream>
//=============================================================================
CSimon::CSimon() {
	Flags = ENTITY_FLAG_GRAVITY;
	Type = 	ENTITY_TYPE_PLAYER;
	Crouch = false;
	MoveLeft  = false;
	MoveRight = false;

	health = 0;
	healthTimer = 0;

}

//=============================================================================
bool CSimon::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }
	if((Surf_Health = CSurface::OnLoad("./images/hearts.png")) == false ) return false;

    return true;
}

//-----------------------------------------------------------------------------
void CSimon::OnLoop() {
	CEntity::OnLoop();
	if(CurrentFrameCol == 0){
		faceRight = true;
		faceLeft = false;
	}
	else{
		faceRight = false;
		faceLeft = true;
	}

	if(healthTimer < 100)healthTimer++;

	if(health >= 10) Dead = true;

}

//-----------------------------------------------------------------------------
void CSimon::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
	CSurface::OnDraw(Surf_Display, Surf_Health, 0, 0, 0, health*60, 160, 60);
}

//------------------------------------------------------------------------------
void CSimon::OnCleanup() {
	CEntity::OnCleanup();
	SDL_FreeSurface(Surf_Health);
}

//------------------------------------------------------------------------------
void CSimon::OnAnimate() {
	if(SpeedX != 0) {
		Anim_Control.MaxFrames = 12;
	}else{
		Anim_Control.MaxFrames = 0;
	}
	
	
	if(MoveLeft) {
		CurrentFrameRow = 0;
		CurrentFrameCol = 1;
	}
	
	else if(MoveRight) {
		CurrentFrameRow = 0;
		CurrentFrameCol = 0;
	}

	else {
		if (faceRight) {
			CurrentFrameCol = 0;
			CurrentFrameRow = 12;
		}
		else {
			CurrentFrameCol = 1;
			CurrentFrameRow = 12;
		}	
		Anim_Control.MaxFrames = 0;
	}	

	CEntity::OnAnimate();
}

//------------------------------------------------------------------------------
bool CSimon::OnCollision(CEntity* Entity) {
	return true;
}

//=============================================================================
