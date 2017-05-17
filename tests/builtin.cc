
class gets;
#include "gtest/gtest.h"

#include "../py/py.hh"

using namespace std;
using namespace py;

namespace {

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
    for (const auto& e : v | [](int i) { return i+1; })
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
    ASSERT_EQ(expected,
              reduce([](string a, string b) { return a + b; }, s));
  }

  TEST(BuiltIn, imap) {
    std::vector<string> expected = {"1", "2", "3"};
    ASSERT_EQ(expected, imap([](string a) { return a; }, expected));
  }

  TEST(BuiltIn, map) {
    std::vector<string> expected = {"1", "2", "3"};
    ASSERT_EQ(expected, py::map([](auto a) { return a; }, expected));
  }

  TEST(BuiltIn, predicate) {
    auto v1 = {3, 4, 5};

    ASSERT_TRUE(all(v1 | [](int i)  { return i > 2; }));
    ASSERT_FALSE(all(v1 | [](int i) { return i < 4; }));

    ASSERT_TRUE(any(v1 | [](int i)  { return i == 4; }));
    ASSERT_FALSE(any(v1 | [](int i) { return i < 3; }));

    ASSERT_TRUE(none(v1 | [](int i)  { return i == 6; }));
    ASSERT_FALSE(none(v1 | [](int i) { return i > 3; } ));
  }

  TEST(BuiltIn, enumerate) {
    auto v = {1, 2, 3};

    int k = 0;
    auto b = v.begin();
    int i, value;
    for (const auto& t : enumerate(v))
    {
      std::tie(i, value) = t;
      ASSERT_EQ(k++, i);
      ASSERT_EQ(*b++, value);
    }
  }

  TEST(BuiltIn, list) {
    auto expected = {1, 2, 3};
    std::vector<int> v1 = py::list({1, 2, 3});
    ASSERT_TRUE(std::equal(expected.begin(), expected.end(), v1.begin()));
    std::vector<int> v2 = py::list(v1 | [](int i) { return i+1; });

    expected = {2, 3, 4};
    ASSERT_TRUE(std::equal(expected.begin(), expected.end(), v2.begin()));
  }

  TEST(BuiltIn, filter) {
    auto v = {1, 2, 3};

    int nb = 0;
    for (const auto& i : ifilter([](int x) { return x == 2; }, v))
    {
      ASSERT_EQ(2, i);
      nb++;
    }
    ASSERT_EQ(1, nb);
  }

  TEST(BuiltIn, zip) {
    vector<int>    v = {1, 2, 3};
    vector<string> w = {"3", "2", "1"};
    auto vw = zip(v, w);

    ASSERT_EQ(vw.size(), v.size());
    size_t i = 0;
    for (const auto& e : vw)
    {
      ASSERT_EQ(std::get<0>(e), v[i]);
      ASSERT_EQ(std::get<1>(e), w[i]);
      i++;
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
