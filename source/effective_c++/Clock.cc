#include "effective_c++/clock.h"

#include <thread>

using std::string;
using namespace effective;

Clock::Clock(int tickFrequency) : tick_frequency(tickFrequency) {}

string Clock::onTick() const { return "tick "; }

string Clock::tick() const {
  using std::this_thread::sleep_for;
  auto num = 0;
  string result = "Tick begin ";
  while (is_running && (num < 3)) {
    num++;
    result += onTick();
    // sleep for 1000 ms.
    sleep_for(std::chrono::milliseconds(1000 / tick_frequency));
  }
  result += "end.";
  return result;
}

void Clock::stop() { is_running = false; }
