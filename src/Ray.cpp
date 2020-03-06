#include "Ray.h"

vec3 Ray::Evaluate(float dist) const {
    return origin + direction * dist;
}