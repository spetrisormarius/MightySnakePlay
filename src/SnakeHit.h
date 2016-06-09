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
#include "hge.h"
#include <assert.h>
#include "GameTilesFactory.h"
#include "GamePlay.h"

class SnakeHit : public GamePlay
{
public:
	SnakeHit();
	enum 
	{
	ANIMATION_START,
	ANIMATION_DONE
	};
public:
	~SnakeHit(void);
public:
	void Create(HGE* pScreen)
	{
	assert(pScreen != 0);
	mpScreen = pScreen;
	
	mpSnakeHitSprite = GameTilesFactory::instance().CreateAnimation(GameTilesFactory::TILE_TYPE_HIT);

	mpSnakeHitSprite->SetMode( HGEANIM_LOOP | HGEANIM_PINGPONG );

	}
public:
	void UpdateFrame(float fDeltaTime)
	{
	assert ( 0 != mpScreen );
	assert ( 0 != mpSnakeHitSprite );

	mpSnakeHitSprite->Update( fDeltaTime );
	}

	virtual void Render(SnakeGame* game) {
		assert(0 != mpSnakeHitSprite);
		mpSnakeHitSprite->Render(mPosition.x, mPosition.y);
	}

	void UpdatePosition(const hgeVertex& point)	
	{
		mPosition = point;
	}

	bool IsPlaying() {

		return mpSnakeHitSprite->IsPlaying();
	}

	int GetAnimationState()
	{
		return mAnimationState;
	}

	void ResetAnimationState()
	{
		mAnimationState = ANIMATION_START;
	}

private:
	HGE* mpScreen;	
	hgeAnimation* mpSnakeHitSprite;
	int mAnimationState;
	hgeVertex mPosition;
};
