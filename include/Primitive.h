#pragma once

#include <algorithm>

#include "vec3.h"
#include "Ray.h"

struct Primitive {
    // polymorphisme + C++ = virtual table pointer 
    virtual float Intersect(const Ray& ray) const = 0;
    virtual vec3 CalcNormal(const vec3& p) const = 0;
    virtual ~Primitive() {}
};