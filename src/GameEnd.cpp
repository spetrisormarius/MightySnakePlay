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
#include "GameEnd.h"
#include "SnakeGame.h"
#include "GameInit.h"
#include "snakehit.h"
#include "hgecolor.h"
#include "SnakePlayer.h"
#include "SnakeFood.h"

void GameEnd::Render( SnakeGame* game )
{
    assert( 0 != game);
	
	assert(0 != mpPlayer);
	assert(0 != mpScreen);

	assert(0 != mpSnakeFood);
	assert(0 != mpSnakeHit);

	float timeEvent = mpScreen->Timer_GetDelta();

	if ( !mGameOverTimer.IsTime() ) {

		mpPlayer->Render();
		mpSnakeFood->Render();

		mpSnakeHit->UpdatePosition(mpPlayer->GetHeadPosition());
		mpSnakeHit->UpdateFrame(timeEvent);
		mpSnakeHit->Render(game);

		//display score
		DisplayGameOver(game);

		mGameOverTimer.UpdateTime(timeEvent);
	} else {
		int nScore = game->GetScore();

		if (nScore >= game->GetHighScore())
		{
			//m_nHighScore = m_nScore;
            game->SetHighScore(nScore);
			game->PersistHighScore();
		}
		mGameOverTimer.Reset();

		GamePlay* stateInit = GameInit::Instance();
		ChangeState(game, stateInit);
		//destroy game
		//TODO: find a better way to destroy game
        game->SetPlayer(NULL);
		game->SetSnakeFood(NULL);
		
		delete mpPlayer;
		mpPlayer = NULL;
		delete mpSnakeFood;
		mpSnakeFood = NULL;
	}
}

void GameEnd::Enter( SnakeGame* game )
{
  	assert( 0 != game);
	mpPlayer = game->GetSnakePlayer();
	assert( 0 != mpPlayer);
    mpSnakeFood = game->GetSnakeFood();
	assert( 0 != mpSnakeFood);
    mpScreen = game->GetScreen();
	assert( 0 != mpScreen);

	if(NULL == mpSnakeHit)
	{
	    mpSnakeHit = new SnakeHit();
	    mpSnakeHit->Create(mpScreen);
	}

	mGameOverTimer.SetTimer(10);
}

void GameEnd::Destroy( SnakeGame* game )
{
	delete mpSnakeHit;
	mpSnakeHit = 0;
}

void GameEnd::DisplayGameOver( SnakeGame* pGame )
{
	assert( 0 != pGame);
	hgeFont* pFnt = pGame->GetFont();
	assert( 0 != pFnt);

	float heightFont = pFnt->GetHeight();

	int nHighScore = pGame->GetHighScore();

	float surfaceWidth, surfaceHeight;
    pGame->GetSurfaceDimension(surfaceWidth, surfaceHeight);

    int nScore = pGame->GetScore();

	stringstream ss;
	ss << nScore;
	string strScore = ss.str();
	if (nScore >= nHighScore)
	{
		//render Master Snake
		string masterSnake = "Master snake";
		hgeColor greyColor(0.25, 0.25, 0.25, 1);
		pFnt->SetScale(2.2f);
		pFnt->SetColor(greyColor.GetHWColor());
		pFnt->Render(surfaceWidth / 2.0f + 2 , surfaceHeight / 3.0f + 2, HGETEXT_CENTER, masterSnake.c_str() );

		hgeColor redColor(1, 0, 0, 1);
		pFnt->SetColor(redColor.GetHWColor());
		pFnt->Render(surfaceWidth / 2.0f , surfaceHeight / 3.0f, HGETEXT_CENTER, masterSnake.c_str() );

		//render high score
		pFnt->SetColor(greyColor.GetHWColor());
		pFnt->Render(surfaceWidth / 2.0f + 2 , surfaceHeight - surfaceHeight / 3.0f + 2, HGETEXT_CENTER,strScore.c_str() );

		pFnt->SetColor(redColor.GetHWColor());
		pFnt->Render(surfaceWidth / 2.0f , surfaceHeight - surfaceHeight / 3.0f , HGETEXT_CENTER,strScore.c_str() );

	} else {
		//render your score
		string yourScore = "Your score";
		hgeColor yellowColor(1, 0.95f, 0, 1);
		pFnt->SetColor(yellowColor.GetHWColor());
		pFnt->SetScale(1.7f);
		//float widthYourScore = mFnt->GetStringWidth(yourScore.c_str(), false);
		pFnt->Render(surfaceWidth / 2.0f , surfaceHeight / 3.0f, HGETEXT_CENTER, yourScore.c_str() );

		//render score
		float widthScore = pFnt->GetStringWidth(strScore.c_str(), false);
		pFnt->Render(surfaceWidth / 2.0f, surfaceHeight - surfaceHeight / 3.0f , HGETEXT_CENTER, strScore.c_str() );

	}
}