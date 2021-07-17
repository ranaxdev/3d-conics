#ifndef _H_MATH
#define _H_MATH

#include <cmath>
#include <initializer_list>
#include <cstring>

template<typename T, const uint16_t n>
struct Vec{
    T arr[n];
    const uint16_t size = n;

    explicit Vec(...){
        T tot = 0;
        va_list param_list;
        va_start(param_list, n);
        va_arg(param_list, float);
        va_end(param_list);
        std::cout << tot << std::endl;
    }

    inline void assign_vec(const Vec& v){
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