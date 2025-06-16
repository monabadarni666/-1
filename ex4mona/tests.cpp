/*
 * email:
 * File: tests.cpp
 * Extended test‑suite for MyContainer – no helper macros/functions
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <sstream>
#include <vector>
#include "ac/MyContainer.hpp"

using ac::MyContainer;

TEST_CASE("Basic add/remove/size and ostream") {
    MyContainer<int> c;
    CHECK(c.size() == 0);

    for (int v : {7, 15, 6, 1, 2, 2}) c.add(v);
    CHECK(c.size() == 6);

    std::ostringstream oss;
    oss << c;
    CHECK(oss.str() == "[7, 15, 6, 1, 2, 2]");

    c.remove(2);
    CHECK(c.size() == 4);

    CHECK_THROWS_AS(c.remove(999), std::runtime_error);
}

TEST_CASE("Iterator orders – ints") {
    MyContainer<int> c; for (int v : {7, 15, 6, 1, 2}) c.add(v);

    CHECK(std::vector<int>(c.beginAscending(),  c.endAscending())  == std::vector<int>{1,2,6,7,15});
    CHECK(std::vector<int>(c.beginDescending(), c.endDescending()) == std::vector<int>{15,7,6,2,1});
    CHECK(std::vector<int>(c.beginSideCross(),  c.endSideCross()) == std::vector<int>{1,15,2,7,6});
    CHECK(std::vector<int>(c.rbegin(),          c.rend())         == std::vector<int>{2,1,6,15,7});
    CHECK(std::vector<int>(c.begin(),           c.end())          == std::vector<int>{7,15,6,1,2});
    CHECK(std::vector<int>(c.beginMiddle(),     c.endMiddle())    == std::vector<int>{6,15,1,7,2});
}

TEST_CASE("Template works for double & std::string") {
    MyContainer<double> d; for (double v : {3.5, -1.0, 2.2}) d.add(v);
    CHECK(std::vector<double>(d.beginAscending(), d.endAscending()) == std::vector<double>{-1.0,2.2,3.5});

    MyContainer<std::string> s; for (const char* raw : {"pear","apple","peach"}) s.add(std::string{raw});
    CHECK(std::vector<std::string>(s.beginAscending(), s.endAscending()) == std::vector<std::string>{"apple","peach","pear"});
}

TEST_CASE("Edge – empty container") {
    const MyContainer<int> e;
    CHECK(e.begin() == e.end());
    CHECK(e.beginAscending() == e.endAscending());
    CHECK(e.rbegin() == e.rend());
}

TEST_CASE("Edge – single element") {
    MyContainer<int> one; one.add(42);

    CHECK(std::vector<int>(one.begin(),          one.end())          == std::vector<int>{42});
    CHECK(std::vector<int>(one.beginAscending(), one.endAscending()) == std::vector<int>{42});
    CHECK(std::vector<int>(one.beginDescending(),one.endDescending())== std::vector<int>{42});
    CHECK(std::vector<int>(one.beginSideCross(), one.endSideCross()) == std::vector<int>{42});
    CHECK(std::vector<int>(one.rbegin(),         one.rend())         == std::vector<int>{42});
    CHECK(std::vector<int>(one.beginMiddle(),    one.endMiddle())    == std::vector<int>{42});
}
