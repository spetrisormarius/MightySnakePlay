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
#include "SnakePartList.h"
#include "GameTilesFactory.h"
#include "InputParameters.h"
#include <cmath>
#include <sstream>
using namespace std;

SnakePartList::SnakePartList(HGE* engine)
{
	mOriginOffset.x = 8;
	mOriginOffset.y = 8;

	mSnakePartWidth = GameTilesFactory::instance().GetSnakePartWidth();
	mSnakePartHeight = GameTilesFactory::instance().GetSnakePartHeight();

	mSurfaceWidth = 0;
	mSurfaceHeight = 0;
	mIsHit = false;
}

SnakePartList::~SnakePartList(void)
{

}

hgeVertex SnakePartList::GetHeadPosition()
{
	if (mSnakeActor.empty())
	{
		throw std::bad_exception();
	}
	hgeVertex res;
	res.x = mSnakeActor.back().x - abs(mOriginOffset.x);
	res.y = mSnakeActor.back().y - abs(mOriginOffset.y);
	return res;
}

bool SnakePartList::IntersectHead(const hgeRect& boundingBox)
{
	if (mSnakeActor.empty() )
	{
		return false;
	}

	return mSnakeActor.back().IntersectRect(boundingBox);
}


bool SnakePartList::Intersect(const hgeRect& boundingBox)
{
	bool bRes = FALSE;
	
	for (vector<SnakePart>::size_type nI = 0; nI < mSnakeActor.size(); nI++)
	{
		bRes |= mSnakeActor[nI].IntersectRect(boundingBox);
	}

	return bRes;
}

void SnakePartList::Grow(const hgeVertex& offsetPos)
{
	SnakePart& tail = mSnakeActor.front();

	SnakePart snakePart;
	snakePart.x = tail.x;
	snakePart.y = tail.y;
	snakePart.dx = tail.dx;
	snakePart.dy = tail.dy;

	snakePart.rot = tail.rot;
	snakePart.rot = tail.rot;

	//take the tail, copy to new element and set his style
	//tail is inverse
	if (tail.GetMorphology() == SnakePart::SNAKE_PART_TAIL_DOWN)
	{
		snakePart.SetMorphology(SnakePart::SNAKE_PART_BODY_DOWN);
		tail.SetMorphology(SnakePart::SNAKE_PART_TAIL_UP);
	}
	else if (tail.GetMorphology() == SnakePart::SNAKE_PART_TAIL_UP)
	{
		snakePart.SetMorphology(SnakePart::SNAKE_PART_BODY_UP);
		tail.SetMorphology(SnakePart::SNAKE_PART_TAIL_DOWN);
	}

	tail.x = tail.x + offsetPos.x;
	tail.y = tail.y + offsetPos.y;

    mSnakeActor.insert(mSnakeActor.begin() + 1, snakePart);
	
	//is necesary to resyncronize all the sprites.
	for (vector<SnakePart>::size_type indexSnake=0; indexSnake < mSnakeActor.size(); indexSnake++) {
		mSnakeActor[indexSnake].InitSkin();
	}
}


void SnakePartList::StepRight(int ix)
{
	float xPos=mSnakeActor[ix].x;
	xPos+=mSnakeActor[ix].dx;

	mIsHit = IsSelfHit();
	if (!mIsHit)
	{
		if (IsBorder( xPos, mSnakeActor[ix].y ))
		{
			mSnakeActor[ix].x= 0 + mOriginOffset.x;
			RotateRight(ix);
		} else {
			mSnakeActor[ix].x=xPos;
			RotateRight(ix);
		}
	}
	

	tracePosition("r.x", ix);
}

void SnakePartList::StepLeft(int ix)
{
	float xPos=mSnakeActor[ix].x;
	xPos-=mSnakeActor[ix].dx;
	
	mIsHit = IsSelfHit();
	if (!mIsHit)
	{
		if (IsBorder( xPos, mSnakeActor[ix].y ))
		{
			mSnakeActor[ix].x= mSurfaceWidth - mOriginOffset.x;
			RotateLeft(ix);
		} else {
			mSnakeActor[ix].x=xPos;
			RotateLeft(ix);
		}
	}
	tracePosition("l.x", ix);

}

