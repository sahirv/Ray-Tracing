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
    Camera(int& x, int& y) {
        
        lower_left_corner = vec3(-x / 100.0, -y / 100.0, -1.0);
        horizontal = vec3(x / 50.0, 0.0, 0.0);
        vertical = vec3(0.0, y / 50.0, 0.0);
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
