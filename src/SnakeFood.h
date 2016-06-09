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
 #pragma once
#include "TileInfo.h"
#include <math.h>
#include <vector>
using std::vector;

#include "hge.h"
#include "hgeanim.h"
#include <assert.h>
#include "GameTilesFactory.h"
#include "GamePlay.h"
#include "InputParameters.h"

class SnakeFood : public GamePlay
{
public:
    SnakeFood(	);
public:
    ~SnakeFood(void);
public:
    void SetFoodRange(float nWidth, float nHeight)
        {
        mWidth = nWidth;
        mHeight = nHeight;
        }

	void Create(HGE* pScreen, GameTilesFactory::SnakeTilesType foodTile)
    {
		assert( 0 != pScreen);

		mpSnakeFoodSprite = GameTilesFactory::instance().CreateAnimation(foodTile);

		mRangeX = mWidth / (int)GameTilesFactory::instance().GetSnakePartWidth();
		mRangeY = mHeight / (int)GameTilesFactory::instance().GetSnakePartHeight();

		//start from zero based index.
		mRangeX--;
		mRangeY--;

		int nStep = (int)GameTilesFactory::instance().GetSnakePartWidth();
		int  nSize = max(mRangeX, mRangeY);
		for (int nI = 0; nI < nSize; nI++)
			{
			mPositionArray.push_back(nI * nStep);
			}

		if ( InputParameters::Instance().IsDebugAnimation() ) 
		{
			x_ = 5; y_ = 0;
			mPosition.x = mPositionArray.at(x_);
			mPosition.y = mPositionArray.at(y_);
		}

    }
public:
    void Generate()
    {
	try
	{
		if ( InputParameters::Instance().IsDebugAnimation() ) 
		{
			mPosition.x = mPositionArray.at(x_);
			mPosition.y = mPositionArray.at(y_);
			x_ += 3;
		}
		else
		{
			int x = (((float) rand() / 
					(float) RAND_MAX) * mRangeX + 0.0f);
			int y = (((float) rand() / 
					(float) RAND_MAX) * mRangeY + 0.0f);
			
			assert( x < mPositionArray.size());
			assert( y < mPositionArray.size());

			mPosition.x = mPositionArray.at(x);
			mPosition.y = mPositionArray.at(y);
		}
	} 
	catch( out_of_range& e) 
	{
		MessageBox(NULL, "Food generate- out of range", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		//abort();
	}

    }
public:
    hgeVertex GetPosition() { return mPosition;}
public:
    void UpdateFrame(float deltaTime)
    {
    assert ( 0 != mpSnakeFoodSprite );
    mpSnakeFoodSprite->Update( deltaTime );
    }

    void Render()
    {
        assert(0 != mpSnakeFoodSprite);
		if ( -1 != mPosition.x && -1 != mPosition.y) {
			mpSnakeFoodSprite->Render( mPosition.x, mPosition.y);
		}
    }

    hgeRect GetBoundingBox()
    {
		assert(0 != mpSnakeFoodSprite);
		hgeRect box;
		if ( -1 == mPosition.x ||  -1 == mPosition.y) {

			box.Clear();
		} else {
			mpSnakeFoodSprite->GetBoundingBox(mPosition.x, mPosition.y, &box);
		}
	
		return box;
    }

private:
    hgeVertex mPosition;
    vector<float> mPositionArray;

    float mRangeX;
    float mRangeY;
    hgeAnimation* mpSnakeFoodSprite;
    HGE* mpScreen;
	int x_, y_;
	int mScorePrice;
	float mWidth;
	float mHeight;
public:
	void SetScorePrice(int price);
	int GetScorePrice(void);
};
