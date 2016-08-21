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
 #include "StdAfx.h"
#include "HgeMenu.h"
#include "menuitem.h"
#include "surface.h"
#include "MenuAction.h"

namespace mightysnake
{

	HgeMenu::HgeMenu( MenuAction& pAction ,HGE * pEngine, hgeFont* pFont ) :
mMenuAction(pAction),
mpEngine(pEngine),
mpFnt(pFont)
{
	mLevels.push_back("Easy");
	mLevels.push_back("Medium");
	mLevels.push_back("Hard");
	mLevels.push_back("Expert");
	mLevels.push_back("Intense");
 
	mMaxLevelIndex = mLevels.size();
	mLevelIndex = 0;
}


HgeMenu::~HgeMenu(void)
{
}


void HgeMenu::Render(void)
{
	if (0 == mpGui)
	{
		return;
	}
	mpGui->Render();
}

bool HgeMenu::UpdateInput(void)
{
	if (!mpEngine || !mpGui)
	{
		return true;
	}

	float dt = mpEngine->Timer_GetDelta();
	int id;
	static int lastid=0;

	// If ESCAPE was pressed, tell the GUI to finish
	//if(mEngine->Input_GetKeyState(HGEK_ESCAPE))
	//{
	//	lastid = 5; 
	//	mGui->Leave(); 
	//}

	// We update the GUI and take an action if
	// one of the menu items was selected
	id=mpGui->Update(dt);
	if(id) 
	{
		switch(id)
		{
		case 1:
			mMenuAction.OnPlay();
			break;
		case 2:
			hgeGUIMenuItem* levelItem = (hgeGUIMenuItem*) mpGui->GetCtrl(2);
	           if (levelItem)
	           {	
				mLevelIndex++;
				if (mLevelIndex >= mMaxLevelIndex)
				{
					mLevelIndex = 0;
				}
				assert( mLevelIndex < mLevels.size());
				levelItem->SetTitle( mLevels.at(mLevelIndex).c_str() );

			} else {
				return true;
			}
			mMenuAction.OnLevel(mLevelIndex);

			break;
		}

	}

	return false;
}

bool HgeMenu::Create(void)
{
	if (0 == mpEngine)
	{
		return false;
	}

	mCursor=mpEngine->Texture_Load("cursor.png");
	mSnd=mpEngine->Effect_Load("menu.wav");
	//snd=0;
	if( (!mCursor) || (!mSnd) )
	{
		// If one of the data files is not found, display
		// an error message and shutdown.
		MessageBox(NULL, "Can't load BG.PNG, CURSOR.PNG or MENU.WAV", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);

		return false;
	}

	mpSprCursor=new hgeSprite(mCursor,0,0,32,32);

	// Create and initialize the GUI
	mpGui=new hgeGUI();

	float startX = SURF_W / 2.0f ;
	float startY = SURF_H2 / 2.0f + 40;

	mpGui->AddCtrl(new hgeGUIMenuItem(1,mpFnt,mSnd,startX,startY, 0.0f,"Play"));
	assert( mLevelIndex < mLevels.size());
	char* title = const_cast<char*>( mLevels.at(mLevelIndex).c_str() );
	mpGui->AddCtrl(new hgeGUIMenuItem(2,mpFnt,mSnd,startX,startY + 30, 0.1f, title ));

	mpGui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	mpGui->SetCursor(mpSprCursor);
	mpGui->SetFocus(1);
	mpGui->Enter();
	return true;
}

void HgeMenu::Destroy(void)
{
	delete mpGui;
	delete mpSprCursor;

	mpEngine->Effect_Free(mSnd);

	mpEngine->Texture_Free(mCursor);
}

}