//
//  hitable.h
//  Ray Tracing
//
//  Created by Sahir Vellani on 2019-06-03.
//

#ifndef hitable_h
#define hitable_h

#include "ray.h"

// friend class
// Material has access to hitable members
class Material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    Material *mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif /* hitable_h */
