#include "effective_c++/home.h"

//> 不要导入整个命名空间std，因为会有符号名冲突。导入具体的符号可以将冲突范围最小化。
using std::string;
using namespace effective;

Home::Home(string address) : Clock(1), address_(address) {}

Home::~Home() {}

string Home::healthValue() const {
  string before = "before ";
  string record = doHealthValue();
  string after = " after.";
  return before + record + after;
}

string Home::draw(int color) const { return doDraw(color); }

string Home::boardcastAddress() const { return tick(); }

string Home::doHealthValue() const { return "check health of full house"; }

string Home::doDraw(int color) const {
  if (color == 1) {
    return "let paint the house as Red";
  }
  return "bad color, can not paint.";
}

string Home::onTick() const { return "My home address is : " + address_; }

string Home::tick() const {
  string result = "This from home begin send address ";
  result += Clock::tick();
  return result;
}
