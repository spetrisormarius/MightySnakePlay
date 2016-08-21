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
//#include "hge.h"
#include <assert.h>
#include "GameGraphicFactory.h"
#include "GamePlay.h"
#include "Vertex.h"

using namespace mightysnake;

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
	void Create(shared_ptr<GameGraphicFactory>& graphics)
	{
	//assert(pScreen != 0);
	//mpScreen = pScreen;
	
	mpSnakeHitSprite = graphics->GetSpriteAnimation(GameGraphicFactory::TILE_HIT);

	mpSnakeHitSprite->SetMode( SpriteAnimation::ANIM_LOOP | SpriteAnimation::ANIM_PINGPONG );

	}
public:
	void UpdateFrame(float fDeltaTime)
	{
	//assert ( 0 != mpScreen );
	assert ( 0 != mpSnakeHitSprite );

	mpSnakeHitSprite->Update( fDeltaTime );
	}

	virtual void Render(SnakeGame* game) {
		assert(0 != mpSnakeHitSprite);
		mpSnakeHitSprite->Render(mPosition.x, mPosition.y);
	}

	void UpdatePosition(const Vertex& point)	
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
	//HGE* mpScreen;	
	shared_ptr<SpriteAnimation> mpSnakeHitSprite;
	int mAnimationState;
	Vertex mPosition;
};
