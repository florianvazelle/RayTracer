#pragma once

#include "vec3.h"

struct Ray {
        vec3 origin;
        float tmin;
        vec3 direction;
        float tmax;

        vec3 Evaluate(float dist) const;
};