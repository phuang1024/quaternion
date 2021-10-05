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

#include <iostream>

#include "quaternion.hpp"


int img_test() {
    Quaternion::Image img(1920, 1080);
    for (int i = 0; i < 1920; i++)
        img.set(i, 100, 0, 255);

    img.write("a.qif");
}

int render_test() {
    Quaternion::Scene scene;
    scene.meshes.push_back(Quaternion::primitive_cube(2));
    scene.lights.push_back(Quaternion::Light({3, -2, 4}));
    scene.cam.location = {0, -5, 1.5};
    Quaternion::preprocess(scene);
}

int main() {
    render_test();
}
