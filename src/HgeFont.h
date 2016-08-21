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
#include "font.h"
#include <hgefont.h>

namespace  mightysnake
{
class HgeFont :
	public Font
{
public:

	HgeFont(void):
	  mpFnt(new hgeFont("font1.fnt"))
	{
	}

	virtual ~HgeFont(void)
	{
		delete mpFnt;
		mpFnt = NULL;
	}
	virtual float		GetHeight() 
	{
	return mpFnt->GetHeight();
	}
	virtual void		SetColor(unsigned long col) 
	{
		mpFnt->SetColor(col);
	}

	virtual void		SetScale(float scale) 
	{
		mpFnt->SetScale(scale);
	}
	virtual float		GetScale() 
	{
	return mpFnt->GetScale();
	}

	virtual float		GetStringWidth(const char *string) const 
	{
		return mpFnt->GetStringWidth(string);
	}
	virtual void Render(float x, float y,  int align, const char *string)
	{
		int hgeAlign = HGETEXT_LEFT;
		if ( TEXT_CENTER == align)
		{
			hgeAlign = HGETEXT_CENTER;
		}
		else if( TEXT_LEFT == align)
		{
			hgeAlign = HGETEXT_LEFT;
		}

		mpFnt->Render(x, y, hgeAlign, string);
	}

	virtual void	SetBlendMode(int blend) 
	{
		mpFnt->SetBlendMode(BLEND_DEFAULT_Z);
		//mFnt->SetBlendMode(BLEND_DEFAULT_Z);

	}
	hgeFont* GetFont() 
	{
		return mpFnt;
	}

private:
	hgeFont* mpFnt;
};

}