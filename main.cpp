//
//  ray_test.cpp
//  Ray Tracing
//
//  Created by Sahir Vellani on 2019-05-27.
//

#include <stdio.h>
#include <fstream>
#include "vec3.h"
#include "ray.h"

// eqn of circle is dot((p(t) - C), (p(t) - C) = R^2
// => dot((A + tB - C), (A + tB - C) = R^2
// => ttdot(B,B) + 2tdot(B,A-C) + dot(A-C,A-C) - RR = 0
bool hit_sphere(const vec3& center, float radius, const ray& r) {
    // origin to center
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0*dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

vec3 color(const ray& r) {
    if (hit_sphere(vec3(0,0,-1), 0.5, r)) return vec3(1,0,0);
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1);
    return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5,0.7,1.0);
}

int main(int argc, const char * argv[]) {
    std::ofstream outputFile;
    outputFile.open("background.ppm");
    
    int nx = 200;
    int ny = 100;
    outputFile << "P3\n" << nx << " " << ny << "\n255\n";
    
    // basis vectors
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            // normalize
            // start at 0
            float u = float(i) / float(nx);
            // start at 1
            float v = float(j) / float(ny);
            
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            
            outputFile << ir << " " << ig << " " << ib << "\n";
        }
    }
}
