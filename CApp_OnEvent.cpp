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
			break;
		}

		case SDLK_RIGHT: {
			Player.MoveRight = true;
			break;
		}

		case SDLK_SPACE: {
   		Player.Jump();
	        break;
		}

		case SDLK_DOWN: {
			Player.Crouch = true;
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
			Player.Crouch = false;
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
