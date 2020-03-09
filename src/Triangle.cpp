#include "Triangle.h"

float Triangle::Intersect(const Ray &ray) const {
    vec3 normal = GetNormal();
    float distance = GetDistance();

    float a = ray.direction.dot(normal);

    if (a == 0.f) {
        // parallel
        return -1.f;
    } else {
        float b = normal.dot(ray.origin + (normal * distance).negated());
        float t = -1 * b / a;

        vec3 Q = (ray.direction * t) + ray.origin;

        float dot1 = (C - A).cross(Q - A).dot(normal);
        float dot2 = (B - C).cross(Q - C).dot(normal);
        float dot3 = (A - B).cross(Q - B).dot(normal);

        if (dot1 >= 0.f && dot2 >= 0.f && dot3 >= 0.f) {
            return t;
        } else {
            return -1.f;
        }
    }
}

vec3 Triangle::CalcNormal(const vec3 &p) const {
    return GetNormal();
}

color Triangle::GetColor(void) const {
    return col;
}

vec3 Triangle::GetNormal() const {
    return (C - A).cross(B - A).normalize();
}

float Triangle::GetDistance() const {
    return GetNormal().dot(A);
}