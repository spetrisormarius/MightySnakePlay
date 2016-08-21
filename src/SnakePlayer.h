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

//#include "TileInfo.h"
//#include "hge.h"
//#include "hgeanim.h"

#include "GamePlay.h"
#include "SnakePartList.h"
#include "SnakeContorsionList.h"
#include "gametime.h"

#include "Rect.h"
#include "GameEngine.h"
using namespace mightysnake;

class SnakeGame;

class SnakePlayer: public GamePlay
{
public:
    SnakePlayer(SnakeGame* game);
public:
    virtual ~SnakePlayer(void);
public:
    int CreatePlayer();
    //game logic: update position, get input
    virtual void UpdateFrame(float timeEvent) ;
    // draw
    virtual void Render() ;
	bool IntersectHead(const Rect& boundingBox);
	bool Intersect(const Rect& boundingBox);
public:
    void UpdateTurn()
        {
        //assert(0 != mpScreen);
        assert( 0 != mpSnakeContorsion);

  //      if(mpScreen->Input_GetKeyState(HGEK_LEFT))
  //          {
  //          mpSnakeContorsion->Turn(SnakeContorsionList::LEFT);
  //          } 
		//else if (mpScreen->Input_GetKeyState(HGEK_RIGHT))
  //          {
  //          mpSnakeContorsion->Turn(SnakeContorsionList::RIGHT);
  //          }
  //      else if (mpScreen->Input_GetKeyState(HGEK_UP))
  //          {
  //          mpSnakeContorsion->Turn(SnakeContorsionList::UP);
  //          }
		//else if (mpScreen->Input_GetKeyState(HGEK_DOWN))
  //          {
  //          mpSnakeContorsion->Turn(SnakeContorsionList::DOWN);
  //          }

		if(mGameEngine->InputGetKeyState(GameEngine::KEY_LEFT))
	{
	    mpSnakeContorsion->Turn(SnakeContorsionList::LEFT);
	} 
	else if (mGameEngine->InputGetKeyState(GameEngine::KEY_RIGHT))
	{
	    mpSnakeContorsion->Turn(SnakeContorsionList::RIGHT);
	}
	else if (mGameEngine->InputGetKeyState(GameEngine::KEY_UP))
	{
	   mpSnakeContorsion->Turn(SnakeContorsionList::UP);
	}
	else if (mGameEngine->InputGetKeyState(GameEngine::KEY_DOWN))
	{
	  mpSnakeContorsion->Turn(SnakeContorsionList::DOWN);
	}

    }
public:
    int SetSurfaceDimension(float Width, float Height);
public:
    bool IsHit()
    {
    assert( 0 != mpSnakePartList); 
            
    return mpSnakePartList->IsHit();
    }
    void Feed()
    {
    mGrowCount++;
    }
public:
    void Grow()
    {
		assert( 0 != mpSnakeContorsion);
		mpSnakeContorsion->Grow(mSurfaceWidth, mSurfaceHeight, mGrowCount);
    }
private:
    float mSurfaceWidth;
    float mSurfaceHeight;
private:
    //HGE* mpScreen;
	shared_ptr<GameEngine> mGameEngine;
    SnakeGame* mpGame;
    int mGrowCount;
    SnakePartList* mpSnakePartList;
	SnakeContorsionList* mpSnakeContorsion;
public:
	bool IsHeadEven();
	Vertex& GetHeadPosition();
	void ResetHit();
private:
	GameTime mSnakePlayerTimer;
	float mPlayerTic;
public:
	void SetTimer(float tic);
};
