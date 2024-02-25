#include "effective_c++/Clock.h"

#include <iostream>
#include <thread>

using std::cout;
using namespace effective;

Clock::Clock(int tickFrequency) : tick_frequency(tickFrequency) {}

void Clock::onTick() const { cout << "Only tick."; }

void Clock::tick() const {
  using std::this_thread::sleep_for;
  cout << "Tick begin";
  while (is_running) {
    onTick();
    // sleep for 1000 ms.
    sleep_for(std::chrono::milliseconds(1000 / tick_frequency));
  }
}

void Clock::stop() { is_running = false; }
