#pragma once

#include "Ray.h"
#include "Primitive.h"
#include "vec3.h"

struct Sphere : public Primitive {
        vec3 position;
        float radius;
        color col;

        Sphere(const vec3 &p, const float r, const color col) : position(p), radius(r), col(col) {}
        virtual ~Sphere() {}

        float Intersect(const Ray &ray) const;
        vec3 CalcNormal(const vec3& p) const;
        color GetColor(void) const;
};