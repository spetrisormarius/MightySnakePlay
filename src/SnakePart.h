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
#include <memory>
#include "GamePlay.h"
#include "GameGraphicFactory.h"
#include "Sprite.h"
#include "Rect.h"

using namespace std::tr1;
using namespace std;
using namespace mightysnake;

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

	bool IntersectRect(const Rect& boundingBox)
	{
		shared_ptr<Rect> snakeBox = GetBoundingBox();

		snakeBox->x1 += 2;
		snakeBox->y1 += 2;
		snakeBox->x2 -= 2;
		snakeBox->y2 -= 2;
	
		return snakeBox->Intersect(&boundingBox);
	}

	shared_ptr<Rect> GetBoundingBox()
	{
		assert( 0 != mSnakeSkin);
		return mSnakeSkin->GetBoundingBoxEx(x,y,rot);
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

	void SetGraphics(shared_ptr<GameGraphicFactory>& graphics) 
	{
      mGraphics = graphics;
	}

	void InitSkin()
	{
		switch(mSnakeMorphology)
		{
			case SnakePart::SNAKE_PART_TAIL_UP:
				mSnakeSkin = mGraphics->GetSprite(GameGraphicFactory::TILE_TAIL_UP);
				break;
			case SnakePart::SNAKE_PART_BODY_UP:
				mSnakeSkin = mGraphics->GetSprite(GameGraphicFactory::TILE_BODY_UP);
				break;
			case SnakePart::SNAKE_PART_HEAD_UP:
				mSnakeSkin = mGraphics->GetSprite(GameGraphicFactory::TILE_HEAD_UP);
				break;
			case SnakePart::SNAKE_PART_TAIL_DOWN:
				mSnakeSkin = mGraphics->GetSprite(GameGraphicFactory::TILE_TAIL_DOWN);
				break;
			case SnakePart::SNAKE_PART_BODY_DOWN:
				mSnakeSkin = mGraphics->GetSprite(GameGraphicFactory::TILE_BODY_DOWN);
				break;
			case SnakePart::SNAKE_PART_HEAD_DOWN:
				mSnakeSkin = mGraphics->GetSprite(GameGraphicFactory::TILE_HEAD_DOWN);
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
private:
	float x;
	float y;
	float dx,dy;
	float rot;
public:
	float GetX() const { return x; }
	void SetX(float val) { x = val; }
	float GetY() const { return y; }
	void SetY(float val) { y = val; }
	float GetDy() const { return dy; }
	void SetDy(float val) { dy = val; }
	float GetDx() const { return dx; }
	void SetDx(float val) { dx = val; }
	float GetRot() const { return rot; }
	void SetRot(float val) { rot = val; }
private:
	ESnakeMorphology mSnakeMorphology;
	shared_ptr<Sprite> mSnakeSkin;
	shared_ptr<GameGraphicFactory> mGraphics;
};