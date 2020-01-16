/*
* Derekas Panagiwths 4014
* Thoma Athanasios 2979
*/


#include "GCube.h"


GCube::GCube() {

	value = BLANK;
	// both of these will be set by the manager,
	//just set to 0 so compiler doesn't complain
	x = 0;
	y = 0;

}

void drawCube(int val){

	switch(val){
		case BLANK:
			//color to beige
			glColor4f(0.96f,0.84f,0.59f,1.0f);
			glutSolidCube(CUBE_SIZE);
			break;

		case ROCK:
			glColor4f(1.0f,1.0f,1.0f,1.0f);
			TextureLoader::drawTiltedSquare(ROCK);
			glutWireCube(CUBE_SIZE);
			break;

		case PAPER:
			glColor4f(1.0f,1.0f,1.0f,1.0f);
			TextureLoader::drawTiltedSquare(PAPER);
			glutWireCube(CUBE_SIZE);
			break;

		case SCISSORS:
			glColor4f(1.0f,1.0f,1.0f,1.0f);
			TextureLoader::drawTiltedSquare(SCISSORS);
			glutWireCube(CUBE_SIZE);
			break;

		case BLUE:
			glColor4f(0.0f,0.0f,0.85f,1.0f);
			glutSolidCube(CUBE_SIZE);
			break;

		case RED:
			glColor4f(0.85f,0.0f,0.0f,1.0f);
			glutSolidCube(CUBE_SIZE);
			break;

		case BOMB:
			glColor4f(1.0f,1.0f,0.0f,1.0f);
			TextureLoader::drawTiltedSquare(BOMB);
			glutWireCube(CUBE_SIZE);
	}
}

void GCube::setValue(int val){

	value = val;
	drawCube(value);
}


void GCube::showUpdatedCubeValue(){

	drawCube(value);

}


int GCube::getValue(){
	return value;
}








