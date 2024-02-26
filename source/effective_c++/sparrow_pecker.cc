#include "effective_c++/sparrow_pecker.h"

#include <iostream>

#include "effective_c++/sparrow.h"
#include "effective_c++/wood_pecker.h"

using std::cout;
using namespace effective;

SparrowPecker::SparrowPecker() : Sparrow(), Woodpecker(){};
SparrowPecker::~SparrowPecker(){};
void SparrowPecker::Fly() { cout << "This is a new fly of sparrowpecker"; };