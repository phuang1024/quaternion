//
//  Quaternion
//  3D raytracer.
//  Copyright Patrick Huang 2021
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

/**
 * This file is just for testing and will not
 * be included in the library.
 */

#include <iostream>

#include "quaternion.hpp"


void img_test() {
    Quaternion::Image img(1920, 1080);
    for (int i = 0; i < 1920; i++)
        img.set(i, 100, 0, 255);
    img.write("a.qif");
}

void render_test() {
    Quaternion::Scene scene;

    //scene.meshes.push_back(Quaternion::primitive_cube(2));
    Quaternion::Mesh m;
    m.faces.push_back(Quaternion::Tri({-2, 0, -2}, {-2, 0, 2}, {2, 0, 0}));
    scene.meshes.push_back(m);

    scene.lights.push_back(Quaternion::Light({3, -2, 4}));
    scene.cam.location = {0, -5, 1.5};

    Quaternion::Image img(1920, 1080);
    img.clear();
    Quaternion::render(scene, img);
    img.write("out.qif");
}

int main() {
    /*
    PF3D q1 = {0, -10, 0};
    PF3D q2 = {0, 10, 1.9};
    Quaternion::Tri tri({-2, 0, -2}, {-2, 0, 2}, {2, 0, 0});
    std::cout << Quaternion::intersects(q1, q2, tri) << std::endl;
    */

    render_test();
}
