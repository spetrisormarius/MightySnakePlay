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
#include "GameGraphicFactory.h"

using namespace std::tr1;
using namespace std;

namespace mightysnake 
{
class HgeGraphicFactory: public GameGraphicFactory
{
public:
	HgeGraphicFactory();

	~HgeGraphicFactory(void);

	void init(HGE* engine);
	//static HgeGraphicFactory& instance();

	shared_ptr<SpriteAnimation> GetSpriteAnimation( enum GameGraphicFactory::GameTiles index );
	float GetSnakePartWidth();
	float GetSnakePartHeight();
	shared_ptr<Sprite> CreateCornerSpace();
	shared_ptr<Sprite>  CreatePoint();
	shared_ptr<Sprite> CreateGrid();
	shared_ptr<Sprite> GetSprite( enum GameTiles index );
	TileInfo GetAnimationTile(enum GameTiles index);
private:
	void doInit();
	void CreateSpriteTile(GameTiles type);
	void CreateAnimationTile(GameTiles type);
	map < GameTiles, TileInfo > mAnimationParts;
	map < GameTiles, shared_ptr<hgeSprite> > mSpriteParts;

	float mSnakePartWidth;
	float mSnakePartHeight;

	HGE* mpEngine;
	HTEXTURE mTile;
	HTEXTURE mTileGrid;
	HTEXTURE mTileStartLogo;
public:
	shared_ptr<Sprite> CreateStartLogo(void);
};

}
