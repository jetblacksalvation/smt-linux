#include "Common.hpp"
/*
	RenderLoop, start with .start method ,, 
	Uses event binder

*/

class RenderLoop
{
public:

	void _RenderLoopMain();
	static void _InitRenderLoop(OnInit*) ;

private:
	static inline  OnInit RenderLoopInitializer = OnInit(_InitRenderLoop);
};
