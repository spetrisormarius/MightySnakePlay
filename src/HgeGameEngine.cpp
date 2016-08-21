/* 
 * Copyright 2016 Petrisor Marius Stoian <spetrisormarius@yahoo.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MightySnake.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "HgeGameEngine.h"
#include "InputParameters.h"
#include "surface.h"
#include <assert.h>
#include "HgeMenu.h"

namespace mightysnake 
{

//HgeGameEngine* HgeGameEngine::mpGameEngine = 0;

HgeGameEngine::HgeGameEngine(void):
mGraphicFactory( new HgeGraphicFactory() ),
mpEngine(0),
mUpdateFn(0),
mRenderFn(0)
{
}

HgeGameEngine::~HgeGameEngine(void)
{
}

void HgeGameEngine::Create(void)
{
	// Here we use global pointer to HGE interface.
	// Instead you may use hgeCreate() every
	// time you need access to HGE. Just be sure to
	// have a corresponding mEngine->Release()
	// for each call to hgeCreate()
	mpEngine = hgeCreate(HGE_VERSION);

	// Set our frame function
	//mpEngine->System_SetState(HGE_FRAMEFUNC, &HgeGameEngine::FrameFunc);

	// Set the window title
	mpEngine->System_SetState(HGE_TITLE, "MightySnake");

	//mpEngine->System_SetState(HGE_RENDERFUNC, &HgeGameEngine::RenderFunc);

	// Run in windowed mode
	// Default window size is 800x600
	mpEngine->System_SetState(HGE_WINDOWED, true);

	// Don't use BASS for sound
	/*mEngine->System_SetState(HGE_USESOUND, false);*/

#ifdef _DEBUG
	mpEngine->System_SetState(HGE_LOGFILE, "MightySnake.log");
#else 
	if (InputParameters::Instance().IsDebug())
	{
		mpEngine->System_SetState(HGE_LOGFILE, "MightySnake.log");
	}
#endif

	mpEngine->System_SetState(HGE_FPS, 30);

	mpEngine->System_SetState(HGE_SCREENWIDTH, SURF_W);
	mpEngine->System_SetState(HGE_SCREENHEIGHT, SURF_H2);

	mpEngine->System_SetState(HGE_SCREENBPP, 32);

	mpEngine->System_SetState(HGE_SHOWSPLASH, false);

	bool bRes = mpEngine->System_Initiate();
	if (!bRes)
	{
		return;
	}

#ifdef NDEBUG
	bRes = mpEngine->Resource_AttachPack("mysnk.cat", "..1.5.9.0.....");
	if (!bRes)
	{
		return;
	}
#endif

	mFont = shared_ptr<HgeFont>( new HgeFont());
	mGraphicFactory->init(mpEngine);

}

shared_ptr<GameGraphicFactory> HgeGameEngine::GetGraphicFactory()
{
	return dynamic_pointer_cast<GameGraphicFactory>(mGraphicFactory);
}

bool HgeGameEngine::InputGetKeyState( int key )
{
	assert( 0 != mpEngine);

	switch(key) 
	{
	case GameEngine::KEY_DOWN:
		return mpEngine->Input_GetKeyState(HGEK_DOWN);
	case GameEngine::KEY_LEFT:
		return mpEngine->Input_GetKeyState(HGEK_LEFT);
	case GameEngine::KEY_UP:
		return mpEngine->Input_GetKeyState(HGEK_UP);
	case GameEngine::KEY_RIGHT:
		return mpEngine->Input_GetKeyState(HGEK_RIGHT);
	case GameEngine::KEY_ESCAPE:
		return mpEngine->Input_GetKeyState(HGEK_ESCAPE);
	}

	return false;
}

float HgeGameEngine::TimerGetDelta()
{
	assert( 0 != mpEngine);
	return mpEngine->Timer_GetDelta();
}

void HgeGameEngine::Start()
{
	assert( 0 != mpEngine);
	// Starts running FrameFunc().
	// Note that the execution "stops" here
	// until "true" is returned from FrameFunc().
    

	mpEngine->System_Start();

}


void HgeGameEngine::Destroy() 
{
	if ( 0 == mpEngine )
	{
		return;
	}

	// Restore video mode and free
	// all allocated resources
	mpEngine->System_Shutdown();

	// Release the HGE interface.
	// If there are no more references,
	// the HGE object will be deleted.
	mpEngine->Release();
	mpEngine = NULL;

}

void HgeGameEngine::SetUpdater(bool (*updateFn)() ) 
{
	assert(0 != mpEngine);

    this->mUpdateFn = updateFn;
	// Set our frame function
	mpEngine->System_SetState(HGE_FRAMEFUNC, updateFn);

}

void HgeGameEngine::SetRenderer(bool (*renderFn)() )
{
	assert(0 != mpEngine);
    this->mRenderFn = renderFn;

	mpEngine->System_SetState(HGE_RENDERFUNC, renderFn);

}

//bool HgeGameEngine::FrameFunc() 
//{
//	assert(0 != mpEngine);
//    return mpGameEngine->mUpdateFn();
//}
//
//bool HgeGameEngine::RenderFunc()
//{
//	assert(0 != mpEngine);
//	return mpGameEngine->mRenderFn();
//}

void HgeGameEngine::StartRender()
{
	assert( 0 != mpEngine);
	// Render graphics
	mpEngine->Gfx_BeginScene();
	mpEngine->Gfx_Clear(0);
}

void HgeGameEngine::EndRender()
{
	assert( 0 != mpEngine);

	mpEngine->Gfx_EndScene();
}

shared_ptr<Menu> HgeGameEngine::GetMenu( MenuAction& menuAction )
{
	return  shared_ptr<Menu>(
		new HgeMenu(menuAction, mpEngine, mFont->GetFont()));
}

shared_ptr<Font> HgeGameEngine::GetFont()
{
  return  mFont;
}

}
