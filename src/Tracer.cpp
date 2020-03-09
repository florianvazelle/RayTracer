#include "Tracer.h"

Tracer::Tracer() {
    primitives.push_back(new Sphere{{0.f, 0.f, 2.f}, 1.f, {1.f, .6f, 1.f}});
    primitives.push_back(new Sphere{{2.f, 2.f, 4.f}, 1.f, {1.f, 1.f, .3f}});
    //scene.push_back(new Sphere{{ -0.5f, -0.5f, 1.f}, 0.2f});
    primitives.push_back(new Sphere{{-1.f, -0.5f, 2.f}, 0.75f, {.2f, .4f, 1.f}});
    primitives.push_back(new Triangle{{.5f, -0.25f, 1.f}, {-.5f, 0.25f, 1.f}, {-.5f, -0.25f, 1.f}, {.5f, 1.f, .5f}});

    Light light;
    light.origin = {1.f, 1.f, 0.f};
    light.diffuseColor = vec3{0.5, 0.0, 0.0};
    light.specColor = vec3{1.0, 1.0, 1.0};
    light.shininess = 16.0f;

    lights.push_back(light);
}

Tracer::~Tracer() {
    for (Primitive *p : primitives) {
        delete p;
    }
}

color Tracer::Trace(const Ray &ray, int depth) {

    color col = background.Get(ray.direction);
    if (depth >= MAX_DEPTH) {
        return col;
    }

    Intersection intersection = Hit(ray);

    if (intersection.primitive != nullptr) {
        color ambient = {0.f, 0.f, 0.f}, diffuse = {0.f, 0.f, 0.f}, specular = {0.f, 0.f, 0.f};

        ambient = intersection.primitive->GetColor();

        // 1. calcul du point d'intersection
        vec3 position = ray.Evaluate(intersection.distance);

        // 2. calcul d'une normal
        vec3 normal = intersection.primitive->CalcNormal(position);


        for(Light& l : lights) {
            l.direction = (l.origin - position).normalize();

            Ray rayFeeler;
            rayFeeler.origin = position + normal * EPSILON;
            rayFeeler.direction = l.direction;
            Intersection intersectionFeeler = Hit(rayFeeler);

            bool vis = (intersectionFeeler.primitive == nullptr);
            ambient = ambient * vis;
            diffuse = diffuse + l.diffuse(normal) * vis;
            specular = specular + l.specular(ray, normal) * vis;
        }

        col = ambient + diffuse + specular;
    }

    return col;
}

void Tracer::Occlusion(const Ray &ray) {
    static const int totalRay = 12;
    int sum = 0;
    int angle = 0;

    Ray newRay;
    newRay.origin = ray.origin;
    for (int i = 0; i < totalRay; i++) {
        angle += 180 / totalRay;

        float xprime = cos(angle) * newRay.origin.x - sin(angle) * newRay.origin.y;
        float yprime = sin(angle) * newRay.origin.x + cos(angle) * newRay.origin.y;

        newRay.direction = {xprime, yprime};

        sum += (Hit(newRay).primitive != nullptr) ? 1 : 0;
    }

    int ratio = sum / totalRay;
}

Tracer::Intersection Tracer::Hit(const Ray &ray) {
    Intersection intersection{std::numeric_limits<float>::max(), nullptr};

    for (Primitive const *p : primitives) {
        float distance = p->Intersect(ray);

        if (distance > 0.f && distance < intersection.distance) {
            intersection.distance = distance;
            intersection.primitive = p;
        }
    }

    return intersection;
}

inline vec3 Tracer::Reflect(const vec3 &I, const vec3 &N) const {
    return I - N * 2.f * I.dot(N);
}