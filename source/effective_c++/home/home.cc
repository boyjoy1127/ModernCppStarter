#include "effective_c++/home/home.h"

#include <future>

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

string Home::BoardcastAddressAsync() const {
  auto send_msg = []() { return "My home address is : empty."; };
  // std::launch::async代表立即异步执行
  // std::future_status::deferred代表延迟执行，等到被调用前执行，在future.get()或wait()调用时同步执行。
  auto future_result = std::async(std::launch::async, send_msg);
  return future_result.get();
}

string Home::DoHealthValue() const { return "check health of full house"; }

string Home::DoDraw(Color color) const { return "let paint the home as " + color.color_name(); }

string Home::OnTick() const { return "My home address is : " + address_; }

string Home::Tick() const {
  string result = "This from home begin send address ";
  result += Clock::Tick();
  return result;
}

std::string Home::address() const { return address_; }
