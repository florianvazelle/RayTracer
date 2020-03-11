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
        float lambertian = std::max(normal.dot(direction), 0.0f);

        return diffuseColor * lambertian;
    }

    color specular(const vec3& position, const vec3& normal) {
        vec3 view_direction = position.negated().normalize();
        vec3 halfDir = (direction + view_direction).normalize();
        float specAngle = std::max(normal.dot(halfDir), 0.0f);
        float specular = pow(specAngle, shininess);

        return specColor * specular;
    }
};