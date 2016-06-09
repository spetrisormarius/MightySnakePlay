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

class GamePlay;
class SnakePlayer;
class SnakeFood;
//class SnakeHit;

#include "hge.h"
#include "TileInfo.h"
#include <vector>
using std::vector;
#include "hgesprite.h"
#include "hgefont.h"

using namespace std::tr1;
using namespace std;

class SnakeGame
{
public:
    SnakeGame();
public:
    virtual ~SnakeGame(void);
public:
	int Init(HGE* pEngine, float widthSurface, float heightSurface, hgeFont* pFnt);

	//game logic: update position, get input
	bool UpdateFrame();
	// draw
	void Render();
public:
	void Create(HGE*  pEngine);
public:
	void GetSurfaceDimension(float& width, float& height);
    void SetSurfaceDimension(float Width, float Height);
	hgeFont* GetFont();
public:
    HGE* GetScreen(void);
    int GetHighScore() {return mHighScore;}
public:
    void OnDestroy(void);
public:
	void PersistHighScore(void);
private:
    friend class GamePlay;
    int ChangeState(GamePlay* state);
    GamePlay* mpState;
private:
    HGE* mpScreen;
private:
    float mSurfaceWidth;
    float mSurfaceHeight;
private:
    int mScore;
    int mHighScore;
public:
	void LoadHighScore(void);
public:
	void SetFont( hgeFont*  pFnt );
private:
	hgeFont	*mFnt;
private:
	string GetKey(void);
	string GetEncryptedHighScore(string highScore);
	static const int KEY_LEN = 15;
	float mSnakeSpeed;
public:
	void SetLevel( short level );
public:
	void Destroy(void);
	void SetHighScore( int score );
	SnakePlayer* GetSnakePlayer() 
	{
		return mpPlayer;
	}
	SnakeFood* GetSnakeFood() 
	{
		return mpSnakeFood;
	}
	void SetScore( int score );
private:
	SnakePlayer* mpPlayer;
	SnakeFood* mpSnakeFood;
public:
	int GetScore(void);
	float GetSnakeSpeed();
	short GetLevel();
	void SetPlayer( SnakePlayer*  pPlayer );
	void SetSnakeFood( SnakeFood*  pSnakeFood );
private:
	short mLevel;
};
