#ifndef _BASE_PARSER_H__
#define _BASE_PARSER_H__

#include "parser.h"
#include <string_view>

Parser<char> ch(char c) {
    return [=](const std::string_view &s) {
        return s.at(0) == c ? ParserResult<char>(c, s.substr(1))
                            : ParserResult<char>(s);
    };
}

Parser<char> one_of(const std::string_view str) {
    return [=](const std::string_view &s) {
        return str.find(s.at(0)) != std::string_view::npos
                   ? ParserResult<char>(s.at(0), s.substr(1))
                   : ParserResult<char>(s);
    };
}

#endif
