#ifndef _CSWORD_H_
#define _CSWORD_H_

#include "CEntity.h"

class CSword : public CEntity {

	public:
		
		CSword();
		
		bool OnLoad(char* File, int Width, int Height, int MaxFrames);

     	void OnLoop();

		void OnRender(SDL_Surface* Surf_Display);

		void OnCleanup();

		void OnAnimate();

		bool OnCollision(CEntity* Entity);

};

#endif
