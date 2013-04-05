#include "CApp.h"

int CApp::OnGameOver() {

	SDL_Surface* gameover;
	if ((gameover = CSurface::OnLoad("./images/gameOver/gameOver.png")) == false) return -1;
	
	CSurface::OnDraw(Surf_Display, gameover, 0,0);
	
	SDL_Flip(Surf_Display);
	
	SDL_Delay(5000);

	Running=false;
}	
