#ifndef CWHIP_H
#define CWHIP_H

#include "CEntity.h"

class CWhip : public CEntity
{
	public:
		//this first finction is the constructor
		CWhip();
		
		bool OnLoad(char* File, int Width, int Height, int MaxFrames);

     		void OnLoop();

		void OnRender(SDL_Surface* Surf_Display);

		void OnCleanup();

		void OnAnimate();

		bool OnCollision(CEntity* Entity);

};

#endif
