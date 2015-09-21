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

#include "grapher.h"

#include <algorithm>

using namespace std;

bool isSpace(char c){
	return (c == ' ') || (c == '\t');
}

grapher::grapher(string expr){

	leftExpr = expr.substr(0, expr.find_first_of("="));
	leftExpr.erase(remove_if(leftExpr.begin(), leftExpr.end(), isSpace), leftExpr.end());
	rightExpr = expr.substr(expr.find_first_of("=")+1, expr.length());
	rightExpr.erase(remove_if(rightExpr.begin(), rightExpr.end(), isSpace), rightExpr.end());

	leftParser.SetExpr(leftExpr);
	rightParser.SetExpr(rightExpr);
}
