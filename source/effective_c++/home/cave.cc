#include "effective_c++/home/cave.h"

using std::string;
using namespace effective;

Cave::Cave(string address) : Home(address) {}

string Cave::doHealthValue() const { return "check health of full Cave"; }

string Cave::doDraw(int color) const {
  if (color == 3) {
    return "let paint the house as Brown";
  }
  return "bad color, can not paint.";
}

string Cave::onTick() const { return "My cave address is : " + address_; }
