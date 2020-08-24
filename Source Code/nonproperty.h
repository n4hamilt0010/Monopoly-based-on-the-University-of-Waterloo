#ifndef __NONPROPERTY_H__
#define __NONPROPERTY_H__
#include <string>

#include "square.h"

class NonProperty: public Square {
    public:
        NonProperty(std::string name);
        ~NonProperty();
        bool property() override;
	int getImprovementCost() override;
	int getImprovementCount() override;
	void setImprovementCount(int i) override;
	std::string getOwner() override;
	void setOwner(std::string s) override;
	int getTuition() override;
	std::vector<int> getMonopolyBlock() override;
	int getPurchaseCost() override;
	bool isAcademic() override;

};

#endif
