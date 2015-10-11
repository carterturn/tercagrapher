#include "graphwindow.h"
#include <GL/gl.h>

#include "grapher2d.h"
#include "grapher3d.h"

using namespace std;

bool check3D(string equation){
	bool threed = false;
	for(int i = 0; i < equation.length(); i++){
		if(equation[i] == 'z') threed = true;
	}
	return threed;
}

void drawAxis(int x, int y, int z){
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0f, 0.0f, 0.0f);

		glBegin(GL_LINES);

		glVertex3i(-1*x, 0, 0);
		glVertex3i(x, 0, 0);
		glVertex3i(0, -1*y, 0);
		glVertex3i(0, y, 0);
		glVertex3i(0, 0, -1*z);
		glVertex3i(0, 0, z);

		glEnd();
}

graphwindow::graphwindow(string equation, string title, int xsize, int ysize) : window(title, xsize, ysize){
	glfwMakeContextCurrent(gwindow);
	glOrtho((-1*xsize)/2, xsize/2, (-1*ysize)/2, ysize/2, (-1*ysize)/2, ysize/2);

	if(check3D(equation)) grapheng = new grapher3d(equation);
	else grapheng = new grapher2d(equation);

	grapheng->process(-200, 200, -200, 200, -200, 200);
}

graphwindow::~graphwindow(){
	delete grapheng;
}

void graphwindow::draw(){
	initDraw();
	
	drawAxis(240, 240, 240);

	grapheng->drawVectors();

	finishDraw();
}
