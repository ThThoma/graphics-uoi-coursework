/*
* Derekas Panagiwths 4014
* Thoma Athanasios 2979
*/

#ifndef GMANAGER_H_
#define GMANAGER_H_

#include <stdlib.h>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "GCube.h"
#include "TextureLoader.h"


#define NOT_NEIGH 0
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define LINE 1
#define COLUMN 2

class GManager {
	public:
		GManager();

		int getScore();
		int getPlayerMoves();
		GCube** getBoard(); // show 15x15 board
		bool gameIsOn();

		void drawText(GLfloat x, GLfloat y, char* s);

		void randomizeBoard();

		void startGame();

		void explosion(int i1, int j1, int i2, int j2, int i3, int j3, int lineOrCol);

		void handlePlayerMove(int i1, int j1, int i2, int j2);

		bool gameIsFinished();

		bool threeSame(int i1, int j1, int i2, int j2, int i3, int j3);

		int areNeighbors(int i1, int j1, int i2, int j2);

		void swapCubeValue(int i1, int j1, int i2, int j2);

		void findAndDestroyNeighborsD1(int i1, int j1, int i2, int j2, int i3, int j3,int value, int lineOrCol);
		void findAndDestroyNeighborsD2_3(int i1, int j1, int i2, int j2, int i3, int j3,int value, int lineOrCol);

		void d1NeighborDestroy(int i, int j, int value);
	private:

		int score;
		int playerMovesLeft;
		GCube** board;
		bool gameOn;




};

#endif /* GMANAGER_H_ */
