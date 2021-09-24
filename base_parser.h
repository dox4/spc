#ifndef _BASE_PARSER_H__
#define _BASE_PARSER_H__

#include "parser.h"
#include <string_view>

extern Parser<char> ch(char c);
extern Parser<char> one_of(const std::string_view str);

#endif
