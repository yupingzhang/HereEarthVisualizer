// n-D vector class
#ifndef VEC_HPP
#define VEC_HPP

#include <math.h>

//////////////////////////////////////////////////////////////////////
// n-D vector
// templated, but "plain old data"
// so in memory, it's the same as a simple float[n] array
// means no inheritance, no constructor or destructor
template <int Size>
class Vec {
// data, should be public for POD class
public:
    float data[Size];
    
// public member functions
public:
    float operator[](int i) const { return data[i]; }
    float &operator[](int i) { return data[i]; }

    // as color, scaled and clamped to 0-255
    int color(int i) const {
        return data[i] < 0 ? 0 : (data[i] > 1 ? 255 : int(255*data[i]+0.5f));
    }

    float length() const;       // length of vector
    Vec<Size> normalize() const; // copy of vector normalized to unit length
};

//////////////////////////////////////////////////////////////////////
// other operators as template functions
// note that since the size is a template parameter, it's a compile-time
// constant. Loops with Size iterations should be unrolled by the compiler

// cross product, v1^v2 for Vec<3> only
inline Vec<3> operator^(const Vec<3> &v1, const Vec<3> &v2) {
    Vec<3> result;
    result[0] = v1[1]*v2[2] - v1[2]*v2[1];
    result[1] = v1[2]*v2[0] - v1[0]*v2[2];
    result[2] = v1[0]*v2[1] - v1[1]*v2[0];
    return result;
}

// vector addition, v1+v2
template <int Size>
inline Vec<Size> operator+(const Vec<Size> &v1, const Vec<Size> &v2) {
    Vec<Size> result;
    for(int i=0; i<Size; ++i)
        result[i] = v1[i] + v2[i];
    return result;
}

// vector subtraction, v1-v2
template <int Size>
inline Vec<Size> operator-(const Vec<Size> &v1, const Vec<Size> &v2) {
    Vec<Size> result;
    for(int i=0; i<Size; ++i)
        result[i] = v1[i] - v2[i];
    return result;
}

// vector dot product, v1*v2
template <int Size>
inline float operator*(const Vec<Size> &v1, const Vec<Size> &v2) {
    float result = 0;
    for(int i=0; i<Size; ++i)
        result += v1[i] * v2[i];
    return result;
}

// scalar multiplication, s*v
template <int Size>
inline Vec<Size> operator*(float s, const Vec<Size> &v) {
    Vec<Size> result;
    for(int i=0; i<Size; ++i)
        result[i] = s * v[i];
    return result;
}

// scalar multiplication, v*s
template <int Size>
inline Vec<Size> operator*(const Vec<Size> &v, float s) {
    return s*v;
}

// scalar division, v/s
template <int Size>
inline Vec<Size> operator/(const Vec<Size> &v, float s) {
    return (1/s)*v;
}

//////////////////////////////////////////////////////////////////////
// member functions
// Use above template functions

// return vector length, v.length()
template <int Size>
inline float Vec<Size>::length() const {
    return sqrt(*this * *this);
}
    
// return normalized vector, v.normalize()
template <int Size>
inline Vec<Size> Vec<Size>::normalize() const {
    return *this / this->length();
}
    
#endif
