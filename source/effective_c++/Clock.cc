#include "effective_c++/clock.h"

#include <thread>

using std::string;
using namespace effective;

Clock::Clock(int tickFrequency) : tick_frequency_(tickFrequency) {}

string Clock::OnTick() const { return "tick "; }

string Clock::Tick() const {
  using std::this_thread::sleep_for;
  auto num = 0;
  string result = "Tick begin ";
  while (is_running_ && (num < 3)) {
    num++;
    result += OnTick();
    // sleep for 1000 ms.
    sleep_for(std::chrono::milliseconds(1000 / tick_frequency_));
  }
  result += "end.";
  return result;
}

void Clock::Stop() { is_running_ = false; }
