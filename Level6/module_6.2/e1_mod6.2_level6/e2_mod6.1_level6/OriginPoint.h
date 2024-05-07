#pragma once
#ifndef OriginPoint_hpp
#define OriginPoint_hpp

#include "Point.h"
#include "Singleton.h"

// Subquestion (a)
class OriginPoint : public Singleton<Point> {
public:

    OriginPoint() {};  // Initializes a new instance

    OriginPoint(const OriginPoint& source) = delete;  // Prevents copy construction

    OriginPoint& operator=(const OriginPoint& source) =
        delete;  // Disables assignment
};

#endif
