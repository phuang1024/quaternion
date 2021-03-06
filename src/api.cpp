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

#include "quaternion.hpp"


namespace Quaternion {


Tri::Tri() {
    p1 = {0, 0, 0};
    p2 = {0, 0, 0};
    p3 = {0, 0, 0};
}

Tri::Tri(PF3D p1, PF3D p2, PF3D p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

Tri::Tri(const Tri& other) {
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
}


Mesh::Mesh() {
    color = {255, 255, 255};
    location = {0, 0, 0};
    scale = {1, 1, 1};
}

Mesh::Mesh(const Mesh& other) {
    faces = other.faces;
    color = other.color;
    location = other.location;
    scale = other.scale;
}


Camera::Camera() {
    location = {0, 0, 0};
    fov = 1.28;
}


Light::Light() {
    power = 1;
}

Light::Light(double power) {
    this->power = power;
}

Light::Light(PF3D location) {
    this->location = location;
}


Scene::Scene() {
    clip_start = 0.01;
    clip_end = 1000.0;
    background = {60, 60, 60};
    width = 1920;
    height = 1080;
}


Mesh primitive_cube(double size) {
    const double half = size / 2.0;

    PF3D v1({-half, -half, half});
    PF3D v2({-half, half, half});
    PF3D v3({half, half, half});
    PF3D v4({half, -half, half});
    PF3D v5({-half, -half, -half});
    PF3D v6({-half, half, -half});
    PF3D v7({half, half, -half});
    PF3D v8({half, -half, -half});

    Mesh mesh;
    mesh.faces.push_back(Tri(v1, v2, v4));
    mesh.faces.push_back(Tri(v3, v2, v4));
    mesh.faces.push_back(Tri(v5, v6, v8));
    mesh.faces.push_back(Tri(v7, v6, v8));
    mesh.faces.push_back(Tri(v1, v4, v5));
    mesh.faces.push_back(Tri(v8, v4, v5));
    mesh.faces.push_back(Tri(v2, v3, v6));
    mesh.faces.push_back(Tri(v7, v3, v6));
    mesh.faces.push_back(Tri(v1, v2, v5));
    mesh.faces.push_back(Tri(v6, v2, v5));
    mesh.faces.push_back(Tri(v4, v3, v7));
    mesh.faces.push_back(Tri(v4, v8, v7));

    return mesh;
}


}  // namespace Quaternion
