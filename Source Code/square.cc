#include "square.h"

Square::Square(std::string name) : name{name} { }

Square::~Square() { }

std::string Square::getName() { return name; }
