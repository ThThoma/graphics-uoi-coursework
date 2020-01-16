/*
* Derekas Panagiwths 4014
* Thoma Athanasios 2979
*/


#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "GManager.h"
#include "GCube.h"



struct BoardPosition{
	int i;
	int j;
};

// for mouse
BoardPosition click1, click2;
// for mouse
bool secondClick = false;


// for camera
float cameraX = 0.0f, cameraY = 0.0f;

// global pointer to the manager
GManager* manager;





void init() {

	//create the Game-Manager
	manager = new GManager();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL); 
	glEnable(GL_LIGHT0);

}

void gameMenu(int option){
	switch (option) {

	case 1:		//START GAME
		manager->startGame();
		break;

	case 0:		//EXIT
		exit(0);
		break;
	}
}

void specialKey(int key, int xx, int yy){

	switch (key) {
		case GLUT_KEY_UP:
			cameraY += 1;
			break;
		case GLUT_KEY_DOWN:
			cameraY -= 1;
			break;
		case GLUT_KEY_RIGHT:
			cameraX += 1;
			break;
		case GLUT_KEY_LEFT:
			cameraX -= 1;
			break;
	}
}

void normalKeys(unsigned char key, int xx, int yy) {

	switch (key) {
		case 27:
			//escape
			exit(0);
			break;
	}
}



void initMenus(){

	glutCreateMenu(gameMenu);

	glutAddMenuEntry("Start Game", 1);
	glutAddMenuEntry("Exit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void drawRectangle(GLfloat width, GLfloat height, GLfloat length){

	glEnable(GL_NORMALIZE);
	glPushMatrix();

	glColor4f(0.59, 0.29, 0.0 , 1.0); //BROWN
	glScalef(width,height,length);
	glutSolidCube(1.0f);

	glPopMatrix();
	glDisable(GL_NORMALIZE);
}


void drawOutsideBox(){

	GLfloat w = 15*1.25*CUBE_SIZE + CUBE_SIZE/2;

	glPushMatrix();
	glTranslatef(1.75f, 1.75f, 0.0f);



	// draw base
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, - CUBE_SIZE * (3/2) );
	drawRectangle(w, w, CUBE_SIZE/2);
	glPopMatrix();

	// draw right side
	glPushMatrix();	
	glTranslatef(w/2, 0.0f, - CUBE_SIZE * (3/2) );
	drawRectangle(CUBE_SIZE/2, w, CUBE_SIZE*3);
	glPopMatrix();

	// draw left side
	glPushMatrix();
	glTranslatef(-w/2, 0.0f, - CUBE_SIZE * (3/2) );
	drawRectangle(CUBE_SIZE/2, w, CUBE_SIZE*3);
	glPopMatrix();

	// draw top side
	glPushMatrix();
	glTranslatef( 0.0f, w/2, - CUBE_SIZE * (3/2) );
	drawRectangle(w, CUBE_SIZE/2, CUBE_SIZE*3);
	glPopMatrix();

	// draw top side
	glPushMatrix();
	glTranslatef( 0.0f, -w/2, - CUBE_SIZE * (3/2) );
	drawRectangle(w, CUBE_SIZE/2, CUBE_SIZE*3);
	glPopMatrix();

	glPopMatrix();



}


void showBoard(){

	GCube** board= manager->getBoard();
	for (int i = 0; i < 15; i++){
		for (int j = 0; j < 15; j++) {
			glPushMatrix();

			float cen_x = CUBE_SIZE * 1.25 * i;
			float cen_y = CUBE_SIZE * 1.25 * j;

			glTranslatef(cen_x,cen_y,0.0f);

			board[i][j].showUpdatedCubeValue();

			glPopMatrix();
		}
	}
}

void idle() {
   glutPostRedisplay();   // call to show display() again
}

void showScore(){
	// print score on top-right of the screen
	char score[15];
	sprintf(score,"Score: %d",manager->getScore());
	manager->drawText( glutGet(GLUT_WINDOW_WIDTH) - 105 , glutGet(GLUT_WINDOW_HEIGHT) - 25 , score);
}

void showRemainingMoves(){
	// print the players remaining moves on top-right of screen
	char movesLeft[15];
	sprintf(movesLeft,"Moves: %d",manager->getPlayerMoves());
	manager->drawText( glutGet(GLUT_WINDOW_WIDTH) - 105 , glutGet(GLUT_WINDOW_HEIGHT) - 50 , movesLeft);
}


