#include "test.h"
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

static int test_cnt = 0;
static int test_succ = 0;

int main() {
    auto a = ch('a');
    auto b = ch('b');
    auto ab = alt({a, b});
    TEST_BASE_PARSER(ab, "ab", 'a', "b");
    TEST_BASE_PARSER(ab, "bb", 'b', "b");
    auto ab2 = a | b;
    TEST_BASE_PARSER(ab2, "ab", 'a', "b");
    TEST_BASE_PARSER(ab2, "bb", 'b', "b");
    auto c = ch('c');
    auto abc = a | b | c;
    TEST_BASE_PARSER(abc, "ab", 'a', "b");
    TEST_BASE_PARSER(abc, "bb", 'b', "b");
    TEST_BASE_PARSER(abc, "cb", 'c', "b");

    auto opta = opt(a, 'b');
    TEST_BASE_PARSER(opta, "cb", 'b', "cb");
    TEST_BASE_PARSER(opta, "ab", 'a', "b");

    auto anb = a + b;
    TEST_PAIR_PARSER(anb, "abc", make_pair('a', 'b'), "c");

    auto v1 = many(a);
    const vector<char> r1(3, 'a');
    TEST_VECTOR_PARSER((v1), "aaab", r1, "b");

    function<const char(const char)> cvt = [](char c) -> char { return c + 1; };
    auto add1 = abc >> cvt;
    TEST_BASE_PARSER(add1, "ab", 'b', "b");
    TEST_BASE_PARSER(add1, "bb", 'c', "b");
    TEST_BASE_PARSER(add1, "cb", 'd', "b");

    cout << "test result: " << test_succ << "/" << test_cnt << endl;
}
