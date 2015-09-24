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

#include "grapher3d.h"
#include <cmath>
#include <iostream>

using namespace std;

void grapher3d::process(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax){
	if(leftExpr == "x") processX(xmin, xmax, ymin, ymax, zmin, zmax);
	else if(rightExpr == "x"){
		rightParser = leftParser;
		processX(xmin, xmax, ymin, ymax, zmin, zmax);
	}
	else if(leftExpr == "y") processY(xmin, xmax, ymin, ymax, zmin, zmax);
	else if(rightExpr == "y"){
		rightParser = leftParser;
		processY(xmin, xmax, ymin, ymax, zmin, zmax);
	}
	else if(leftExpr == "z") processZ(xmin, xmax, ymin, ymax, zmin, zmax);
	else if(rightExpr == "z"){
		rightParser = leftParser;
		processZ(xmin, xmax, ymin, ymax, zmin, zmax);
	}
	else processAll(xmin, xmax, ymin, ymax, zmin, zmax);
}

void grapher3d::processX(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax){
	double yvar;
	double zvar;

	rightParser.DefineVar("y", &yvar);
	rightParser.DefineVar("z", &zvar);

	for(yvar = ymin; yvar < ymax; yvar += 0.15){
		for(zvar = zmin; zvar < zmax; zvar += 0.15){
			double xout = rightParser.Eval();

			if(xout > xmin && xout < xmax){
				points.push_back(ctvector(xout, yvar, zvar));
			}
		}
	}
}

void grapher3d::processY(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax){
	double xvar;
	double zvar;

	rightParser.DefineVar("x", &xvar);
	rightParser.DefineVar("z", &zvar);

	for(xvar = xmin; xvar < xmax; xvar += 0.15){
		for(zvar = zmin; zvar < zmax; zvar += 0.15){
			double yout = rightParser.Eval();

			if(yout > ymin && yout < ymax){
				points.push_back(ctvector(xvar, yout, zvar));
			}
		}
	}
}

void grapher3d::processZ(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax){
	double xvar;
	double yvar;

	rightParser.DefineVar("x", &xvar);
	rightParser.DefineVar("y", &yvar);

	for(xvar = xmin; xvar < xmax; xvar += 0.15){
		for(yvar = ymin; yvar < ymax; yvar += 0.15){
			double zout = rightParser.Eval();

			if(zout > zmin && zout < zmax){
				points.push_back(ctvector(xvar, yvar, zout));
			}
		}
	}
}

void grapher3d::processAll(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax){
	double xvar;
	double yvar;
	double zvar;

	rightParser.DefineVar("x", &xvar);
	rightParser.DefineVar("y", &yvar);
	rightParser.DefineVar("z", &zvar);

	leftParser.DefineVar("x", &xvar);
	leftParser.DefineVar("y", &yvar);
	leftParser.DefineVar("z", &zvar);

	for(int xiter = xmin; xiter < xmax; xiter += 32){
		for(int yiter = ymin; yiter < ymax; yiter += 32){
			for(int ziter = zmin; ziter < zmax; ziter += 32){
				xvar = xiter;
				yvar = yiter;
				zvar = ziter;

				if(abs(leftParser.Eval() - rightParser.Eval()) <= abs(rightParser.Eval()) || (abs(leftParser.Eval() - rightParser.Eval()) <= abs(leftParser.Eval()))){
					for(xvar = xiter - 16; xvar < xiter + 16; xvar += 0.5){
						for(yvar = yiter - 16; yvar < yiter + 16; yvar += 0.5){
							for(zvar = ziter - 16; zvar < ziter + 16; zvar += 0.5){
								if(abs(leftParser.Eval() - rightParser.Eval()) < 1){
									points.push_back(ctvector(xvar, yvar, zvar));
								}
							}
						}
					}
				}
			}
		}
	}
}

vector<ctvector> grapher3d::getVectors(){
	return points;
}

void grapher3d::drawVectors(){}
