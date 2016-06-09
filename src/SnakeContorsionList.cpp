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
#include "SnakeContorsionList.h"


SnakeContorsionList::SnakeContorsionList(SnakePartList* snakePartList):
mpSnakePartList(snakePartList),
mCornerSpace( GameTilesFactory::instance().CreateCornerSpace() )
{
	assert( 0 != mpSnakePartList);
	
	mCurrentDirection = RIGHT;
	
	mContorsion.clear();

	SnakeContorsion sc;
	sc.nDirection = RIGHT;
	sc.nStart= 0;
	sc.nEnd  = mpSnakePartList->GetSize(); 
	sc.m_CornerPosition = hgeVertex();
	sc.m_CornerMorphology = SnakePart::SNAKE_PART_HEAD_UP;

	mContorsion.push_back(sc);

}


SnakeContorsionList::~SnakeContorsionList(void)
{
}

void SnakeContorsionList::Turn(E_Direction direction)
{
	assert( 0 != mpSnakePartList);
	if(!mpSnakePartList->IsHeadEvenPosition())
	{
		return;
	}

	E_Direction opositeDirection;
	switch(direction)
	{
	case DOWN:
		opositeDirection = UP;
		TRACE("\n");
		break;
	case UP:
		opositeDirection = DOWN;
		TRACE("\n");
		break;
	case LEFT:
		opositeDirection = RIGHT;
		TRACE("\n");
		break;
	case RIGHT:
		opositeDirection = LEFT;
		TRACE("\n");
		break;
	}


	if (mCurrentDirection != direction && mCurrentDirection != opositeDirection)
	{
		mCurrentDirection = direction;
		SnakeContorsion sc;
		sc.nDirection = direction;
		sc.nStart    = mpSnakePartList->GetSize();
		sc.nEnd      = mpSnakePartList->GetSize();
		mContorsion.push_back(sc);
	}

}

void SnakeContorsionList::EraseContorsion(void)
{
	vector<SnakeContorsion>::iterator it;

	for (it = mContorsion.begin(); it != mContorsion.end(); )
		if ( (*it).nStart == 0 && (*it).nEnd == 0)
			it = mContorsion.erase(it);
		else
			++it;
}

void SnakeContorsionList::MoveRight(int nIndex)
{
	assert( 0 != mpSnakePartList);
	for(int ix = mContorsion[nIndex].nStart; ix < mContorsion[nIndex].nEnd; ix++)
	{
		mpSnakePartList->StepRight(ix);
	}
}
void SnakeContorsionList::MoveLeft(int nIndex)
{
	assert( 0 != mpSnakePartList);
	for(int ix=mContorsion[nIndex].nStart;ix<mContorsion[nIndex].nEnd;ix++)
	{
		mpSnakePartList->StepLeft(ix);
	}

}
void SnakeContorsionList::MoveUp(int nIndex)
{
	assert( 0 != mpSnakePartList);
	// move all figurine one step down
	for(int ix=mContorsion[nIndex].nStart;ix<mContorsion[nIndex].nEnd;ix++)
	{
		mpSnakePartList->StepUp(ix);
	}

}

void SnakeContorsionList::MoveDown(int nIndex)
{
	assert( 0 != mpSnakePartList);
	// move all part from a contortion one step down
	for(int ix = mContorsion[nIndex].nStart; ix < mContorsion[nIndex].nEnd; ix++)
	{
		mpSnakePartList->StepDown(ix);
	}
}

void SnakeContorsionList::UpdateContorsion()
	{
		int ContorsionNo =static_cast<int>(mContorsion.size());

		if(ContorsionNo <= 1)
		{
			return;
		}

		assert ( 0 != mpSnakePartList );
		if( mpSnakePartList->IsHeadEvenPosition())
		{ 
			UpdateContorsionPart();
			EraseContorsion();
		}
	}

void SnakeContorsionList::UpdateContorsionPart()
	{
		// first contorsion - tail
		if(mContorsion[0].nEnd > 0)
		{
			mContorsion[0].nEnd--;
		}

		//int ContorsionNo =static_cast<int>(m_Contorsion.size());
		int ContorsionNo = GetContorsionNo();

		// the remaining contortions without tail and head
		for (int i = 1 ;i < ContorsionNo -1; i++)
		{
			if((mContorsion[i].nStart > 0) && (mContorsion[i].nEnd > 0))
			{
				mContorsion[i].nStart--;
				mContorsion[i].nEnd--;
			}			   
		}

		// last contorsion - head;
		if(mContorsion[ContorsionNo -1].nStart>0)
		{
			mContorsion[ContorsionNo -1].nStart--;
		} 

		mContorsion[ContorsionNo -1].nEnd = mpSnakePartList->GetSize();
	}

