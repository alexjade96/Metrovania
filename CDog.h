#ifndef _CDOG_H_
#define _CDOG_H_

#include "CEntity.h"

//=======================================
class CDog : public CEntity {
	public:
		
		CDog();

		bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

        void OnAnimate();

        bool OnCollision(CEntity* Entity);
        
        float playerPos;

	int dogGrowlSound;
	int soundTimer;

};

#endif
