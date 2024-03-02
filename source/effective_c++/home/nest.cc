#include "effective_c++/home/nest.h"

using namespace effective;
using std::string;

Nest::Nest(string address) : Home(address) {}

string Nest::doHealthValue() const { return "check health of full Nest"; }

string Nest::doDraw(int color) const {
  if (color == 2) {
    return "let paint the house as Blue";
  }
  return "bad color, can not paint.";
}

string Nest::onTick() const { return "My nest address is : " + address_; }
