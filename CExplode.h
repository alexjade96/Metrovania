#ifndef CEXPLODE_H
#define CEXPLODE_H

#include "CEntity.h"

class CExplode : public CEntity
{
	public:
		//this first finction is the constructor
		CExplode();
		
		bool OnLoad(char* File, int Width, int Height, int MaxFrames);

     		void OnLoop();

		void OnRender(SDL_Surface* Surf_Display);

		void OnCleanup();

		void OnAnimate();

		bool OnCollision(CEntity* Entity);
		int cycle;
		int fm; //max frames
		int cyclelimit; //how many iterations

};

#endif
