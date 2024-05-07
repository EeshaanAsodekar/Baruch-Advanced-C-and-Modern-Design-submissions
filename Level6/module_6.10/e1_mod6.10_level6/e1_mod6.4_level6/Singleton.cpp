#ifndef Singleton_cpp
#define Singleton_cpp

#include "Singleton.h"

template <class TYPE>
Destroyer<TYPE>::Destroyer() {

    doomed_object = nullptr;
}

template <class TYPE>
Destroyer<TYPE>::Destroyer(
    TYPE* t) {

    doomed_object = t;
}

template <class TYPE>
Destroyer<TYPE>::Destroyer(
    const Destroyer<TYPE>& source) {
}

template <class TYPE>
Destroyer<TYPE>& Destroyer<TYPE>::operator=(
    const Destroyer<TYPE>& source) {

    return *this;
}

template <class TYPE>
Destroyer<TYPE>::~Destroyer() {

    delete doomed_object;
}

template <class TYPE>
void Destroyer<TYPE>::doomed(TYPE* t) {

    doomed_object = t;
}


template <class TYPE>
TYPE* Singleton<TYPE>::ins = nullptr;
template <class TYPE>
Destroyer<TYPE> Singleton<TYPE>::des;

template <class TYPE>
Singleton<TYPE>::Singleton() {
}

template <class TYPE>
Singleton<TYPE>::Singleton(const Singleton<TYPE>& source) {
}

template <class TYPE>
Singleton<TYPE>::~Singleton() {

    int x;
    x = 0;
}

template <class TYPE>
TYPE* Singleton<TYPE>::instance() {

    if (ins == nullptr) {
        ins = new TYPE;
        des.doomed(ins);
    }

    return ins;
}

template <class TYPE>
Singleton<TYPE>& Singleton<TYPE>::operator=(
    const Singleton<TYPE>& source) {

    return *this;
}

#endif  // Singleton_cpp