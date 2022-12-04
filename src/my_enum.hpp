//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY__ENUM_HPP__
#define _MY__ENUM_HPP__

typedef std::map< std::string, uint32_t > enum_map;

/*
 * Enum list macros .h definitions
 */
#define ENUM_LIST_MACRO_VALUE(enum_arg, string_arg) enum_arg

#define ENUM_DEF_H(ENUM_NAME, enum_name)                                                                             \
                                                                                                                     \
  typedef enum { ENUM_NAME(ENUM_LIST_MACRO_VALUE) } enum_name;                                                       \
                                                                                                                     \
  extern const char *enum_name##_val2str(enum_name val);                                                             \
  extern enum_name   enum_name##_str2val(const char *val);                                                           \
  extern void        enum_name##_destroy(void);

/*
 * Enum list macros .c definitions
 */
#define ENUM_LIST_MACRO_STRING(enum_arg, string_arg) string_arg

/*
 * Enum to string.
 */
#define ENUM_DEF_C(ENUM_NAME, enum_name)                                                                             \
                                                                                                                     \
  const char *enum_name##_val2str(enum_name val)                                                                     \
  {                                                                                                                  \
    static const char *arr[] = {ENUM_NAME(ENUM_LIST_MACRO_STRING)};                                                  \
                                                                                                                     \
    if (val >= (__typeof__(val)) ARRAY_SIZE(arr)) {                                                                  \
      return ("[bad]");                                                                                              \
    }                                                                                                                \
                                                                                                                     \
    if (! arr[ val ]) {                                                                                              \
      return ("[undefined]");                                                                                        \
    }                                                                                                                \
                                                                                                                     \
    return (arr[ val ]);                                                                                             \
  }                                                                                                                  \
                                                                                                                     \
  static enum_map enum_name##_tree;                                                                                  \
                                                                                                                     \
  /*                                                                                                                 \
   * String to enum.                                                                                                 \
   */                                                                                                                \
  enum_name enum_name##_str2val(const char *val)                                                                     \
  {                                                                                                                  \
    static const char *arr[] = {ENUM_NAME(ENUM_LIST_MACRO_STRING)};                                                  \
                                                                                                                     \
    /*                                                                                                               \
     * If no tree, create one and fill it with enums.                                                                \
     */                                                                                                              \
    if (! enum_name##_tree.size()) {                                                                                 \
      /*                                                                                                             \
       * Populate the tree with enum values.                                                                         \
       */                                                                                                            \
      FOR_ALL_IN_ARRAY(iter, arr)                                                                                    \
      {                                                                                                              \
        auto result = enum_name##_tree.insert(std::make_pair(std::string(*iter), (uint32_t) (iter - arr)));          \
                                                                                                                     \
        if (result.second == false) {                                                                                \
          ERR("enum insert name [%s] failed", *iter);                                                                \
        }                                                                                                            \
      }                                                                                                              \
    }                                                                                                                \
                                                                                                                     \
    /*                                                                                                               \
     * Tree lookup of string.                                                                                        \
     */                                                                                                              \
    auto result = enum_name##_tree.find(std::string(val));                                                           \
                                                                                                                     \
    if (result == enum_name##_tree.end()) {                                                                          \
      return ((enum_name) -1);                                                                                       \
    }                                                                                                                \
                                                                                                                     \
    return ((__typeof__(enum_name)) result->second);                                                                 \
  }                                                                                                                  \
                                                                                                                     \
  void enum_name##_destroy(void)                                                                                     \
  {                                                                                                                  \
  }

#define _EXAMPLE(list_macro) list_macro(_RED = 0, "red"), list_macro(_GREEN, "green"),

#endif
