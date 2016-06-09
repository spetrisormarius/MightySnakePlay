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
#include "GameTilesFactory.h"

#include <memory>

using namespace std::tr1;
using namespace std;

class SnakePart: public GamePlay
{
public:
	enum ESnakeMorphology
	{
		SNAKE_PART_UNKNOWN,
		SNAKE_PART_TAIL_UP,
		SNAKE_PART_BODY_UP,
		SNAKE_PART_HEAD_UP,
		SNAKE_PART_TAIL_DOWN,
		SNAKE_PART_BODY_DOWN,
		SNAKE_PART_HEAD_DOWN
	};

	SnakePart(void):
	x(0),
	y(0),
	dx(0),
	dy(0),
	rot(0),
	mSnakeMorphology (SNAKE_PART_UNKNOWN)
	{
	}



	~SnakePart(void)
	{
	}

	bool IntersectRect(const hgeRect& boundingBox)
	{
		hgeRect snakeBox = GetBoundingBox();
		snakeBox.x1 += 2;
		snakeBox.y1 += 2;
		snakeBox.x2 -= 2;
		snakeBox.y2 -= 2;
	
		return snakeBox.Intersect(&boundingBox);
	}

	hgeRect GetBoundingBox()
	{
		assert( 0 != mSnakeSkin);
		hgeRect snakeBox;
		mSnakeSkin->GetBoundingBoxEx(x,y,rot, 1,1, &snakeBox);

		return snakeBox;
	}

	virtual bool UpdateFrame()
	{
		assert( 0 != mSnakeSkin);

		switch(mSnakeMorphology)
		{
		case SnakePart::SNAKE_PART_TAIL_UP:
			mSnakeMorphology = SNAKE_PART_TAIL_DOWN;
			break;
		case SnakePart::SNAKE_PART_BODY_UP:
			mSnakeMorphology = SNAKE_PART_BODY_DOWN;
			break;
		case SnakePart::SNAKE_PART_HEAD_UP:
			mSnakeMorphology = SNAKE_PART_HEAD_DOWN;
			break;
		case SnakePart::SNAKE_PART_TAIL_DOWN:
			mSnakeMorphology = SNAKE_PART_TAIL_UP;
			break;
		case SnakePart::SNAKE_PART_BODY_DOWN:
			mSnakeMorphology = SNAKE_PART_BODY_UP;
			break;
		case SnakePart::SNAKE_PART_HEAD_DOWN:
			mSnakeMorphology = SNAKE_PART_HEAD_UP;
			break;
		}

		InitSkin();

		return true;
	}

	virtual void Render() 
	{
		assert( 0 != mSnakeSkin);
		mSnakeSkin->RenderEx(x, y, rot);
	}

	void InitSkin()
	{
		switch(mSnakeMorphology)
		{
			case SnakePart::SNAKE_PART_TAIL_UP:
				mSnakeSkin = GameTilesFactory::instance().GetSpriteTile(GameTilesFactory::TILE_TYPE_TAIL_UP);
				break;
			case SnakePart::SNAKE_PART_BODY_UP:
				mSnakeSkin = GameTilesFactory::instance().GetSpriteTile(GameTilesFactory::TILE_TYPE_BODY_UP);
				break;
			case SnakePart::SNAKE_PART_HEAD_UP:
				mSnakeSkin = GameTilesFactory::instance().GetSpriteTile(GameTilesFactory::TILE_TYPE_HEAD_UP);
				break;
			case SnakePart::SNAKE_PART_TAIL_DOWN:
				mSnakeSkin = GameTilesFactory::instance().GetSpriteTile(GameTilesFactory::TILE_TYPE_TAIL_DOWN);
				break;
			case SnakePart::SNAKE_PART_BODY_DOWN:
				mSnakeSkin = GameTilesFactory::instance().GetSpriteTile(GameTilesFactory::TILE_TYPE_BODY_DOWN);
				break;
			case SnakePart::SNAKE_PART_HEAD_DOWN:
				mSnakeSkin = GameTilesFactory::instance().GetSpriteTile(GameTilesFactory::TILE_TYPE_HEAD_DOWN);
				break;
		}

		float hotspotX = mSnakeSkin->GetWidth() / 2;
		float hotspotY = mSnakeSkin->GetHeight() / 2;
		//snakeSkin->SetHotSpot(2, 2);
		mSnakeSkin->SetHotSpot(hotspotX, hotspotY);
		//snakeSkin->Play();
	}

	void SetMorphology(ESnakeMorphology morph) {
		mSnakeMorphology = morph;
	}

	ESnakeMorphology GetMorphology() {
		return mSnakeMorphology;
	}

public:
	float x;
	float y;
	float dx,dy;
	float rot;
private:
	ESnakeMorphology mSnakeMorphology;
	shared_ptr<hgeSprite> mSnakeSkin;
};

