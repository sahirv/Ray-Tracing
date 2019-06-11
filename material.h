//
//  material.h
//  CPP Practice
//
//  Created by Sahir Vellani on 2019-06-06.
//

#ifndef material_h
#define material_h

// friendly struct, access to hit_record members
struct hit_record;

#include "ray.h"
#include "hitable.h"

vec3 reflect(const vec3& v, const vec3& n){
    // project v on to n but negate it because v is going inwards, and multiply by 2. ||n|| = 1
    return v - 2 * dot(v, n) * n;
}

bool refract(const vec3& v, const vec3& n, float ni_nt, vec3& refracted) {
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_nt * ni_nt * (1 - dt * dt);
    if (discriminant > 0) {
        // formula for getting a refracted vector - some complicated shit
        refracted = ni_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    } else return false;
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}

float schlick_approx(float cosine, float refractive_i) {
    float r0 = (1-refractive_i) / (1+refractive_i);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1-cosine), 5);
}

class Material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

// diffuse material (matte)
class Lambertian : public Material {
public:
    Lambertian(const vec3& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
    
    vec3 albedo;
};

class Metal : public Material {
public:
    Metal(const vec3& a, float f) : albedo(a) { if (f < 1) fuzz  = f; else fuzz = 1;}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    
    vec3 albedo;
    float fuzz;
};

class Dielectric : public Material {
public:
    Dielectric(float r_i) : refractive_index(r_i) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 outward_normal;
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        float ni_nt;
        attenuation = vec3(1.0, 1.0, 1.0);
        vec3 refracted;
        float cosine;
        float reflect_prob;
        if (dot(r_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_nt = refractive_index;
            cosine = refractive_index * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        } else {
            outward_normal = rec.normal;
            ni_nt = 1.0 / refractive_index;
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }
        if (refract(r_in.direction(), outward_normal, ni_nt, refracted)) {
            reflect_prob = schlick_approx(cosine, refractive_index);
        } else {
            reflect_prob = 1.0;
        }
        if (drand48() < reflect_prob) {
            scattered = ray(rec.p, reflected);
        } else {
            scattered = ray(rec.p, refracted);
        }
        return true;
    }
    float refractive_index;
};

#endif /* material_h */
