#pragma once

#include <limits>
#include <vector>
#include <algorithm>

#include "vec3.h"
#include "Primitive.h"
#include "Background.h"
#include "Sphere.h"
#include "Light.h"
#include "Ray.h"

struct Tracer {
        static const int MAX_DEPTH = 5;
        static constexpr float EPSILON = 0.001f;

        Background background;

        std::vector<Primitive *> primitives;
        std::vector<Light> lights;
        Ray light;

        Tracer();
        ~Tracer();

        struct Intersection {
            float distance;
            Primitive const *primitive;
        };

        color Trace(const Ray& ray, int depth = 0);

        void Occlusion(const Ray &ray);
        Tracer::Intersection Hit(const Ray &ray);

        inline vec3 Reflect(const vec3& I, const vec3& N) const;
};