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


/**
 * True if positive else False
 */
bool sign(double n) {
    return (n > 0);
}

bool sign(int n) {
    return (n > 0);
}


namespace Quaternion {


/**
 * From https://stackoverflow.com/questions/42740765
 * Calculates volume of tetrahedron.
 */
float signed_volume(PF3D a, PF3D b, PF3D c, PF3D d) {
    return (0.166) * (b-a).cross(c-a).dot(d-a);
}

/**
 * From https://stackoverflow.com/questions/42740765
 * Checks if line segment through p1 and p2 intersects tri.
 */
bool intersects(const PF3D q1, const PF3D q2, const Tri& tri) {
    const PF3D p1 = tri.p1, p2 = tri.p2, p3 = tri.p3;
    const bool v1 = sign(signed_volume(q1, p1, p2, p3));
    const bool v2 = sign(signed_volume(q2, p1, p2, p3));
    const bool v3 = sign(signed_volume(q1, q2, p1, p2));
    const bool v4 = sign(signed_volume(q1, q2, p2, p3));
    const bool v5 = sign(signed_volume(q1, q2, p3, p1));
    return (v1 != v2) && (v3 == v4) && (v4 == v5);
}


void render(Scene& scene, Image& img) {
    if (img.width != scene.width || img.height != scene.height) {
        std::cerr << "Quaternion::render: Dimensions must match." << std::endl;
        throw 1;
    }

    preprocess(scene);

    const float clip_end = scene.clip_end;

    for (int y = 0; y < scene.height; y++) {
        for (int x = 0; x < scene.width; x++) {
            const _4F& lims = scene._angle_limits[y*scene.width + x];
            Line ray(scene.cam.location, {tanf(lims.a), 1, tanf(lims.c)});

            // Fake algorithm for now
            const PF3D q1 = ray.point + 2*clip_end*ray.dir;
            const PF3D q2 = ray.point - 2*clip_end*ray.dir;
            //printf("%d %d %f %f\n", x, y, lims.a, lims.c);
            printf("%i %i  %f %f  %f %f %f  %f %f %f\n", x, y, lims.a, lims.c, q1(0), q1(1), q1(2), q2(0), q2(1), q2(2));

            bool inter = false;
            for (int i = 0; i < (int)scene.meshes.size(); i++) {
                if (inter)
                    break;

                const Mesh& mesh = scene.meshes[i];
                for (int j = 0; j < (int)mesh.faces.size(); j++) {
                    const Tri& tri = mesh.faces[j];
                    if (intersects(q1, q2, tri)) {
                        inter = true;
                        break;
                    }
                }
            }

            if (inter)
                img.set(x, y, 0, 255);
        }
    }
}


}  // namespace Quaternion
