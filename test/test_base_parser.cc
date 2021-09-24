#include "test.h"
#include <iostream>
using namespace std;

static int test_cnt = 0;
static int test_succ = 0;

int main() {
    auto a = ch('a');
    TEST_BASE_PARSER(a, "a"sv, 'a', ""sv);
    auto isdigit = one_of("0123456789");
    TEST_BASE_PARSER(isdigit, "1", '1', ""sv);
    TEST_BASE_PARSER(isdigit, "123", '1', "23"sv);
    cout << "test result: " << test_succ << "/" << test_cnt << endl;
}
