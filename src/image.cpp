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

#include <fstream>

#include "quaternion.hpp"


namespace Quaternion {


Image::~Image() {
    delete[] mem;
}

Image::Image(int width, int height) {
    this->width = width;
    this->height = height;
    mem = new UCH[width*height*3];
}

int Image::mempos(int x, int y, int channel) {
    return y*height*3 + x*3 + channel;
}

void Image::clear() {
    memset(mem, 0, 3 * width * height);
}

UCH Image::get(int x, int y, int channel) {
    return mem[mempos(x, y, channel)];
}

void Image::set(int x, int y, int channel, UCH value) {
    mem[mempos(x, y, channel)] = value;
}

void Image::write(std::string path) {
    std::ofstream fp(path);

    fp.write((char*)&width, sizeof(width));
    fp.write((char*)&height, sizeof(height));
    fp.write((char*)mem, width*height*3);
}


}
