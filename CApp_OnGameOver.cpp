#include "CApp.h"

int CApp::OnGameOver() {

	SDL_Surface* gameover;
	if ((gameover = CSurface::OnLoad("./images/gameOver/gameOver.png")) == false) return -1;
	
	SDL_Surface* simonDeath;
	if ((simonDeath = CSurface::OnLoad("./images/simondeath.png")) == false) return -1;
	SDL_Surface* samusDeath;
	if ((samusDeath = CSurface::OnLoad("./images/samusdeath.png")) == false) return -1;
	
	CSurface::OnDraw(Surf_Display, gameover, 0,0);
	
	if (metroid) {
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
		CSurface::OnDraw(Surf_Display, simonDeath, 285, 232, 0, 0, 65,32);
		SDL_Flip(Surf_Display);
	}		
	
	SDL_Delay(1000);
	
	SDL_FreeSurface(simonDeath);
	SDL_FreeSurface(samusDeath);
	SDL_FreeSurface(gameover);

	Running=false;
}	
