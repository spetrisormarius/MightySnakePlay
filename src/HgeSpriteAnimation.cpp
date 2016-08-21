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
#include "HgeSpriteAnimation.h"

namespace mightysnake 
{

	HgeSpriteAnimation::HgeSpriteAnimation( shared_ptr<hgeAnimation>& spriteAnimation ) :
HgeSprite(spriteAnimation),
mSpriteAnimation(spriteAnimation)
{
}

HgeSpriteAnimation::~HgeSpriteAnimation(void)
{
}

void HgeSpriteAnimation::Update( float fDeltaTime )
{
	mSpriteAnimation->Update(fDeltaTime);
}

}
