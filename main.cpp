//
//  main.cpp
//  Ray Tracing
//
//  Created by Sahir Vellani on 2019-05-25.
//

#include <iostream>
#include <fstream>

int main(int argc, const char * argv[]) {
    std::ofstream outputFile;
    outputFile.open("img.ppm");
    
    int nx = 200;
    int ny = 100;
    outputFile << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.5;
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            outputFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    outputFile.close();
    return 0;
}
