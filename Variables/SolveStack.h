#pragma once

#include "FSObject.h"


//class FSObject;

class SolveStack
{
public:
	SolveStack()
	{
		_top = -1;
	};
	void Add(FSObject* item)
	{
		_count++;

		//_items = new FSObject[_count];

		//realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
		//should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.
		//is this safe? sizeof items may be different cos some are streams some are unit ops. 

		_items = (FSObject**)realloc(_items, _count* sizeof(*item)); //allocate new array

		if (_items != NULL) //if it's null then realloc tak jadi
		{
			_items[_count - 1] = &(*item);
		}
	}
	bool Solve()
	{
		bool retval;
		int itemssolved=0;
		int i = _count-1;
		bool thisitemsolved;
		int solvepasses=0;

		while (itemssolved != _count)
		{
			thisitemsolved = _items[i]->Solve();
			if (thisitemsolved)
			{
				itemssolved++;
			}

			i = i - 1;
			if (i == -1)
			{
				i = _count-1;
				solvepasses++;
			}
			if (solvepasses == _count+1)// at most for n items you need n passes. add one for luck.
			{
				break;
			}
		}
		return true;
	}

	//at some point figure out how to move stuff around the stack. Makes it that much faster.
	~SolveStack(){ delete[] _items; };
private:
	int _top;
	FSObject** _items;
	int _count = 0;

};

