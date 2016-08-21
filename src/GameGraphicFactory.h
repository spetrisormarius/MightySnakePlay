/* 
 * Copyright 2016 Petrisor Marius Stoian <spetrisormarius@yahoo.com>
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
#include "Sprite.h"
#include "SpriteAnimation.h"

using namespace mightysnake;
using namespace std::tr1;

namespace mightysnake 
{

class GameGraphicFactory
{
public:
	GameGraphicFactory(void);
	virtual ~GameGraphicFactory(void);
	enum GameTiles
	{
		TILE_TAIL_UP,
		TILE_TAIL_DOWN,

		TILE_BODY_UP,
		TILE_BODY_DOWN,

		TILE_HEAD_UP,
		TILE_HEAD_DOWN,
		TILE_FOOD,
		TILE_BIG_FOOD,
		TILE_HIT,
		TILE_CORNER_UP,
		TILE_CORNER_DOWN
	};

	//static GameGraphicFactory& instance();

	virtual shared_ptr<Sprite> GetSprite( enum GameTiles index );
	virtual float GetSnakePartHeight();
	virtual float GetSnakePartWidth();
	virtual shared_ptr<SpriteAnimation> GetSpriteAnimation( GameTiles index ) 
	{
		//reimplemnt this - no distnction betwenn hgeSprite and hgeSprite animation  when using sprite?
		throw std::exception("The method or operation is not implemented.");
	}
	virtual shared_ptr<Sprite> CreateStartLogo() 
	{
		throw std::exception("The method or operation is not implemented.");
	}
	virtual shared_ptr<Sprite> CreateCornerSpace();
	virtual shared_ptr<Sprite> CreateGrid() 
	{
		throw std::exception("The method or operation is not implemented.");
	}
	virtual shared_ptr<Sprite> CreatePoint() 
	{
		throw std::exception("The method or operation is not implemented.");
	}
};

}
