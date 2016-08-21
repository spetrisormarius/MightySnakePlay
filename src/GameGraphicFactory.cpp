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
#include "GameGraphicFactory.h"
//#include "HgeGraphicFactory.h"

namespace mightysnake 
{

GameGraphicFactory::GameGraphicFactory(void)
{
}

GameGraphicFactory::~GameGraphicFactory(void)
{
}

//GameGraphicFactory& GameGraphicFactory::instance()
//{
//	static HgeGraphicFactory factory;
//
//	return factory;
//}

shared_ptr<Sprite> GameGraphicFactory::GetSprite( enum GameTiles index )
{
	return shared_ptr<Sprite>(new Sprite());
}

float GameGraphicFactory::GetSnakePartHeight()
{
	throw std::exception("The method or operation is not implemented.");
}

float GameGraphicFactory::GetSnakePartWidth()
{
	throw std::exception("The method or operation is not implemented.");
}

shared_ptr<Sprite> GameGraphicFactory::CreateCornerSpace()
{
	throw std::exception("The method or operation is not implemented.");
}

//end namespace
}
