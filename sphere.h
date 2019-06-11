//
//  sphere.hpp
//  Ray Tracing
//
//  Created by Sahir Vellani on 2019-06-04.
//

#ifndef sphere_hpp
#define sphere_hpp

#include "hitable.h"

class sphere: public hitable {
public:
    sphere() {}
    //initialize members center and radius
    sphere(vec3 cen, float r, Material *mat) : center(cen), radius(r), mat_ptr(mat) {};
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    vec3 center;
    float radius;
    Material *mat_ptr;
};

#endif /* sphere_hpp */
