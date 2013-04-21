#include "CApp.h"

int CApp::OnGameOver() {
	
	int gameOverSound;
	
	CSoundBank::SoundControl.OnCleanup();

	SDL_Surface* gameover;
	if ((gameover = CSurface::OnLoad("./images/gameOver/gameOver.png")) == false) return -1;
	
	SDL_Surface* simonDeath;
	if ((simonDeath = CSurface::OnLoad("./images/simondeath.png")) == false) return -1;
	SDL_Surface* samusDeath;
	if ((samusDeath = CSurface::OnLoad("./images/samusdeath.png")) == false) return -1;
	
	CSurface::OnDraw(Surf_Display, gameover, 0,0);
	
	if (metroid) {
		if (( gameOverSound = CSoundBank::SoundControl.OnLoad("./sounds/samusDeathSound.wav")) == -1) return -1;
		CSoundBank::SoundControl.Play(-1, gameOverSound, -1);
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 0, 70, 90);
		SDL_Flip(Surf_Display);
		SDL_Delay(1000);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 90, 70, 90);
		SDL_Flip(Surf_Display);
		SDL_Delay(200);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 180, 70, 90);
		SDL_Flip(Surf_Display);
		SDL_Delay(200);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 270, 70, 90);
		SDL_Flip(Surf_Display);
		SDL_Delay(200);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 360, 70, 90);
		SDL_Flip(Surf_Display);
		SDL_Delay(200);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 450, 70, 90);
		SDL_Flip(Surf_Display);
		SDL_Delay(200);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 540, 70, 90);
		SDL_Flip(Surf_Display);
		SDL_Delay(1000);
	} else if (castlevania) {
		if (( gameOverSound = CSoundBank::SoundControl.OnLoad("./sounds/simonDeathSound.wav")) == -1) return -1;
		CSoundBank::SoundControl.Play(-1, gameOverSound, -1);
		CSurface::OnDraw(Surf_Display, simonDeath, 285, 220, 0, 0, 65,50);
		SDL_Flip(Surf_Display);
		SDL_Delay(1000);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, simonDeath, 285,220, 0,50, 65, 50);
		SDL_Flip(Surf_Display);
		SDL_Delay(500);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, simonDeath, 285,220, 0, 100, 65, 50);
		SDL_Flip(Surf_Display);
		SDL_Delay(500);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, simonDeath, 285, 220, 0, 150, 65, 50);
		SDL_Flip(Surf_Display);
		SDL_Delay(1500);
	}		
	
	bool gameOverRunning = true;
	
	SDL_Event event;
	while(gameOverRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:
							SDL_FreeSurface(simonDeath);
							SDL_FreeSurface(samusDeath);
							SDL_FreeSurface(gameover);
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
