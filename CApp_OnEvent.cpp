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
				if (!Samus.morphBall) //as long as she is not in a ball, she can shoot
				{
					SDL_EnableKeyRepeat(0, 10000);
					CShot* Bullet = new CShot;
					Bullet->OnLoad("./images/shot.png", 8, 8, 0);
					if(Samus.faceRight){
						Bullet->faceRight = true;
						Bullet->faceLeft = false;
						Bullet->MoveRight = true;
						Bullet->MoveLeft = false;
						Bullet->X = Samus.X+30;
						Bullet->Y = Samus.Y+15;
						Bullet->SpeedX = 15;
					}
					if(Samus.faceLeft){
						Bullet->faceRight = false;
						Bullet->faceLeft = true;
						Bullet->MoveRight = false;
						Bullet->MoveLeft = true;
						Bullet->X = Samus.X;
						Bullet->Y = Samus.Y+15;
						Bullet->SpeedX = -15;
					}
					if(Samus.faceRight && Samus.PointUpDiagonal){
						Bullet->faceRight = true;
						Bullet->faceLeft = false;
						Bullet->MoveRight = true;
						Bullet->MoveLeft = false;
						Bullet->X = Samus.X+30;
						Bullet->Y = Samus.Y-4;
						Bullet->SpeedX = 10.605; //net velocity is 12
						Bullet->SpeedY = -10.605;
					}
					if(Samus.faceLeft && Samus.PointUpDiagonal){
						Bullet->faceRight = false;
						Bullet->faceLeft = true;
						Bullet->MoveRight = false;
						Bullet->MoveLeft = true;
						Bullet->X = Samus.X;
						Bullet->Y = Samus.Y;
						Bullet->SpeedX = -10.605;
						Bullet->SpeedY = -10.605;
					}
					if(Samus.faceRight && Samus.PointDownDiagonal){
						Bullet->faceRight = true;
						Bullet->faceLeft = false;
						Bullet->MoveRight = true;
						Bullet->MoveLeft = false;
						Bullet->X = Samus.X+30;
						Bullet->Y = Samus.Y+25;
						Bullet->SpeedX = 10.605;
						Bullet->SpeedY = 10.605;
					}
					if(Samus.faceLeft && Samus.PointDownDiagonal){
						Bullet->faceRight = false;
						Bullet->faceLeft = true;
						Bullet->MoveRight = false;
						Bullet->MoveLeft = true;
						Bullet->X = Samus.X;
						Bullet->Y = Samus.Y+18;
						Bullet->SpeedX = -10.605;
						Bullet->SpeedY = 10.605;
					}
					if(Samus.PointUp){ //trap the up shots
						if(Samus.faceRight){
							Bullet->faceRight = true;
							Bullet->faceLeft = false;
							Bullet->MoveRight = false;
							Bullet->MoveLeft = false;
							Bullet->X = Samus.X+8;
							Bullet->Y = Samus.Y-5;
							Bullet->SpeedX = 0;
							Bullet->SpeedY = -15;
						}
						if(Samus.faceLeft){
							Bullet->faceRight = false;
							Bullet->faceLeft = true;
							Bullet->MoveRight = false;
							Bullet->MoveLeft = false;
							Bullet->X = Samus.X+8;
							Bullet->Y = Samus.Y-5;
							Bullet->SpeedX = 0;
							Bullet->SpeedY = -15;
						}
					}
					if(Samus.Crouch){ //trap the crouching
						if(Samus.faceRight){
							Bullet->faceRight = true;
							Bullet->faceLeft = false;
							Bullet->MoveRight = true;
							Bullet->MoveLeft = false;
							Bullet->X = Samus.X+30;
							Bullet->Y = Samus.Y+22;
							Bullet->SpeedX = 15;
						}
						if(Samus.faceLeft){
							Bullet->faceRight = false;
							Bullet->faceLeft = true;
							Bullet->MoveRight = false;
							Bullet->MoveLeft = true;
							Bullet->X = Samus.X;
							Bullet->Y = Samus.Y+22;
							Bullet->SpeedX = -15;
						}
						if(Samus.faceRight && Samus.PointUpDiagonal){
							Bullet->faceRight = true;
							Bullet->faceLeft = false;
							Bullet->MoveRight = true;
							Bullet->MoveLeft = false;
							Bullet->X = Samus.X+30;
							Bullet->Y = Samus.Y+3;
							Bullet->SpeedX = 10.605;
							Bullet->SpeedY = -10.605;
						}
						if(Samus.faceLeft && Samus.PointUpDiagonal){
							Bullet->faceRight = false;
							Bullet->faceLeft = true;
							Bullet->MoveRight = false;
							Bullet->MoveLeft = true;
							Bullet->X = Samus.X;
							Bullet->Y = Samus.Y+8;
							Bullet->SpeedX = -10.605;
							Bullet->SpeedY = -10.605;
						}
						if(Samus.faceRight && Samus.PointDownDiagonal){
							Bullet->faceRight = true;
							Bullet->faceLeft = false;
							Bullet->MoveRight = true;
							Bullet->MoveLeft = false;
							Bullet->X = Samus.X+30;
							Bullet->Y = Samus.Y+30;
							Bullet->SpeedX = 10.605;
							Bullet->SpeedY = 10.605;
						}
						if(Samus.faceLeft && Samus.PointDownDiagonal){
							Bullet->faceRight = false;
							Bullet->faceLeft = true;
							Bullet->MoveRight = false;
							Bullet->MoveLeft = true;
							Bullet->X = Samus.X;
							Bullet->Y = Samus.Y+25;
							Bullet->SpeedX = -10.605;
							Bullet->SpeedY = 10.605;
						}
					}
					CEntity::EntityList.push_back(Bullet);
				}
				break;
				case SDLK_d: { //bomb button
					if (Samus.morphBall){ //if Samus is in her morphball
						SDL_EnableKeyRepeat(0, 10000);
						CExplode* bomb = new CExplode; //a new pointer to a bomb
						bomb->OnLoad("./images/Bomb.png", 28, 28, 0);
						if (Samus.faceLeft){
							bomb->X = Samus.X+3; //make the bomb match the position of Samus
							bomb->Y = Samus.Y+18;
						}
						if (Samus.faceRight){
							bomb->X = Samus.X+3; //make the bomb match the position of Samus
							bomb->Y = Samus.Y+18;
						}
						bomb->isbomb = 1; //make the effect an actual bomb
						bomb->fm = 5; //main bomb animation
						bomb->altframemax = 9; //explosion animation
						bomb->cyclelimit = 300;
						CEntity::EntityList.push_back(bomb); //push back the bomb into the list
					}
					break;
				}
			}
			
			case SDLK_r: {
				Samus.X = 100;
				Samus.Y = 500;
				Enemy1.X = 200;
				Enemy1.Y = 540;
				Enemy2.X = 600;
				Enemy2.Y = 560;
				Enemy3.X = 400;
				Enemy3.Y = 500;
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

			case SDLK_q: {
				if(Simon.Attack == false){
					SDL_EnableKeyRepeat(0, 10000);
					Simon.Attack = true;
					Simon.MoveRight = false;
					Simon.MoveLeft = false;
				}
				break;
			}

			case SDLK_LEFT: {
				if(Simon.Attack == false){
					Simon.MoveLeft = true;
					Simon.Crouch = false;
				}
				break;
			}
	
			case SDLK_RIGHT: {
				if(Simon.Attack == false){
					Simon.MoveRight = true;
					Simon.Crouch = false;
				}
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

			
			case SDLK_r: {
				Simon.X = 100;
				Simon.Y = 500;
				Enemy1.X = 200;
				Enemy1.Y = 540;
				Enemy2.X = 600;
				Enemy2.Y = 560;
				Enemy3.X = 400;
				Enemy3.Y = 500;
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
