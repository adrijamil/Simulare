#ifndef __FSOBJECT_H_INCLUDED__
#define __FSOBJECT_H_INCLUDED__
using namespace std;
class FSObject
{
public:
	 FSObject();
	~FSObject();
private:
	string _name;
	int* _interface; //link this to some kinda interface object

};

#endif
