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

.PHONY: release debug docs

release:
	mkdir -p ./build; \
	cd ./build; \
	cmake ../src -DCMAKE_BUILD_TYPE=Release; \
	make -j`nproc`


debug:
	mkdir -p ./build; \
	cd ./build; \
	cmake ../src -DCMAKE_BUILD_TYPE=Debug; \
	make -j`nproc`

docs:
	cd ./docs; \
	make html
