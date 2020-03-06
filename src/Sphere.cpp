#include "Sphere.h"

float Sphere::Intersect(const Ray &ray) const {
    vec3 diff = ray.origin - position;
    float a = diff.dot(diff);
    vec3 v = ray.direction;
    v.normalize();
    float b = diff.dot(v);
    float c = a - radius * radius;
    float t = b * b - c;
    if (t >= 0.f)
        t = -b - sqrt(t);
    return t;
}

vec3 Sphere::CalcNormal(const vec3 &p) const {
    return (p - position).normalize();
}