#include "effective_c++/nest.h"

#include <iostream>

using std::cout;
using namespace effective;

int Nest::doHealthValue() const { return 2; }

void Nest::doDraw(int color) const {
  if (color == 2) {
    cout << "let paint the house as Blue";
  }
}

void Nest::onTick() const { cout << "My nest address is : " + address_; }
