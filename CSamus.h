//=============================================================================
#ifndef _CSAMUS_H_
    #define _CSAMUS_H_

#include "CEntity.h"

//=============================================================================
class CSamus : public CEntity {
    public:
        CSamus();

	bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

        void OnAnimate();

        bool OnCollision(CEntity* Entity);

	bool	Crouch;
	bool	PointUpDiagonal;
	bool	PointDownDiagonal;
	bool	morphBall;
	bool	PointUp;
};

//=============================================================================

#endif


