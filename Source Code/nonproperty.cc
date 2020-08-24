#include "nonproperty.h"

int DONT_RETURN  = -1; // return value for functions that will not be used in program


NonProperty::NonProperty(std::string name) : Square{name} { }

NonProperty::~NonProperty() { }

bool NonProperty::property() { return false; } //is not a property 

int NonProperty::getImprovementCost() {return DONT_RETURN;}

int NonProperty::getImprovementCount(){ return DONT_RETURN; }
	
std::string NonProperty::getOwner(){ return "Dummy return variable"; }
	
void NonProperty::setOwner(std::string s){}
	
int NonProperty::getTuition(){ return DONT_RETURN; }
	
int NonProperty::getPurchaseCost(){ return DONT_RETURN;}

void NonProperty::setImprovementCount(int i) { }

std::vector<int> NonProperty::getMonopolyBlock() { 
std::vector<int> dontReturn;
return dontReturn;
}

bool NonProperty::isAcademic(){
	const bool DONT_RETURN = false;
	return DONT_RETURN;
}
