//=============================================================================
#ifndef _CINSECT_H_
#define _CINSECT_H_

#include "CEntity.h"

//=============================================================================
class CInsect : public CEntity {
	public:
	
	int jumpTimer;

	CInsect();

	bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

        void OnAnimate();

        bool OnCollision(CEntity* Entity);

	int collisionTimer;

};
//=============================================================================

#endif
