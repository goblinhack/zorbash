//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_TEMPLATE_H_
#define _MY_TEMPLATE_H_

#include "my_random.h"

template < class T, template < typename ELEM, typename ALLOC = std::allocator< ELEM > > class C >

bool contains(C< T > *c, T t)
{
  typename C< T >::iterator i = c->begin();

  while (i != c->end()) {
    if (*i == t) {
      return true;
    }
    i++;
  }
  return false;
}

template < class T, template < typename ELEM, typename ALLOC = std::allocator< ELEM > > class C >

void push_back_if_unique(C< T > &c, T d)
{
  typename C< T >::iterator so = c.begin();
  typename C< T >::iterator eo = c.end();

  while (so != eo) {
    T t = *so;

    if (t == d) {
      return;
    }
    so++;
  }
  c.push_back(d);
}

#ifdef NO_ONE_USES_YET_AND_COINCERNED_ABOUT_WHICH_RAND_SHOULD_BE_USED
template < class T, template < typename ELEM, typename ALLOC = std::allocator< ELEM > > class C >

T one_of(C< T > &c)
{
  typename C< T >::iterator so = c.begin();
  typename C< T >::iterator eo = c.end();

  size_t sz = eo - so;
  return *(so + (myrand() % sz));
}
#endif

#endif
