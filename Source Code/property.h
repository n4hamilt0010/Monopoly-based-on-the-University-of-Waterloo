#ifndef __PROPERTY_H__
#define __PROPERTY_H__
#include <string>
#include <vector>

#include "square.h"

class Property: public Square {
    std::string owner; //if empty string, then belongs to bank
    int purchaseCost;
    std::string monopoly; //name of the monopoly block
    int improvementCount;
    std::vector<int> monopolyBlock; //indexes of the all squares in the monopoly block

    public:
        Property(std::string name, std::string owner, int purchaseCost, std::string monopoly, int improvementCount);
        ~Property();
        //accessors
        std::string getOwner() override;
        int getPurchaseCost() override;
        std::string getMonopoly();
        std::vector<int> getMonopolyBlock() override;
        int getImprovementCount() override;
	int getImprovementCost() override;
        //mutators
        void setOwner(std::string i) override;
        void setImprovementCount(int i);
        //other
        bool property() override;
	virtual bool isAcademic() = 0;
};

#endif
