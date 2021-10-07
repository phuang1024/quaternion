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

#pragma once

#include <string>
#include <vector>

#include <Eigen/Dense>


typedef  unsigned char  UCH;
typedef  unsigned int   UINT;

typedef  Eigen::Vector3d           PF3D;
typedef  Eigen::Matrix<UCH, 3, 1>  RGB;


namespace Quaternion {


// Convenience structs, typedefs, and functions.
// Implemntations in utils.cpp

/**
 * Four doubles.
 */
struct _4F {
    _4F();
    _4F(double a, double b, double c, double d);

    double a, b, c, d;
};

/**
 * 3D line represented with point and direction vector.
 */
struct Line {
    Line();
    Line(PF3D point, PF3D dir);

    PF3D point;
    PF3D dir;
};

/**
 * hypot() but in 3d.
 */
double hypot(const double dx, const double dy, const double dz);


// Image processing
// Implementations in image.cpp

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
     * Set all channels and pixels to 0.
     */
    void clear();

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


// API
// Implementations in api.cpp

/**
 * Triangle in 3D space, defined by three points.
 */
struct Tri {
    /**
     * All three points are (0, 0, 0)
     */
    Tri();

    Tri(PF3D p1, PF3D p2, PF3D p3);

    Tri(const Tri& other);

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
 * Transformations are applied in this order:
 * - rotation (TODO)
 * - scale
 * - location
 */
struct Mesh {
    /**
     * No faces, location = (0, 0, 0), scale = (1, 1, 1).
     */
    Mesh();

    Mesh(const Mesh& other);

    std::vector<Tri> faces;
    RGB color;

    PF3D location;
    PF3D scale;
};

/**
 * Perspective camera.
 * FOV is radians of the X direction.
 */
struct Camera {
    Camera();

    PF3D location;
    double fov;
};

/**
 * Uniform spherical light object.
 */
struct Light {
    Light();

    /**
     * Initialize with power.
     */
    Light(double power);

    /**
     * Initialize with location.
     */
    Light(PF3D location);

    PF3D location;
    double power;
};

/**
 * Groups together meshes and a camera.
 * Pass this to the render function.
 */
struct Scene {
    Scene();

    /**
     * Output dimensions in pixels.
     */
    int width, height;

    /**
     * Min and max distance for rendering.
     */
    double clip_start, clip_end;

    std::vector<Mesh> meshes;
    std::vector<Light> lights;
    Camera cam;
    RGB background;

    // Set by preprocessor

    /**
     * Size = width * height.
     * Entry i has values (x_min, x_max, y_min, y_max) (maps to (a, b, c, d) for _4F),
     * specifying angle (radian) limits to fit in the pixel (x = i%width, y = i/width).
     * Angle (0, 0) = directly forward from camera.
     */
    std::vector<_4F> _angle_limits;

    /**
     * Vector of pointers to each face.
     * Easier indexing of faces.
     */
    std::vector<Tri*> _fptrs;
};

/**
 * Create a cube mesh with side length size at the origin.
 */
Mesh primitive_cube(double size);


// Preprocessing
// Implementations in preprocess.cpp

/**
 * Compute normal of a triangle and store in a vector.
 */
void get_normal(PF3D& dest, Tri& tri);

/**
 * Preprocess the mesh (modifies it in place).
 * This will be called automatically. No need to call manually.
 * - Apply transformations to each face.
 * - Calculate the normal of each face and store in Tri.normal
 */
void preprocess(Scene& scene);

bool intersects(const PF3D, const PF3D, const Tri&);


// Rendering
// Implementations in render.cpp

/**
 * Groups together settings for rendering.
 */
struct RenderSettings {
    RenderSettings();

    UINT samples;
    UINT max_bounces;
};

/**
 * Render the scene and store in img.
 * Throws:
 * - 1 if dimensions do not match.
 */
void render(Scene& scene, Image& img, RenderSettings& settings);


}  // namespace Quaternion
