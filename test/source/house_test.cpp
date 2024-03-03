#include "effective_c++/home/house.h"

#include "doctest/doctest.h"

TEST_CASE("House") {
  using namespace effective;
  //> create()返回共享指针。这样可以使得registerHouse的share_from_this有效。
  //> 也就是share_from_this使用前该类的对象必须已经被shared_ptr接管，
  //> 为了保证这一点只对外提供一种创建对象的方式create。
  //> 防止使用其他构造函数，得到一个不被shared_ptr管理的对象。
  auto one_house = House::Create("PeopleRoad-No.99");
  // one_house->registerHouse();
  CHECK(one_house->Draw(Color::Green()) == "let paint the house as Green");
  CHECK(one_house->HealthValue() == "before check health of full House after.");
  CHECK(one_house->GetAddress("decorate ") == "decorate PeopleRoad-No.99");
  CHECK(one_house->GetAddress() == "PeopleRoad-No.99");
  CHECK(one_house->BoardcastAddress() == "This from home begin send address Tick begin My House address is : PeopleRoad-No.99My House address is : PeopleRoad-No.99My House address is : PeopleRoad-No.99end.");
}
