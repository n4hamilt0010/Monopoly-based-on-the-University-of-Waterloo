#include "property.h"

Property::Property(std::string name, std::string owner, int purchaseCost, std::string monopoly, 
		int improvementCount = 0) : Square{name},  owner{owner}, purchaseCost{purchaseCost}, 
	monopoly{monopoly}, improvementCount{improvementCount}  { 

        //monopolyBlock stores the positions of all indexes of the monopoly blocks

        if (monopoly == "GYM") {
            monopolyBlock.emplace_back(12); //PAC
            monopolyBlock.emplace_back(28); //CIF
        } else if (monopoly == "RES") {
            monopolyBlock.emplace_back(5); //MKV
            monopolyBlock.emplace_back(15); //UWP
            monopolyBlock.emplace_back(25); //V1
            monopolyBlock.emplace_back(35); //REV
        } else if (monopoly == "Arts1") {
            monopolyBlock.emplace_back(1); //AL
            monopolyBlock.emplace_back(3); //ML
        } else if (monopoly == "Arts2") {
            monopolyBlock.emplace_back(6); //ECH
            monopolyBlock.emplace_back(8); //PAS
            monopolyBlock.emplace_back(9); //HH
        } else if (monopoly == "Eng") {
            monopolyBlock.emplace_back(11); //RCH
            monopolyBlock.emplace_back(13); //DWE
            monopolyBlock.emplace_back(14); //CPH
        } else if (monopoly == "Health") {
            monopolyBlock.emplace_back(16); //LHI
            monopolyBlock.emplace_back(18); //BMH
            monopolyBlock.emplace_back(19); //OPT
        } else if (monopoly == "Env") {
            monopolyBlock.emplace_back(21); //EV1
            monopolyBlock.emplace_back(23); //EV2
            monopolyBlock.emplace_back(24); //EV3
        } else if (monopoly == "Sci1") {
            monopolyBlock.emplace_back(26); //PHYS
            monopolyBlock.emplace_back(27); //B1
            monopolyBlock.emplace_back(29); //B2
        } else if (monopoly == "Sci2") {
            monopolyBlock.emplace_back(31); //EIT
            monopolyBlock.emplace_back(32); //ESC
            monopolyBlock.emplace_back(34); //C2
        } else if (monopoly == "Math") {
            monopolyBlock.emplace_back(37); //MC
            monopolyBlock.emplace_back(39); //DC
        }
    }

Property::~Property() { }

std::string Property::getOwner() { return owner; }

int Property::getPurchaseCost() { return purchaseCost; }

std::string Property::getMonopoly() { return monopoly; }

int Property::getImprovementCost() {return -1; }

std::vector<int> Property::getMonopolyBlock() { return monopolyBlock; }

int Property::getImprovementCount() { return improvementCount; }

void Property::setOwner(std::string i) { owner = i; }

//int Property::getPurchaseCost() {return purchaseCost;}

void Property::setImprovementCount(int i) {
    if (i <= 5 && i >= -1) {
        improvementCount = i;
    }
}

bool Property::property() { return true; } //return true because it's a property
