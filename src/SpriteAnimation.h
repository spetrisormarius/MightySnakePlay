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

#include "Sprite.h"
namespace mightysnake 
{

class SpriteAnimation :
	public virtual Sprite
{
public:
	enum {
		ANIM_LOOP,
		ANIM_PINGPONG
	};

	SpriteAnimation(void);
	virtual ~SpriteAnimation(void);

	virtual void SetMode( int flag );
	virtual bool IsPlaying();
	virtual void Update( float fDeltaTime );

};

}

