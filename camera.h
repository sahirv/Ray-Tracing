//
//  camera.h
//  Ray Tracing
//
//  Created by Sahir Vellani on 2019-06-05.
//

#ifndef camera_h
#define camera_h

#include "ray.h"

class Camera {
public:
    Camera() {
        lower_left_corner = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }
    
    ray get_ray(float u, float v) {
        return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }
    
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif /* camera_h */
