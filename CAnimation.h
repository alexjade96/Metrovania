//==============================================================================
// Animation Class
//==============================================================================
#ifndef _CANIMATION_H_
    #define _CANIMATION_H_

#include <SDL.h>

//==============================================================================
class CAnimation {
	public:
		int	    CurrentFrame;

		int     FrameInc;

    private:
        int     FrameRate; //Milliseconds

		long    OldTime;

	public:
        int	    MaxFrames;

		bool	Oscillate;

	public:
		CAnimation();

		void OnAnimate();

	public:
        void SetFrameRate(int Rate);

		void SetCurrentFrame(int Frame);

		int GetCurrentFrame();
};

//==============================================================================

#endif