void SnakeContorsionList::Update()
	{
		UpdateContorsion();
		UpdatePosition();
	}

void SnakeContorsionList::RenderCornerSpace()
{
	int ContorsionNo = static_cast<int>(mContorsion.size());

	//first contorsion has empty corner.
	if (ContorsionNo <= 1) {
		return;
	}

	// the remainign contorsions
	for (int i = 1; i < ContorsionNo; i++)
	{
		//display at second step until last step -1
		if ( mContorsion[i].nEnd != mContorsion[i].nStart && mContorsion[i].nStart != 1) {
			hgeVertex corner = mContorsion[i].m_CornerPosition;
			mCornerSpace->Render(corner.x, corner.y);
			RenderCorners(i);
		}
	}
}

bool SnakeContorsionList::IsLastTailEven()
{
	assert( 0 != mpSnakePartList);
	try 
	{
		if ( (mContorsion.at(0).nEnd == 1) && mpSnakePartList->IsTailEvenPosition() ) 
			return true;
	} 
	catch (out_of_range& e)
	{
		MessageBox(NULL, "IsLastTailEven - out of range", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

	return false;
}

void SnakeContorsionList::Grow( float surfaceWidth, float surfaceHeight, int& growCounter )
{
	assert( 0 != mpSnakePartList);
	if ( growCounter > 0)
	{
		if (mpSnakePartList->IsHeadEvenPosition())
		{
			hgeVertex offsetPos;
			if (IsRoomAvailable(surfaceWidth, surfaceHeight, offsetPos))
			{
				//grow - add offset pos
				mpSnakePartList->Grow(offsetPos);

				for (int nI = 0; nI < mContorsion.size(); nI++)
				{
					if (nI != 0)
					{
						mContorsion[nI].nStart++;
					}
					mContorsion[nI].nEnd++;
				}

				growCounter--;
			}
		}
	}
}

bool SnakeContorsionList::IsRoomAvailable(int nSurfaceWidth, int nSurfaceHeight, hgeVertex& offsetPos)
{
	if (IsLastTailEven())
	{
		return false;
	}
	assert ( 0 != mpSnakePartList);
	hgeVertex pos = mpSnakePartList->GetTailPosition();

	bool bRes = false;
	switch(mContorsion[0].nDirection)
	{
	case RIGHT:
		if (pos.x != 0)
		{
			offsetPos.x = - 16;
			offsetPos.y = 0;
			bRes = true;
		}
		break;
	case LEFT:
		if (pos.x != nSurfaceWidth - 16)
		{
			offsetPos.x = 16;
			offsetPos.y = 0;
			bRes = true;
		}
		break;
	case UP:
		if (pos.y != nSurfaceHeight - 16)
		{
			offsetPos.x = 0;
			offsetPos.y = 16;
			bRes = true;
		}
		break;
	case DOWN:
		if (pos.y != 0)
		{
			offsetPos.x = 0;
			offsetPos.y = -16;
			bRes = true;
		}
		break;
	}

	return bRes;
}


void SnakeContorsionList::UpdatePosition()
{
	//update position
	int ContorsionNo = static_cast<int>(mContorsion.size());

	int skipTail = UpdateLastTailPosition();
    //int skipTail = 0;

	for (int i = skipTail; i < ContorsionNo; i++)
	{
		switch (mContorsion[i].nDirection)
		{
		case RIGHT:
			MoveRight(i);
			break;
		case LEFT:
			MoveLeft(i);
			break;
		case UP:
			MoveUp(i);
			break;
		case DOWN:
			MoveDown(i);
			break;
		}
	}
}

int SnakeContorsionList::UpdateLastTailPosition(void)
{
	int skipTail = 0;
	//last step will be wrong rotated in this case
	// the check for ContorsionNo <= 1 done elswere
	if ( 1 == mContorsion[0].nEnd)
	{
		switch (mContorsion[0].nDirection)
		{
		case RIGHT:
			MoveRight(0);
			break;
		case LEFT:
			MoveLeft(0);
			break;
		case UP:
			MoveUp(0);
			break;
		case DOWN:
			MoveDown(0);
			break;
		}

		switch (mContorsion[1].nDirection)
		{
		case RIGHT:
			mpSnakePartList->RotateRight(0);
			break;
		case LEFT:
			mpSnakePartList->RotateLeft(0);
			break;
		case UP:
			mpSnakePartList->RotateUp(0);
			break;
		case DOWN:
			mpSnakePartList->RotateDown(0);
			break;
		}
		skipTail = 1;
	}
	return skipTail;
}

int SnakeContorsionList::GetContorsionNo(void)
{
	int contorsionNo = static_cast<int>(mContorsion.size());
	int sizePart =  mpSnakePartList->GetSize();
	
	int actualContorsionNo = 0;
	for (int i = 0 ;i < contorsionNo; i++)
	{
		if( (mContorsion[i].nStart != sizePart) || (mContorsion[i].nEnd != sizePart) ) {
            actualContorsionNo++;
		}
	}

	if (actualContorsionNo != contorsionNo) {
		mContorsion[actualContorsionNo].m_CornerPosition = mpSnakePartList->GetHeadPosition();
		mContorsion[actualContorsionNo].m_CornerMorphology = mpSnakePartList->GetHeadMorphology();
		actualContorsionNo++;// +1 is a head contortion that is start=end=sizepart
	}

	return actualContorsionNo;
}

void SnakeContorsionList::RenderCorners( int index )
{
	assert(0 != mpSnakePartList);

	hgeVertex corner = mContorsion[index].m_CornerPosition;
	int direction1 = mContorsion[index-1].nDirection;
	int direction2 = mContorsion[index].nDirection;

	hgeVertex offset = mpSnakePartList->GetOriginOffset();

	int cornerMorphology =  mContorsion[index].m_CornerMorphology;
	if( cornerMorphology == SnakePart::SNAKE_PART_HEAD_UP) {
		mCornerSprite = 
			GameTilesFactory::instance().GetSpriteTile(GameTilesFactory::TILE_CORNER_DOWN);
	} else 	if( cornerMorphology == SnakePart::SNAKE_PART_HEAD_DOWN) {
		mCornerSprite = 
			GameTilesFactory::instance().GetSpriteTile(GameTilesFactory::TILE_CORNER_UP);
	}
	assert(0 != mCornerSprite);

	mCornerSprite->SetHotSpot(2,2);
 	mCornerSprite->SetFlip(false, false);   
	
	switch (direction1)
	{
	case RIGHT:
		if (direction2 == UP)
		{
			mCornerSprite->SetFlip(false, true);
			mCornerSprite->Render(corner.x, corner.y);

		} else if (direction2 == DOWN) {
			mCornerSprite->Render(corner.x, corner.y);
		}
		break;
	case LEFT:
		if (direction2 == UP)
		{
			mCornerSprite->SetFlip(true, true);
			mCornerSprite->Render(corner.x, corner.y);

		} else if (direction2 == DOWN) {
			mCornerSprite->SetFlip(true, false);
			mCornerSprite->Render(corner.x, corner.y);
		}
		break;
	case UP:
		if (direction2 == RIGHT)
		{
			mCornerSprite->SetHotSpot(mCornerSprite->GetWidth()/2, mCornerSprite->GetHeight()/2);
			mCornerSprite->RenderEx(corner.x + offset.x, corner.y + offset.y, -M_PI_2);

		} else if (direction2 == LEFT) {
			mCornerSprite->SetFlip(true, false);
			mCornerSprite->SetHotSpot(mCornerSprite->GetWidth()/2, mCornerSprite->GetHeight()/2);
			mCornerSprite->RenderEx(corner.x+ offset.x, corner.y + offset.y, M_PI_2);
		}
		break;
	case DOWN:
		if (direction2 == RIGHT)
		{
			mCornerSprite->SetFlip(false, true);
			mCornerSprite->SetHotSpot(mCornerSprite->GetWidth()/2, mCornerSprite->GetHeight()/2);
			mCornerSprite->RenderEx(corner.x + offset.x, corner.y + offset.y, M_PI_2);
		} else if (direction2 == LEFT) {
			mCornerSprite->SetFlip(true, true);
			mCornerSprite->SetHotSpot(mCornerSprite->GetWidth()/2, mCornerSprite->GetHeight()/2);
			mCornerSprite->RenderEx(corner.x + offset.x, corner.y + offset.y, -M_PI_2);
		}
		break;
	}
}
