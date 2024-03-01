#include "effective_c++/nest.h"

using namespace effective;

std::string Nest::doHealthValue() const { return "check health of full Nest"; }

std::string Nest::doDraw(int color) const {
  if (color == 2) {
    return "let paint the house as Blue";
  }
  return "bad color, can not paint.";
}

std::string Nest::onTick() const { return "My nest address is : " + address_; }
