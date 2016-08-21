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
#include "SnakePlayer.h"
#include "snakegame.h"
#include "InputParameters.h"

SnakePlayer::SnakePlayer(SnakeGame* game):
mpSnakePartList(0),
mpGame (game),
mPlayerTic(0),
mGrowCount(0),
mpSnakeContorsion(0)
{
  assert( 0 != mpGame);
  //mpScreen = mpGame->GetScreen();
  mGameEngine = mpGame->GetEngine();
  //assert( 0 != mpScreen);

  }

SnakePlayer::~SnakePlayer(void)
{
	delete mpSnakePartList;
    mpSnakePartList = 0;

	delete mpSnakeContorsion;
    mpSnakeContorsion = 0;
}

int SnakePlayer::CreatePlayer()
{
	try 
	{
		assert( 0 != mpGame);
		mpGame->GetSurfaceDimension(mSurfaceWidth, mSurfaceHeight);

		assert( 0 == mpSnakePartList);
		
		shared_ptr<GameGraphicFactory> graphics = mGameEngine->GetGraphicFactory();

		mpSnakePartList = new SnakePartList(graphics->GetSnakePartWidth(), graphics->GetSnakePartHeight());

		mpSnakePartList->SetSurfaceDimension(mSurfaceWidth, mSurfaceHeight);
		mpSnakePartList->Create(graphics);

		assert( 0 == mpSnakeContorsion);
		mpSnakeContorsion = new SnakeContorsionList(mpSnakePartList, graphics);

		mPlayerTic = 0.2f;
		mSnakePlayerTimer.SetTimer(mPlayerTic);

	}
	catch (...)
	{
		MessageBox(NULL, "CreatePlayer- unknown error", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

    return 0;
}

int SnakePlayer::SetSurfaceDimension(float Width, float Height)
{
    mSurfaceWidth = Width;
    mSurfaceHeight = Height;
    return 0;
}

void SnakePlayer::UpdateFrame(float timeEvent) 
{
	assert( 0 != mpSnakeContorsion);
	assert(0 != mpSnakePartList);
	
	if (InputParameters::Instance().IsDebugAnimation())
	{	
		mpSnakeContorsion->Update();
	    mpSnakePartList->UpdateFrame(timeEvent);
	} else 
	{
		if ( mSnakePlayerTimer.IsTime() )
		{
			mpSnakeContorsion->Update();
			mpSnakePartList->UpdateFrame(timeEvent);
			mSnakePlayerTimer.SetTimer(mPlayerTic);
		}
		else
		{
			mSnakePlayerTimer.UpdateTime(timeEvent);
		}

	}

}

void SnakePlayer::Render() 
{
	assert(0 != mpSnakePartList);
	assert(0 != mpSnakeContorsion);

	mpSnakePartList->Render();	
	mpSnakeContorsion->RenderCornerSpace();
}

bool SnakePlayer::IntersectHead( const Rect& boundingBox )
{
	assert( 0 != mpSnakePartList);
	return mpSnakePartList->IntersectHead(boundingBox);
}

bool SnakePlayer::Intersect( const Rect& boundingBox )
{
	assert( 0 != mpSnakePartList);
	return mpSnakePartList->Intersect(boundingBox);
}

bool SnakePlayer::IsHeadEven()
{
	assert(0 != mpSnakePartList);
	return mpSnakePartList->IsHeadEvenPosition();
}


Vertex& SnakePlayer::GetHeadPosition()
{
	assert(0 != mpSnakePartList);
	return mpSnakePartList->GetHeadPosition();
}

void SnakePlayer::ResetHit()
{
	assert(0 != mpSnakePartList);
    mpSnakePartList->ResetHit();
}

void SnakePlayer::SetTimer(float tic)
{
	mPlayerTic = tic;
}
