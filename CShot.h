#ifndef CSHOT_H
#define CSHOT_H

#include "CEntity.h"

class CShot : public CEntity
{
	public:
		//this first finction is the constructor
		CShot();
		
		bool OnLoad(char* File, int Width, int Height, int MaxFrames);

     		void OnLoop();

		void OnRender(SDL_Surface* Surf_Display);

		void OnCleanup();

		void OnAnimate();

		bool OnCollision(CEntity* Entity);

};

#endif
