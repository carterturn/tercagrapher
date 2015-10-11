#include "equwindow.h"
#include <GL/gl.h>

#include "grapher2d.h"
#include "grapher3d.h"

using namespace std;

equwindow::equwindow(string title, int xsize, int ysize) : window(title, xsize, ysize){
}

equwindow::~equwindow(){
}

void equwindow::draw(){
	initDraw();
	finishDraw();
}

vector<string> equwindow::getEquations(){
	return equations;
}
