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


void get_normal(PF3D& dest, Tri& tri) {
    // From https://stackoverflow.com/questions/19350792
    const PF3D a = tri.p2 - tri.p1;
    const PF3D b = tri.p3 - tri.p1;
    dest(0) = a(1)*b(2) - a(2)*b(1);
    dest(1) = a(2)*b(0) - a(0)*b(2);
    dest(2) = a(0)*b(1) - a(1)*b(0);
}


void preprocess_point(Eigen::Vector3f& point, Mesh& mesh) {
    // Helper function for a vertex of a mesh.
    point(0) *= mesh.scale(0);
    point(1) *= mesh.scale(1);
    point(2) *= mesh.scale(2);
    point(0) += mesh.location(0);
    point(1) += mesh.location(1);
    point(2) += mesh.location(2);
}

void preprocess_mesh(Mesh& mesh) {
    for (int i = 0; i < (int)mesh.faces.size(); i++) {
        Tri& face = mesh.faces[i];
        preprocess_point(face.p1, mesh);
        preprocess_point(face.p2, mesh);
        preprocess_point(face.p3, mesh);
        get_normal(face.normal, face);
    }
    mesh.location = {0, 0, 0};
    mesh.scale = {1, 1, 1};
}

void preprocess_cam(Scene& scene, Camera& cam) {
}

void preprocess(Scene& scene) {
    for (int i = 0; i < (int)scene.meshes.size(); i++)
        preprocess_mesh(scene.meshes[i]);
    preprocess_cam(scene, scene.cam);
}


}  // namespace Quaternion
