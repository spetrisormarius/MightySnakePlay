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

#include "gametime.h"
#include "snakefood.h"
#include "hgeguictrls.h"
#include "snakeplayer.h"

class BigFoodControl : GamePlay
{
public:
	BigFoodControl(void);
	~BigFoodControl(void);
private:
	GameTime mBigFoodTimer;
	GameTime mProgressTimer;
	SnakeFood* mpSnakeBigFood;
	hgeGUISlider* mpSlider;
	short mSliderIndex;
	float mBigFoodTic;
	float mProgressTic;
public:
	void Create(shared_ptr<GameGraphicFactory>& graphics, float surfaceWidth, float surfaceHeight, float surfaceHeightOffset);
	//game logic: update position, get input
	virtual void UpdateFrame(float fDeltaTime);
	// draw
	virtual void Render();
	void Generate(SnakePlayer* player);
private:
	bool BigFoodFilter( const Rect& bigFoodRect );
	short mBigFoodIndex;
	float mSurfaceHeight;
public:
	void OnStart(void);
	int LaunchTime(SnakePlayer* player);
	void SetLevel(short level);
private:
	shared_ptr<GameGraphicFactory> mGraphics;
};
