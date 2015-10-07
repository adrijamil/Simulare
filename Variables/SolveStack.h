#pragma once

#include "FSObject.h"
#include <iostream>


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

		if (_items != NULL) //if it's null then realloc tak jadi//means theres only one guy;
		{
			_items[_count - 1] = &(*item);
		}
	}

	
	bool Solve()
	{
		bool retval = false;
		int itemssolved=0;
		int i = 0;
		bool thisitemsolved;
		int solvepasses=0;
		int nitems = _count;


		std::cout << "stack is: " << "\n";
		for (int k = 0; k < _count; k++)//if i get to second last then must be the last one that needs to be removed;
		{
			std::cout << "item " << k << " is " << _items[k]->Name().c_str() << "\n";
		}

		while (_count>0)
		{

			std::cout << "solving " << _items[i]->Name().c_str() << "\n";
			thisitemsolved = _items[i]->Solve();
			if (thisitemsolved)
			{
				std::cout << "solved " << _items[i]->Name().c_str() << "\n";
				_remove(_items[i]);
				i--;
			}
			
			i++;

			if (i == _count)
			{
				solvepasses++;
				i = 0;
			}
			
			if (solvepasses == nitems * 5)// at most for n items you need n passes. add one for luck.
			{
				std::cout << "i've tried so hard but didnt get far";
				break;
			}
		}
		if (_count==0){ retval = true; }
		return retval;
	}

	//at some point figure out how to move stuff around the stack. Makes it that much faster.
	~SolveStack(){ delete[] _items; };
private:
	int _top;
	FSObject** _items;
	int _count = 0;
	int offset = 0;
	void _remove(FSObject* item)
	{
		FSObject** newitems;
		if (_count == 1)
		{
			_count = 0;
			_items = NULL;
			return;
		}
		newitems = (FSObject**)realloc(_items, (_count - 1)* sizeof(*item));
		for (int i = 0; i < _count; i++)//if i get to second last then must be the last one that needs to be removed;
		{
			if (_items[i] != item)
			{
				std::cout << "adding " << _items[i]->Name().c_str() << "\n";
				newitems[i+offset] = &(*_items[i]);
			}
			else
			{
				offset = -1;
				std::cout << "skipping " << _items[i]->Name().c_str() << "\n";
			}
		}
		_count--;
		_items = NULL;
		_items = (FSObject**)realloc(newitems, _count* sizeof(*item)); //allocate to existing array
		
		std::cout << "new stack is: " << "\n";
		for (int i = 0; i < _count ; i++)//if i get to second last then must be the last one that needs to be removed;
		{
			std::cout << "item " << i << " is " << _items[i]->Name().c_str() << "\n";
		}
	}

};

