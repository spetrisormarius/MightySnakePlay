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

//#include "hge.h"
#include "SnakeGame.h"
//#include "hgefont.h"
#include "GameEngineFactory.h"

using namespace mightysnake;

class GameMain        
{
public:
	static GameMain& GetInstance();
	
	bool Create(void);
	bool Run();
	void Destroy(void);
	static bool FrameFunc();
	static bool RenderFunc();
	void ErrorMessage();
private:
	GameMain(void);
	~GameMain(void);
	bool UpdateFrame();
	void Render();
    
	//HGE * mpEngine;
	SnakeGame mSnakeGame;
	//hgeFont* mpFnt;
    shared_ptr<Font> mFnt;
};
