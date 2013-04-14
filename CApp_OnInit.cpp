//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    
    if (OnTitle() != 0) Running = false;

    if(CArea::AreaControl.OnLoad("./maps/2.area") == false) {
    	return false;
    }

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	if(metroid){
		if(Samus.OnLoad("images/samusanim.png", 30, 40, 11) == false) {
			return false;
		}
	}

	if(castlevania){
		if(Simon.OnLoad("images/simonanim.png", 30, 50, 13) == false){
			return false;
		}
	}

	if(Enemy1.OnLoad("images/Enemy1.png", 40, 17, 6) == false) {
	return false;
	}
	
	if(Enemy2.OnLoad("images/Enemy2.png",58,49,3) == false) {
	return false;	
	}

	if(Enemy3.OnLoad("images/skeleton.png", 33, 52, 3) == false){
		return false;
	}

	if(metroid){
		Samus.X = 100;
		Samus.Y = 500;
	}

	if(castlevania){
		Simon.X = 100;
		Simon.Y = 500;
	}

	Enemy1.X = 200;
	Enemy1.Y = 540;
	Enemy2.X = 600;
	Enemy2.Y = 560;
	Enemy3.X = 400;
	Enemy3.Y = 500;

	if(metroid) CEntity::EntityList.push_back(&Samus);
	if(castlevania) CEntity::EntityList.push_back(&Simon);
	CEntity::EntityList.push_back(&Enemy1);
	CEntity::EntityList.push_back(&Enemy2);
	CEntity::EntityList.push_back(&Enemy3);

	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
   	if(metroid) CCamera::CameraControl.SetTarget(&Samus.X, &Samus.Y);
	if(castlevania) CCamera::CameraControl.SetTarget(&Simon.X, &Simon.Y);

    return true;
}

//==============================================================================
