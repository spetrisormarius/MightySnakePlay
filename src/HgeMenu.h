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
#include "hgegui.h"
#include "hgefont.h"
#include "hgeguictrls.h"

#include <vector>
#include <string>
#include <memory>
using namespace std;
using namespace std::tr1;

#include "Menu.h"
class MenuAction;

namespace mightysnake 
{

	class HgeMenu : public Menu
{
public:
	HgeMenu(MenuAction& pAction ,HGE * pEngine, hgeFont* pFont);
	~HgeMenu(void);
	void Render(void);
	bool UpdateInput(void);
public:
	bool Create(void);
public:
	void Destroy(void);
private:
	// Some resource handles
	HEFFECT mSnd;
	HTEXTURE mCursor;

	// Pointers to the HGE objects we will use
	hgeGUI *mpGui;
	hgeFont	*mpFnt;
	hgeSprite *mpSprCursor;

	HGE* mpEngine;
	
	MenuAction& mMenuAction;
	vector<string> mLevels;
	int mLevelIndex;
	int mMaxLevelIndex;
};

}