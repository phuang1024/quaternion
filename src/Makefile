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

CXX = g++
CXXFLAGS = -Wall -O3 -fPIC
CXXFILES = image.o mesh.o

.PHONY: exe static dynamic clean

# Build executable for testing.
exe: static
	$(CXX) $(CXXFLAGS) main.cpp -L. -lquaternion

static: $(CXXFILES)
	$(CXX) -shared $(CXXFILES) -o libquaternion.a

dynamic: $(CXXFILES)
	$(CXX) -shared -Wl,-soname,libquaternion.so $(CXXFILES) -o libquaternion.so

clean:
	rm *.o
