;//==============================================================================
#include "CApp.h"
#include "CEntity.h"
#include "CExplode.h"
#include "CInsect.h"
#include "CWhip.h"
#include <vector>
#include <iostream>
//==============================================================================
void CApp::OnLoop() {
    //--------------------------------------------------------------------------
    // Entities
    //--------------------------------------------------------------------------
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnLoop();
    }

    for(int i = 0;i < CEntityCol::EntityColList.size();i++) {
       CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;
       CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;
 
       if(EntityA == NULL || EntityB == NULL) continue;
 
       if(EntityA->OnCollision(EntityB)) {
           EntityB->OnCollision(EntityA);
       }
    }
 
    CEntityCol::EntityColList.clear();

    CFPS::FPSControl.OnLoop();

    char Buffer[255];
    sprintf(Buffer, "%d", CFPS::FPSControl.GetFPS());
    SDL_WM_SetCaption(Buffer, Buffer);


	if(metroid) {
		Enemy3.playerPos = Samus.X;
		Enemy3.yPlayerPos= Samus.Y;
		Enemy4.playerPos = Samus.X;
		Enemy4.yPlayerPos = Samus.Y;
		if(Samus.Dead==true) {
			OnGameOver();
		}
	}	
		
	if(castlevania) {
		Enemy3.playerPos = Simon.X;
		Enemy3.yPlayerPos = Simon.Y;
		Enemy4.playerPos = Simon.X;
		Enemy4.yPlayerPos = Simon.Y;
		if(Simon.Dead==true) {
			OnGameOver();
		}
		if(Simon.Attack && Simon.AttackTimer > 30 && Simon.AttackTimer <= 90 && Simon.PointUp) {
			CWhip* VerticalWhip = new CWhip;
			VerticalWhip->OnLoad("./images/VerticalWhip.png", 6, 52, 2);
			if(Simon.faceRight) {
				VerticalWhip->X = Simon.X + 19;
				VerticalWhip->Y = Simon.Y - 52;
				VerticalWhip->CurrentFrameCol = 0;
			}
			if(Simon.faceLeft) {
				VerticalWhip->X = Simon.X + 6;
				VerticalWhip->Y = Simon.Y - 52;
				VerticalWhip->CurrentFrameCol = 1;
			}
			CEntity::EntityList.push_back(VerticalWhip);
		}
		else if(Simon.Attack && Simon.AttackTimer > 60 && Simon.AttackTimer <= 90 && !Simon.PointUp) {
			CWhip* HorizontalWhip = new CWhip;
			HorizontalWhip->OnLoad("./images/HorizontalWhip.png", 50, 5, 2);
			if(Simon.faceRight) {
				HorizontalWhip->X = Simon.X + 30;
				HorizontalWhip->Y = Simon.Y + 15;
				HorizontalWhip->CurrentFrameCol = 0;
			}
			if(Simon.faceLeft) {
				HorizontalWhip->X = Simon.X - 50;
				HorizontalWhip->Y = Simon.Y + 15;
				HorizontalWhip->CurrentFrameCol = 1;
			}
			CEntity::EntityList.push_back(HorizontalWhip);
		}
			
	}

	std::vector<CEntity*>::iterator i;
	enemyCounter = 0;
	for(i = CEntity::EntityList.begin(); i != CEntity::EntityList.end(); i++){
		if(((*i)->Type == ENTITY_TYPE_DOG) || ((*i)->Type == ENTITY_TYPE_INSECT) || ((*i)->Type == ENTITY_TYPE_SKELETON)){
			enemyCounter++;
		}
		if(((*i)->Type == ENTITY_TYPE_BULLET) && ((*i)->Dead == true)){
			CExplode* expl = new CExplode;
			expl->OnLoad("images/ShotDeath.png",34,34,0);
			expl->X = (*i)->X-12;///added this gives the explosion proper coordinates
			expl->Y = (*i)->Y-12;////////added
			expl->fm = 7;
			expl->cyclelimit = 160;
			delete(*i);
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
			CEntity::EntityList.push_back(expl); //added pushes back after deleting the bullet
		}

		if(((*i)->Type == ENTITY_TYPE_INSECT) && ((*i)->Dead == true)){
			(*i)->OnCleanup();
			CExplode* bug = new CExplode;
			bug->OnLoad("images/InsectDeath.png",60,50,0);
			bug->X = (*i)->X;
			bug->Y = (*i)->Y;
			bug->fm = 4;
			bug->cyclelimit = 160;
			(*i)->OnCleanup();
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
			CEntity::EntityList.push_back(bug); //push back the bug
		}
		if(((*i)->Type == ENTITY_TYPE_SKELETON) && ((*i)->Dead == true)){
			CExplode* bones = new CExplode;
			bones->OnLoad("images/SkeletonDeath.png",30,52,0);
			bones->X = (*i)->X;
			bones->Y = (*i)->Y;
			bones->fm = 7;
			bones->cyclelimit = 200;
			(*i)->OnCleanup();
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
			CEntity::EntityList.push_back(bones); //push back the skeleton death
		}
		
		if (((*i)->Type == ENTITY_TYPE_DOG) && ((*i)->Dead == true)) {
			CExplode* mutt = new CExplode;
			mutt->OnLoad("images/DogDeath.png",35,25,0);
			mutt->X = (*i)->X;
			mutt->Y = (*i)->Y;
			mutt->fm = 7;
			mutt->cyclelimit = 200;
			(*i)->OnCleanup();
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
			CEntity::EntityList.push_back(mutt);
		}
		if(((*i)->Type == ENTITY_TYPE_WHIP) && ((Simon.AttackTimer <= 60 && !Simon.PointUp) || (Simon.AttackTimer <= 30 && Simon.PointUp))){
			delete(*i);
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
		}
		
		
		if(((*i)->Type == ENTITY_TYPE_BOMB) && ((*i)->Dead == true)){ //delete the bomb pointers
			delete(*i);
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
		}
	}
}

//==============================================================================
