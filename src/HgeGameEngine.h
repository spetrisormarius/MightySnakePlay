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
#include "GameEngine.h"
#include "HgeGraphicFactory.h"
#include "hge.h"
#include "Menu.h"
#include "HgeFont.h"

namespace mightysnake 
{

class HgeGameEngine : public GameEngine
{
public:
	HgeGameEngine(void);
	~HgeGameEngine(void);
	virtual void Create(void);
	virtual void Destroy();
	virtual shared_ptr<GameGraphicFactory> GetGraphicFactory();
	virtual void SetUpdater(bool (*updateFn)() );
	virtual void SetRenderer(bool (*renderFn)() );
	virtual bool InputGetKeyState(int key);
	virtual float TimerGetDelta();
	virtual void Start();
	virtual void StartRender();
	virtual void EndRender();
	virtual shared_ptr<Menu> GetMenu(MenuAction& menuAction);
	virtual shared_ptr<Font> GetFont();
private:
	shared_ptr<HgeGraphicFactory> mGraphicFactory;
	HGE * mpEngine;
	bool (*mUpdateFn)();
    bool (*mRenderFn)();
	shared_ptr<HgeFont> mFont;

};
}
