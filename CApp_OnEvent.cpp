//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

//==============================================================================
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {

	if(metroid){
		switch(sym) {
			case SDLK_LEFT: {
				Samus.MoveLeft = true;
				Samus.Crouch = false;
				break;
			}
	
			case SDLK_RIGHT: {
				Samus.MoveRight = true;
				Samus.Crouch = false;
				break;
			}
	
			case SDLK_SPACE: {
				SDL_EnableKeyRepeat(0, 10000);
	   			Samus.Jump();
		        break;
			}
	
			case SDLK_UP: {
				SDL_EnableKeyRepeat(0, 10000);
				if (Samus.morphBall) {
					Samus.morphBall = false;
					Samus.Crouch = true;
				} else if (Samus.Crouch) {
					Samus.Crouch = false;
				}
				else Samus.PointUp = true;
				break;
			}
	
			case SDLK_DOWN: {
				SDL_EnableKeyRepeat(0, 10000);
				if (Samus.Crouch) {
					Samus.morphBall = true;
					Samus.Crouch = false;
				}else if(!Samus.morphBall) {
					Samus.Crouch = true;
					Samus.morphBall = false;
				}
				break;
			}
	
			case SDLK_w: {
				Samus.PointUpDiagonal = true;
				break;
			}  
	
			case SDLK_s: {
				Samus.PointDownDiagonal = true;
				break;
			}

			case SDLK_q: {
				SDL_EnableKeyRepeat(0, 10000);
				CShot* Bullet = new CShot;
				Bullet->OnLoad("images/SuperMetroidSamus.gif", 9, 9, 0);
				if(Samus.faceRight){
					Bullet->faceRight = true;
					Bullet->faceLeft = false;
					Bullet->MoveRight = true;
					Bullet->MoveLeft = false;
					Bullet->X = Samus.X+30;
					Bullet->Y = Samus.Y+15;
					Bullet->SpeedX = 12;
				}
				if(Samus.faceLeft){
					Bullet->faceRight = false;
					Bullet->faceLeft = true;
					Bullet->MoveRight = false;
					Bullet->MoveLeft = true;
					Bullet->X = Samus.X;
					Bullet->Y = Samus.Y+15;
					Bullet->SpeedX = -12;
				}
				if(Samus.faceRight && Samus.PointUpDiagonal){
					Bullet->faceRight = true;
					Bullet->faceLeft = false;
					Bullet->MoveRight = true;
					Bullet->MoveLeft = false;
					Bullet->X = Samus.X+30;
					Bullet->Y = Samus.Y-4;
					Bullet->SpeedX = 12;
					Bullet->SpeedY = -12;
				}
				if(Samus.faceLeft && Samus.PointUpDiagonal){
					Bullet->faceRight = false;
					Bullet->faceLeft = true;
					Bullet->MoveRight = false;
					Bullet->MoveLeft = true;
					Bullet->X = Samus.X;
					Bullet->Y = Samus.Y;
					Bullet->SpeedX = -12;
					Bullet->SpeedY = -12;
				}
				if(Samus.faceRight && Samus.PointDownDiagonal){
					Bullet->faceRight = true;
					Bullet->faceLeft = false;
					Bullet->MoveRight = true;
					Bullet->MoveLeft = false;
					Bullet->X = Samus.X+30;
					Bullet->Y = Samus.Y+25;
					Bullet->SpeedX = 12;
					Bullet->SpeedY = 12;
				}
				if(Samus.faceLeft && Samus.PointDownDiagonal){
					Bullet->faceRight = false;
					Bullet->faceLeft = true;
					Bullet->MoveRight = false;
					Bullet->MoveLeft = true;
					Bullet->X = Samus.X;
					Bullet->Y = Samus.Y+18;
					Bullet->SpeedX = -12;
					Bullet->SpeedY = 12;
				}
				CEntity::EntityList.push_back(Bullet);
				break;
			}
	

			case SDLK_ESCAPE: {
				OnExit();
			break;
			}

			default: {
			}
		}
	}
	if(castlevania){
		switch(sym) {
			case SDLK_LEFT: {
				Simon.MoveLeft = true;
				Simon.Crouch = false;
				break;
			}
	
			case SDLK_RIGHT: {
				Simon.MoveRight = true;
				Simon.Crouch = false;
				break;
			}

			case SDLK_a: {
				Simon.Taunt = true;
				break;
			}
	
			case SDLK_SPACE: {
				SDL_EnableKeyRepeat(0, 10000);
	   			Simon.Jump();
		        	break;
			}

			case SDLK_UP: {
				Simon.Crouch = false;
				break;
			}

			case SDLK_DOWN: {
				Simon.Crouch = true;
				break;
			}

			case SDLK_ESCAPE: {
				OnExit();
			break;
			}

			default: {
			}
		}
	}
}

//------------------------------------------------------------------------------
void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	if(metroid){
		switch(sym) {
			case SDLK_LEFT: {
				Samus.MoveLeft = false;
				break;
			}

			case SDLK_RIGHT: {
				Samus.MoveRight = false;
				break;
			}

			case SDLK_UP: {
				Samus.PointUp = false;
				break;
			}

			case SDLK_DOWN: {
				break;
			}

			case SDLK_w: {
				Samus.PointUpDiagonal = false;
				break;
			}

			case SDLK_s: {
				Samus.PointDownDiagonal = false;
				break;
			}


			default: {
			}
		}
	}
	if(castlevania){
		switch(sym) {
			case SDLK_LEFT: {
				Simon.MoveLeft = false;
				break;
			}

			case SDLK_RIGHT: {
				Simon.MoveRight = false;
				break;
			}

			case SDLK_a: {
				Simon.Taunt = false;
			}

			default: {
			}
		}
	}
}

//------------------------------------------------------------------------------
void CApp::OnExit() {
	Running = false;
}

//==============================================================================
