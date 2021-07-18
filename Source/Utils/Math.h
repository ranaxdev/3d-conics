#ifndef _H_MATH
#define _H_MATH

#include <cmath>
#include <list>
#include <cstring>

#include "Globals.h"
#include "Logger.h"

template<typename T, const uint16_t n>
struct Vec{
    T arr[n];
    const uint16_t size = n;


    explicit Vec(const std::list<T>&& params){
        // Log size error
        if(params.size() < n){
            Logger::log(WARN, "Vector not fully filled", __FILENAME__);
        }

        typename std::list<T>::const_iterator it = params.cbegin();
        for(int i=0; i<n; i++){
            std::cout << *it << std::endl;
            it++;
        }

    }

    inline void assign_vec(const Vec& v){
        // Copies other vec into this vec
        if(!this->size == v.size){
            // Log assignment error
            Logger::log(ERROR, "Cannot assign vector to another vector of different size", __FILENAME__);
            return;
        }
        for(int i=0; i<n; i++)
            arr[i] = v[i];
    }
};

#endif