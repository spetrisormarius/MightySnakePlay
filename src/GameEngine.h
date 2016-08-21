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
#include <memory>
using namespace std::tr1;
#include "GameGraphicFactory.h"
#include "Menu.h"
#include "MenuAction.h"
#include "Font.h"

namespace mightysnake 
{

class GameEngine
{
public:
	enum 
	{
    KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_ESCAPE
	};
	GameEngine(void);
	virtual ~GameEngine(void);
	virtual void Create();
	virtual void Destroy();
	virtual void SetUpdater(bool (*updateFn)() );
	virtual void SetRenderer(bool (*renderFn)() );
	virtual shared_ptr<GameGraphicFactory> GetGraphicFactory();
	virtual bool InputGetKeyState(int key);
	virtual shared_ptr<Menu> GetMenu(MenuAction& menuAction) 
	{
		throw std::exception("The method or operation is not implemented.");
	}
	virtual float TimerGetDelta();
	virtual void Start();
	virtual void StartRender();
	virtual void EndRender();
	virtual shared_ptr<Font> GetFont() 
	{
		throw std::exception("The method or operation is not implemented.");
	}
};

}
