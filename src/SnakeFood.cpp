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
#include "SnakeFood.h"
#include <time.h>

SnakeFood::SnakeFood()
{
	srand( (unsigned)time( NULL ) );
	mScorePrice = 0;
	mPosition.x = -1;
    mPosition.y = -1;
}

SnakeFood::~SnakeFood(void)
{
 SAFEDELETE(mpSnakeFoodSprite);
}


void SnakeFood::SetScorePrice(int price)
{
	mScorePrice = price;
}

int SnakeFood::GetScorePrice(void)
{
	return mScorePrice;
}
