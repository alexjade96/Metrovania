//==============================================================================
#include "CApp.h"
#include <iostream>
//==============================================================================
bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {//init SDL
        return false;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {//init sound
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {//init the window
        return false;
    }
    
    if (OnTitle() != 0) Running = false;//check to see if the title screen is still going
    
    SDL_Delay(2000);// do nothing

    if(CArea::AreaControl.OnLoad("./maps/test.area") == false) {//load the map
    	return false;
    }

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);//make it so that a button repeats if held down
    
    int backgroundMusic;//declare background sound

	if(metroid){//if we are playing samus
		if(Samus.OnLoad("images/samusanim.png", 30, 40, 11) == false) {//load samus image
			return false;
		}
		if((attackSound = CSoundBank::SoundControl.OnLoad("./sounds/shot.wav")) == -1) {//load her shot sound
			return false;
		}
		if((backgroundMusic = CSoundBank::SoundControl.OnLoad("./sounds/samusBackground.wav")) == -1) {//load her background music
			return false;
		}	
		CSoundBank::SoundControl.Play(-1,backgroundMusic, -1);//play her background music
	}

	if(castlevania){//if we are playing simon
		if(Simon.OnLoad("images/simonanim.png", 30, 50, 13) == false){//load his image
			return false;
		}
		if((attackSound = CSoundBank::SoundControl.OnLoad("./sounds/whip.wav")) == -1) {//load his whip sound
			return false;
		}
		if((backgroundMusic = CSoundBank::SoundControl.OnLoad("./sounds/simonBackground.wav")) == -1) {//loadload his background music
			return false;
		}	
		CSoundBank::SoundControl.Play(-1,backgroundMusic, -1);//play his background music
	}

	//load all the enemys
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

	//load the image for the enemy counter
	if((Surf_Counter = CSurface::OnLoad("./images/numberChart.png")) == false ) return false;


	//init samus position if we are playing her
	if(metroid){
		Samus.X = 100;
		Samus.Y = 500;
	}

	//init simon posiiton if we are playing him
	if(castlevania){
		Simon.X = 100;
		Simon.Y = 500;
	}

	//init enemy positions
	Enemy1.X = 200;
	Enemy1.Y = 540;
	Enemy2.X = 600;
	Enemy2.Y = 560;
	Enemy3.X = 500;
	Enemy3.Y = 550;
	Enemy4.X = 350;
	Enemy4.Y = 560;

	//push all the entitys into the entity list
	if(metroid) CEntity::EntityList.push_back(&Samus);
	if(castlevania) CEntity::EntityList.push_back(&Simon);
	CEntity::EntityList.push_back(&Enemy1);
	CEntity::EntityList.push_back(&Enemy2);
	CEntity::EntityList.push_back(&Enemy3);
	CEntity::EntityList.push_back(&Enemy4);

	//set camera to follow the player
	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
   	if(metroid) CCamera::CameraControl.SetTarget(&Samus.X, &Samus.Y);
	if(castlevania) CCamera::CameraControl.SetTarget(&Simon.X, &Simon.Y);

    return true;
}

//==============================================================================
