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

#include "grapher2d.h"
#include <cmath>
#include <iostream>

using namespace std;

void grapher2d::process(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax){
	process(xmin, xmax, ymin, ymax);
}

// This function just decides how to process data
void grapher2d::process(int xmin, int xmax, int ymin, int ymax){
	if(leftExpr == "x") processX(xmin, xmax, ymin, ymax);
	else if(rightExpr == "x"){
		rightParser = leftParser;
		processX(xmin, xmax, ymin, ymax);
	}
	else if(leftExpr == "y") processY(xmin, xmax, ymin, ymax);
	else if(rightExpr == "y"){
		rightParser = leftParser;
		processY(xmin, xmax, ymin, ymax);
	}
	else processAll(xmin, xmax, ymin, ymax);
}

// This function is designed to process functions of the form x = ...
void grapher2d::processX(int xmin, int xmax, int ymin, int ymax){
	double yvar;

	rightParser.DefineVar("y", &yvar);
	
	for(yvar = ymin; yvar < ymax; yvar += 0.05){
		double xout = rightParser.Eval();
		
		if(xout > xmin && xout < xmax){
			points.push_back(ctvector(xout, yvar, 0.0));
		}
	}
}

// This function is designed to process functions of the form y = ...
void grapher2d::processY(int xmin, int xmax, int ymin, int ymax){
	double xvar;

	rightParser.DefineVar("x", &xvar);
	
	for(xvar = xmin; xvar < xmax; xvar += 0.05){
		double yout = rightParser.Eval();
		
		if(yout > ymin && yout < ymax){
			points.push_back(ctvector(xvar, yout, 0.0));
		}
	}
}

// This function is designed to process everything else (but it is slower)
void grapher2d::processAll(int xmin, int xmax, int ymin, int ymax){
	double xvar;
	double yvar;

	leftParser.DefineVar("x", &xvar);
	leftParser.DefineVar("y", &yvar);
	rightParser.DefineVar("x", &xvar);
	rightParser.DefineVar("y", &yvar);
	
	for(int xiter = xmin; xiter < xmax; xiter += 32){
		for(int yiter = ymin; yiter < ymax; yiter += 32){
			xvar = xiter;
			yvar = yiter;

			if(abs(leftParser.Eval() - rightParser.Eval()) <= abs(rightParser.Eval()) || (abs(leftParser.Eval() - rightParser.Eval()) <= abs(leftParser.Eval()))){
				for(xvar = xiter - 16; xvar < xiter + 16; xvar += 0.05){
					for(yvar = yiter - 16; yvar < yiter + 16; yvar += 0.05){
						if(abs(leftParser.Eval() - rightParser.Eval()) < 0.05){
							points.push_back(ctvector(xvar, yvar, 0.0));
						}
					}
				}
			}
		}
	}
}

// This function just returns a vector of vectors
vector<ctvector> grapher2d::getVectors(){
	return points;
}

void grapher2d::drawVectors(){

}
