#include "effective_c++/home/nest.h"

using namespace effective;
using std::string;

Nest::Nest(string address) : Home(address) {}

string Nest::DoHealthValue() const { return "check health of full Nest"; }

string Nest::DoDraw(Color color) const { return "let paint the nest as " + color.color_name(); }

string Nest::OnTick() const { return "My nest address is : " + address_; }
