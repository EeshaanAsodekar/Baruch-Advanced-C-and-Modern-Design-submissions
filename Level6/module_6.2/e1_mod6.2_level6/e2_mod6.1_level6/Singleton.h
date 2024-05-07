#pragma once
#ifndef Singleton_hpp
#define Singleton_hpp

template <class TYPE>
class Singleton;

template <class TYPE>
class Destroyer {  
    

    friend class Singleton<TYPE>;  

private:
    TYPE* doomed_object;  

    Destroyer(TYPE* t);  
    Destroyer(const Destroyer<TYPE>& source);  
    Destroyer<TYPE>& operator=(
        const Destroyer<TYPE>& source);  

    
    void doomed(TYPE* t);

public:
    
    virtual ~Destroyer();


    Destroyer();  
};

template <class TYPE>
class Singleton {  

private:
    static TYPE* ins;
    static Destroyer<TYPE> des;

protected:
    Singleton();
    Singleton(const Singleton<TYPE>& source);
    virtual ~Singleton();
    Singleton<TYPE>& operator=(const Singleton<TYPE>& source);

public:
    static TYPE* instance();
};

#ifndef Singleton_cpp
#include "Singleton.cpp"
#endif

#endif  // Singleton_hpp