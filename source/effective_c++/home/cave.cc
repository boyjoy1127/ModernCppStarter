#include "effective_c++/home/cave.h"

using std::string;
using namespace effective;

Cave::Cave(string address) : Home(address) {}

string Cave::DoHealthValue() const { return "check health of full Cave"; }

string Cave::DoDraw(Color color) const { return "let paint the cave as " + color.color_name(); }

string Cave::OnTick() const { return "My cave address is : " + address(); }
