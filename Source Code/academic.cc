#include "academic.h"

Academic::Academic(std::string name, std::string owner, int purchaseCost, std::string monopoly, int improvementCost, int t0, int t1, int t2, int t3, int t4, int t5, int improvementCount = 0) :
    Property{name, owner, purchaseCost, monopoly, improvementCount}, 
    improvementCost{improvementCost} {

        tuition.emplace_back(t0);
        tuition.emplace_back(t1);
        tuition.emplace_back(t2);
        tuition.emplace_back(t3);
        tuition.emplace_back(t4);
        tuition.emplace_back(t5);
    }

Academic::~Academic() { }

int Academic::getImprovementCost() { return improvementCost; }

int Academic::getTuition() { return tuition[getImprovementCount()]; }

bool Academic::isAcademic(){ return true; }
