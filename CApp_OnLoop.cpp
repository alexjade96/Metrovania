//==============================================================================
#include "CApp.h"
#include "CEntity.h"
#include "CExplode.h"
#include "CInsect.h"
#include <vector>
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
		if(Samus.Dead==true) {
			OnGameOver();
		}
	}	
		
	if(castlevania) {
		if(Simon.Dead==true) {
			OnGameOver();
		}	
	}

	std::vector<CEntity*>::iterator i;
	for(i = CEntity::EntityList.begin(); i != CEntity::EntityList.end(); i++){
		if(((*i)->Type == ENTITY_TYPE_BULLET) && ((*i)->Dead == true)){
			CExplode* expl = new CExplode;///////////////////added this
			expl->OnLoad("images/ShotDeath.png",34,34,0);
			expl->X = (*i)->X-12;///added this gives the explosion proper coordinates
			expl->Y = (*i)->Y-12;////////added
			expl->fm = 6;
			expl->cyclelimit = 200;
			(*i)->OnCleanup();
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
			bug->fm = 3;
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
			bones->fm = 6;
			bones->cyclelimit = 200;
			(*i)->OnCleanup();
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
			CEntity::EntityList.push_back(bones); //push back the bug
		}
	}
}

//==============================================================================
