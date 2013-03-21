//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

//==============================================================================
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_LEFT: {
			Player.MoveLeft = true;
			Player.Crouch = false;
			break;
		}

		case SDLK_RIGHT: {
			Player.MoveRight = true;
			Player.Crouch = false;
			break;
		}

		case SDLK_SPACE: {
   			Player.Jump();
	        break;
		}

		case SDLK_UP: {
			if (Player.morphBall) {
				Player.morphBall = false;
				Player.Crouch = true;
			} else if (Player.Crouch) {
				Player.Crouch = false;
			}
			break;
		}

		case SDLK_DOWN: {
			if (Player.Crouch) {
				Player.morphBall = true;
				Player.Crouch = false;
			} else {
				Player.Crouch = true;
			}
			break;
		}

		case SDLK_w: {
			Player.PointUpDiagonal = true;
			break;
		}  

		case SDLK_s: {
			Player.PointDownDiagonal = true;
			break;
		}

		case SDLK_m: {
			Player.Crouch = false;
			Player.morphBall = false;
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

//------------------------------------------------------------------------------
void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_LEFT: {
			Player.MoveLeft = false;
			break;
		}

		case SDLK_RIGHT: {
			Player.MoveRight = false;
			break;
		}

		case SDLK_DOWN: {
			break;
		}

		case SDLK_w: {
			Player.PointUpDiagonal = false;
			break;
		}

		case SDLK_s: {
			Player.PointDownDiagonal = false;
			break;
		}


		default: {
		}
	}
}

//------------------------------------------------------------------------------
void CApp::OnExit() {
	Running = false;
}

//==============================================================================
