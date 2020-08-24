#include "subject.h"
#include "observer.h"

void Subject::subscribe(Observer *newView){
	observers_.insert( newView );
}

void Subject::unsubscribe(Observer *formerView){
	observers_.erase(formerView);
}

void Subject::notify(const std::string & s){
	for(auto i: observers_){
		i->update(s);
	}	
}

