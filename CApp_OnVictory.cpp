#include "CApp.h"

int CApp::OnVictory() {
	
	int victorySound;
	
	CSoundBank::SoundControl.OnCleanup();
	
	SDL_Surface* victoryScreen;
	if (( victoryScreen = CSurface::OnLoad("./images/gameOver/gameOver.png")) == false) return -1;
	
	if (( victorySound = CSoundBank::SoundControl.OnLoad("./sounds/victory.wav")) == -1) return -1;//load the victory music
	CSoundBank::SoundControl.Play(-1, victorySound, -1);//play the music
	
	CSurface::OnDraw(Surf_Display,victoryScreen,0,0);
	SDL_Flip(Surf_Display);

	bool gameOverRunning = true;
	
	SDL_Event event;
	while(gameOverRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:
							SDL_FreeSurface(victoryScreen);
							gameOverRunning = false;
							Running=false;
							break;
						default:
							break;
					}
					break;	
			}	
		}		
	}	
	
	
}	
