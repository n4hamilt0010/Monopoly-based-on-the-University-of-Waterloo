#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <set>
#include <string>

class Observer;

class Subject{
	public: 
		void subscribe ( Observer * );
		void unsubscribe ( Observer * );

	protected: 
		void notify(const std::string & s);
	
	private: 
		std::set< Observer * > observers_;

};

#endif
