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
//#include "hgeanim.h"
#include<vector>
using namespace std;
#include "SnakePart.h"
#include "GameGraphicFactory.h"
#include "GamePlay.h"
#include <sstream>
using namespace std;
#include "Vertex.h"
using namespace mightysnake;

class SnakePartList: public GamePlay
{
public:
	//game logic: update position, get input
	virtual void UpdateFrame(float fDeltaTime) ;
	// draw
	virtual void Render() ;

	SnakePartList(float snakePartWidth, float snakePartHeight);
	~SnakePartList(void);
	void Create(shared_ptr<GameGraphicFactory>& gameGraphicFactory);
	//void Destroy();
	bool IntersectHead(const Rect& boundingBox);
	bool Intersect(const Rect& boundingBox);
	void Grow(const Vertex& offsetPos);
	void StepDown(int ix);
	void StepUp(int ix);
	void StepRight(int ix);
	void StepLeft(int ix);
	bool IsSelfHit();
	Vertex GetHeadPosition();
	Vertex GetTailPosition();
	bool IsHeadEvenPosition();
	bool IsTailEvenPosition();
	int GetSize();
	bool IsBorder();
private:
	bool IsEvenPosition(const Vertex& r);
	void InitSnakeSkin(shared_ptr<GameGraphicFactory>& gameGraphicFactory);
	vector<SnakePart> mSnakeActor;
	Vertex mOriginOffset;
	float mSnakePartWidth;
	float mSnakePartHeight;

public:
	void tracePosition(const string & text, int ix);
	void RotateLeft(int ix);
	void RotateRight(int ix);
	void RotateUp(int ix);
	void RotateDown(int ix);
public:
	void SetSurfaceDimension( float nSurfaceWidth, float nSurfaceHeight );
private:
	bool CheckHit();
	float mSurfaceWidth;
	float mSurfaceHeight;
	bool mIsHit;
	shared_ptr<GameGraphicFactory> mGameGraphicFactory;
public:

	bool IsHit(void)
	{
		return mIsHit;
	}

	void ResetHit(void)
	{
		mIsHit = false;
	}
	int GetHeadMorphology();
private:
	bool IsBorder(float x, float y);
public:
	Vertex GetOriginOffset(void);
};

