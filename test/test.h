#ifndef _TEST_H__
#define _TEST_H__

#include "../base_parser.h"

#define TEST_EQUAL(expected, actual)                                           \
    do {                                                                       \
        test_cnt++;                                                            \
        if ((expected) == (actual)) {                                          \
            test_succ++;                                                       \
        } else {                                                               \
            cout << "test failed: expected " << (expected) << ", but got "     \
                 << (actual) << ", at " << __FILE__ << ":" << __LINE__ << "."  \
                 << endl;                                                      \
        }                                                                      \
    } while (false)

#define TEST_BASE_PARSER(parser, source, expected, expected_rest)              \
    do {                                                                       \
        auto result = parser(source);                                          \
        if (result.succeed()) {                                                \
            auto actual = result.value();                                      \
            TEST_EQUAL(expected, actual);                                      \
            const string_view &rest = result.rest();                           \
            TEST_EQUAL(expected_rest, rest);                                   \
        } else {                                                               \
            cout << "test failed: parsing " << #source << " failed at "        \
                 << __FILE__ << ":" << __LINE__ << "." << endl;                \
        }                                                                      \
    } while (false)

#endif