void SnakePartList::StepUp(int ix)
{
	float yPos=mSnakeActor[ix].y; 
	yPos-=mSnakeActor[ix].dy;
	mIsHit = IsSelfHit();
	if (!mIsHit)
	{
		if (IsBorder(mSnakeActor[ix].x, yPos))
		{
			mSnakeActor[ix].y = mSurfaceHeight - mOriginOffset.y;
			RotateUp(ix);
		} else {
			mSnakeActor[ix].y=yPos;
			RotateUp(ix);
		}
	}
	tracePosition("u.y", ix);
}


void SnakePartList::StepDown(int ix)
{
	float yPos=mSnakeActor[ix].y; 
	yPos+=mSnakeActor[ix].dy;
	mIsHit = IsSelfHit();
	if (!mIsHit)
	{
		if (IsBorder(mSnakeActor[ix].x, yPos ))
		{
			mSnakeActor[ix].y = 0 +  mOriginOffset.y;
			RotateDown(ix);
		} else {
			mSnakeActor[ix].y=yPos;
			RotateDown(ix);
		}

	}
	tracePosition("d.y", ix);

}

bool SnakePartList::IsSelfHit()
{
	if (mSnakeActor.size() <= 3)
	{
		return FALSE;
	}

	SnakePart snakePart = mSnakeActor.back();
	hgeRect headRect = snakePart.GetBoundingBox();

	headRect.x1 += 2;
	headRect.y1 += 2;
	headRect.x2 -= 2;
	headRect.y2 -= 2;

	bool bRes = FALSE;

	for (vector<SnakePart>::size_type nI = 0; nI < mSnakeActor.size() - 3; nI++)
	{
		bRes |= mSnakeActor[nI].IntersectRect(headRect);
	}

	return bRes;

}

hgeVertex SnakePartList::GetTailPosition()
{
	if (mSnakeActor.empty())
	{
		throw std::bad_exception();
	}
	hgeVertex res;
	//idea: the pos can be retrieved with getboundingbox- etc
	res.x = mSnakeActor.front().x - abs(mOriginOffset.x);
	res.y = mSnakeActor.front().y - abs(mOriginOffset.y);
	return res;
}

void SnakePartList::Create()
{
	hgeVertex snakeFramePos;
	if (InputParameters::Instance().IsDebugAnimation())
	{
		snakeFramePos.x = mOriginOffset.x;
		snakeFramePos.y = mOriginOffset.y;
	} 
	else
	{
		snakeFramePos.x = 	mSurfaceWidth / 2 + mOriginOffset.x;
		snakeFramePos.y = 	mSurfaceHeight /2 + mOriginOffset.y;
	}

	mSnakeActor.clear();

	// Load the player
	for(int snakePartCnt = 0; snakePartCnt < 3; snakePartCnt++)
	{
		SnakePart snakePart;

		if(snakePartCnt == 0)
		{
			snakePart.SetMorphology( SnakePart::SNAKE_PART_TAIL_UP);	//tail up
		} else
		{
			if(snakePartCnt == 2)
			{
				snakePart.SetMorphology( SnakePart::SNAKE_PART_HEAD_UP);	//head up
			}else
			{
				if( snakePartCnt %2 == 1)
				{
					snakePart.SetMorphology(SnakePart::SNAKE_PART_BODY_DOWN);
				}
				else
				{
					snakePart.SetMorphology(SnakePart::SNAKE_PART_BODY_UP);
				}
			}
		}

		snakePart.x = snakeFramePos.x;
		snakePart.y =  snakeFramePos.y;

		//snakePart.dx = 4;
		//snakePart.dy = 4;
		//snakePart.dx = 1.0f;
		//snakePart.dy = 1.0f;
		snakePart.dx = mSnakePartWidth;
		snakePart.dy = mSnakePartWidth;

		snakePart.rot = 0;

		mSnakeActor.push_back(snakePart);

		snakeFramePos.x += mSnakePartWidth;
	}

	InitSnakeSkin();
}

