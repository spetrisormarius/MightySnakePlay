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
#include "SnakeGame.h"
#include "GameInit.h"
#include "GameGraphicFactory.h"
#include <fstream>

using namespace std;

SnakeGame::SnakeGame()
: mpPlayer(NULL),
  mpSnakeFood( NULL ),
  mScore(0),
  mHighScore(0),
  mSnakeSpeed(0.2f),
  mLevel(0),
  mSurfaceWidth(0),
  mSurfaceHeight(0)
{
    mpState = GameInit::Instance();
}

SnakeGame::~SnakeGame(void)
{
	Destroy();
}

int SnakeGame::Init( shared_ptr<GameEngine> gameEngine )
{
	assert( 0 != gameEngine);
	assert( 0 != mSurfaceWidth);
	assert( 0 != mSurfaceHeight);
	assert( 0 != mFnt);

	mGameEngine = gameEngine;

    mpState->Enter(this);

    return 0;
}

int SnakeGame::ChangeState(GamePlay* state)
{
    mpState = state;
    return 0;
}
        
void SnakeGame::Create()
{
	if (0 == mFnt) {
		MessageBox(NULL, "Game error: Font missing", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	 
}

void SnakeGame::GetSurfaceDimension( float& width, float& height )
{
    width = mSurfaceWidth;
    height = mSurfaceHeight;
}

void SnakeGame::SetSurfaceDimension(float Width, float Height)
{
    mSurfaceWidth = Width;
    mSurfaceHeight = Height;
}	

void SnakeGame::SetFont( shared_ptr<Font>& pFnt )
{
	mFnt = pFnt;
}

shared_ptr<Font>& SnakeGame::GetFont()
{
	return mFnt;
}

void SnakeGame::PersistHighScore(void)
{
	try {
	  stringstream ss;
	  ss << mHighScore;
	  string highScore = ss.str();

	  highScore = GetEncryptedHighScore(highScore);

	  ofstream out("mysnk.dat");
	  out << highScore;
	  out.close();
	} 
	catch(...) {
		MessageBox(NULL, "Game error: Font missing", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

}

string SnakeGame::GetKey(void)
{
	unsigned char k1[KEY_LEN + 1] = {110, 137, 130, 175, 8,  82,  60,  99,  42, 141,  19,  94, 233,  44, 114, 0};

	string key(k1, k1+KEY_LEN);
	//stringstream ss;
	//ss << key;
	//return ss.str();
	return key;
}

void SnakeGame::LoadHighScore(void)
{
	ifstream in("mysnk.dat");
	string highScore;
	in >> highScore;
 
    highScore = GetEncryptedHighScore(highScore);
    
	istringstream ss(highScore);
     
	ss >> mHighScore;
}

string SnakeGame::GetEncryptedHighScore(string highScore)
{
	string highScoreKey = GetKey();
    char* newHighScore = const_cast<char* >(highScore.c_str());
	for (int i = 0; i < highScore.length(); i ++) 
	{
		if ( i <= KEY_LEN) {
			newHighScore[i] = newHighScore[i] ^ highScoreKey[i];
		}
	}

	return string(newHighScore);
}

void SnakeGame::SetLevel( short level )
{  
	switch (level)
	{
	case 0:
		mSnakeSpeed = 0.2f;
		break;
	case 1:
		mSnakeSpeed = 0.2f/2;
		break;
	case 2:
		mSnakeSpeed = 0.2f/4;
		break;
	case 3:
		mSnakeSpeed = 0.2f/6;
		break;
	case 4:
		mSnakeSpeed = 0.2f/8;
		break;
	}

    mLevel = level;    
}


//game logic: update position, get input
bool SnakeGame::UpdateFrame()
{
	assert( 0 != mpState);
	return mpState->UpdateFrame(this);
};

// draw
void SnakeGame::Render() {
	assert( 0 != mpState);
	mpState->Render(this);
}


void SnakeGame::Destroy(void)
{
	/*PersistHighScore();*/
}

void SnakeGame::SetHighScore( int score )
{
	mHighScore = score;
}

void SnakeGame::SetScore( int score )
{
	mScore = score;
}

int SnakeGame::GetScore(void)
{
	return mScore;
}

float SnakeGame::GetSnakeSpeed()
{
	return mSnakeSpeed;
}

short SnakeGame::GetLevel()
{
	return mLevel;
}

void SnakeGame::SetPlayer( SnakePlayer* pPlayer )
{
	mpPlayer = pPlayer; 
}

void SnakeGame::SetSnakeFood( SnakeFood* pSnakeFood )
{
	mpSnakeFood = pSnakeFood;
}

shared_ptr<GameEngine> SnakeGame::GetEngine( void )
{
return mGameEngine;
}
