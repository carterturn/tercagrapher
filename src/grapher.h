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

#include <vector>
#include <ctvector.h>
#include <muParser.h>

struct ctline{
	ctvector point1;
	ctvector point2;
};

class grapher{
public:
	grapher(std::string expr);

	virtual void process(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax)=0;
	
	virtual std::vector<ctvector> getVectors()=0;
	virtual void drawVectors()=0;

protected:
	std::vector<ctvector> points;

	std::string leftExpr;
	std::string rightExpr;
	mu::Parser leftParser;
	mu::Parser rightParser;

};
