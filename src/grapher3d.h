/*
  Copyright 2015 Carter Turnbaugh

  This file is part of Terca Grapher.

  Terca Grapher is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Terca Grapher is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Terca Grapher.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "grapher.h"

class grapher3d : public grapher{
public:
	grapher3d(std::string expr) : grapher(expr){}

	void process(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax);

	std::vector<ctvector> getVectors();
	void drawVectors();

private:
	void processX(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax);
	void processY(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax);
	void processZ(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax);
	void processAll(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax);

};
