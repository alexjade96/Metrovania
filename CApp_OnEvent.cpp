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
				if(Samus.BulletCount > 9){
					Samus.BulletCount = 0;
				}
				Bullet[Samus.BulletCount].OnLoad("images/SuperMetroidSamus.gif", 9, 9, 0);
				if(Samus.faceRight){
					Bullet[Samus.BulletCount].faceRight = true;
					Bullet[Samus.BulletCount].faceLeft = false;
					Bullet[Samus.BulletCount].MoveRight = true;
					Bullet[Samus.BulletCount].MoveLeft = false;
					Bullet[Samus.BulletCount].X = Samus.X+50;
					Bullet[Samus.BulletCount].Y = Samus.Y+20;
					Bullet[Samus.BulletCount].SpeedX = 10;
				}
				if(Samus.faceLeft){
					Bullet[Samus.BulletCount].faceRight = false;
					Bullet[Samus.BulletCount].faceLeft = true;
					Bullet[Samus.BulletCount].MoveRight = false;
					Bullet[Samus.BulletCount].MoveLeft = true;
					Bullet[Samus.BulletCount].X = Samus.X;
					Bullet[Samus.BulletCount].Y = Samus.Y+50;
					Bullet[Samus.BulletCount].SpeedX = -10;
				}
				CEntity::EntityList.push_back(&Bullet[Samus.BulletCount]);
				Samus.BulletCount++;
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
	
			case SDLK_SPACE: {
				SDL_EnableKeyRepeat(0, 10000);
	   			Simon.Jump();
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
