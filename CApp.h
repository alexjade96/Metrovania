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
#include "CSoundBank.h"

#include "CSamus.h"
#include "CSimon.h"
#include "CTurtle.h"
#include "CInsect.h"
#include "CShot.h"
#include "CExplode.h"
#include "CSkeleton.h"
#include "CWhip.h"
#include "CSword.h"
#include "CDog.h"

//==============================================================================
class CApp : public CEvent {
    private:
        bool            Running;//is the game running?

        SDL_Surface*    Surf_Display;//the main display

        CSamus		Samus;//declaration of power suit wearing samus
	CSimon		Simon;//declaration of whip wielding simon
	CTurtle		Enemy1;//declaration of rocket powered turtle
	CInsect		Enemy2;//declaration of oversized hopping insect
	CSkeleton	Enemy3;//declaration of sword swinging skeleton
	CDog 		Enemy4;//declaration of leaping rabid dog
	int		attackSound;//declaration of either a gun firing or a whip snapping

    public:
        CApp();//constructer

        int OnExecute();//executes all other functions
        
        int OnTitle();//title screen declaration
        
        int OnGameOver();//game over screen declaration

    public:
        bool OnInit();//initializes all objects

        void OnEvent(SDL_Event* Event);//takes input

        	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);//when a key is pressed down

        	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);//when a key is depressed

            void OnExit();//when the game exits

        void OnLoop();//function that updates all data

        void OnRender();//draws all images to screen

        void OnCleanup();//cleans up all objects
        
        
        
	bool metroid;//are we playing with samus?
	bool castlevania;//are we playing with simon?
};

//==============================================================================

#endif
