//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_SIZE_H_
#define _MY_SIZE_H_

template<class T> class my_asize
{
public:
    T w {};
    T h {};

    my_asize (void) : w(0), h(0) { }

    my_asize (T w, T h) : w(w), h(h) { }

    my_asize (const my_asize &a) : w(a.w), h(a.h) { }

    void operator+= (my_asize a)
    {
        w += a.w; h += a.h;
    }

    void operator-= (my_asize a)
    {
        w -= a.w; h -= a.h;
    }

    void operator/= (my_asize a)
    {
        w /= a.w; h /= a.h;
    }

    void operator*= (my_asize a)
    {
        w *= a.w; h *= a.h;
    }

    friend my_asize operator/ (my_asize a, T i)
    {
        return (my_asize(a.w / i, a.h / i));
    }

    friend my_asize operator* (my_asize a, T i)
    {
        return (my_asize(a.w * i, a.h * i));
    }

    friend my_asize operator+ (my_asize a, my_asize b)
    {
        return (my_asize(a.w + b.w, a.h + b.h));
    }

    friend my_asize operator- (my_asize a, my_asize b)
    {
        return (my_asize(a.w - b.w, a.h - b.h));
    }

    friend my_asize operator/ (my_asize a, my_asize b)
    {
        return (my_asize(a.w / b.w, a.h / b.h));
    }

    friend my_asize operator* (my_asize a, my_asize b)
    {
        return (my_asize(a.w * b.w, a.h * b.h));
    }

    friend bool operator== (my_asize a, my_asize b)
    {
        return (a.w == b.w) && (a.h == b.h);
    }

    friend bool operator!= (my_asize a, my_asize b)
    {
        return (!(a==b));
    }

    //
    // Compare areas of a and b
    //
    friend bool operator< (my_asize a, my_asize b)
    {
        return (a.w * a.h) < (b.w * b.h);
    }

    //
    // Compare areas of a and b
    //
    friend bool operator> (my_asize a, my_asize b)
    {
        return (a.w * a.h) > (b.w * b.h);
    }
};

typedef my_asize<int> size;
typedef my_asize<float> fsize;

template<class T> class my_asize3d
{
public:

    T w {};
    T h {};
    T d {};

    my_asize3d (void) : w(0), h(0), d(0) { }

    my_asize3d (T w, T h) : w(w), h(h), d(0) { }

    my_asize3d (T w, T h, T d) : w(w), h(h), d(d) { }

    my_asize3d (const my_asize3d &a) : w(a.w), h(a.h), d(a.d) { }

    void operator+= (my_asize3d a)
    {
        w += a.w; h += a.h; d += a.d;
    }

    void operator-= (my_asize3d a)
    {
        w -= a.w; h -= a.h; d -= a.d;
    }

    friend my_asize3d operator/ (my_asize3d a, T i)
    {
        return (my_asize3d(a.w / i, a.h / i, a.d / i));
    }

    friend my_asize3d operator* (my_asize3d a, T i)
    {
        return (my_asize3d(a.w * i, a.h * i, a.d * i));
    }

    friend my_asize3d operator+ (my_asize3d a, my_asize3d b)
    {
        return (my_asize3d(a.w + b.w, a.h + b.h, a.d + b.d));
    }

    friend my_asize3d operator- (my_asize3d a, my_asize3d b)
    {
        return (my_asize3d(a.w - b.w, a.h - b.h, a.d - b.d));
    }

    friend my_asize3d operator/ (my_asize3d a, my_asize3d b)
    {
        return (my_asize3d(a.w / b.w, a.h / b.h, a.d / b.d));
    }

    friend my_asize3d operator* (my_asize3d a, my_asize3d b)
    {
        return (my_asize3d(a.w * b.w, a.h * b.h, a.d * b.d));
    }

    friend bool operator== (my_asize3d a, my_asize3d b)
    {
        return (a.w == b.w) && (a.h == b.h) && (a.d == b.d);
    }

    friend bool operator!= (my_asize3d a, my_asize3d b)
    {
        return (!(a==b));
    }

    //
    // Compare areas of a and b
    //
    // If either depth is zero treat as a 2 dimensional space
    //
    friend bool operator> (my_asize3d a, my_asize3d b)
    {
        if ((a.d == 0) && (b.d == 0))
            return (a.w * a.h) > (b.w * b.h);
        else
            return (a.w * a.h * a.d) > (b.w * b.h * b.d);
    }

    //
    // Compare areas of a and b
    //
    // If either depth is zero treat as a 2 dimensional space
    //
    friend bool operator< (my_asize3d a, my_asize3d b)
    {
        if ((a.d == 0) && (b.d == 0))
            return (a.w * a.h) < (b.w * b.h);
        else
            return (a.w * a.h * a.d) < (b.w * b.h * b.d);
    }
};

typedef my_asize3d<int> size3d;
typedef my_asize3d<double> fsize3d;

#endif // _MY_SIZE_H_
