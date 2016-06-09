/* 
 * Copyright 2016 Petrisor Marius Stoian
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
 #include "StdAfx.h"
#include "GameMain.h"
#include "surface.h"
#include "InputParameters.h"

GameMain::GameMain(void):
mpEngine(0)
{

}

GameMain::~GameMain(void)
{
}

bool GameMain::Create(void)
{
	// Here we use global pointer to HGE interface.
	// Instead you may use hgeCreate() every
	// time you need access to HGE. Just be sure to
	// have a corresponding mEngine->Release()
	// for each call to hgeCreate()
	mpEngine = hgeCreate(HGE_VERSION);

	// Set our frame function
	mpEngine->System_SetState(HGE_FRAMEFUNC, &GameMain::FrameFunc);

	// Set the window title
	mpEngine->System_SetState(HGE_TITLE, "MightySnake");

	mpEngine->System_SetState(HGE_RENDERFUNC, &GameMain::RenderFunc);

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
		return false;
	}

#ifdef NDEBUG
	bRes = mpEngine->Resource_AttachPack("mysnk.cat", "..1.5.9.0.....");
	if (!bRes)
	{
		return false;
	}
#endif

	// Load the font, create the cursor sprite
	mpFnt=new hgeFont("font1.fnt");

	mSnakeGame.Init( mpEngine, SURF_W, SURF_H, mpFnt );

	return true;
}

void GameMain::Destroy(void)
{
	if ( 0 == mpEngine )
	{
		return;
	}

	mSnakeGame.Destroy();
  
	delete mpFnt;
	mpFnt = NULL;

	// Restore video mode and free
	// all allocated resources
	mpEngine->System_Shutdown();

	// Release the HGE interface.
	// If there are no more references,
	// the HGE object will be deleted.
	mpEngine->Release();
	mpEngine = NULL;
}

bool GameMain::Run()
{
	// Starts running FrameFunc().
	// Note that the execution "stops" here
	// until "true" is returned from FrameFunc().

	mpEngine->System_Start();

	return true;
}

// This function will be called by HGE once per frame.
// Put your game loop code here. In this example we
// just check whether ESC key has been pressed.
bool GameMain::FrameFunc()
{
	return GameMain::GetInstance().UpdateFrame();

	// Continue execution
	//return false;
}

bool GameMain::RenderFunc()
{
	GameMain::GetInstance().Render();

	return false;
}

void GameMain::ErrorMessage()
{
	// If HGE initialization failed show error message
	MessageBox(NULL, mpEngine->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
}

GameMain& GameMain::GetInstance()
{
	static GameMain game;
	return game;
}


bool GameMain::UpdateFrame()
{
	// By returning "true" we tell HGE
	// to stop running the application.
	mSnakeGame.UpdateFrame();

	return false;
}

void GameMain::Render()
{
	assert( 0 != mpEngine);
	// Render graphics
	mpEngine->Gfx_BeginScene();
	mpEngine->Gfx_Clear(0);

	mSnakeGame.Render();

	mpEngine->Gfx_EndScene();
}