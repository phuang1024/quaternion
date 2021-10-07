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

#include <cmath>
#include <iostream>

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


void preprocess_point(PF3D& point, Mesh& mesh) {
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


/**
 * Helper for preprocess_cam.
 * Return angle between cam direction and sensor at pixel.
 */
double cam_px_angle(double clip, double fov, int res, int pixel) {
    const double shutter_size = 2 * clip * tan(fov/2.0);
    const double x = (shutter_size * (double)pixel / (double)res) - shutter_size/2.0;  // sensor position
    return atan(x / clip);
}

void preprocess_cam(Scene& scene, Camera& cam) {
    const double clip = scene.clip_start;
    const double fovx = cam.fov;
    const double fovy = 2 * atan(tan(fovx/2) / (double)scene.width * (double)scene.height);

    scene._angle_limits.clear();
    scene._angle_limits.reserve(scene.width * scene.height);
    for (int y = 0; y < scene.height; y++) {
        for (int x = 0; x < scene.width; x++) {
            const double x_start = cam_px_angle(clip, fovx, scene.width, x);
            const double x_end   = cam_px_angle(clip, fovx, scene.width, x+1);
            const double y_start = cam_px_angle(clip, fovy, scene.height, y);
            const double y_end   = cam_px_angle(clip, fovy, scene.height, y+1);
            scene._angle_limits.push_back(_4F(x_start, x_end, -y_start, -y_end));
        }
    }
}


void preprocess(Scene& scene) {
    for (int i = 0; i < (int)scene.meshes.size(); i++)
        preprocess_mesh(scene.meshes[i]);
    preprocess_cam(scene, scene.cam);
}


}  // namespace Quaternion
