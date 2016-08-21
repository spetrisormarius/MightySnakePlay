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
#include "snakegame.h"
#include "GameInit.h"
#include "gamerun.h"

bool GameInit::UpdateFrame(SnakeGame* game)
{
	//create window create input
	if (game)
	{
       return mSnakeMainScreen.UpdateFrame();
	} 
	else 
	{
		return false;
	}

};


// draw
void GameInit::Render(SnakeGame* game) {
	mSnakeMainScreen.Render();
}

void GameInit::UpdateMainScreen(void)
{
	mSnakeMainScreen.UpdateFrame();
}

void GameInit::Destroy(SnakeGame* game) 
{
	mSnakeMainScreen.Destroy();
}

void GameInit::OnPlay()
{
	if (mpGame)
	{
        GamePlay* stateRun = GameRun::Instance();
		ChangeState(mpGame, stateRun);
        stateRun->Enter(mpGame);
	}
}

void GameInit::OnLevel( short level )
{
	if (mpGame) 
	{
		mpGame->SetLevel(level);
	}
}

void GameInit::Enter( SnakeGame* game )
{
		//create window create input
		if (game)
		{
			//game->SetSurfaceDimension(widthSurface, heightSurface);
			//game->SetFont(fnt);
			game->Create();
			game->LoadHighScore();

			mSnakeMainScreen.Init(game->GetEngine(), game->GetFont());
			float widthSurface, heightSurface;
            game->GetSurfaceDimension(widthSurface, heightSurface);
			mSnakeMainScreen.SetDimension(widthSurface, heightSurface);
			mSnakeMainScreen.SetHighScore( game->GetHighScore() );

			mpGame = game;
		}
}
