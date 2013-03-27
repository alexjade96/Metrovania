//=============================================================================
#include "CPlayer.h"

//=============================================================================
CPlayer::CPlayer() {
	Crouch = false;
	PointUpDiagonal = false;
	PointDownDiagonal = false;
	morphBall = false;
}

//=============================================================================
bool CPlayer::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }

    return true;
}

//-----------------------------------------------------------------------------
void CPlayer::OnLoop() {
	CEntity::OnLoop();
}

//-----------------------------------------------------------------------------
void CPlayer::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);
}

//------------------------------------------------------------------------------
void CPlayer::OnCleanup() {
	CEntity::OnCleanup();
}

//------------------------------------------------------------------------------
void CPlayer::OnAnimate() {
	if(SpeedX != 0) {
		Anim_Control.MaxFrames = 10;
	}else{
		Anim_Control.MaxFrames = 0;
	}
	if(MoveLeft) {
		if (morphBall) {
			CurrentFrameCol = 3;
			CurrentFrameRow = 0;
			Anim_Control.MaxFrames = 8;
		} else if (PointUpDiagonal) {
			CurrentFrameCol = 5;
			CurrentFrameRow = 0;
		} else if (PointDownDiagonal) {
			CurrentFrameCol = 7;
			CurrentFrameRow = 0;
		} else {
			CurrentFrameCol = 1;
			CurrentFrameRow = 0;
		}
	}else

	if(MoveRight) {
		if (morphBall) {
			CurrentFrameCol = 2;
			CurrentFrameRow = 0;
			Anim_Control.MaxFrames = 8;
		}
		else if (PointUpDiagonal) {
			CurrentFrameCol = 4;
			CurrentFrameRow = 0;
		}
		else if (PointDownDiagonal) {
			CurrentFrameCol = 6;
			CurrentFrameRow = 0;
		}
		else {
		CurrentFrameCol = 0;
		CurrentFrameRow = 0;
		}
	}

	else if(PointUpDiagonal && !morphBall){
		if (CurrentFrameCol == 0) CurrentFrameCol = 4;
		if (CurrentFrameCol == 1) CurrentFrameCol = 5;
		if (!Crouch) CurrentFrameRow = 10;
		else CurrentFrameRow = 11;
		Anim_Control.MaxFrames = 0;
	}

	else if(PointDownDiagonal && !morphBall){
		if (CurrentFrameCol == 0) CurrentFrameCol = 6;
		if (CurrentFrameCol == 1) CurrentFrameCol = 7;
		if (!Crouch) CurrentFrameRow = 10;
		else CurrentFrameRow = 11;
		Anim_Control.MaxFrames = 0;
	}

	else if(Crouch) {
		if (CurrentFrameCol == 4 || CurrentFrameCol == 6) CurrentFrameCol = 0;
		if (CurrentFrameCol == 5 || CurrentFrameCol == 7) CurrentFrameCol = 1;
		CurrentFrameRow = 11;
		Anim_Control.MaxFrames = 0;
	}


	else if (morphBall) {
		if (CurrentFrameCol == 0 || CurrentFrameCol == 5 || CurrentFrameCol == 7) CurrentFrameCol = 2;
		if (CurrentFrameCol == 1 || CurrentFrameCol == 6 || CurrentFrameCol == 8) CurrentFrameCol = 3;
		CurrentFrameRow = 0;
		Anim_Control.MaxFrames = 8;	
	}	

	else {
		if (CurrentFrameCol == 0 || CurrentFrameCol == 2 || CurrentFrameCol == 4 || CurrentFrameCol == 6) {
			CurrentFrameCol = 0;
			if(PointUp) CurrentFrameRow = 12;
			else CurrentFrameRow = 10;
		}
		else {
			CurrentFrameCol = 1;
			if(PointUp) CurrentFrameRow = 12;
			else CurrentFrameRow = 10;
		}	
		Anim_Control.MaxFrames = 0;
	}	

	CEntity::OnAnimate();
}

//------------------------------------------------------------------------------
bool CPlayer::OnCollision(CEntity* Entity) {
	Jump();

	return true;
}

//=============================================================================
