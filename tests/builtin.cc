#include "gtest/gtest.h"
#include "../py/builtin.hxx"
#include "../py/range.hh"
#include "../py/open.hh"
#include "../py/transformed.hh"
#include "../py/reduce.hh"

using namespace std;

namespace py
{

  // Tests Zip.
  TEST(BuiltIn, iprint) {
    print("Hello world !"); //FIXME cout.set_rbuf
  }

  TEST(BuiltIn, range) {
    vector<int> v = {1, 2, 3, 4, 5};
    auto b = v.begin();
    range< vector<int>::iterator > range(b + 1, b + 3);
    ASSERT_TRUE(std::equal(b + 1, b + 3, range.begin()));
  }

  TEST(BuiltIn, transformed) {
    auto expected = {2, 3, 4, 5, 6};
    auto v = {1, 2, 3, 4, 5};
    ASSERT_EQ(expected, v | [](int i) { return i+1; });
  }

  TEST(BuiltIn, for_transformed) {
    auto expected = {2, 3, 4, 5, 6};
    auto v = {1, 2, 3, 4, 5};

    auto b = expected.begin();
    for (auto e : v | [](int i) { return i+1; })
      ASSERT_EQ(e, *b++);
  }

  TEST(BuiltIn, open) {
    auto expected = {"test1 test1 test1 test1",
                     "test2 test2 test2",
                     "test3"};
    ASSERT_EQ(expected, open("test.txt"));
  }

  TEST(BuiltIn, reduce) {
    auto s = {"1", "2", "3"};
    string expected = "123";
    ASSERT_EQ(expected, reduce([](string a, string b) { return a + b; }, s));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
