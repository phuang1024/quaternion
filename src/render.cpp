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


RenderSettings::RenderSettings() {
    samples = 16;
    max_bounces = 8;
}


/**
 * From https://stackoverflow.com/questions/42740765
 * Calculates volume of tetrahedron.
 */
double signed_volume(PF3D a, PF3D b, PF3D c, PF3D d) {
    return (b-a).cross(c-a).dot(d-a) / 6.0;
}


/**
 * From https://stackoverflow.com/questions/42740765
 * Checks if line segment through p1 and p2 intersects tri.
 */
bool intersects(const PF3D q1, const PF3D q2, const Tri& tri) {
    const PF3D& p1 = tri.p1, p2 = tri.p2, p3 = tri.p3;
    const bool v1 = sign(signed_volume(q1, p1, p2, p3));
    const bool v2 = sign(signed_volume(q2, p1, p2, p3));
    const bool v3 = sign(signed_volume(q1, q2, p1, p2));
    const bool v4 = sign(signed_volume(q1, q2, p2, p3));
    const bool v5 = sign(signed_volume(q1, q2, p3, p1));
    return (v1 != v2) && (v3 == v4) && (v4 == v5);
}

/**
 * From https://stackoverflow.com/questions/42740765
 * Finds intersection of line segment and tri and stores in @param dest.
 */
void intersect_pt(PF3D& dest, const PF3D q1, const PF3D q2, const Tri& tri) {
    const PF3D& p1 = tri.p1, p2 = tri.p2, p3 = tri.p3;
    const PF3D n = (p2-p1).cross(p3-p1);
    const double t = -(q1-p1).dot(n) / (q2-q1).dot(n);
    dest = q1 + t * (q2-q1);
}


/**
 * Closest distance between a line and a point.
 * From https://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
 */
double closest_dist(Line& line, PF3D point) {
    const PF3D p2 = line.point + line.dir;
    const double t = -(line.point-point).dot(p2-line.point) / pow((p2-line.point).norm(), 2);
    const PF3D line_pt = line.point + t*line.dir;
    return (line_pt-point).norm();
}


void render_px(Scene& scene, Image& img, RenderSettings& settings, int x, int y) {
    const double clip_end = scene.clip_end;
    const PF3D cam_loc = scene.cam.location;

    bool intersect = false;  // whether there was any intersect
    double total_dist = 0;   // total distance of closest face from all samples
    for (int s = 0; s < (int)settings.samples; s++) {
        const _4F& lims = scene._angle_limits[y*scene.width + x];
        const double x_angle = Random::uniform(lims.a, lims.b);
        const double y_angle = Random::uniform(lims.c, lims.d);
        Line ray(cam_loc, {tanf(x_angle), 1, tanf(y_angle)});

        const PF3D q1 = ray.point;
        const PF3D q2 = ray.point + 2*clip_end*ray.dir;

        Tri* face_ind = nullptr;
        double min_dist = clip_end;
        for (int i = 0; i < (int)scene._fptrs.size(); i++) {
            Tri& tri = *scene._fptrs[i];
            if (intersects(q1, q2, tri)) {
                PF3D inter;
                intersect_pt(inter, q1, q2, tri);
                const double dist = hypot(inter(0)-cam_loc(0), inter(1)-cam_loc(1), inter(2)-cam_loc(2));
                if (dist < min_dist) {
                    min_dist = dist;
                    face_ind = &tri;
                }
            }
        }

        if (face_ind != nullptr) {
            intersect = true;
            total_dist += min_dist;
        }
    }

    if (intersect) {
        const UCH v = 255.0 / total_dist * settings.samples;
        img.set(x, y, 0, v);
        img.set(x, y, 1, v);
        img.set(x, y, 2, v);
    }
}

void render(Scene& scene, Image& img, RenderSettings& settings) {
    if (img.width != scene.width || img.height != scene.height) {
        std::cerr << "Quaternion::render: Dimensions must match." << std::endl;
        throw 1;
    }

    preprocess(scene);

    for (int y = 0; y < scene.height; y++) {
        for (int x = 0; x < scene.width; x++) {
            render_px(scene, img, settings, x, y);
        }
    }
}


}  // namespace Quaternion
