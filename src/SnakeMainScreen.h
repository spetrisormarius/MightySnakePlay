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
//#include "HgeMenu.h"
#include "MenuAction.h"
//#include "hgesprite.h"
#include <memory>
#include <sstream>
#include "hgecolor.h"
#include "GameGraphicFactory.h"
using namespace std;
using namespace std::tr1;

#include "Sprite.h"
#include "Menu.h"
#include "Font.h"

using namespace mightysnake;


class SnakeMainScreen
{
public:

	SnakeMainScreen(MenuAction& menuAction):
	  mHighScore(0),
	  mMenuAction (menuAction)
	{
	}

	~SnakeMainScreen(void)
	{

	}

	void Init(shared_ptr<GameEngine> engine, shared_ptr<Font>& fnt) {
		assert ( 0 != fnt);
		assert ( 0 != engine);

		mMenu = engine->GetMenu(mMenuAction);

		if ( !mMenu->Create() )
		{
			engine->Destroy();
			return;
		}

		mStartLogoSprite = engine->GetGraphicFactory()->CreateStartLogo();
		mFnt = fnt;
	}

	virtual bool UpdateFrame()
	{
		if (0 != mMenu)
		{
			if (mMenu->UpdateInput()) return true;
		}
		return false;
	};

	// draw
	virtual void Render() {
		DisplayStartLogo();

		if (0 != mMenu)
		{
			mMenu->Render();
		}

	}

	virtual void Destroy() 
	{
		if ( 0 != mMenu.get())
		{
			mMenu->Destroy();
			mMenu.reset();
		}
	}
    void DisplayStartLogo() 
	{
			assert(0 != mStartLogoSprite);
			mStartLogoSprite->Render(0,0);

			DisplayMasterSnakeScore();
			DisplayMissionInfo();
			DisplayCredits();
	}

	void DisplayMasterSnakeScore(void)
	{
		stringstream ss;
		ss << mHighScore;
		string strScore = ss.str();

		//render Master Snake
		string masterSnake = "Master snake: " + strScore;
		hgeColor whiteColor(1, 1, 1, 1);
		mFnt->SetColor(whiteColor.GetHWColor());
		mFnt->SetScale(0.5f);
		mFnt->Render( 2 , 2, Font::TEXT_LEFT, masterSnake.c_str() );
          

	}
	void DisplayMissionInfo(void)
	{
		float heightFont = mFnt->GetHeight();

		string snakeMission = "Mission: Move with arrows. Eat food to grow. Become Master Snake.";
		hgeColor whiteColor(1, 1, 1, 1);
		mFnt->SetColor(whiteColor.GetHWColor());
		mFnt->SetScale(0.6f);
		float width = mFnt->GetStringWidth(snakeMission.c_str());
		mFnt->Render(mSurfaceWidth / 2.0f  , mSurfaceHeight - mSurfaceHeight / 8.0f, Font::TEXT_CENTER, snakeMission.c_str() );

	}

	void DisplayCredits(void)
	{
		string credits = "spetrisormarius@yahoo.com";
		hgeColor whiteColor(1, 1, 1, 0.3f);
		mFnt->SetColor(whiteColor.GetHWColor());
		//mFnt->SetBlendMode(BLEND_DEFAULT_Z);
		mFnt->SetScale(0.4f);
		float heightFont = mFnt->GetHeight() * mFnt->GetScale();
		mFnt->Render(0, mSurfaceHeight + 20 - heightFont, Font::TEXT_LEFT, credits.c_str() );

	}

	void SetDimension(float nSurfaceWidth, float nSurfaceHeight) 
	{
		mSurfaceWidth = nSurfaceWidth;
		mSurfaceHeight = nSurfaceHeight;
	}

	void SetHighScore( int highScore ) 
	{
		mHighScore = highScore;
	}


private:
	shared_ptr<Menu> mMenu;
	MenuAction& mMenuAction;
	shared_ptr<Sprite> mStartLogoSprite;
     shared_ptr<Font> mFnt;

	int mHighScore;
	float  mSurfaceWidth;
	float mSurfaceHeight;
};
