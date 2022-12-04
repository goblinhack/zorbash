#pragma once
#ifndef _MY_SOURCE_LOC_HPP_
#define _MY_SOURCE_LOC_HPP_

#if defined(__cpp_lib_source_location) && (__cpp_lib_source_location >= 201907L)
// Feature test macros https://en.cppreference.com/w/cpp/feature_test
#define SRC_FILE_NAME (std::source_location::current().file_name())
#define SRC_FUNC_NAME (std::source_location::current().function_name())
#define SRC_LINE_NUM  (std::source_location::current().line())
#else
#define SRC_FILE_NAME __FILE__
#define SRC_FUNC_NAME __PRETTY_FUNCTION__
#define SRC_LINE_NUM  __LINE__
#endif

#endif // _MY_SOURCE_LOC_HPP_
