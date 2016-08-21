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
#include "BigFoodControl.h"

BigFoodControl::BigFoodControl(void):
mBigFoodTic (10.0f),
mProgressTic (1.0f),
mSliderIndex (10),
mpSlider(NULL),
mpSnakeBigFood(NULL),
mBigFoodIndex (0)
{
}

BigFoodControl::~BigFoodControl(void)
{
	delete mpSnakeBigFood;
	mpSnakeBigFood = 0;
}

void BigFoodControl::Create( shared_ptr<GameGraphicFactory>& graphics, float surfaceWidth, float surfaceHeight, float surfaceHeightOffset )
{
	if ( NULL == mpSlider)
	{
		mpSlider = new hgeGUISlider(0, 5, surfaceHeight + surfaceHeightOffset/4,
			100, 10, 0, 0, 0, 1, 1);
		mpSlider->SetMode(0, 10, HGESLIDER_BAR);
		mpSlider->SetValue(10);
	}

	if(NULL == mpSnakeBigFood)
	{
		mpSnakeBigFood = new SnakeFood();
		mpSnakeBigFood->SetFoodRange(surfaceWidth, surfaceHeight);
		mpSnakeBigFood->Create(graphics, GameGraphicFactory::TILE_BIG_FOOD);
		mpSnakeBigFood->SetScorePrice(10);
	}

	mSurfaceHeight = surfaceHeight;
	mGraphics = graphics;
}


void BigFoodControl::UpdateFrame(float timeEvent)
{
	if (mBigFoodTimer.IsEnable())
	{	
		if (!mBigFoodTimer.IsTime())
		{
			mpSnakeBigFood->UpdateFrame(timeEvent);
			mBigFoodTimer.UpdateTime(timeEvent);
		} else  {
			mBigFoodTimer.Reset();
			mProgressTimer.Reset();
			mSliderIndex = 10;
			mpSlider->SetValue(mSliderIndex);
		}
	}

	if (mProgressTimer.IsEnable())
	{
		if (mProgressTimer.IsTime())
		{
			mProgressTimer.SetTimer(mProgressTic);
			mpSlider->SetValue(--mSliderIndex);
		} else {
			mProgressTimer.UpdateTime(timeEvent);
		}
	}
}

void BigFoodControl::Render()
{
	if (0 == mpSnakeBigFood )
	{
		MessageBox(NULL, "SnakeGame::OnRun 0 == m_pSnakeBigFood ", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		return;
	}

	if(mBigFoodTimer.IsEnable() ) {
		if (!mBigFoodTimer.IsTime())
		{
			mpSnakeBigFood->Render();	
			mpSlider->Render();
		}
	}

}

void BigFoodControl::Generate( SnakePlayer* player )
{
	assert( 0 != player);
	assert( 0 != mpSnakeBigFood);

	mBigFoodIndex++;
	if ( 5 == mBigFoodIndex )
	{
		mpSnakeBigFood->Generate();
		Rect& bigFoodRect = *mpSnakeBigFood->GetBoundingBox();
		while (player->Intersect(bigFoodRect) || BigFoodFilter(bigFoodRect))
		{
			mpSnakeBigFood->Generate();
            bigFoodRect = *mpSnakeBigFood->GetBoundingBox();
		}
		mBigFoodIndex = 0;
		mBigFoodTimer.SetTimer(mBigFoodTic);
		mProgressTimer.SetTimer(mProgressTic);
	}
}

bool BigFoodControl::BigFoodFilter( const Rect& bigFoodRect )
{
	float snakePartHeight = mGraphics->GetSnakePartHeight();

	return bigFoodRect.y1 == (mSurfaceHeight - snakePartHeight);
}

void BigFoodControl::OnStart(void)
{
    assert( 0 != mpSlider);

	mBigFoodIndex = 0;
    mSliderIndex  = 10;
	mpSlider->SetValue(mSliderIndex);
	mBigFoodTimer.Reset();
	mProgressTimer.Reset();

}

int BigFoodControl::LaunchTime( SnakePlayer* player )
{
    int nScore = 0;
	if (mBigFoodTimer.IsEnable() && player->IntersectHead(*mpSnakeBigFood->GetBoundingBox()))
	{
		nScore += mpSnakeBigFood->GetScorePrice();
		mSliderIndex = 10;
		mpSlider->SetValue(mSliderIndex);
		mBigFoodTimer.Reset();
		mProgressTimer.Reset();
	}

	return nScore;
}

void BigFoodControl::SetLevel(short level)
{
	switch (level)
	{
	case 0:
		mBigFoodTic = 10.0f;
		mProgressTic = 1.0f;
		break;
	case 1:
		mBigFoodTic = 10 / 2.0f;
		mProgressTic = 1 / 2.0f;
		break;
	case 2:
		mBigFoodTic = 10 / 4.0f;
		mProgressTic = 1 / 4.0f;
		break;
	case 3:
		mBigFoodTic = 10 / 6.0f;
		mProgressTic = 1 / 6.0f;
		break;
	case 4:
		mBigFoodTic = 10 / 8.0f;
		mProgressTic = 1 / 8.0f;
		break;
	}
}
