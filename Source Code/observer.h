#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>

class Subject;

class Observer{
	public: 
		virtual void update(const std::string & s) = 0;
};

#endif
