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

    if(CArea::AreaControl.OnLoad("./maps/1.area") == false) {
    	return false;
    }

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    if(Player.OnLoad("images/samusanim.png", 30, 40, 10) == false) {
    	return false;
    }

   /* if(Player2.OnLoad("images/samusanim.png", 30, 40, 10) == false) {
    	return false;
    } */

	if(Enemy1.OnLoad("images/Enemy1.png", 40, 17, 5) == false) {
	return false;
	}
	
	if(Enemy2.OnLoad("images/Enemy2.png",58,49,2) == false) {
	return false;	
	}	

	Player.X = 100;
	Player.Y = 560;
	//Player2.X = 500;
	Enemy1.X = 150;
	Enemy1.Y = 560;
	Enemy2.X = 600;
	Enemy2.Y = 560;

	CEntity::EntityList.push_back(&Player);
	//CEntity::EntityList.push_back(&Player2);
	CEntity::EntityList.push_back(&Enemy1);
	CEntity::EntityList.push_back(&Enemy2);

	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
   	CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);

    return true;
}

//==============================================================================
