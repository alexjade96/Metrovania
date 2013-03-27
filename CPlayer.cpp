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
	if(CurrentFrameCol == 0 || CurrentFrameCol == 2 || CurrentFrameCol == 4 || CurrentFrameCol == 6){
		faceRight = true;
		faceLeft = false;
	}
	else{
		faceRight = false;
		faceLeft = true;
	}
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
		CurrentFrameRow = 0;
		if (morphBall) {
			CurrentFrameCol = 3;
			Anim_Control.MaxFrames = 8;
		} else if (PointUpDiagonal) {
			CurrentFrameCol = 5;
		} else if (PointDownDiagonal) {
			CurrentFrameCol = 7;
		} else {
			CurrentFrameCol = 1;
		}
	}else

	if(MoveRight) {
		CurrentFrameRow = 0;
		if (morphBall) {
			CurrentFrameCol = 2;
			Anim_Control.MaxFrames = 8;
		}
		else if (PointUpDiagonal) {
			CurrentFrameCol = 4;
		}
		else if (PointDownDiagonal) {
			CurrentFrameCol = 6;
		}
		else {
		CurrentFrameCol = 0;
		}
	}

	else if(PointUpDiagonal && !morphBall){
		if (faceRight) CurrentFrameCol = 4;
		if (faceLeft) CurrentFrameCol = 5;
		if (!Crouch) CurrentFrameRow = 10;
		else CurrentFrameRow = 11;
		Anim_Control.MaxFrames = 0;
	}

	else if(PointDownDiagonal && !morphBall){
		if (faceRight) CurrentFrameCol = 6;
		if (faceLeft) CurrentFrameCol = 7;
		if (!Crouch) CurrentFrameRow = 10;
		else CurrentFrameRow = 11;
		Anim_Control.MaxFrames = 0;
	}

	else if(Crouch) {
		if (faceRight) CurrentFrameCol = 0;
		if (faceLeft) CurrentFrameCol = 1;
		CurrentFrameRow = 11;
		Anim_Control.MaxFrames = 0;
	}


	else if (morphBall) {
		if (faceRight) CurrentFrameCol = 2;
		if (faceLeft) CurrentFrameCol = 3;
		CurrentFrameRow = 0;
		Anim_Control.MaxFrames = 8;	
	}	

	else {
		if (faceRight) {
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
