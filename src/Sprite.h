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
using namespace std::tr1;

namespace mightysnake {

class Rect;

class Sprite
{
public:
	Sprite(void);
	virtual ~Sprite(void);
	virtual shared_ptr<Rect> GetBoundingBoxEx( float x, float y, float rot ) ;
	virtual void SetHotSpot( float x, float y ) ;
	virtual void RenderEx( float x, float y, float rot );
	virtual float GetWidth();
	virtual float GetHeight();
	virtual void Render( float x, float y );
	virtual shared_ptr<Rect> GetBoundingBox( float x, float y );
	virtual void SetFlip( bool param1, bool param2 );
};

}