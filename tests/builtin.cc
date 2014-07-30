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

  TEST(BuiltIn, range) {
    vector<int> v = {1, 2, 3, 4, 5};
    auto b = v.begin();
    range< vector<int> > range(b + 1, b + 3);

    EXPECT_TRUE(std::equal(b + 1, b + 3, range.begin()));
    b = b + 1;
    for (auto e : range)
      EXPECT_EQ(*b++, e);
  }

  TEST(BuiltIn, transformed) {
    vector<int> v = {1, 2, 3, 4, 5};
    auto v2 = transformed(v, [](int i) { return i+1; });

    ASSERT_EQ(v2, v);
  }

  TEST(BuiltIn, open) {
    auto f = open("test.txt");
    vector<string> v;
    for (auto& e : f)
      v.push_back(e);
    auto expected = {"test1 test1 test1 test1",
                     "test2 test2 test2",
                     "test3"};
    EXPECT_TRUE(std::equal(v.begin(), v.end(), expected.begin()));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
