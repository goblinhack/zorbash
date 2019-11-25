#ifndef MY_SHARED_PTR
#define MY_SHARED_PTR
#include <memory>
#include <sstream>
#include <string>
#include <iostream>
#include "my_ptrcheck.h"

template <typename T> class SmartPointerWrapper {
private:
    std::shared_ptr<T> sptr;
    std::string name {"nullptr"};

    void debug (const std::string &what) {
#ifdef DEBUG
        std::cout << what << " " << to_string() << std::endl;
#endif
    }

    std::string to_string (void) {
        auto address = static_cast<const void*>(this);
        std::stringstream ss;
        ss << address;
        if (sptr) {
            return "SmartPointerWrapper(" + ss.str() + "," + sptr->to_string() + ")";
        } else {
            return "SmartPointerWrapper(" + ss.str() + ")";
        }
    }
public:
    // explicit means constructor must match exactly
    template <typename ...ARGS> explicit 
      SmartPointerWrapper(const std::string &name, ARGS... a) : name(name) { 
        sptr = std::make_shared<T>(a...);
        debug("make_shared");
    }

    explicit SmartPointerWrapper(const std::string &name) : name(name) { 
        sptr = std::make_shared<T>();
        debug("make_shared");
    }

    explicit SmartPointerWrapper(void) {
        debug("init");
    }

    ~SmartPointerWrapper() {
        debug("delete");
    }

    void rename(const std::string &name) { 
        this->name = name;
        debug("rename");
    }

    T* const operator->() { return sptr.operator->(); }
    T* get() const { return sptr.get(); }
    T& operator*() { return *sptr; }
    const T& operator*() const { return *sptr; }
    operator bool() const { return (bool)sptr; }

    void reset() { 
        debug("reset");
        sptr.reset(); 
    }
};
#endif
