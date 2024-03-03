#include "effective_c++/home/house.h"

using std::string;
using namespace effective;

std::shared_ptr<House> House::Create(std::string address) {
  return std::shared_ptr<House>(new House(address));
}

void House::RegisterHouse() { registered_houses_.emplace_back(shared_from_this()); }

House::House(string address) : Home(address), bucket_water_volume_(0) {}

string House::DoHealthValue() const { return "check health of full House"; }

string House::DoDraw(Color color) const { return "let paint the house as " + color.color_name(); }

string House::OnTick() const { return "My House address is : " + address(); }

long House::AddWater(const Water& water) {
  auto water_volume = water.GetWater();
  bucket_water_volume_ += water_volume;
  return bucket_water_volume_;
}