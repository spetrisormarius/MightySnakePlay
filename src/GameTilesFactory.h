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
#include <utility>
#include <map>
using namespace std;
#include "TileInfo.h"
#include "hgeanim.h"
#include <memory>

using namespace std::tr1;
using namespace std;

class GameTilesFactory
{
public:
	GameTilesFactory();
	~GameTilesFactory(void);
	enum SnakeTilesType
	{
		TILE_TYPE_TAIL_UP,
		TILE_TYPE_TAIL_DOWN,

		TILE_TYPE_BODY_UP,
		TILE_TYPE_BODY_DOWN,

		TILE_TYPE_HEAD_UP,
		TILE_TYPE_HEAD_DOWN,
		TILE_TYPE_FOOD,
		TILE_TYPE_BIG_FOOD,
		TILE_TYPE_HIT,
		TILE_CORNER_UP,
		TILE_CORNER_DOWN
	};

	static void init(HGE* engine);
	static GameTilesFactory& instance();

	hgeAnimation* CreateAnimation( enum SnakeTilesType index );
	float GetSnakePartWidth();
	float GetSnakePartHeight();
	shared_ptr<hgeSprite> CreateCornerSpace();
	shared_ptr<hgeSprite>  CreatePoint();
	shared_ptr<hgeSprite> CreateGrid();
	shared_ptr<hgeSprite> GetSpriteTile( enum SnakeTilesType index );
	TileInfo GetAnimationTile(enum SnakeTilesType index);
private:
	void CreateSpriteTile(SnakeTilesType type);
	void CreateAnimationTile(SnakeTilesType type);
	map < SnakeTilesType, TileInfo > mAnimationParts;
	map < SnakeTilesType, shared_ptr<hgeSprite> > mSpriteParts;

	float mSnakePartWidth;
	float mSnakePartHeight;

	static HGE* sEngine;
	static HTEXTURE sTile;
	HTEXTURE mTileGrid;
	HTEXTURE mTileStartLogo;
public:
	shared_ptr<hgeSprite> CreateStartLogo(void);
};

