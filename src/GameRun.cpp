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
 #include "stdafx.h"
#include "gamerun.h"
#include "GameInit.h"
#include "GameEnd.h"
#include "SnakeGame.h"
#include "snakefood.h"
#include "snakeplayer.h"
#include "hge.h"
#include "hgecolor.h"


bool GameRun::UpdateFrame(SnakeGame* game)
{
	if (0 == mpPlayer)
	{
		MessageBox(NULL, "SnakeGame::OnRun 0 == m_Player ", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		return true;
	}
	if (0 == mpSnakeFood )
	{
		MessageBox(NULL, "SnakeGame::OnRun 0 == m_pSnakeFood ", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		return true;
	}

	if ( 0 == game) return true;

	//HGE* pScreen = game->GetScreen();
     shared_ptr<GameEngine> gameEngine = game->GetEngine();
	//if (0 == pScreen)
	//{
	//	MessageBox(NULL, "SnakeGame::OnRun  0 == mScreen ", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	//	return true;
	//}

	 if (gameEngine->InputGetKeyState(GameEngine::KEY_ESCAPE)) 
	{
		mHitPause = true;
		ChangeState(game, GameInit::Instance());
		return false;
	}

	mpPlayer->UpdateTurn();

	//float timeEvent = pScreen->Timer_GetDelta();
    float timeEvent = gameEngine->TimerGetDelta();

	mpPlayer->UpdateFrame(timeEvent);

	if (InputParameters::Instance().IsDebugAnimation())
	{
		if (mpPlayer->IsHeadEven()) {
			//Pause();
		}
	}

	mpSnakeFood->UpdateFrame(timeEvent);

	if ( mpPlayer->IsHit() )
	{
		mpPlayer->ResetHit();
		
		game->SetPlayer(mpPlayer);
		game->SetSnakeFood(mpSnakeFood);
		GamePlay* stateEnd = GameEnd::Instance();
		ChangeState(game, stateEnd);
        stateEnd->Enter(game);
		return false;
	}

	LaunchTime(game, timeEvent);

	mpPlayer->Grow();

	//continue;
	return false;
};


// draw
void GameRun::Render(SnakeGame* game)
{
	if (InputParameters::Instance().IsDebugAnimation())
	{
		RenderGrid();
	}

	assert( 0 != mpPlayer);
	assert( 0 != mpSnakeFood);

	mpPlayer->Render();
	mpSnakeFood->Render();

	mBigFoodControl.Render();

	DisplayScore(game);

}

void GameRun::Enter(SnakeGame* game) 
{	
	if (NULL == game) 
	{
		return;
	}

	if ( mHitPause ) {
		mHitPause = false;
		short level = game->GetLevel();
		mBigFoodControl.SetLevel(level);
		mSnakeSpeed = game->GetSnakeSpeed();
		mpPlayer->SetTimer(mSnakeSpeed);
		return;
	}

	float surfaceWidth, surfaceHeight;
	game->GetSurfaceDimension(surfaceWidth, surfaceHeight);
    //HGE* mScreen = game->GetScreen();

     mpSnakeFood = game->GetSnakeFood();
	 if(NULL == mpSnakeFood)
        {
        mpSnakeFood = new SnakeFood();
        mpSnakeFood->SetFoodRange(surfaceWidth, surfaceHeight);
        mpSnakeFood->Create(game->GetEngine()->GetGraphicFactory(), GameGraphicFactory::TILE_FOOD);
		mpSnakeFood->SetScorePrice(SCORE_PRICE);
        }
    mpSnakeFood->Generate();

    CreatePlayer(game);
    mScore = 0;

	mPoint = game->GetEngine()->GetGraphicFactory()->CreatePoint();

	mBigFoodControl.Create(game->GetEngine()->GetGraphicFactory(), surfaceWidth, surfaceHeight, mSurfaceHeightOffset);

	mBigFoodControl.OnStart();

	if (InputParameters::Instance().IsDebugAnimation())
	{
		CreateGrid();
	}

	short level = game->GetLevel();
	mBigFoodControl.SetLevel(level);
}

void GameRun::CreatePlayer(SnakeGame* game)
{
	assert( 0 != game);
	//TODO:: smart pointer
	mpPlayer = game->GetSnakePlayer();
	if(NULL == mpPlayer)
	{
		mpPlayer = new SnakePlayer(game);

		int nRet = mpPlayer->CreatePlayer();
		if ( 0 != nRet)
		{
			MessageBox( NULL, "Game error: Create player", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(nRet);
		}
        mSnakeSpeed = game->GetSnakeSpeed();
		mpPlayer->SetTimer(mSnakeSpeed);
	}

}

void GameRun::CreateGrid()
{
	//mGridSprite = GameGraphicFactory::instance().CreateGrid();
}


void GameRun::RenderGrid()
{

	//for (int y = 0; y < 30; y++) {
	//	for (int x = 0; x < 40; x++) {
	//		mGridSprite->Render(x*16.0f, y*16.0f);
	//	}
	//}
}

void GameRun::DisplayScore(SnakeGame* game)
{
	if (0 == game)  {
		return;
	}

	shared_ptr<Font> fnt = game->GetFont();
	//if (0 == fnt)
	//{
	//	return;
	//}

    float m_nSurfaceWidth, m_nSurfaceHeight;
	game->GetSurfaceDimension(m_nSurfaceWidth, m_nSurfaceHeight);

	RenderLine(m_nSurfaceWidth, m_nSurfaceHeight);

	hgeColor yellowColor(1, 0.95f, 0, 1);
	fnt->SetColor(yellowColor.GetHWColor());
	fnt->SetScale(0.5f);
	stringstream ss;
	ss << mScore;
	string strScore = ss.str();
	float width = fnt->GetStringWidth(strScore.c_str());
	fnt->Render(m_nSurfaceWidth - width, m_nSurfaceHeight , HGETEXT_RIGHT, strScore.c_str());

}

void GameRun::LaunchTime( SnakeGame* pGame, float timeEvent )
{
	assert( 0 != mpSnakeFood);
	assert( 0 != mpPlayer);
	assert( 0 != pGame);
	try 
	{
		if (mpPlayer->IntersectHead(*mpSnakeFood->GetBoundingBox()))
		{
			mpSnakeFood->Generate();
			while (mpPlayer->Intersect(*mpSnakeFood->GetBoundingBox()))
			{
				mpSnakeFood->Generate();
			}
			mpPlayer->Feed();
			mScore += mpSnakeFood->GetScorePrice();
            pGame->SetScore(mScore);

			if (mScore >= pGame->GetHighScore())
			{
				pGame->SetHighScore(mScore);
			}

			mBigFoodControl.Generate(mpPlayer);
		} 

		mScore += mBigFoodControl.LaunchTime(mpPlayer);
		pGame->SetScore(mScore);
		if (mScore >= pGame->GetHighScore())
		{
			pGame->SetHighScore(mScore);
		}

		//update
		mBigFoodControl.UpdateFrame(timeEvent);
	}
	catch (...) 
	{
		//MessageBox(NULL, "LaunchTime - unknown exception ", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
}

void GameRun::RenderLine( float surfaceWidth, float surfaceHeight )
{
	for (int x = 0; x < surfaceWidth; x++) {
		mPoint->Render(x, surfaceHeight);
	}
}

void GameRun::Destroy( SnakeGame* game )
{
	delete  mpPlayer;
	mpPlayer = 0;

	delete mpSnakeFood;
	mpSnakeFood = 0;
}
