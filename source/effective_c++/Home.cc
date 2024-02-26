#include "effective_c++/home.h"

#include <iostream>

//> 不要导入整个命名空间std，因为会有符号名冲突。导入具体的符号可以将冲突范围最小化。
using std::cout;
using std::string;
using namespace effective;

Home::Home(string address) : Clock(1), address_(address) {}

Home::~Home() {}

int Home::healthValue() const {
  cout << "do something before doHealthValue().";
  int retVal = doHealthValue();
  cout << "do something after doHealthValue().";
  return retVal;
}

void Home::draw(int color) const { doDraw(color); }

void Home::boardcastAddress() const { tick(); }

int Home::doHealthValue() const { return 1; }

void Home::doDraw(int color) const {
  if (color == 1) {
    cout << "let paint the house as Red";
  }
}

void Home::onTick() const { cout << "My home address is : " + address_; }

void Home::tick() const {
  cout << "This from home";
  Clock::tick();
}
