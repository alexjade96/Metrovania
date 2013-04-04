#include "CApp.h"

int CApp::OnTitle() {
	SDL_Surface* test = NULL;
	SDL_Surface* screen = NULL;
	
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
	
	test = IMG_Load("images/titleScreen/TitleScreen.png");
	
	SDL_BlitSurface(test, NULL, screen, NULL);
	
	SDL_Flip(screen);
	
	SDL_Event event;
	bool titleRunning = true;
	
	while (titleRunning) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_1:
							metroid = true;
							castlevania = false;
							titleRunning = false;
							break;
						case SDLK_2:
							metroid = false;
							castlevania = true;
							titleRunning = false;
							break;
						default:
							metroid = true;
							castlevania = false;
							titleRunning = false;
					}	
					break;
			}	
		}	
	}	
	
	SDL_FreeSurface(test);
	
	SDL_Quit();
	
	return 0;	
	
}
