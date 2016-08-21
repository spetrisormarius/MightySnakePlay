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
#include "GamePlay.h"
#include "BigFoodControl.h"
#include "hgesprite.h"
#include <memory>
#include "GameGraphicFactory.h"

class SnakeFood;
class SnakePlayer;

using namespace std::tr1;
using namespace std;

class GameRun: public GamePlay
{
protected:
	GameRun(void): 
		mpPlayer(NULL),
		mpSnakeFood( NULL ),
		mSnakeSpeed(0),
		mScore(0),
		mSurfaceHeightOffset (20),
		mHitPause(false)
	{

	}
public:
	~GameRun(void)
	{
	  Destroy(NULL);
	}
public:
	static GamePlay* Instance(void)
	{
	static GameRun game;
    return &game;
	}
	virtual bool UpdateFrame(SnakeGame* game);
	// draw
	virtual void Render(SnakeGame* game);
	virtual void Enter(SnakeGame* game);
private:
	void Destroy(SnakeGame* game);
	//TODO:convert to smart pointer
	SnakeFood* mpSnakeFood;
private:
	static const int SCORE_PRICE = 5;
private:
	BigFoodControl mBigFoodControl;
private:
	void CreatePlayer(SnakeGame* game);
private:
	//TODO:convert to smart pointer
	SnakePlayer* mpPlayer;
	float mSnakeSpeed;
private:
	int mScore;
private:
	shared_ptr<Sprite> mPoint;
private:
	float mSurfaceHeightOffset;
public:
	void CreateGrid();
private:
	shared_ptr<Sprite> mGridSprite;
	bool mHitPause;
public:
	void RenderGrid();
private:
	void DisplayScore(SnakeGame* game);
private:
	void LaunchTime(SnakeGame* pGame, float timeEvent);
	void RenderLine(float surfaceWidth, float surfaceHeight);
};
