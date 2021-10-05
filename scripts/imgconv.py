#
#  Quaternion
#  3D raytracer.
#  Copyright Patrick Huang 2021
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

import os
import struct
import argparse
import numpy as np
import cv2


def main():
    parser = argparse.ArgumentParser(description="Convert between .qif and another image format.")
    parser.add_argument("input", help="Input image path.")
    parser.add_argument("output", help="Output image path.")
    parser.add_argument("--be", help="Big endian (default false)", action="store_true")
    args = parser.parse_args()

    input_path = os.path.realpath(os.path.expanduser(args.input))
    output_path = os.path.realpath(os.path.expanduser(args.output))
    e = ">" if args.be else "<"

    with open(input_path, "rb") as fp:
        width, height = struct.unpack(f"{e}II", fp.read(8))
        img = np.empty((height, width, 3), dtype=np.uint8)

        for y in range(height):
            for x in range(width):
                for ch in range(2, -1, -1):  # BGR
                    byte = fp.read(1)[0]
                    img[y][x][ch] = byte

    cv2.imwrite(output_path, img)


main()
