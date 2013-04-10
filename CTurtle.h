//=============================================================================
#ifndef _CTURTLE_H_
#define _CTURTLE_H_

#include "CEntity.h"

//=============================================================================
class CTurtle : public CEntity {
	public:

	CTurtle();

	bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

        void OnAnimate();

        bool OnCollision(CEntity* Entity);

};
//=============================================================================

#endif
