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
#include "HgeSprite.h"
#include <exception>
#include <hgerect.h>
#include "Rect.h"
#include "hgerect.h"


namespace mightysnake 
{

HgeSprite::HgeSprite(shared_ptr<hgeSprite> sprite):
mSprite(sprite)
{
}

HgeSprite::~HgeSprite(void)
{
}

shared_ptr<Rect> HgeSprite::GetBoundingBoxEx( float x, float y, float rot )
{
	hgeRect rect;
	mSprite->GetBoundingBoxEx(x, y, rot, 1, 1, &rect);

	shared_ptr<Rect> box = shared_ptr<HgeRect>(new HgeRect());

	box->x1 = rect.x1;
	box->x2 = rect.x2;
	box->y1 = rect.y1;
	box->y2 = rect.y2;
	
	return box;
}

void HgeSprite::SetHotSpot( float x, float y ) 
{
	mSprite->SetHotSpot(x, y);
}

void HgeSprite::RenderEx( float x, float y, float rot )
{
	mSprite->RenderEx(x,y, rot);
}

float HgeSprite::GetWidth()
{
	return mSprite->GetWidth();
}

float HgeSprite::GetHeight()
{
	return mSprite->GetHeight();
}

void HgeSprite::Render( float x, float y )
{
	mSprite->Render(x, y);
}

shared_ptr<Rect> HgeSprite::GetBoundingBox( float x, float y )
{
	shared_ptr<Rect> box = shared_ptr<HgeRect>(new HgeRect());

	if ( -1 == x ||  -1 == y) {

		box->Clear();
		return box;
	} 

	hgeRect rect;
	mSprite->GetBoundingBox(x, y, &rect);

	box->x1 = rect.x1;
	box->x2 = rect.x2;
	box->y1 = rect.y1;
	box->y2 = rect.y2;

	return box;

}


//end namespace
}