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

#include <string>
#include <vector>

#include <Eigen/Dense>


namespace Quaternion {


// Useful stuff
typedef  unsigned char  UCH;

typedef  Eigen::Vector3f  PF3D;


// Image processing

/**
 * Image with three channels.
 */
struct Image {
    /**
     * Deallocates memory.
     */
    ~Image();

    /**
     * Initialize with width and height (pixels).
     */
    Image(int width, int height);

    /**
     * Index of byte to satisfy arguments.
     */
    int mempos(int x, int y, int channel);

    /**
     * Get value at (x, y) and channel.
     * Channel 0 is R, 1 is G, 2 is B.
     */
    UCH get(int x, int y, int channel);

    /**
     * Set value at (x, y) and channel.
     * Channel 0 is R, 1 is G, 2 is B.
     */
    void set(int x, int y, int channel, UCH value);

    /**
     * Write image as unstandardized binary format.
     * Recommended extension: .qif (quaternion image format).
     * See docs for more info.
     */
    void write(std::string path);

    /**
     * Size is width * height * 3
     * Three bytes form a pixel.
     * "width" pixels together form one line on the image.
     * "height" rows form the whole image.
     */
    UCH* mem;

    /**
     * You can change these, but you shouldn't.
     */
    int width, height;
};


// Mesh API

/**
 * Triangle in 3D space, defined by three points.
 */
struct Tri {
    /**
     * All three points are (0, 0, 0)
     */
    Tri();

    Tri(PF3D& p1, PF3D& p2, PF3D& p3);

    Tri(Tri& other);

    PF3D p1, p2, p3;

    /**
     * MAY NOT be correct. Set by the preprocessor.
     * Vector representing the direction of the face.
     * Also consider -1 * normal as the correct normal.
     */
    PF3D normal;
};

/**
 * Mesh is a collection of triangles along with transformations.
 */
struct Mesh {
    /**
     * No faces, location = (0, 0, 0), scale = (1, 1, 1).
     */
    Mesh();

    Mesh(Mesh& other);

    std::vector<Tri> faces;

    PF3D location;
    PF3D scale;
};

/**
 * Compute normal of a triangle and store in a vector.
 */
void get_normal(PF3D& dest, Tri& tri);


}  // namespace Quaternion
