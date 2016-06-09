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
#include "hge.h"
#include "hgeanim.h"
#include<vector>
using namespace std;

#include "SnakePartList.h"

class SnakeContorsionList
{
public:
	SnakeContorsionList(SnakePartList* snakePartList);
	~SnakeContorsionList(void);

	enum E_Direction
	{
		LEFT=1,
		RIGHT,
		UP,
		DOWN
	};

	struct SnakeContorsion
	{
		int nStart,nEnd,nDirection;
		hgeVertex m_CornerPosition;
		int m_CornerMorphology;
	};

	enum CornerDirection
	{
		CORNER_RIGHT_DOWN,
		CORNER_RIGHT_UP,
		CORNER_LEFT_DOWN,
		CORNER_LEFT_UP
	};

	void Turn(E_Direction direction);
	void Update();

	void Grow( float surfaceWidth, float surfaceHeight, int& growCounter);

private:
	void MoveRight(int nIndex);
	void MoveLeft(int nIndex);
	void MoveUp(int nIndex); 
	void MoveDown(int nIndex);
	void EraseContorsion(void);

	void UpdateContorsionPart();
	void UpdateContorsion();
	
	bool IsRoomAvailable(int nSurfaceWidth, int nSurfaceHeight, hgeVertex& offsetPos);
	bool IsLastTailEven();

	void UpdateFrame(float fDeltaTime);
private:
	vector<SnakeContorsion>  mContorsion;
	SnakePartList* mpSnakePartList;
	E_Direction mCurrentDirection;
	void UpdatePosition();

	shared_ptr<hgeSprite> mCornerSpace;
	shared_ptr<hgeSprite> mCornerSprite;
public:
	void RenderCornerSpace();

private:
	int UpdateLastTailPosition(void);
	int GetContorsionNo(void);
	void RenderCorners( int index );
};

