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
#include "HgeSprite.h"
#include "SpriteAnimation.h"
//#include <memory>
//using namespace std::tr1;
#include <hgeanim.h>

namespace mightysnake 
{

class HgeSpriteAnimation :
	private HgeSprite, public SpriteAnimation
{
public:
	HgeSpriteAnimation(shared_ptr<hgeAnimation>& spriteAnimation);
	virtual ~HgeSpriteAnimation(void);
	virtual void Update( float fDeltaTime );

private:
	shared_ptr<hgeAnimation> mSpriteAnimation;
};

}
