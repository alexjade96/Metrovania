//=============================================================================
#ifndef _CSKELETON_H_
#define _CSKELETON_H_

#include "CEntity.h"
#include "CSword.h"

//=============================================================================
class CSkeleton : public CEntity {
	public:

	CSkeleton();

	bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

        void OnAnimate();

        bool OnCollision(CEntity* Entity);
        
    bool swordOut;
    int AttackTimer;
    
    float playerPos;


};
//=============================================================================

#endif
