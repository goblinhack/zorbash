//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_FILENODE_HPP_
#define _MY_FILENODE_HPP_

#include <map>
#include <memory>

using file_nodep = class file_node;
using file_nodes = std::map< std::string, std::shared_ptr< class file_node > >;

class file_node
{
private:
public:
  file_node(void) = default;

  ~file_node(void) = default;

  std::string name; // key

  int8_t is_file {};
};

uint8_t dir_exists(const char *filename);

file_nodes dirlist(const char *dir, const char *include_suffix, const char *exclude_suffix, uint8_t include_dirs,
                   uint8_t include_ramdisk);

char *dir_dot(void);
char *dir_dotdot(char *in);
char *dospath2unix(char *in);
#endif
