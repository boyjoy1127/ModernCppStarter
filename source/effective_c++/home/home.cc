#include "effective_c++/home/home.h"

//> 不要导入整个命名空间std，因为会有符号名冲突。导入具体的符号可以将冲突范围最小化。
using std::string;
using namespace effective;

Home::Home(string address) : Clock(1), address_(address) {}

Home::~Home() {}

string Home::HealthValue() const {
  string before = "before ";
  string record = DoHealthValue();
  string after = " after.";
  return before + record + after;
}

string Home::Draw(Color color) const { return DoDraw(color); }

string Home::BoardcastAddress() const { return Tick(); }

string Home::DoHealthValue() const { return "check health of full house"; }

string Home::DoDraw(Color color) const { return "let paint the home as " + color.color_name(); }

string Home::OnTick() const { return "My home address is : " + address_; }

string Home::Tick() const {
  string result = "This from home begin send address ";
  result += Clock::Tick();
  return result;
}

std::string Home::address() const { return address_; }
