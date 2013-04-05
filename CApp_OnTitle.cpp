#include "CApp.h"
#include "CSurface.h"

int CApp::OnTitle() {
	
	SDL_Surface* title;
	if ((title = CSurface::OnLoad("./images/titleScreen/TitleScreen.png")) == false) return -1;
	SDL_Surface* arrow;
	if ((arrow = CSurface::OnLoad("./images/titleScreen/arrow.png")) == false) return -1;


	SDL_Surface* screen = NULL;	
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
	
	CSurface::OnDraw(screen, title, 0,0);
	
	SDL_Flip(screen);
	
	SDL_Event event;
	bool titleRunning = true;
	bool choice1 = true;
	bool choice2 = false;
	
	while (titleRunning) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_UP:
							if (choice1) {
									
							}	
							else if (choice2) {
								
							}	
							break;
						case SDLK_DOWN:

							break;
						case SDLK_RETURN:
							if (choice1) { 
								metroid=true;
								castlevania=false;
								titleRunning=false;
							} else { 
								castlevania=true;
								metroid=false;
								titleRunning=false;
							}
							break;
						default:
							break;	
					}	
					break;
			}	
		}	
	}	
	
	SDL_FreeSurface(title);
	SDL_FreeSurface(arrow);
	
	SDL_Quit();
	
	return 0;	
	
}
