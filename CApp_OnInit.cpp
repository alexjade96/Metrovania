//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    
    if (OnTitle() != 0) Running = false;
    
    SDL_Delay(2000);

    if(CArea::AreaControl.OnLoad("./maps/test.area") == false) {
    	return false;
    }

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
    
    int backgroundMusic;

	if(metroid){
		if(Samus.OnLoad("images/samusanim.png", 30, 40, 11) == false) {
			return false;
		}
		if((attackSound = CSoundBank::SoundControl.OnLoad("./sounds/shot.wav")) == -1) {
			return false;
		}
		if((backgroundMusic = CSoundBank::SoundControl.OnLoad("./sounds/samusBackground.wav")) == -1) {
			return false;
		}	
		CSoundBank::SoundControl.Play(-1,backgroundMusic, -1);
	}

	if(castlevania){
		if(Simon.OnLoad("images/simonanim.png", 30, 50, 13) == false){
			return false;
		}
		if((attackSound = CSoundBank::SoundControl.OnLoad("./sounds/whip.wav")) == -1) {
			return false;
		}
		if((backgroundMusic = CSoundBank::SoundControl.OnLoad("./sounds/simonBackground.wav")) == -1) {
			return false;
		}	
		CSoundBank::SoundControl.Play(-1,backgroundMusic, -1);
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
	
	if(Enemy4.OnLoad("images/dog.png",43,26, 5) == false) {
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
	Enemy3.X = 500;
	Enemy3.Y = 550;
	Enemy4.X = 350;
	Enemy4.Y = 560;

	if(metroid) CEntity::EntityList.push_back(&Samus);
	if(castlevania) CEntity::EntityList.push_back(&Simon);
	CEntity::EntityList.push_back(&Enemy1);
	CEntity::EntityList.push_back(&Enemy2);
	CEntity::EntityList.push_back(&Enemy3);
	CEntity::EntityList.push_back(&Enemy4);

	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
   	if(metroid) CCamera::CameraControl.SetTarget(&Samus.X, &Samus.Y);
	if(castlevania) CCamera::CameraControl.SetTarget(&Simon.X, &Simon.Y);

    return true;
}

//==============================================================================
