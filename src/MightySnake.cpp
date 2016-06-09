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
 // MightySnake.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MightySnake.h"
#include "GameMain.h"
#include "InputParameters.h"
#include <shellapi.h>
#include <string>

using std::string;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{

	//_set_abort_behavior( 0, _WRITE_ABORT_MSG);

	int argCount;
	LPWSTR * argList;
	argList = CommandLineToArgvW(GetCommandLineW(), &argCount);
	if( argCount > 1) {
		if ( wstring(argList[1]) == wstring(L"d") ) 
		{
			InputParameters::Instance().SetDebugMode(true);
		}
	}
	LocalFree(argList);

	GameMain& game = GameMain::GetInstance();
	
    // Tries to initiate HGE with the states set.
    // If something goes wrong, "false" is returned
    // and more specific description of what have
    // happened can be read with System_GetErrorMessage().
    if( game.Create()  )
    {
		game.Run();
    }
    else
    {	
		game.ErrorMessage();
    }

	// Now ESC has been pressed or the user
	// has closed the window by other means.
	game.Destroy();

    return 0;
}
