//=============================================================================
#ifndef _CSIMON_H_
    #define _CSIMON_H_

#include "CEntity.h"

//=============================================================================
class CSimon : public CEntity {
    public:
        CSimon();

	bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

        void OnAnimate();

        bool OnCollision(CEntity* Entity);

	bool	Crouch;

	SDL_Surface*	Surf_Health;
};

//=============================================================================

#endif