void display(){

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 0 0 0 black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/* CAMERA */
	gluLookAt (cameraX, cameraY, 5.0,
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0);


	glTranslatef(-1.75f, -1.75f, 0.0f);
	showBoard();

	drawOutsideBox();


	showScore();
	showRemainingMoves();

	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height){

	GLfloat aspect_ratio ;

	if (height == 0){
			height = 1; // To prevent divide by 0
	}

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspect_ratio = (GLfloat)width / (GLfloat)height;

	gluPerspective(45.0f, aspect_ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);


}

// this fuction is used in playerMoveOnClick() , 
// it returns the minimum distance of the ray to the center of the cube
double pointToLineDistance3D(double* a, double* b, double* point){
	
	double bminusa[3] , lineDirection[3], sizeofbminusa;
	for(int i = 0 ;i < 3 ;i++){
		bminusa[i] = b[i] - a[i];
	}
	sizeofbminusa = sqrt(bminusa[0] * bminusa[0] + bminusa[1] * bminusa[1] + bminusa[2] * bminusa[2]);
	for(int i = 0 ;i < 3 ;i++){
			lineDirection[i] = bminusa[i]/sizeofbminusa;
	}

	double pointDirection[3];
	for(int i = 0 ;i < 3 ;i++){
		pointDirection[i] = point[i] - a[i];
	}

	double dotProduct = 0.0;
	for (int i = 0; i < 3; i++) {
		dotProduct = dotProduct + pointDirection[i] * lineDirection[i];
	}

	double projection[3];
	for (int i = 0; i < 3; i++) {
		projection[i] = a[i] + (lineDirection[i] * dotProduct);
	}

	double shortDist[3];
	for(int i = 0 ;i < 3 ;i++){
		shortDist[i] = projection[i] - point[i];
	}

	double shortDistlen = sqrt(shortDist[0] * shortDist[0] + shortDist[1]*shortDist[1] + shortDist[2]*shortDist[2] );

	return shortDistlen;

}


BoardPosition playerMoveOnClick(int button, int state, int x,int y){

	GCube** board= manager->getBoard();
	BoardPosition click;

	// from screenspace (x,y) to clipspace (win_x , win_y)
	float win_x = x;
	float win_y = glutGet(GLUT_WINDOW_HEIGHT) -y;

	// store matrices
	GLdouble model[16];
	GLdouble proj[16];
	GLint view[16];

	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	glGetIntegerv(GL_VIEWPORT, view);

	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

		for (int i = 0; i < 15; i++){
			for (int j = 0; j < 15; j++) {

				float cen_x = CUBE_SIZE * 1.25 * i;
				float cen_y = CUBE_SIZE * 1.25 * j;

				double mouse_start[3];
				double mouse_end[3];
				double center[3] = {cen_x,cen_y,0};

				gluUnProject(win_x, win_y, 0, model, proj, view, &mouse_start[0], &mouse_start[1], &mouse_start[2]);

				gluUnProject(win_x, win_y, 1, model, proj, view, &mouse_end[0], &mouse_end[1], &mouse_end[2]);

				double d = pointToLineDistance3D(mouse_start,mouse_end,center);

				if( d < CUBE_SIZE/2 * sqrt(2)){
					// found it
					click.i = i;
					click.j = j;

					return click;
				}

			}
		}

	}
	// this will always give a 'cube' out of bounds
	click.i = 999;
	click.j = 999;
	return click;

}

void playerMove(int button, int state, int x,int y){

	bool ON = manager->gameIsOn();


	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ON){
		if (!secondClick){

			// handle 1st click

			secondClick = true;
			click1 = playerMoveOnClick(button,state,x,y);

		}else{

			//handle 2nd click
			click2 = playerMoveOnClick(button,state,x,y);
			manager->handlePlayerMove(click1.i,click1.j, click2.i,click2.j);
			secondClick = false;

		}

	}

}



int main(int argc, char **argv){



	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(600,600);
	glutInitWindowPosition(50,50);
	glutCreateWindow("VRAXAPSA III");


	init(); // enables and stuff


	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutReshapeFunc(reshape);

	//menu
	initMenus();

	//keyboard
	glutSpecialFunc(specialKey);
	glutKeyboardFunc(normalKeys);


	//mouse
	glutMouseFunc(playerMove);


	glutMainLoop();

	return 0;
}

