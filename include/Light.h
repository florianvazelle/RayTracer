#pragma once

#include <algorithm>

#include "vec3.h"
#include "Ray.h"

struct Light {
    vec3 origin;
    vec3 direction;

    color diffuseColor;
    color specColor;
    float shininess;

    color diffuse(const vec3& normal) {
        float lambertian = std::max(0.f, normal.dot(direction));

        return diffuseColor * lambertian;
    }

    color specular(const Ray& ray, const vec3& normal) {
        vec3 view_direction = ray.direction.negated().normalize();
        vec3 halfDir = (direction + view_direction).normalize();
        float specAngle = std::max(halfDir.dot(normal), 0.0f);
        float specular = pow(specAngle, shininess);

        return specColor * specular;
    }
};