//==============================================================================
#include "CApp.h"
#include "CEntity.h"
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
		if((*i)->Type == ENTITY_TYPE_BULLET && (*i)->Dead == true){
			delete(*i);
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
		}
	}
}

//==============================================================================
