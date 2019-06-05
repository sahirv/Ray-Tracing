//
//  ray_test.cpp
//  Ray Tracing
//
//  Created by Sahir Vellani on 2019-05-27.
//

#include <stdio.h>
#include <fstream>
#include "vec3.h"
#include "sphere.h"
#include "float.h"
#include "hitable_list.h"
#include "camera.h"
#include <random>

// eqn of circle is dot((p(t) - C), (p(t) - C) = R^2
// => dot((A + tB - C), (A + tB - C) = R^2
// => ttdot(B,B) + 2tdot(B,A-C) + dot(A-C,A-C) - RR = 0

vec3 color(const ray& r, hitable *world) {
    hit_record rec;
    if (world->hit(r, 0.0, MAXFLOAT, rec)) {
        return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

int main(int argc, const char * argv[]) {
    std::ofstream outputFile;
    outputFile.open("background.ppm");
    
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0, 0.9999);
    
    int nx = 200;
    int ny = 100;
    int ns = 100;
    
    outputFile << "P3\n" << nx << " " << ny << "\n255\n";
    
    hitable *list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hitable *world = new hitable_list(list, 2);
    
    Camera cam;
    
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + distribution(generator)) / float(nx);
                float v = float(j + distribution(generator)) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world);
            }
            col /= float(ns);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            
            outputFile << ir << " " << ig << " " << ib << "\n";
        }
    }
}
