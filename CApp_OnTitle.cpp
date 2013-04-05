#include "CApp.h"
#include "CSurface.h"

int CApp::OnTitle() {
		
	SDL_Surface* title;
	if ((title = CSurface::OnLoad("./images/titleScreen/TitleScreen.png")) == false) return -1;
	SDL_Surface* arrow;
	if ((arrow = CSurface::OnLoad("./images/titleScreen/arrow.png")) == false) return -1;


	CSurface::OnDraw(Surf_Display, title, 0,0);
	CSurface::OnDraw(Surf_Display, arrow, 240,230);
	
	SDL_Flip(Surf_Display);
	
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
								CSurface::OnDraw(Surf_Display, title, 0,0);
								choice1=false;
								choice2=true;
								CSurface::OnDraw(Surf_Display,arrow,240,270);
								SDL_Flip(Surf_Display);
							}	
							else if (choice2) {
								CSurface::OnDraw(Surf_Display, title, 0,0);
								choice1=true;
								choice2=false;
								CSurface::OnDraw(Surf_Display,arrow,240,230);
								SDL_Flip(Surf_Display);
							}	
							break;
						case SDLK_DOWN:
							if (choice1) {
								CSurface::OnDraw(Surf_Display, title, 0,0);
								choice1=false;
								choice2=true;
								CSurface::OnDraw(Surf_Display,arrow,240,270);
								SDL_Flip(Surf_Display);
							}	
							else if (choice2) {
								CSurface::OnDraw(Surf_Display, title, 0,0);
								choice1=true;
								choice2=false;
								CSurface::OnDraw(Surf_Display,arrow,240,230);
								SDL_Flip(Surf_Display);
							}	
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
						     return -1;
							break;	
					}	
					break;
			}	
		}	
	}	
	
	SDL_FreeSurface(title);
	SDL_FreeSurface(arrow);
	
	return 0;	
	
}
