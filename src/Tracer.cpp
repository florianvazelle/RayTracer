#include "Tracer.h"

Tracer::Tracer() {
    scene.push_back(new Sphere{{0.f, 0.f, 2.f}, 1.f});
    scene.push_back(new Sphere{{2.f, 2.f, 4.f}, 1.f});
    //scene.push_back(new Sphere{{ -0.5f, -0.5f, 1.f}, 0.2f});
    scene.push_back(new Sphere{{-1.f, -0.5f, 2.f}, 0.75f});

    light.origin = {1.f, 1.f, 0.f};
}

Tracer::~Tracer() {
    for (Primitive *p : scene) {
        delete p;
    }
}

color Tracer::Trace(const Ray &ray, int depth) {

    color col = background.Get(ray.direction);
    if (depth >= MAX_DEPTH) {
        return col;
    }

    Tracer::Intersection intersection = Hit(ray);

    if (intersection.primitive != nullptr) {
        col = {0.5f, 0.5f, 0.75f};

        // 1. calcul du point d'intersection
        vec3 position = ray.Evaluate(intersection.distance);

        // 2. calcul d'une normal
        vec3 normal = intersection.primitive->CalcNormal(position);

        // exo2 shadow feeler
        Ray rayFeeler;
        rayFeeler.origin = position;
        rayFeeler.direction = light.origin - position;
        Tracer::Intersection intersectionFeeler = Hit(rayFeeler);
        bool vis = (intersectionFeeler.primitive != nullptr);

        if (!vis) {
            // 3. init. du nouveau rayon
            Ray newRay;
            newRay.origin = position + normal * EPSILON;
            newRay.direction = normal;

            col = col + Trace(newRay, depth + 1);

            static const vec3 diffuseColor = vec3{0.5, 0.0, 0.0};
            static const vec3 specColor = vec3{1.0, 1.0, 1.0};
            static const float shininess = 16.0f;

            // Diffuse (Lambert)
            light.direction = (light.origin - position).normalize();
            float lambertian = std::max(0.f, normal.dot(light.direction));

            col = col * (diffuseColor * lambertian);

            // Specular
            vec3 view_direction = ray.direction.negated().normalize();
            vec3 halfDir = (light.direction + view_direction).normalize();
            float specAngle = std::max(halfDir.dot(normal), 0.0f);
            float specular = pow(specAngle, shininess);

            col = col + (specColor * specular);
        } else {
            col = vec3{0.f, 0.f, 0.f};
        }
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
    Tracer::Intersection intersection{std::numeric_limits<float>::max(), nullptr};

    for (Primitive const *p : scene) {
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