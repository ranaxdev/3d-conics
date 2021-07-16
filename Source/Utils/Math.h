#ifndef _H_MATH
#define _H_MATH

#include <cmath>

template<typename T, const u_int16_t n>
struct Vec{
    T arr[n];
    const u_int16_t size = n;
    
    inline void assign(const Vec& v){
        // Copies other vec into this vec
        if(!this->size == v.size){
            // TODO
            // Log assignment error
            return;
        }
        for(int i=0; i<n; i++)
            arr[i] = v[i];
    }
};

#endif