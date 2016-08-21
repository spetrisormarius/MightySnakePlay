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
#include "GamePlay.h"
#include "SnakeMainScreen.h"

class GameInit :
	public GamePlay,
	public MenuAction
{
public:

	GameInit(void):mSnakeMainScreen(*this)
	{
	}
public:

	virtual ~GameInit(void)
	{
		Destroy(NULL);
	}
	static GamePlay* Instance(void)
	{
		static GameInit game;
		return &game;
	}
public:
	//virtual void Init(SnakeGame* game, HGE* engine, float widthSurface, float heightSurface, hgeFont* fnt);
	virtual void Enter(SnakeGame* game);

	virtual bool UpdateFrame(SnakeGame* game);
	// draw
	virtual void Render(SnakeGame* game);
	virtual void OnPlay();
	virtual void OnLevel(short level);
private:
	void Destroy(SnakeGame* game);
	void UpdateMainScreen(void);
	SnakeMainScreen mSnakeMainScreen;
	SnakeGame* mpGame;
};
