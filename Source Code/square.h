#ifndef __SQUARE_H__
#define __SQUARE_H__
#include <string>
#include <vector>
class Square {
    std::string name; //name of each building square
    public:
        Square(std::string name);
        ~Square();
        std::string getName();
        virtual bool property() = 0;
	virtual int getImprovementCount() = 0;
	virtual int getImprovementCost() = 0;
	virtual void setImprovementCount(int i) = 0;
	virtual std::string getOwner() = 0;
	virtual std::vector<int> getMonopolyBlock() = 0;
	virtual void setOwner(std::string s) = 0;
	virtual int getTuition() = 0;
	virtual int getPurchaseCost() = 0;
	virtual bool isAcademic() = 0;
};

#endif
