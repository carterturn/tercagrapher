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

#include <iostream>
#include <unistd.h>

#include <chrono>

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <futuregl/futuregl.h>

#include <muParser.h>

#include "grapher3d.h"
#include "grapher2d.h"

using namespace std;

futuregl * gui;
grapher * grapheng;

void initGUI(){
	// TODO: actually initialize Future GUI
}

int main(int argc, char* argv[]){

	if(argc < 2){
		cout << "Usage: ./grapher [equation]\n";
		return -1;
	}

	gui = new futuregl(3, 2);

	string equation = argv[1];
	bool threed = false;
	for(int i = 0; i < equation.length(); i++){
		if(equation[i] == 'z') threed = true;
	}

	if(threed) grapheng = new grapher3d(argv[1]);
	else grapheng = new grapher2d(argv[1]);

	glfwInit();
	GLFWwindow * graphwindow = glfwCreateWindow(640, 480, "Terca Grapher", NULL, NULL);
	initGUI();

	if(!graphwindow){
		cout << "Graphwindow Error\n";
		return -1;
	}

	glfwMakeContextCurrent(graphwindow);

	glOrtho(-320, 320, -240, 240, -240, 240);

	gui->draw();

	chrono::high_resolution_clock::time_point before = chrono::high_resolution_clock::now();
	
	grapheng->process(-10, 10, -10, 10, -10, 10);

	chrono::high_resolution_clock::time_point after = chrono::high_resolution_clock::now();

	cout << chrono::duration_cast<chrono::duration<double>>(after - before).count() << "\n";
	
	vector<ctvector> points = grapheng->getVectors();

	while(true){
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0f, 0.0f, 0.0f);

		glBegin(GL_LINES);

		glVertex3i(-240, 0, 0);
		glVertex3i(240, 0, 0);
		glVertex3i(0, -240, 0);
		glVertex3i(0, 240, 0);
		glVertex3i(0, 0, -240);
		glVertex3i(0, 0, 240);

		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		
		before = chrono::high_resolution_clock::now();
		
		for(int i = 0; i < points.size(); i++){
			glBegin(GL_POINTS);

			glColor3f(0.0f, 1.0f, ((float) points[i].z) / 10.0f);

			glVertex3i(points[i].x, points[i].y, points[i].z);

			glEnd();

//			points[i].rotate(0.0f, 0.1f, 0.0f);

		}

		after = chrono::high_resolution_clock::now();

		cout << chrono::duration_cast<chrono::duration<double>>(after - before).count() << "\n";

		glfwSwapBuffers(graphwindow);
		glfwPollEvents();

		usleep(1000000);
		
	}

	glfwTerminate();
	
	delete gui;
	delete grapheng;
}
