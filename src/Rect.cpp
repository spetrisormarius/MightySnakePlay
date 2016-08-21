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
#include "Rect.h"
#include <exception>
using namespace std;

namespace mightysnake 
{

Rect::Rect(void)
{
}

Rect::~Rect(void)
{
}

void Rect::Clear()
{
	throw std::exception("The method or operation is not implemented.");

}

bool Rect::Intersect( const Rect *rect ) const
{
	throw std::exception("The method or operation is not implemented.");

}

}
