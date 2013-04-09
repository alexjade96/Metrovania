#include "CApp.h"
#include "CSurface.h"

int CApp::OnTitle() {
		
	SDL_Surface* title;
	if ((title = CSurface::OnLoad("./images/titleScreen/TitleScreen.png")) == false) return -1;
	SDL_Surface* arrow;
	if ((arrow = CSurface::OnLoad("./images/titleScreen/arrow.png")) == false) return -1;
	SDL_Surface* intro;


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
								if (( intro = CSurface::OnLoad("./images/titleScreen/samusintro.png")) == false) return -1;
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 0, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(1000);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 30, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 60, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 90, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 120, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 150, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 180, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 210, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 240, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								metroid=true;
								castlevania=false;
								titleRunning=false;
							} else { 
								if (( intro = CSurface::OnLoad("./images/titleScreen/simonintro.png")) == false) return -1;
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 0, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(1000);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 80, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 160, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 240, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 320, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 400, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 480, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 560, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(1000);
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
