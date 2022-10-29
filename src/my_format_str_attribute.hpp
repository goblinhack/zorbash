#pragma once
#ifndef _MY_FORMAT_STR_ATTRIBUTE_HPP_
#define _MY_FORMAT_STR_ATTRIBUTE_HPP_

#if defined(__GNUC__) || defined(__clang__)
#define CHECK_FORMAT_STR(a, b, c) __attribute__((format(a, b, c)))
#else
#define CHECK_FORMAT_STR(a, b, c)
#endif

#endif // _MY_FORMAT_STR_ATTRIBUTE_HPP_
