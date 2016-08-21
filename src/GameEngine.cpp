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
#include "GameEngine.h"
#include "HgeGameEngine.h"

namespace mightysnake 
{


GameEngine::GameEngine(void)
{
}

GameEngine::~GameEngine(void)
{
}

void GameEngine::Create()
{

	throw std::exception("The method or operation is not implemented.");
}

float GameEngine::TimerGetDelta()
{
	throw std::exception("The method or operation is not implemented.");
}

void GameEngine::StartRender()
{
	throw std::exception("The method or operation is not implemented.");
}

void GameEngine::EndRender()
{
	throw std::exception("The method or operation is not implemented.");
}

void GameEngine::Destroy()
{
	throw std::exception("The method or operation is not implemented.");

}

void GameEngine::SetUpdater( bool (*updateFn)() )
{
	throw std::exception("The method or operation is not implemented.");

}

void GameEngine::SetRenderer( bool (*renderFn)() )
{
	throw std::exception("The method or operation is not implemented.");

}

shared_ptr<GameGraphicFactory> GameEngine::GetGraphicFactory()
{
	throw std::exception("The method or operation is not implemented.");

}

bool GameEngine::InputGetKeyState( int key )
{
	throw std::exception("The method or operation is not implemented.");

}

void GameEngine::Start()
{
	throw std::exception("The method or operation is not implemented.");

}


}
