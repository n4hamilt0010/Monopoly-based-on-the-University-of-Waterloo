#ifndef __ACADEMIC_H__
#define __ACADEMIC_H__
#include <string>
#include <vector>

#include "property.h"

class Academic: public Property{
    int improvementCost; //cost of a single improvement
    std::vector <int> tuition; //stores the tuition costs associated with each improvement, tuiton[0]=tuition with none

    public:
        Academic(std::string name, std::string owner, int purchaseCost, std::string monopoly,
                int improvementCost, int t0, int t1, int t2, int t3, int t4, int t5, int improvementCount);
        ~Academic();

        //accessors
        int getImprovementCost() override;
        int getTuition() override;
	bool isAcademic() override;
};

#endif
