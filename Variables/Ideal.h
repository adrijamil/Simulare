#ifndef __IDEAL_H__
#define __IDEAL_H__

#include "FlashMethod.h"
#include "Stream.h"

using namespace std;

class Ideal :
	public FlashMethod
{
public:
	Ideal(){ _name = "ideal"; };
	~Ideal();
	
	void PT_Flash(Stream* theStream, PropPack* thePP);
	//{
	//	cout << "im flashing" <<thestream->Name() << "overrided by"<<_name;
	//};// i need P, T and x. Output H, vf and a bunch of props.
private:
	double* _Ki;
	double _RR(double vfrac,double* comps, int NComp);
};

#endif
