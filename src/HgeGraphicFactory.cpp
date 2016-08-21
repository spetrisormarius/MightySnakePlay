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
 #include "StdAfx.h"
#include "HgeGraphicFactory.h"
#include "hgecolor.h"
#include "InputParameters.h"
#include "HgeSpriteAnimation.h"

namespace  mightysnake 
{

//HGE* HgeGraphicFactory::sEngine = 0;
//HTEXTURE HgeGraphicFactory::sTile = 0;

HgeGraphicFactory::HgeGraphicFactory():
mSnakePartWidth(0),
mSnakePartHeight(0),
mTileGrid(0)
{

}

void HgeGraphicFactory::doInit() 
{
	GameTiles tileTypeAnim[] =
	{	TILE_FOOD,
	TILE_BIG_FOOD,
	TILE_HIT
	};

	for ( int i = 0; i < 3; i++)
	{
		CreateAnimationTile(tileTypeAnim[i]);
	}

	GameTiles tileType[] =
	{
		TILE_TAIL_UP,
		TILE_TAIL_DOWN,
		TILE_BODY_UP,
		TILE_BODY_DOWN,
		TILE_HEAD_UP,
		TILE_HEAD_DOWN,
		TILE_CORNER_UP,
		TILE_CORNER_DOWN
	};

	for ( int i = 0; i < 8; i++)
	{
		CreateSpriteTile(tileType[i]);
	}
}



HgeGraphicFactory::~HgeGraphicFactory(void)
{
//	sEngine->Texture_Free(mTileStartLogo);
//#ifdef _DEBUG
//	sEngine->Texture_Free(mTileGrid);
//#endif
//	sEngine->Texture_Free(sTile);

}


shared_ptr<SpriteAnimation> HgeGraphicFactory::GetSpriteAnimation( enum GameTiles index )
{
	TileInfo skin = GetAnimationTile(index);
	shared_ptr<hgeAnimation> pTile( new hgeAnimation(skin.tile, skin._frames, skin._FPS, skin._x, skin._y, skin._w, skin._h));
	pTile->SetHotSpot(0, 0);
	pTile->Play();

	return shared_ptr<SpriteAnimation>(new HgeSpriteAnimation(pTile));
}

void HgeGraphicFactory::CreateAnimationTile(GameTiles type)
	{
		TileInfo snakeinfo;		
		
		snakeinfo._FPS = 5;
		switch (type)
		{
		case TILE_FOOD:
			snakeinfo.tile = mTile;
			snakeinfo._w = 16;
			snakeinfo._h = 16;
			snakeinfo._frames = 2;
			snakeinfo._x = 0;
			snakeinfo._y = 20;
			snakeinfo._FPS = 10;
			break;
		case TILE_BIG_FOOD:
			snakeinfo.tile = mTile;
			snakeinfo._w = 25;
			snakeinfo._h = 25;
			snakeinfo._frames = 2;
			snakeinfo._x = 160;
			snakeinfo._y = 0;
			snakeinfo._FPS = 15;
			break;
		case  TILE_HIT:
			snakeinfo.tile = mTile;
			snakeinfo._w = 23;
			snakeinfo._h= 23;
			snakeinfo._frames = 6;
			snakeinfo._x = 0;
			snakeinfo._y = 36;
			snakeinfo._FPS = 10;
			break;
		}
		
		mAnimationParts.insert( make_pair(type, snakeinfo));
	}

TileInfo HgeGraphicFactory::GetAnimationTile( enum GameTiles index )
{
	map < GameTiles, TileInfo >::iterator itParts = mAnimationParts.find(index);
	if (itParts != mAnimationParts.end())
	{
		return itParts->second;
	}
	else 
		throw exception("tiles factory error");
};

float HgeGraphicFactory::GetSnakePartWidth()
{
	return mSnakePartWidth;
}

float HgeGraphicFactory::GetSnakePartHeight()
{
	return mSnakePartHeight;
}

 void HgeGraphicFactory::init(HGE* engine)
{
	mpEngine = engine;
	assert(0 != mpEngine);

#ifdef _DEBUG
	mTile = mpEngine->Texture_Load( "game_tiles_debug.png" );
#else 
	if (InputParameters::Instance().IsDebug())
	{
		mTile = mpEngine->Texture_Load( "game_tiles_debug.png" );
	} 
	else 
	{
		mTile = mpEngine->Texture_Load( "game_tiles.png" );
	}
#endif

	assert ( 0 != mTile );
	doInit();
}


 shared_ptr<Sprite> HgeGraphicFactory::CreateCornerSpace()
 {
	 //when texture = 0 the texture is  a white rect
	 shared_ptr<hgeSprite>  cornerSpace (new hgeSprite(0, 0, 0, 16, 16));

	 if (InputParameters::Instance().IsDebugAnimation())
	 {
		 hgeColor whiteColor(1, 1, 1, 1);
		 cornerSpace->SetColor(whiteColor.GetHWColor());
	 } 
	 else {
		 hgeColor blackColor(0,0,0,1);
		 cornerSpace->SetColor(blackColor.GetHWColor());
	 }

	 return shared_ptr<Sprite> (new HgeSprite(cornerSpace));
 }


