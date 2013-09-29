#include "gtest/gtest.h"
#include "../py/builtin.hxx"

namespace {

  // Tests Zip.
  TEST(BuiltIn, ZipBaseTest) {
    std::list<int> a = {1};
    std::list<int> b = {2};

    auto c = py::zip_new(a,b);
    EXPECT_EQ(1, c.size());
    EXPECT_EQ(1, std::get<0>(*c.begin()));
    EXPECT_EQ(2, std::get<1>(*c.begin()));
  }

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
