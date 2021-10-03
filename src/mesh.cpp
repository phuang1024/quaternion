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

Tri::Tri(PF3D& p1, PF3D& p2, PF3D& p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

Tri::Tri(Tri& other) {
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
}


Mesh::Mesh() {
    location = {0, 0, 0};
    scale = {1, 1, 1};
}

Mesh::Mesh(Mesh& other) {
    location = other.location;
    scale = other.scale;
    faces = other.faces;
}


void get_normal(PF3D& dest, Tri& tri) {
    // From https://stackoverflow.com/questions/19350792
    const PF3D a = tri.p2 - tri.p1;
    const PF3D b = tri.p3 - tri.p1;
    dest(0) = a(1)*b(2) - a(2)*b(1);
    dest(1) = a(2)*b(0) - a(0)*b(2);
    dest(2) = a(0)*b(1) - a(1)*b(0);
}

}  // namespace Quaternion
