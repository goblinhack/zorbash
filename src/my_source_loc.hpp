#pragma once
#ifndef _MY_SOURCE_LOC_HPP_
#define _MY_SOURCE_LOC_HPP_

#define HAVE_WORKING_SOURCE_LOCATION_HEADER

#ifdef __clang__
// Seems to be missing for clang. Including <experimental/source_location> did not help
#undef HAVE_WORKING_SOURCE_LOCATION_HEADER
#endif

#ifdef __APPLE__
// Missing with macports
#undef HAVE_WORKING_SOURCE_LOCATION_HEADER
#endif

#ifdef HAVE_WORKING_SOURCE_LOCATION_HEADER
#include <source_location>
#define SRC_FILE_NAME (std::source_location::current().file_name())
#define SRC_FUNC_NAME (std::source_location::current().function_name())
#define SRC_LINE_NUM  (std::source_location::current().line())
#else
#define SRC_FILE_NAME __FILE__
#define SRC_FUNC_NAME __PRETTY_FUNCTION__
#define SRC_LINE_NUM  __LINE__
#endif

#endif // _MY_SOURCE_LOC_HPP_
