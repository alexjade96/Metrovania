//==============================================================================
#include <iostream>
#include "CEntity.h"
//==============================================================================
std::vector<CEntity*> 	CEntity::EntityList;//entity vector that will hold all of the active entitys

//constructer
//==============================================================================
CEntity::CEntity() {

	CanJump = false;

	Surf_Entity = NULL;

	X = 0;
	Y = 0;

	Width 	= 0;
	Height 	= 0;

	Dead = false;

	SpeedX = 0;
	SpeedY = 0;

	AccelX = 0;
	AccelY = 0;

	MaxSpeedX = 10;
	MaxSpeedY = 10;

	CurrentFrameCol = 0;
	CurrentFrameRow = 0;

	Col_X = 0;
	Col_Y = 0;

	Col_Width  = 0;
	Col_Height = 0;
}

//deconstructer
//------------------------------------------------------------------------------
CEntity::~CEntity() {
}

//==============================================================================
bool CEntity::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if((Surf_Entity = CSurface::OnLoad(File)) == NULL) {//load the surface of the entity
		return false;
	}

	CSurface::Transparent(Surf_Entity, 255, 0, 255);//make it transparent

	this->Width = Width;//its width is equal to the width passed in
	this->Height = Height;//its height is equal to the height passed in

	Anim_Control.MaxFrames = MaxFrames;//its maxframes is equal to the maxframes passed in

    return true;
}

