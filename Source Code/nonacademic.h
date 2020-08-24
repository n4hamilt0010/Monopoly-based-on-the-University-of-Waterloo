#ifndef __NONACADEMIC_H__
#define __NONACADEMIC_H__
#include <string>

#include "property.h"

class NonAcademic: public Property {
    public:
        NonAcademic(std::string name, std::string monopoly, int purchaseCost, std::string ownership, int improvementCount);
        ~NonAcademic();
	int getTuition() override;
	bool isAcademic() override;
};

#endif
