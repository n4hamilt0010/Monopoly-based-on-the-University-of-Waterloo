#include "nonacademic.h"

NonAcademic::NonAcademic(std::string name, std::string owner, int purchaseCost, std::string monopoly, int improvementCount = 0) :
    Property{name, owner, purchaseCost, monopoly, improvementCount} { }

NonAcademic::~NonAcademic() { }

int NonAcademic::getTuition(){
	int dummyRetval = -1;
	return dummyRetval;
}

bool NonAcademic::isAcademic(){ return false; }