void SnakePartList::Destroy()
{

}

bool SnakePartList::IsHeadEvenPosition()
{
	hgeVertex r = GetHeadPosition();
	return IsEvenPosition(r);
}

bool SnakePartList::IsEvenPosition(const hgeVertex& r)
{
	if ( ( fmod(r.x, mSnakePartWidth) == 0) && (fmod(r.y, mSnakePartHeight) == 0))
	{
		return true;
	}
	return false;
}

bool SnakePartList::IsTailEvenPosition()
{
	hgeVertex r = GetTailPosition();

	return IsEvenPosition(r);
}

int SnakePartList::GetSize()
{
	return mSnakeActor.size();
}

//game logic: update position, get input
void SnakePartList::UpdateFrame(float fDeltaTime) 
{
	for (vector<SnakePart>::size_type i = 0; i < mSnakeActor.size(); i++)
	{
		mSnakeActor[i].UpdateFrame();
	}
}

// draw
void SnakePartList::Render()
{
	for (vector<SnakePart>::size_type i = 0; i < mSnakeActor.size(); i++)
	{
		mSnakeActor[i].Render();
	}
}

void SnakePartList::InitSnakeSkin()
{
	for (vector<SnakePart>::size_type i = 0; i < mSnakeActor.size(); i++)
	{
		mSnakeActor[i].InitSkin();
	}
}

bool SnakePartList::IsBorder()
{
	hgeVertex r = GetHeadPosition();

	float nx = mSurfaceWidth  - mSnakePartWidth; // last position for border x
	float ny = mSurfaceHeight - mSnakePartHeight; // last position for border y

	if( (r.x >= nx + 1.0f ) || (r.y >= ny + 1.0f ) || r.x <= -1.0f || r.y <= -1.0f)
		return true;  

	return false;
};

void SnakePartList::tracePosition(const string& text, int ix)
{
#ifdef _DEBUG
	std::ostringstream stringStream;
	stringStream << text << "(" << mSnakeActor[ix].GetMorphology() << ")" << "=" << "(" << mSnakeActor[ix].x << "," << mSnakeActor[ix].y <<  ")" <<",";
	std::string copyOfStr = stringStream.str();
	OutputDebugString(copyOfStr.c_str());
#endif

}

void SnakePartList::RotateLeft(int ix)
{
	mSnakeActor[ix].rot = M_PI;
}

void SnakePartList::RotateRight(int ix)
{
	mSnakeActor[ix].rot = 0;
}

void SnakePartList::RotateUp(int ix)
{
	mSnakeActor[ix].rot = -M_PI_2;
}

void  SnakePartList::RotateDown(int ix)
{
	mSnakeActor[ix].rot = M_PI_2;
	//m_SnakeActor[ix].rot = 3 * M_PI /2;
}

bool SnakePartList::CheckHit()
{
	if ( IsBorder() )
		return true;

	if ( IsSelfHit() )
		return true;

	return false;
}

void SnakePartList::SetSurfaceDimension( float nSurfaceWidth, float nSurfaceHeight )
{
	mSurfaceWidth = nSurfaceWidth;
	mSurfaceHeight = nSurfaceHeight;
}


bool SnakePartList::IsBorder(float x, float y)
{
	x-= mOriginOffset.x;
	y-= mOriginOffset.y;

	float nx = mSurfaceWidth  - mSnakePartWidth; // last position for border x
	float ny = mSurfaceHeight - mSnakePartHeight; // last position for border y

	if( (x >= nx + 1.0f ) || (y >= ny + 1.0f ) || x <= -1.0f || y <= -1.0f)
		return true;  

	return false;
}

int SnakePartList::GetHeadMorphology()
{
	if (mSnakeActor.empty())
	{
		throw std::bad_exception();
	}

	return 	mSnakeActor.back().GetMorphology();;
}

hgeVertex SnakePartList::GetOriginOffset(void)
{
	return mOriginOffset;
}
