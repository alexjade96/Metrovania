//==============================================================================
// SDL Tutorial 8
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>

#include "Define.h"

#include "CFPS.h"

#include "CArea.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CEvent.h"
#include "CSurface.h"

#include "CSamus.h"
#include "CSimon.h"
#include "CTurtle.h"
#include "CInsect.h"
#include "CShot.h"
#include "CExplode.h"
#include "CSkeleton.h"
#include "CWhip.h"
#include "CSword.h"

//==============================================================================
class CApp : public CEvent {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;

                CSamus		Samus;
		CSimon		Simon;
		CTurtle		Enemy1;
		CInsect		Enemy2;
		CSkeleton	Enemy3;

    public:
        CApp();

        int OnExecute();
        
        int OnTitle();
        
        int OnGameOver();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);

        	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

        	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

            void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();
        
        
        
	bool metroid;
	bool castlevania;
};

//==============================================================================

#endif
