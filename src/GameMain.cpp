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
#include "GameEngine.h"


GameMain::GameMain(void)
//mpEngine(0)
{

}

GameMain::~GameMain(void)
{
}

bool GameMain::Create(void)
{
	shared_ptr<GameEngine> hgeEngine = GameEngineFactory::getEngine(mightysnake::GameEngineFactory::HGE);                       

	hgeEngine->Create();

	hgeEngine->SetUpdater(&GameMain::FrameFunc);
	hgeEngine->SetRenderer(&GameMain::RenderFunc);

	// Load the font, create the cursor sprite
	//mpFnt=new hgeFont("font1.fnt");
    mFnt= hgeEngine->GetFont();

	mSnakeGame.SetSurfaceDimension(SURF_W, SURF_H);
    mSnakeGame.SetFont(mFnt);
	mSnakeGame.Init( hgeEngine );

	return true;
}

void GameMain::Destroy(void)
{
	mSnakeGame.PersistHighScore();

	//shared_ptr<GameEngine> hgeEngine = GameEngineFactory::getEngine(mightysnake::GameEngineFactory::HGE);                       
	//hgeEngine->Destroy();

	//if ( 0 == mpEngine )
	//{
	//	return;
	//}

	//mSnakeGame.Destroy();
  
	//delete mpFnt;
	//mpFnt = NULL;

	//// Restore video mode and free
	//// all allocated resources
	//mpEngine->System_Shutdown();

	//// Release the HGE interface.
	//// If there are no more references,
	//// the HGE object will be deleted.
	//mpEngine->Release();
	//mpEngine = NULL;
}

bool GameMain::Run()
{
	// Starts running FrameFunc().
	// Note that the execution "stops" here
	// until "true" is returned from FrameFunc().

	GameEngineFactory::getEngine(mightysnake::GameEngineFactory::HGE)->Start();                       

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
	//MessageBox(NULL, mpEngine->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
}

GameMain& GameMain::GetInstance()
{
	static GameMain game;
	return game;
}


bool GameMain::UpdateFrame()
{
	 //By returning "true" we tell HGE
	 //to stop running the application.
	mSnakeGame.UpdateFrame();

	return false;
}

void GameMain::Render()
{

	shared_ptr<GameEngine> hgeEngine = GameEngineFactory::getEngine(mightysnake::GameEngineFactory::HGE);  

	hgeEngine->StartRender();

	mSnakeGame.Render();

	hgeEngine->EndRender();


	//assert( 0 != mpEngine);
	// Render graphics
	//mpEngine->Gfx_BeginScene();
	//mpEngine->Gfx_Clear(0);

	//mSnakeGame.Render();

	//mpEngine->Gfx_EndScene();
}