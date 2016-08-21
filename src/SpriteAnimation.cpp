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
#include "SpriteAnimation.h"
#include <exception>

namespace mightysnake
{

SpriteAnimation::SpriteAnimation(void)
{
}

SpriteAnimation::~SpriteAnimation(void)
{
}

void SpriteAnimation::SetMode( int flag )
{
	throw std::exception("The method or operation is not implemented.");
}

bool SpriteAnimation::IsPlaying()
{
	throw std::exception("The method or operation is not implemented.");
}

void SpriteAnimation::Update( float fDeltaTime )
{
	throw std::exception("The method or operation is not implemented.");
}

}