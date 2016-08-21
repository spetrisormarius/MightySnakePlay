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
#include "HgeRect.h"
#include <assert.h>

namespace mightysnake
{

HgeRect::HgeRect(void)
{
}

HgeRect::~HgeRect(void)
{
}

bool HgeRect::Intersect( const Rect *rect ) const
{
	assert( 0 != rect);
     
	hgeRect rectTmp;
	rectTmp.x1 = rect->x1;
	rectTmp.x2 = rect->x2;
	rectTmp.y1 = rect->y1;
	rectTmp.y2 = rect->y2;

	return this->rect.Intersect(&rectTmp);

}

void HgeRect::Clear()
{
	rect.x1 = x1;
	rect.x2 = x2;
	rect.y1 = y1;
	rect.y2 = y2;

	rect.Clear();

	x1 = rect.x1;
	x2 = rect.x2;
	y1 = rect.y1;
	y2 = rect.y2;

}

}

