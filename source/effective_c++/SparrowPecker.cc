#include "effective_c++/SparrowPecker.h"

#include <iostream>

#include "effective_c++/Sparrow.h"
#include "effective_c++/Woodpecker.h"

using std::cout;
using namespace effective;

SparrowPecker::SparrowPecker() : Sparrow(), Woodpecker(){};
SparrowPecker::~SparrowPecker(){};
void SparrowPecker::Fly() { cout << "This is a new fly of sparrowpecker"; };