 shared_ptr<Sprite> HgeGraphicFactory::CreatePoint()
 {
	 //when texture = 0 the texture is  a white rect
	 shared_ptr<hgeSprite> point(new hgeSprite(0, 0, 0, 1, 1));
	 hgeColor whiteColor(1, 1, 1, 1);
	 point->SetColor(whiteColor.GetHWColor());

	 return shared_ptr<Sprite>(new HgeSprite(point));
 }


shared_ptr<Sprite> HgeGraphicFactory::CreateGrid()
 {
	 assert(0 != mpEngine);

	 mTileGrid = mpEngine->Texture_Load("grid2.png");
	 //hge->Texture_Free(bgtex);

	 assert(0 != mTileGrid);

     shared_ptr<hgeSprite> grid (new hgeSprite(mTileGrid, 0, 0, 16, 16));

	 //grid->SetBlendMode(BLEND_COLORADD | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	 // grid->SetBlendMode(BLEND_COLORADD | BLEND_ALPHAADD | BLEND_ZWRITE);
	 return shared_ptr<Sprite>(new HgeSprite(grid));
 }


 void HgeGraphicFactory::CreateSpriteTile(GameTiles type)
 {
	 TileInfo snakeinfo;		

	 switch (type)
	 {
		 case TILE_BODY_UP:
		 	snakeinfo.tile = mTile;
		 	snakeinfo._w = 20;
		 	snakeinfo._h = 20;
		 	snakeinfo._x = 0;
		 	snakeinfo._y = 0;
		 	break;
		 case TILE_HEAD_UP:
		 	snakeinfo.tile = mTile;
		 	snakeinfo._w = 20;
		 	snakeinfo._h = 20;
		 	snakeinfo._x = 80;
		 	snakeinfo._y = 0;
		 	mSnakePartWidth = snakeinfo._w - 4;
		 	mSnakePartHeight = snakeinfo._h - 4;
		 	break;
		 case TILE_TAIL_UP:
		 	snakeinfo.tile = mTile;
		 	snakeinfo._w = 20;
		 	snakeinfo._h = 20;
		 	snakeinfo._x = 120;
		 	snakeinfo._y = 0;
		 	break;
		 case TILE_BODY_DOWN:
			 snakeinfo.tile = mTile;
			 snakeinfo._w = 20;
			 snakeinfo._h = 20;
			 snakeinfo._x = 20;
			 snakeinfo._y = 0;
			 break;
		 case TILE_HEAD_DOWN:
			 snakeinfo.tile = mTile;
			 snakeinfo._w = 20;
			 snakeinfo._h = 20;
			 snakeinfo._x = 100;
			 snakeinfo._y = 0;
			 break;
		 case TILE_TAIL_DOWN:
			 snakeinfo.tile = mTile;
			 snakeinfo._w = 20;
			 snakeinfo._h = 20;
			 snakeinfo._x = 140;
			 snakeinfo._y = 0;
			 break;
		 case TILE_CORNER_UP:
			 snakeinfo.tile = mTile;
			 snakeinfo._w = 20;
			 snakeinfo._h = 20;
			 snakeinfo._x = 40;
			 snakeinfo._y = 0;
			 break;
		 case TILE_CORNER_DOWN:
			 snakeinfo.tile = mTile;
			 snakeinfo._w = 20;
			 snakeinfo._h = 20;
			 snakeinfo._x = 60;
			 snakeinfo._y = 0;
			 break;
	 }

	 hgeSprite* pTile = new hgeSprite(snakeinfo.tile, snakeinfo._x, snakeinfo._y, snakeinfo._w, snakeinfo._h);
	 pTile->SetHotSpot(2, 2);

	 mSpriteParts.insert( make_pair(type, pTile));
 }

 shared_ptr<Sprite> HgeGraphicFactory::GetSprite( enum GameTiles index )
 {
	 map < GameTiles, shared_ptr<hgeSprite> >::iterator itParts = mSpriteParts.find(index);
	 if (itParts != mSpriteParts.end())
	 {
		 return shared_ptr<Sprite>(new HgeSprite(itParts->second));
	 }
	 else 
		 throw exception("tiles factory error");
 };

 shared_ptr<Sprite> HgeGraphicFactory::CreateStartLogo(void)
 {
	assert(0 != mpEngine);

	mTileStartLogo = mpEngine->Texture_Load("MightySnakeLogo.png");

	assert(0 != mTileStartLogo);

	shared_ptr<hgeSprite> logo (new hgeSprite(mTileStartLogo, 0, 0, 640, 500));

	return shared_ptr<Sprite>( new HgeSprite(logo));
 }

//end namespace
 }
