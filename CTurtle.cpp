//=============================================================================
#include "CTurtle.h"

//=============================================================================

CTurtle::CTurtle() {
}

//=============================================================================

bool CTurtle::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false){
	return false;
	}

	return true
}

//=============================================================================
void CTurtle::OnLoop(){
	CEntity::OnLoop();
	if(CurrentFrameRow == 0){
		faceRight = true;
		faceLeft = false;
	}
	else{
		faceRight = false;
		faceLeft = true;
	}
}

//=============================================================================
