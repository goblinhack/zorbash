/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

template <class T> std::vector<T> range (const size_t how_many) {
    std::vector<T> v(how_many);
    std::generate(v.begin(), v.end(), [n = 0] () mutable { return n++; });
    return (v);
}

template <class T> std::vector<T> range (T start, T stop) {
    size_t how_many = stop - start;
    std::vector<T> v(how_many);
    std::generate(v.begin(), v.end(), [n = start] () mutable { return n++; });
    return (v);
}
