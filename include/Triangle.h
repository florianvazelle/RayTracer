#pragma once

#include <vector>

#include "Ray.h"
#include "Primitive.h"
#include "vec3.h"

struct Triangle : public Primitive {
        vec3 A, B, C;
        color col;

        Triangle(const vec3 &a, const vec3 &b, const vec3 &c, const color col) : A(a), B(b), C(c), col(col) {}
        virtual ~Triangle() {}

        float Intersect(const Ray &ray) const;
        vec3 CalcNormal(const vec3& p) const;
        color GetColor(void) const;

        vec3 GetNormal() const;
        float GetDistance() const;
};