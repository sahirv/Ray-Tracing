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
#include "material.h"
#include "hitable_list.h"
#include "camera.h"
#include <random>

// eqn of circle is dot((p(t) - C), (p(t) - C) = R^2
// => dot((A + tB - C), (A + tB - C) = R^2
// => ttdot(B,B) + 2tdot(B,A-C) + dot(A-C,A-C) - RR = 0



// Use recursion. Matte - Object absorbs some light and reflects remaining to random direction
// this keeps happening until ray hits nothing / light source wich is the background
vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
        } else {
            return vec3(0, 0, 0);
        }
        
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

int main(int argc, const char * argv[]) {
    std::ofstream outputFile;
    outputFile.open("background.ppm");
    
    int nx = 300;
    int ny = 200;
    int ns = 100;
    
    outputFile << "P3\n" << nx << " " << ny << "\n255\n";
    
    hitable *list[4];
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new Lambertian(vec3(0.8,0.3,0.3)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new Lambertian(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new Metal(vec3(0.96, 0.96, 0.96), 0.2));
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new Dielectric(1.5));
    hitable *world = new hitable_list(list, 4);
    
    Camera cam(nx, ny);
    
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            int ir = int(255.99*sqrt(col[0]));
            int ig = int(255.99*sqrt(col[1]));
            int ib = int(255.99*sqrt(col[2]));
            
            outputFile << ir << " " << ig << " " << ib << "\n";
        }
    }
}
