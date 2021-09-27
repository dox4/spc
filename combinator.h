#ifndef _SPC_COMBINATOR_H__
#define _SPC_COMBINATOR_H__

#include "parser.h"
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

template <typename T>
const Parser<T> alt(std::initializer_list<const Parser<T>> ps) {
    return [=](const std::string_view &s) {
        for (auto p = ps.begin(); p != ps.end(); p++) {
            ParserResult<T> result = (*p)(s);
            if (result.succeed()) {
                return result;
            }
        }
        return ParserResult<T>(s);
    };
}

template <typename T>
const Parser<T> operator|(const Parser<T> p1, const Parser<T> p2) {
    return [=](const std::string_view &s) {
        auto result = p1(s);
        if (result.succeed()) {
            return result;
        }
        return p2(s);
    };
}

template <typename T, typename U>
const Parser<std::pair<T, U>> operator+(const Parser<T> p1,
                                        const Parser<U> p2) {
    return [=](const std::string_view &s) {
        auto r1 = p1(s);
        if (r1.succeed()) {
            auto r2 = p2(r1.rest());
            if (r2.succeed()) {
                return ParserResult<std::pair<T, U>>(
                    std::make_pair(r1.value(), r2.value()), r2.rest());
            }
        }
        return ParserResult<std::pair<T, U>>(s);
    };
}

template <typename T> const Parser<T> opt(Parser<T> p, const T defval) {
    return [=](const std::string_view &s) {
        auto r = p(s);
        return r.succeed() ? r : ParserResult(defval, s);
    };
}

template <typename T>
const Parser<const std::vector<T>> many(const Parser<T> parser,
                                        const int at_leat = 1) {
    using ManyParser = decltype(many(parser, at_leat));
    auto vp = std::make_shared<std::vector<T>>();
    ManyParser mp = [=, &mp](const std::string_view &s) {
        auto rt = parser(s);
        if (rt.succeed()) {
            vp->emplace_back(rt.value());
            // std::cout << __LINE__ << " rt.value(): " << rt.value() <<
            // std::endl; std::cout << __LINE__ << " r.size(): " << vp->size()
            //           << ", *r.end(): " << *(vp->end()) << std::endl;
            return mp(rt.rest());
        }
        return vp->size() < at_leat
                   ? ParserResult<const std::vector<T>>(s)
                   : ParserResult<const std::vector<T>>(*vp.get(), rt.rest());
    };
    return mp;
}

template <typename T, typename R>
const Parser<R> operator>>(const Parser<T> parser,
                           std::function<const R(const T)> f) {
    return [=](const std::string_view &s) {
        auto r = parser(s);
        if (r.succeed()) {
            return ParserResult(f(r.value()), r.rest());
        }
        return ParserResult<R>(s);
    };
}

#endif
