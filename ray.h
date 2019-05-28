//
//  ray.h
//  CPP Practice
//
//  Created by Sahir Vellani on 2019-05-27.
//  Ray class. A ray is of the form A + tB where
//  A is the origin of the ray and B is the direction of the ray
//

#ifndef ray_h
#define ray_h
#include "vec3.h"

class ray {
public:
    ray() {}
    ray(const vec3& a, const vec3& b) {
        A = a;
        B = b;
    }
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_paramter(float t) const { return A + t*B; }
    
    vec3 A;
    vec3 B;
};


#endif /* ray_h */
