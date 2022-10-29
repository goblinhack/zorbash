#pragma once
#ifndef _MY_SOURCE_LOC_HPP_
#define _MY_SOURCE_LOC_HPP_

#include <source_location>

#define SRC_FILE_NAME (std::source_location::current().file_name())
#define SRC_FUNC_NAME (std::source_location::current().function_name())
#define SRC_LINE_NUM  (std::source_location::current().line())

#endif // _MY_SOURCE_LOC_HPP_
