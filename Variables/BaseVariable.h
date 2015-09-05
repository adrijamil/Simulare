// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	2/9/15
// PURPOSE     :	This is a parent class for the RealVariable, BoolVariable etc classes. 
//					Basically it is just a container with a reference to variables
//					Variables can be a single number(pressure) or an array(composition)
//					Also contains size of the array.
//					May need to use std array but not needed so far
// SPECIAL NOTES:	HYSYS uses RealFlexVariable for arrays. Why this is (aside from convenience) remains to be seen.
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================


#ifndef __BASEVARIABLE_H_INCLUDED__
#define __BASEVARIABLE_H_INCLUDED__
using namespace std;

template <class T>
class BaseVariable
{
public:
	//Default constructor. Create a new block. This may not need to happen till later as Variables should not exist in the wild.
	BaseVariable(){ _value = new T; }

	//Constructor when value is known. By default a new block is created every time. But _value can also be made to point to another block in another 
	//instance of this class. ie two Variable objects pointing to same value. This is so Stream and Phase can share 1 block for pressure.
	BaseVariable(T theValue)  // this is constructor with single element
	{
		_value = new T;
		*_value = theValue;
	}

	//constructor when value is and array and known.
	// template class is used to get size of array if it is
	template <class T, size_t N > 
	BaseVariable(T const (&thevalue)[N]) //this is constructor for array
	{
		SetValue(thevalue);
	}

	//default destructor
	//TO BE IMPLEMENTED
	~BaseVariable(){};

	//Get size of array
	int Size(){ 
		return _size;
	}

	//Setting the value by passing an array
	template <class T, size_t N >
	void SetValue(T const (&thevalue)[N])
	{
		if (!(N==(sizeof(_value) / sizeof(*_value)))) //if my array is a different size then redim it. 
		{
			_size = N;
			_value = new T[N];
		}
		

		for (int i = 0;i< N ; i++)
		{
			_value[i] = thevalue[i];
		}
	}


	//setting a value for a single element
	void SetValue(T thevalue){ *_value = thevalue; }; //setval single element

	void SetValue(int i, T thevalue){ _value[i] = thevalue; }

	T* GetValues(){ return  _value; };  // to get an array
	T GetValue(){ return *_value; };// to get the single value //otherwise gotta treat element as array of 1. this is not nice.
	T GetValue(int i)
	{
		T theElement;
		theElement = _value[i];
		return theElement;
	};
protected:
	T* _value; //pointer to value
	int _size=1;//size of array. by default its 1
};


#endif // !__BASEVARIABLE_H__
