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


_4F::_4F() {
    a = b = c = d = 0;
}

_4F::_4F(double a, double b, double c, double d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}


Line::Line() {
    point = {0, 0, 0};
    dir = {1, 0, 0};
}

Line::Line(PF3D point, PF3D dir) {
    this->point = point;
    this->dir = dir;
}


double hypot(const double dx, const double dy, const double dz) {
    return pow(dx*dx + dy*dy + dz*dz, 0.5);
}


namespace Random {
    double uniform(const double lower, const double upper) {
        const double num = ((double)rand())/1e9 + (double)rand();
        return lower + fmod(num, upper-lower);
    }
}


}  // namespace Quaternion