//------------------------------------------------------------------------------
void CEntity::OnLoop() {
	//We're not Moving
	if(MoveLeft == false && MoveRight == false ) {
		StopMove();
	}

	if(MoveLeft) {//moving left
		AccelX = -0.5;
	}else

	if(MoveRight) {//moving right
		AccelX = 0.5;
	}

	if(Flags & ENTITY_FLAG_GRAVITY) {//moving down due to gravity
		AccelY = 0.75f;
	}

	SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();//match the speed to the acceleration times the frames per second
	SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

	if(SpeedX > MaxSpeedX)  SpeedX =  MaxSpeedX;
	if(SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
	if(SpeedY > MaxSpeedY)  SpeedY =  MaxSpeedY;
	if(SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;

	OnAnimate();
	OnMove(SpeedX, SpeedY);
}

//------------------------------------------------------------------------------
void CEntity::OnRender(SDL_Surface* Surf_Display) {
    if(Surf_Entity == NULL || Surf_Display == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY(), CurrentFrameCol * Width,(CurrentFrameRow + Anim_Control.GetCurrentFrame()) * Height, Width, Height);
}

//------------------------------------------------------------------------------
void CEntity::OnCleanup() {

	if(Surf_Entity) SDL_FreeSurface(Surf_Entity);
	Surf_Entity = NULL;
	if(Type == ENTITY_TYPE_BULLET) Dead = true;
}

//------------------------------------------------------------------------------
void CEntity::OnAnimate() {
	
	Anim_Control.OnAnimate();
}

//------------------------------------------------------------------------------
bool CEntity::OnCollision(CEntity* Entity) {
}

//==============================================================================
void CEntity::OnMove(float MoveX, float MoveY) {

	CanJump = false;

	if(MoveX == 0 && MoveY == 0) return;

	double NewX = 0;
	double NewY = 0;

	MoveX *= CFPS::FPSControl.GetSpeedFactor();
	MoveY *= CFPS::FPSControl.GetSpeedFactor();

	if(MoveX != 0) {
		if(MoveX >= 0) 	NewX =  CFPS::FPSControl.GetSpeedFactor();
		else 			NewX = -CFPS::FPSControl.GetSpeedFactor();
	}

	if(MoveY != 0) {
		if(MoveY >= 0) 	NewY =  CFPS::FPSControl.GetSpeedFactor();
		else 			NewY = -CFPS::FPSControl.GetSpeedFactor();
	}

	while(true) {
		if(Flags & ENTITY_FLAG_GHOST) {
			PosValid((int)(X + NewX), (int)(Y + NewY)); //We don't care about collisions, but we need to send events to other entities

			X += NewX;
			Y += NewY;


		}else if (Type == ENTITY_TYPE_INSECT){
			if(PosValid((int)(X + NewX), (int)(Y))) {
				X += NewX;
			}else{
				if (faceLeft && collisionTimer > 100) {
					faceLeft = false;
					faceRight = true;
					collisionTimer = 0;
				} else if (faceRight && collisionTimer > 100) {
					faceRight = false;
					faceLeft = true;
					collisionTimer = 0;
				}		
				SpeedX = 0;
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {
				Y += NewY;
			}else{
    				if(MoveY > 0) {
    				    CanJump = true;
 			        }
				SpeedY = 0;
			}
		} else if (Type == ENTITY_TYPE_PLAYER) {
			if(PosValid((int)(X + NewX), (int)(Y))) {
				X += NewX;
			}else{
				SpeedX = 0;
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {
				Y += NewY;
			}else{
    				if(MoveY > 0) {
    				    CanJump = true;
 			        }
				
				SpeedY = 0;
			}		
		}else if (Type == ENTITY_TYPE_BULLET){
			if(PosValid((int)(X + NewX), (int)(Y))) {
				X += NewX;
			}else{
				OnCleanup();
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {
				Y += NewY;
			}else{
				OnCleanup();
			}
		}else if (Type == ENTITY_TYPE_SKELETON){
			if(PosValid((int)(X + NewX), (int)(Y))) {
				X += NewX;
			}else{
				if(faceRight && collisionTimer > 200){
					faceLeft = true;
					faceRight = false;
					MoveLeft = true;
					MoveRight = false;
					collisionTimer = 0;
					SpeedX = -MaxSpeedX;
				}
				else if(faceLeft && collisionTimer > 200){
					faceLeft = false;
					faceRight = true;
					MoveLeft = false;
					MoveRight = true;
					collisionTimer = 0;
					SpeedX = MaxSpeedX;
				}
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {
				Y += NewY;
			}else{
    				if(MoveY > 0) {
    				    CanJump = true;
 			        }
				
				SpeedY = 0;
			}		
		} else if (Type == ENTITY_TYPE_DOG) {
			if(PosValid((int)(X + NewX), (int)(Y))) {
				X += NewX;
			}else{
				if(faceRight && collisionTimer > 200){
					faceLeft = true;
					faceRight = false;
					MoveLeft = true;
					MoveRight = false;
					collisionTimer = 0;
					SpeedX = -MaxSpeedX;
				}
				else if(faceLeft && collisionTimer > 200){
					faceLeft = false;
					faceRight = true;
					MoveLeft = false;
					MoveRight = true;
					collisionTimer = 0;
					SpeedX = MaxSpeedX;
				}
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {
				Y += NewY;
			}else{
    				if(MoveY > 0) {
    				    CanJump = true;
 			        }
				
				SpeedY = 0;
			}	
		} else {
			if(PosValid((int)(X + NewX), (int)(Y))) {
				X += NewX;
			}else{
				if(faceRight && collisionTimer > 100){
					faceLeft = true;
					faceRight = false;
					MoveLeft = true;
					MoveRight = false;
					collisionTimer = 0;
					SpeedX = -MaxSpeedX;
				}
				else if(faceLeft && collisionTimer > 100){
					faceLeft = false;
					faceRight = true;
					MoveLeft = false;
					MoveRight = true;
					collisionTimer = 0;
					SpeedX = MaxSpeedX;
				}
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {
				Y += NewY;
			}else{
    				if(MoveY > 0) {
    				    CanJump = true;
 			        }
				
				SpeedY = 0;
			}		
		}	
		

		MoveX += -NewX;
		MoveY += -NewY;

		if(NewX > 0 && MoveX <= 0) NewX = 0;
		if(NewX < 0 && MoveX >= 0) NewX = 0;

		if(NewY > 0 && MoveY <= 0) NewY = 0;
		if(NewY < 0 && MoveY >= 0) NewY = 0;

		if(MoveX == 0) NewX = 0;
		if(MoveY == 0) NewY = 0;

		if(MoveX == 0 && MoveY 	== 0) 	break;
		if(NewX  == 0 && NewY 	== 0) 	break;
	}
}

//------------------------------------------------------------------------------
void CEntity::StopMove() {
	if(SpeedX > 0) {
		AccelX = -1;
	}

	if(SpeedX < 0) {
		AccelX =  1;
	}

	if(SpeedX < 2.0f && SpeedX > -2.0f) {
		AccelX = 0;
		SpeedX = 0;
	}
}

//==============================================================================
bool CEntity::Collides(int oX, int oY, int oW, int oH) {
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

	int tX = (int)X + Col_X;
	int tY = (int)Y + Col_Y;

    left1 = tX;
    left2 = oX;

    right1 = left1 + Width - 1 - Col_Width;
    right2 = oX + oW - 1;

    top1 = tY;
    top2 = oY;

    bottom1 = top1 + Height - 1 - Col_Height;
    bottom2 = oY + oH - 1;


    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;

    if (right1 < left2) return false;
    if (left1 > right2) return false;

    return true;
}

//==============================================================================
bool CEntity::PosValid(int NewX, int NewY) {
	bool Return = true;

	int StartX 	= (NewX + Col_X) / TILE_SIZE;
	int StartY 	= (NewY + Col_Y) / TILE_SIZE;

	int EndX	= ((NewX + Col_X) + Width - Col_Width - 1) 		/ TILE_SIZE;
	int EndY	= ((NewY + Col_Y) + Height - Col_Height - 1)	/ TILE_SIZE;

	for(int iY = StartY;iY <= EndY;iY++) {
		for(int iX = StartX;iX <= EndX;iX++) {
			CTile* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);

			if(PosValidTile(Tile) == false) {
				Return = false;
			}
		}
	}

	if(Flags & ENTITY_FLAG_MAPONLY) {
	}else{
		for(int i = 0;i < EntityList.size();i++) {
			if(PosValidEntity(EntityList[i], NewX, NewY) == false) {
				Return = false;
			}
		}
	}

	return Return;
}

//------------------------------------------------------------------------------
bool CEntity::PosValidTile(CTile* Tile) {
	if(Tile == NULL) {
		return true;
	}

	if(Tile->TypeID == TILE_TYPE_BLOCK) {
		return false;
	}
	
	if (Tile->TypeID == TILE_TYPE_DAMAGE) {
		if (healthTimer >= 100)	{
			health++;
			healthTimer=0;
		}
		return false;	
	}	

	return true;
}

//------------------------------------------------------------------------------
bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY) {
	if(this != Entity && Entity != NULL && Entity->Dead == false &&
		Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
		Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width - 1, Height - Col_Height - 1) == true) {

		if(this->Type == ENTITY_TYPE_PLAYER && Entity->Type == ENTITY_TYPE_BULLET) return true;
		if(Entity->Type == ENTITY_TYPE_PLAYER && this->Type == ENTITY_TYPE_BULLET) return true;//Samus won't collide with bullets
		if(this->Type == ENTITY_TYPE_BULLET && Entity->Type == ENTITY_TYPE_BULLET) return true;

		if(Entity->Type == ENTITY_TYPE_EFFECT) return true;
		if(this->Type == ENTITY_TYPE_EFFECT) return true;

		if(Entity->Type == ENTITY_TYPE_WHIP && this->Type == ENTITY_TYPE_PLAYER) return true;
		if(Entity->Type == ENTITY_TYPE_PLAYER && this->Type == ENTITY_TYPE_WHIP) return true;
		
		if((Entity->Type == ENTITY_TYPE_SWORD1 || Entity->Type == ENTITY_TYPE_SWORD2) && this->Type == ENTITY_TYPE_SKELETON) return true;
		if(Entity->Type == ENTITY_TYPE_SKELETON && (this->Type == ENTITY_TYPE_SWORD1 || this->Type == ENTITY_TYPE_SWORD2)) return true;
		if(Entity->Type == ENTITY_TYPE_SKELETON && this->Type == ENTITY_TYPE_DOG) return true;
		if(Entity->Type == ENTITY_TYPE_DOG && this->Type == ENTITY_TYPE_SKELETON) return true;
		if(Entity->Type == ENTITY_TYPE_DOG && this->Type == ENTITY_TYPE_DOG) return true;
		if(Entity->Type == ENTITY_TYPE_SKELETON && this->Type == ENTITY_TYPE_SKELETON) return true;
		
		if(this->Type == ENTITY_TYPE_PLAYER && Entity->Type == ENTITY_TYPE_BOMB) return true;
		if(Entity->Type == ENTITY_TYPE_PLAYER && this->Type == ENTITY_TYPE_BOMB) return true;//Samus won't collide with bombs
		if(this->Type == ENTITY_TYPE_BOMB && Entity->Type == ENTITY_TYPE_BOMB) return true;

		CEntityCol EntityCol;

		EntityCol.EntityA = this;
		EntityCol.EntityB = Entity;

		CEntityCol::EntityColList.push_back(EntityCol);

		return false;
	}

	return true;
}

//==============================================================================
bool CEntity::Jump() {
    if(CanJump == false) return false;

    	Anim_Control.MaxFrames = 0; 
    SpeedY = -MaxSpeedY;
    return true;
}
