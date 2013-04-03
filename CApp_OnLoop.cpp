//==============================================================================
#include "CApp.h"

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


	if(metroid) if(Samus.Dead==true) Running = false;
	if(castlevania) if(Simon.Dead==true) Running = false;
}

//==============================================================================
