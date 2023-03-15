//
// Borrowed from "crawl"
//
#pragma once
#ifndef _MY_ENGLISH_HPP_
#define _MY_ENGLISH_HPP_
#include <string>

extern bool starts_with(const std::string &s, const std::string &prefix);
extern bool ends_with(const std::string &s, const std::string &suffix);

extern std::string pluralise(const std::string &name);
extern std::string apostrophise(const std::string &name);
extern void        abbreviate(std::string &s);
#endif
