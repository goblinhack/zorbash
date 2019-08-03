//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

//
// Create a vector of numbers
//
template <class T> std::vector<T> make_range (const size_t how_many) {
    std::vector<T> v(how_many);
    std::generate(v.begin(), v.end(), [n = 0] () mutable { return n++; });
    return (v);
}

template <class T> std::vector<T> make_range (T start, T stop) {
    size_t how_many = stop - start;
    std::vector<T> v(how_many);
    std::generate(v.begin(), v.end(), [n = start] () mutable { return n++; });
    return (v);
}

//
// Create a vector of numbers and then shuffle them
//
#include <random>
#include <algorithm>
extern std::default_random_engine rng;
template <class T> std::vector<T> make_shuffled_range (const size_t how_many) {
    std::vector<T> v(how_many);
    std::generate(v.begin(), v.end(), [n = 0] () mutable { return n++; });
    std::shuffle(v.begin(), v.end(), rng);
    return (v);
}

//
// This one is better as does not create a vector
//
template <class T> class range {
private:
    class iter {
    private:
        T at;
    public:
        iter(T at) : at(at) {}
        bool operator!=(iter const& other) const { return at != other.at; }
        T const& operator*() const { return at; }
        iter& operator++() { ++at; return *this; }
    };

    T begin_val;
    T end_val;
public:
    range(T begin_val, T end_val) : begin_val(begin_val), end_val(end_val) { }
    iter begin() { return iter(begin_val); }
    iter end() { return iter(end_val); }
};
