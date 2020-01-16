/*
* Derekas Panagiwths 4014
* Thoma Athanasios 2979
*/


#ifndef GCUBE_H_
#define GCUBE_H_

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <cstdio>
#include "TextureLoader.h"




#define BLANK 0
#define ROCK 1
#define PAPER 2
#define SCISSORS 3
#define BLUE 4
#define RED 5
#define BOMB 6

#define CUBE_SIZE 0.2f


class GCube {
	public:
		GCube();
		int getValue();
		void setValue(int val);
		void showUpdatedCubeValue();


	private:
		GLfloat x;
		GLfloat y;
		int value;

};

#endif /* GCUBE_H_ */
