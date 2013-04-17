//==============================================================================
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
		if(Samus.Dead==true) {
			OnGameOver();
		}
	}	
		
	if(castlevania) {
		Enemy3.playerPos = Simon.X;
		if(Simon.Dead==true) {
			OnGameOver();
		}
		if(Simon.Attack && Simon.AttackTimer > 60 && Simon.AttackTimer <= 90 && Simon.PointUp) {
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
	
	if (Enemy3.swordOut && Enemy3.AttackTimer > 30 && Enemy3.AttackTimer <=60) {
		CSword* upSword = new CSword;
		upSword->Type = ENTITY_TYPE_SWORD1;
		upSword->OnLoad("./images/sword1.png", 17, 16, 2);
		if (Enemy3.faceRight) {
			upSword->X = Enemy3.X + 7;
			upSword->Y = Enemy3.Y - 16;
			upSword->CurrentFrameCol = 1;
		}	
		else if (Enemy3.faceLeft) {
			upSword->X = Enemy3.X + 7;
			upSword->Y = Enemy3.Y - 16;
			upSword->CurrentFrameCol = 0;
		}	
		CEntity::EntityList.push_back(upSword);
	} 
	else if (Enemy3.swordOut && Enemy3.AttackTimer > 60 && Enemy3.AttackTimer <= 90) {
		CSword* outSword = new CSword;
		outSword->Type = ENTITY_TYPE_SWORD2;
		outSword -> OnLoad("./images/sword2.png", 25, 8, 2);
		if (Enemy3.faceRight) {
			outSword->X = Enemy3.X + 30;
			outSword->Y = Enemy3.Y + 15;
			outSword->CurrentFrameCol = 0;
		}
		else if (Enemy3.faceLeft) {
			outSword->X = Enemy3.X - 20;
			outSword->Y = Enemy3.Y + 15;
			outSword->CurrentFrameCol = 1;
		}		
		CEntity::EntityList.push_back(outSword);
	}	

	std::vector<CEntity*>::iterator i;
	for(i = CEntity::EntityList.begin(); i != CEntity::EntityList.end(); i++){
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
		if(((*i)->Type == ENTITY_TYPE_WHIP) && (Simon.AttackTimer <= 60)){
			delete(*i);
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
		}
		
		if(((*i)->Type == ENTITY_TYPE_SWORD1) && (Enemy3.AttackTimer > 60 || Enemy3.AttackTimer < 30)) {
			delete(*i);
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
		} 
		
		if (((*i)->Type == ENTITY_TYPE_SWORD2) && (Enemy3.AttackTimer < 60 || Enemy3.AttackTimer >90)) {
			delete(*i);
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
		}	
		
		if ((((*i)->Type == ENTITY_TYPE_SWORD1) || ((*i)->Type == ENTITY_TYPE_SWORD2)) && Enemy3.Dead) {
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
