#include "effective_c++/home/house.h"

using std::string;
using namespace effective;

std::shared_ptr<House> House::create(std::string address) {
  return std::shared_ptr<House>(new House(address));
}

void House::registerHouse() { registered_houses_.emplace_back(shared_from_this()); }

House::House(string address) : Home(address) {}

string House::doHealthValue() const { return "check health of full House"; }

string House::doDraw(int color) const {
  if (color == 5) {
    return "let paint the house as Green";
  }
  return "bad color, can not paint.";
}

string House::onTick() const { return "My House address is : " + address_; }
